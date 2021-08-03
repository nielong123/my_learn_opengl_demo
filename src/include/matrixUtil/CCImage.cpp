/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

//#define HAVE_BOOLEAN



#include <ctype.h>
#include <setjmp.h>
#include <GLES2/gl2.h>
#include "CCImage.h"
#include "BaseLog.h"

extern "C"
{
#include "jpeg/jpeglib.h"
#include "jpeg/jmorecfg.h"
#include "jpeg/jerror.h"
#include "jpeg/jinclude.h"
#include "png/png.h"
}

#define CC_GL_ATC_RGB_AMD                                          0x8C92
#define CC_GL_ATC_RGBA_EXPLICIT_ALPHA_AMD                          0x8C93
#define CC_GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD                      0x87EE

// 由Image 类进行内存管理
#define AUTO_ALLOC_MEMORY

//libjpg用的是gdal中编的，用的是6.2版本，没有jpeg_mem_src方法（9.0），特增加
//begin
static void init_source (j_decompress_ptr cinfo) {}
static boolean fill_input_buffer (j_decompress_ptr cinfo)
{
    ERREXIT(cinfo, JERR_INPUT_EMPTY);
return TRUE;
}
static void skip_input_data (j_decompress_ptr cinfo, long num_bytes)
{
    struct jpeg_source_mgr* src = (struct jpeg_source_mgr*) cinfo->src;

    if (num_bytes > 0) {
        src->next_input_byte += (size_t) num_bytes;
        src->bytes_in_buffer -= (size_t) num_bytes;
    }
}
static void term_source (j_decompress_ptr cinfo) {}
static void jpeg_mem_src (j_decompress_ptr cinfo, void* buffer, long nbytes)
{
    struct jpeg_source_mgr* src;

    if (cinfo->src == NULL) {   /* first time for this JPEG object? */
        cinfo->src = (struct jpeg_source_mgr *)
            (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
            SIZEOF(struct jpeg_source_mgr));
    }

    src = (struct jpeg_source_mgr*) cinfo->src;
    src->init_source = init_source;
    src->fill_input_buffer = fill_input_buffer;
    src->skip_input_data = skip_input_data;
    src->resync_to_restart = jpeg_resync_to_restart; /* use default method */
    src->term_source = term_source;
    src->bytes_in_buffer = nbytes;
    src->next_input_byte = (JOCTET*)buffer;
}
//end

namespace
{
    typedef struct
    {
        const unsigned char * data;
        ssize_t size;
        int offset;
    }tImageSource;

    static void pngReadCallback(png_structp png_ptr, png_bytep data, png_size_t length)
    {
        tImageSource* isource = (tImageSource*)png_get_io_ptr(png_ptr);

        if((int)(isource->offset + length) <= isource->size)
        {
            memcpy(data, isource->data+isource->offset, length);
            isource->offset += length;
        }
        else
        {
            png_error(png_ptr, "pngReaderCallback failed");
        }
    }
}

Image::Image()
: _data(NULL)
, _dataLen(0)
, _width(0)
, _height(0)
{

}

Image::~Image()
{
    freeData();
}

Data Image::getDataFromFile(CKQString filename, bool forString)
{
    if (filename.IsEmpty())
    {
        return Data::Null;
    }

    Data ret;
    unsigned char* buffer = NULL;
    size_t size = 0;
    size_t readsize;
    const char* mode = NULL;
    if (forString)
        mode = "rt";
    else
        mode = "rb";

    do
    {
        // Read the file from hardware
        FILE *fp = fopen((const char*)filename, mode);
        if(fp==NULL)
            break;

        fseek(fp,0,SEEK_END);
        size = ftell(fp);
        fseek(fp,0,SEEK_SET);

        if (forString)
        {
            buffer = (unsigned char*)malloc(sizeof(unsigned char) * (size + 1));
            buffer[size] = '\0';
        }
        else
        {
            buffer = (unsigned char*)malloc(sizeof(unsigned char) * size);
        }

        readsize = fread(buffer, sizeof(unsigned char), size, fp);
        fclose(fp);

        if (forString && readsize < size)
        {
            buffer[readsize] = '\0';
        }
    } while (0);

    if (NULL == buffer || 0 == readsize)
    {
        std::string msg = "Get data from file(";
        msg.append(filename).append(") failed!");
        LOGD("%s",msg.c_str());
    }
    else
    {
        ret.fastSet(buffer, readsize);
    }

    return ret;
}

bool Image::initWithImageFile(CKQString fullpath)
{
    bool ret = false;
    _filePath = fullpath;

    Data data = getDataFromFile(fullpath,false);

    if (!data.isNull())
    {
        ret = initWithImageData(data.getBytes(), data.getSize());
    }

    return ret;
}

bool Image::initWithImageData(const unsigned char * data, size_t dataLen)
{
    bool ret = false;

    do
    {
        if(data==NULL || dataLen <= 0)
            break;

        unsigned char* unpackedData = NULL;
        size_t unpackedLen = 0;

        //detecgt and unzip the compress file
        // if (ZipUtils::isCCZBuffer(data, dataLen))
        // {
        //     unpackedLen = ZipUtils::inflateCCZBuffer(data, dataLen, &unpackedData);
        // }
        // else if (ZipUtils::isGZipBuffer(data, dataLen))
        // {
        //     unpackedLen = ZipUtils::inflateMemory(const_cast<unsigned char*>(data), dataLen, &unpackedData);
        // }
        // else
        // {
            unpackedData = const_cast<unsigned char*>(data);
            unpackedLen = dataLen;
        //}

        //_data=unpackedData;
        //ret = initWithJpgData(unpackedData, unpackedLen);

        Format _fileType = detectFormat(unpackedData, unpackedLen);
        // LOGD_LAYER("图片类型：%d", (int)_fileType);
        switch (_fileType)
        {
        case PNG:
            ret = initWithPngData(unpackedData, unpackedLen);
            break;
        case JPG:
            ret = initWithJpgData(unpackedData, unpackedLen);
            break;
        // case Format::TIFF:
        //     ret = initWithTiffData(unpackedData, unpackedLen);
        //     break;
        // case Format::WEBP:
        //     ret = initWithWebpData(unpackedData, unpackedLen);
        //     break;
        // case Format::PVR:
        //     ret = initWithPVRData(unpackedData, unpackedLen);
        //     break;
        // case Format::ETC:
        //     ret = initWithETCData(unpackedData, unpackedLen);
        //     break;
        // case Format::S3TC:
        //     ret = initWithS3TCData(unpackedData, unpackedLen);
        //     break;
        // case Format::ATITC:
        //     ret = initWithATITCData(unpackedData, unpackedLen);
        //     break;
        default:
            {
                LOGD_S("Unkown type!");
                ret = false;
                //     // load and detect image format
                //     tImageTGA* tgaData = tgaLoadBuffer(unpackedData, unpackedLen);
                //
                //     if (tgaData != NULL && tgaData->status == TGA_OK)
                //     {
                //         ret = initWithTGAData(tgaData);
                //     }
                //     else
                //     {
                //         CCAssert(false, "unsupport image format!");
                //     }
                //
                //     free(tgaData);
                break;
            }
        }

        if(unpackedData != data)
        {
            free(unpackedData);
        }
    } while (0);

    return ret;
}

Format Image::detectFormat(const unsigned char * data, ssize_t dataLen)
{
    if (isPng(data, dataLen))
    {
        return PNG;
    }
    else if (isJpg(data, dataLen))
    {
        return JPG;
    }
    //    else if (isTiff(data, dataLen))
    //    {
    //        return Format::TIFF;
    //    }
    //    else if (isWebp(data, dataLen))
    //    {
    //        return Format::WEBP;
    //    }
    //    else if (isPvr(data, dataLen))
    //    {
    //        return Format::PVR;
    //    }
    //    else if (isEtc(data, dataLen))
    //    {
    //        return Format::ETC;
    //    }
    //    else if (isS3TC(data, dataLen))
    //    {
    //        return Format::S3TC;
    //    }
    //    else if (isATITC(data, dataLen))
    //    {
    //        return Format::ATITC;
    //    }
    else
    {
        return UNKOWN;
    }
}

bool Image::isJpg(const unsigned char * data, size_t dataLen)
{
    if (dataLen <= 4)
    {
        return false;
    }

    static const unsigned char JPG_SOI[] = {0xFF, 0xD8};

    return memcmp(data, JPG_SOI, 2) == 0;
}

bool Image::isPng(const unsigned char * data, size_t dataLen)
{
    if (dataLen <= 8)
    {
        return false;
    }

    static const unsigned char PNG_SIGNATURE[] = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a};

    return memcmp(PNG_SIGNATURE, data, sizeof(PNG_SIGNATURE)) == 0;
}

bool Image::expandImageData(int newsize) {
    if (newsize > _dataLen) {
        unsigned char* newData = NULL;
        if (NULL == _data) {
            // 初次分配内存
            newData = static_cast<unsigned char*>(malloc(newsize * sizeof(unsigned char)));
            if (NULL == newData) {
                LOGD("Image: expandImageData alloc failed!");
                return false;
            }
        } else {
            // 重复利用
            unsigned char* backAddr = _data;
            newData = static_cast<unsigned char*>(realloc(_data, newsize * sizeof(unsigned char)));
            if (NULL == newData) {
                LOGD("Image: expandImageData realloc failed!");
                _data = backAddr;
                freeData();

                // 再分配一次
                newData = static_cast<unsigned char*>(malloc(newsize * sizeof(unsigned char)));
                if (NULL == newData) {
                    LOGD("Image: expandImageData alloc failed!");
                    return false;
                }
            }
            backAddr = NULL;
        }

        _data = newData;
        _dataLen = newsize;
    }

    // 新的大小小于等于上次的, 则可以重复利用, 不需要再进行申请
    memset(_data, 0, _dataLen);

    return (true);
}

namespace
{
/*
 * ERROR HANDLING:
 *
 * The JPEG library's standard error handler (jerror.c) is divided into
 * several "methods" which you can override individually.  This lets you
 * adjust the behavior without duplicating a lot of code, which you might
 * have to update with each future release.
 *
 * We override the "error_exit" method so that control is returned to the
 * library's caller when a fatal error occurs, rather than calling exit()
 * as the standard error_exit method does.
 *
 * We use C's setjmp/longjmp facility to return control.  This means that the
 * routine which calls the JPEG library must first execute a setjmp() call to
 * establish the return point.  We want the replacement error_exit to do a
 * longjmp().  But we need to make the setjmp buffer accessible to the
 * error_exit routine.  To do this, we make a private extension of the
 * standard JPEG error handler object.  (If we were using C++, we'd say we
 * were making a subclass of the regular error handler.)
 *
 * Here's the extended error handler struct:
 */
    struct MyErrorMgr
    {
        struct jpeg_error_mgr pub;  /* "public" fields */
        jmp_buf setjmp_buffer;  /* for return to caller */
    };

    typedef struct MyErrorMgr * MyErrorPtr;

    /*
     * Here's the routine that will replace the standard error_exit method:
     */

    METHODDEF(void)
    myErrorExit(j_common_ptr cinfo)
    {
        /* cinfo->err really points to a MyErrorMgr struct, so coerce pointer */
        MyErrorPtr myerr = (MyErrorPtr) cinfo->err;

        /* Always display the message. */
        /* We could postpone this until after returning, if we chose. */
        /* internal message function cann't show error message in some platforms, so we rewrite it here.
         * edit it if has version confilict.
         */
        //(*cinfo->err->output_message) (cinfo);
        char buffer[JMSG_LENGTH_MAX];
        (*cinfo->err->format_message) (cinfo, buffer);
        LOGD("jpeg error: %s", buffer);
        /* Return control to the setjmp point */
        longjmp(myerr->setjmp_buffer, 1);
    }
}

void Image::freeData()
{
    if(NULL != _data){
        free(_data);
        _data = NULL;

        _dataLen = 0;
    }
}

bool Image::initWithJpgData(const unsigned char * data, size_t dataLen)
{
    /* these are standard libjpeg structures for reading(decompression) */
    struct jpeg_decompress_struct cinfo;
    /* We use our private extension JPEG error handler.
     * Note that this struct must live as long as the main JPEG parameter
     * struct, to avoid dangling-pointer problems.
     */
    struct MyErrorMgr jerr;
    /* libjpeg data structure for storing one row, that is, scanline of an image */
    JSAMPROW row_pointer[1] = {0};
    unsigned long location = 0;
    unsigned int i = 0;

    bool bRet = false;
    do
    {
        /* We set up the normal JPEG error routines, then override error_exit. */
        cinfo.err = jpeg_std_error(&jerr.pub);
        jerr.pub.error_exit = myErrorExit;
        /* Establish the setjmp return context for MyErrorExit to use. */
        if (setjmp(jerr.setjmp_buffer)) {
            /* If we get here, the JPEG code has signaled an error.
             * We need to clean up the JPEG object, close the input file, and return.
             */
            jpeg_destroy_decompress(&cinfo);
            break;
        }

        /* setup decompression process and source, then read JPEG header */
        jpeg_create_decompress( &cinfo );

        jpeg_mem_src( &cinfo, const_cast<unsigned char*>(data), dataLen );

        /* reading the image header which contains image information */
#if (JPEG_LIB_VERSION >= 90)
        // libjpeg 0.9 adds stricter types.
        jpeg_read_header( &cinfo, TRUE );
#else
        jpeg_read_header( &cinfo, true );
#endif

        // we only support RGB or grayscale
        if (cinfo.jpeg_color_space == JCS_GRAYSCALE)
        {
            //_renderFormat = Texture2D::PixelFormat::I8;
        }else
        {
            cinfo.out_color_space = JCS_RGB;
            //_renderFormat = Texture2D::PixelFormat::RGB888;
            _renderFormat=GL_RGB;
        }

        /* Start decompression jpeg here */
        jpeg_start_decompress( &cinfo );

        /* init image info */
        _width  = cinfo.output_width;
        _height = cinfo.output_height;

        //_preMulti = false;
        row_pointer[0] = static_cast<unsigned char*>(malloc(cinfo.output_width*cinfo.output_components * sizeof(unsigned char)));
        if(row_pointer[0]==NULL)
            break;

#ifdef AUTO_ALLOC_MEMORY
        // TODO: 根据新的大小决定是否重新申请内存
        int newSize = cinfo.output_width*cinfo.output_height*cinfo.output_components;
        if (!expandImageData(newSize)) {
            break;
        }
#else
        _dataLen = cinfo.output_width*cinfo.output_height*cinfo.output_components;
        _data = static_cast<unsigned char*>(malloc(_dataLen * sizeof(unsigned char)));
#endif
        if(_data==NULL)
            break;

        /* now actually read the jpeg into the raw buffer */
        /* read one scan line at a time */
        while( cinfo.output_scanline < cinfo.output_height )
        {
            jpeg_read_scanlines( &cinfo, row_pointer, 1 );
            for( i=0; i<cinfo.output_width*cinfo.output_components;i++)
            {
                _data[location++] = row_pointer[0][i];
            }
        }

        /* When read image file with broken data, jpeg_finish_decompress() may cause error.
         * Besides, jpeg_destroy_decompress() shall deallocate and release all memory associated
         * with the decompression object.
         * So it doesn't need to call jpeg_finish_decompress().
         */
        //jpeg_finish_decompress( &cinfo );
        jpeg_destroy_decompress( &cinfo );
        /* wrap up decompression, destroy objects, free pointers and close open files */
        bRet = true;
    } while (0);

    if (row_pointer[0] != NULL)
    {
        free(row_pointer[0]);
    };

    return bRet;
}

bool Image::initWithPngData(const unsigned char *  data, size_t dataLen)
{
    //LOGD("load pngdata");
    // length of bytes to check if it is a valid png file
    #define PNGSIGSIZE  8
    bool bRet = false;
    png_byte        header[PNGSIGSIZE]   = {0};
    png_structp     png_ptr     =   0;
    png_infop       info_ptr    = 0;

    do
    {
        // png header len is 8 bytes
        if(dataLen < PNGSIGSIZE)
            break;

        // check the data is png or not
        memcpy(header, data, PNGSIGSIZE);
        if(png_sig_cmp(header, 0, PNGSIGSIZE))
            break;

        //LOGD("png_create_read_struct");
        // init png_struct
        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
        if(! png_ptr)
            break;

        //LOGD("png_create_info_struct");
        // init png_info
        info_ptr = png_create_info_struct(png_ptr);
        if(!info_ptr)
            break;

        /* 设置错误处理。如果你在调用 png_create_read_struct() 时没
           * 有设置错误处理函数，那么这段代码是必须写的。*/
        if (setjmp(png_jmpbuf(png_ptr)))
        {
            LOGD_LAYER("Use lib png failed, maybe png is invalid!");
            /* 如果程序跑到这里了，那么读文件时出现了问题 */
            png_destroy_read_struct(&png_ptr, &info_ptr, 0);
            return false;
        }

        // set the read call back function
        tImageSource imageSource;
        imageSource.data    = (unsigned char*)data;
        imageSource.size    = dataLen;
        imageSource.offset  = 0;
        png_set_read_fn(png_ptr, &imageSource, pngReadCallback);

        // read png header info

        // read png file info
        png_read_info(png_ptr, info_ptr);

        _width = png_get_image_width(png_ptr, info_ptr);
        _height = png_get_image_height(png_ptr, info_ptr);
        png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
        png_uint_32 color_type = png_get_color_type(png_ptr, info_ptr);


        // force palette images to be expanded to 24-bit RGB
        // it may include alpha channel
        if (color_type == PNG_COLOR_TYPE_PALETTE)
        {
            png_set_palette_to_rgb(png_ptr);
        }
        // low-bit-depth grayscale images are to be expanded to 8 bits
        if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        {
            bit_depth = 8;
            png_set_expand_gray_1_2_4_to_8(png_ptr);
        }
        // expand any tRNS chunk data into a full alpha channel
        if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        {
            png_set_tRNS_to_alpha(png_ptr);
        }
        // reduce images with 16-bit samples to 8 bits
        if (bit_depth == 16)
        {
            png_set_strip_16(png_ptr);
        }

        // Expanded earlier for grayscale, now take care of palette and rgb
        if (bit_depth < 8) {
            png_set_packing(png_ptr);
        }
        // LOGD_S("png_read_update_info");
        // update info
        png_read_update_info(png_ptr, info_ptr);
        bit_depth = png_get_bit_depth(png_ptr, info_ptr);
        color_type = png_get_color_type(png_ptr, info_ptr);
        // LOGD_S("Png get color type: ");

        switch (color_type)
        {
        case PNG_COLOR_TYPE_GRAY:
            _renderFormat = GL_LUMINANCE;
            break;
        case PNG_COLOR_TYPE_GRAY_ALPHA:
            _renderFormat = GL_LUMINANCE_ALPHA;
            break;
        case PNG_COLOR_TYPE_RGB:
            _renderFormat = GL_RGB;
            break;
        case PNG_COLOR_TYPE_RGB_ALPHA:
            _renderFormat = GL_RGBA;
            break;
        default:
            break;
        }

        // LOGD_S("type %d",_renderFormat);
        // read png data
        png_size_t rowbytes;
        png_bytep* row_pointers = (png_bytep*)malloc( sizeof(png_bytep) * _height );

        rowbytes = png_get_rowbytes(png_ptr, info_ptr);

#ifdef AUTO_ALLOC_MEMORY
        int newSize = rowbytes * _height;
        if (!expandImageData(newSize)) {
            break;
        }
#else

        _dataLen = rowbytes * _height;
        _data = static_cast<unsigned char*>(malloc(_dataLen * sizeof(unsigned char)));
#endif
        if(!_data)
        {
            if (row_pointers != NULL)
            {
                free(row_pointers);
            }
            break;
        }
        // LOGD_S("Row pointer:%x", row_pointers);

        for (unsigned short i = 0; i < _height; ++i)
        {
            row_pointers[i] = _data + i*rowbytes;
        }
        // LOGD_LAYER("png_read_image, len: %d ", _dataLen);
        png_read_image(png_ptr, row_pointers);
        // LOGD_LAYER("png_read_image end!");

        png_read_end(png_ptr, NULL);

        if (row_pointers != NULL)
        {
            free(row_pointers);
        }

        bRet = true;
    } while (0);

    if (png_ptr)
    {
        png_destroy_read_struct(&png_ptr, (info_ptr) ? &info_ptr : 0, 0);
    }
    return bRet;
}

bool Image::initWithRawData(const unsigned char * data, int width, int height)
{
    bool bRet = false;

    if(0 == width || 0 == height)
        return bRet;

    _height   = height;
    _width    = width;
    _renderFormat = GL_RGBA;

    // only RGBA8888 supported
    int bytesPerComponent = 4;
#ifdef AUTO_ALLOC_MEMORY
	int newSize = height * width * bytesPerComponent;
	if (!expandImageData(newSize)) {
		return bRet;
	}
#else
    _dataLen = height * width * bytesPerComponent;
    _data = static_cast<unsigned char*>(malloc(_dataLen * sizeof(unsigned char)));
#endif
    if(! _data)
        return bRet;

    memcpy(_data, data, _dataLen);

    bRet = true;

    return bRet;
}


bool Image::saveToFile(const std::string& filename)
{
    //only support for Texture2D::PixelFormat::RGB888 or Texture2D::PixelFormat::RGBA8888 uncompressed data
    if (_renderFormat != GL_RGBA)
    {
         return false;
    }

    bool bRet = false;

    if(filename.size() <= 4)
        return bRet;

    std::string strLowerCasePath(filename);
    for (unsigned int i = 0; i < strLowerCasePath.length(); ++i)
    {
        strLowerCasePath[i] = tolower(filename[i]);
    }

    if (std::string::npos != strLowerCasePath.find(".png"))
    {
        if(!saveImageToPNG(filename))
            return bRet;
    }
    else if (std::string::npos != strLowerCasePath.find(".jpg"))
    {
        if(!saveImageToJPG(filename))
            return bRet;
    }
    else
    {
        return bRet;
    }

    bRet = true;

    return bRet;
}

bool Image::saveImageToPNG(const std::string& filePath)
{
    bool bRet = false;

    FILE *fp;
    png_structp png_ptr;
    png_infop info_ptr;
    png_colorp palette;
    png_bytep *row_pointers;

    fp = fopen(filePath.c_str(), "wb+");
    if(NULL == fp)
        return bRet;

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (NULL == png_ptr)
    {
        fclose(fp);
        return bRet;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (NULL == info_ptr)
    {
        fclose(fp);
        png_destroy_write_struct(&png_ptr, NULL);
        return bRet;
    }

    png_init_io(png_ptr, fp);

    png_set_IHDR(png_ptr, info_ptr, _width, _height, 8, PNG_COLOR_TYPE_RGB_ALPHA,
        PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    palette = (png_colorp)png_malloc(png_ptr, PNG_MAX_PALETTE_LENGTH * sizeof (png_color));
    png_set_PLTE(png_ptr, info_ptr, palette, PNG_MAX_PALETTE_LENGTH);

    png_write_info(png_ptr, info_ptr);

    png_set_packing(png_ptr);

    row_pointers = (png_bytep *)malloc(_height * sizeof(png_bytep));
    if(row_pointers == NULL)
    {
        fclose(fp);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return bRet;
    }

    for (int i = 0; i < (int)_height; i++)
    {
        row_pointers[i] = (png_bytep)_data + i * _width * 4;
    }

    png_write_image(png_ptr, row_pointers);

    free(row_pointers);
    row_pointers = NULL;

    png_write_end(png_ptr, info_ptr);

    png_free(png_ptr, palette);
    palette = NULL;

    png_destroy_write_struct(&png_ptr, &info_ptr);

    fclose(fp);

    bRet = true;

    return bRet;
}

bool Image::saveImageToJPG(const std::string& filePath)
{
    bool bRet = false;

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE * outfile;                 /* target file */
    JSAMPROW row_pointer[1];        /* pointer to JSAMPLE row[s] */
    int     row_stride;          /* physical row width in image buffer */

    cinfo.err = jpeg_std_error(&jerr);
    /* Now we can initialize the JPEG compression object. */
    jpeg_create_compress(&cinfo);

    if((outfile = fopen(filePath.c_str(), "wb+")) == NULL)
        return bRet;

    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = _width;    /* image width and height, in pixels */
    cinfo.image_height = _height;
    cinfo.input_components = 3;       /* # of color components per pixel */
    cinfo.in_color_space = JCS_RGB;       /* colorspace of input image */

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 90, TRUE);

    jpeg_start_compress(&cinfo, TRUE);

    row_stride = _width * 3; /* JSAMPLEs per row in image_buffer */

    unsigned char *pTempData = static_cast<unsigned char*>(malloc(_width * _height * 3 * sizeof(unsigned char)));
    if (NULL == pTempData)
    {
        jpeg_finish_compress(&cinfo);
        jpeg_destroy_compress(&cinfo);
        fclose(outfile);
        return bRet;
    }

    for (int i = 0; i < _height; ++i)
    {
        for (int j = 0; j < _width; ++j)

        {
            pTempData[(i * _width + j) * 3] = _data[(i * _width + j) * 4];
            pTempData[(i * _width + j) * 3 + 1] = _data[(i * _width + j) * 4 + 1];
            pTempData[(i * _width + j) * 3 + 2] = _data[(i * _width + j) * 4 + 2];
        }
    }

    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = & pTempData[cinfo.next_scanline * row_stride];
        (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    if (pTempData != NULL)
    {
        free(pTempData);
    }

    jpeg_finish_compress(&cinfo);
    fclose(outfile);
    jpeg_destroy_compress(&cinfo);

    bRet = true;

    return bRet;
}

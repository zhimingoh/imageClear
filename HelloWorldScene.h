#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "jpeglib.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	//enum class Format
	//{
	//	//! JPEG
	//	JPG,
	//	//! PNG
	//	PNG,
	//	//! TIFF
	//};

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	//void convertImageData(const unsigned char * data, ssize_t dataLen, std::string oldFileName);




	//Format detectFormat(const unsigned char * data, ssize_t dataLen);
	//bool isPng(const unsigned char * data, ssize_t dataLen);
	//bool isJpg(const unsigned char * data, ssize_t dataLen);
	//bool initWithJpgData(const unsigned char *  data, ssize_t dataLen, std::string oldFileName);
	//bool initWithPngData(const unsigned char * data, ssize_t dataLen);
	//void write_YUV_JPEG_file(char * filename, unsigned char* yuvData, int quality,
	//	int image_width, int image_height);
	//void HelloWorld::write_RGB_JPEG_file(char * filename, unsigned char *rgb, int image_width,
	//	int image_height, int quality /*= 90*/);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__

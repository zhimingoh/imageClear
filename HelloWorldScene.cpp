#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <atlconv.h>
#include "pngconf.h"
#include "png.h"
#include "jpeglib.h"

USING_NS_CC;



Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void selectFile(std::string path);
std::string getApplicationPath();
std::string getApplicationExePath();
char* convertTCharToUtf8(const TCHAR* src);
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_0(selectFile, ""));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}

void selectFile(std::string str)
{
	CCLOG("PATH ==%s", str.c_str());
	if (str.c_str() ==" ")
	{
		CCLOG("NO STR");
		return;
	}

	int poss = str.find_last_of('\\');
	std::string fileName(str.substr(poss + 1));
	CCLOG("fileName%s", fileName.c_str());

	//createSpriteFormPath(str);
	auto _filePath = FileUtils::getInstance()->fullPathForFilename(str);


	std::string path = _filePath;
	size_t pos;
	while ((pos = path.find_first_of("\\")) != std::string::npos)
	{
		path.replace(pos, 1, "/");
	}
	size_t p = path.find_last_of("/");
	std::string workdir;
	if (p != path.npos)
	{
		workdir = path.substr(0, p);
	}
	std::string outPath = workdir;

	CCLOG("workdir %s", workdir.c_str());

	size_t posx;
	while ((posx = outPath.find_first_of("/")) != std::string::npos)
	{
		outPath.replace(posx, 1, "\\");
	}
	CCLOG("path==2222222====%s", outPath.c_str());
	Image image;
	image.initWithImageFile(_filePath);
	std::string fileExtension = FileUtils::getInstance()->getFileExtension(_filePath);
	if (fileExtension == ".png") {
		if (image.getRenderFormat() == Texture2D::PixelFormat::RGB888) {
			ssize_t len = image.getDataLen() / 3 * 4;
			unsigned char* dummy = nullptr;
			dummy = (unsigned char*)malloc(len);
			memset(dummy, 0, len);

			auto tempLen = image._dataLen;
			auto temp = image._data;
			image._data = dummy;
			image._dataLen = len;
			image._renderFormat = Texture2D::PixelFormat::RGBA8888;
			outPath += "\\" + fileName;
			image.saveImageToPNG(outPath, false);

			image._dataLen = tempLen;
			image._data = temp;
			image._renderFormat = Texture2D::PixelFormat::RGB888;
			free(dummy);
		}
		else {
			unsigned char * data = image.getData();
			memset((void *)data, 0, image.getDataLen());
			outPath += "\\"+fileName;
			image.saveImageToPNG(outPath, false);
		}
		
	}
	else if (fileExtension == ".jpg") {
		unsigned char * data = image.getData();
		memset((void *)data, 0, image.getDataLen());
		outPath += "\\" + fileName;
		image.saveImageToJPG(outPath);
	}

}

//»ñÈ¡exeÂ·¾¶
std::string getApplicationExePath()
{
	TCHAR szFileName[MAX_PATH];
	GetModuleFileName(NULL, szFileName, MAX_PATH);
	std::u16string u16ApplicationName;
	char *applicationExePath = convertTCharToUtf8(szFileName);
	std::string path(applicationExePath);
	CC_SAFE_FREE(applicationExePath);
	CCLOG("EXE PATH%s", path.c_str());
	return path;
}

std::string getApplicationPath()
{
	std::string path = getApplicationExePath();
	size_t pos;
	while ((pos = path.find_first_of("\\")) != std::string::npos)
	{
		path.replace(pos, 1, "/");
	}
	size_t p = path.find_last_of("/");
	std::string workdir;
	if (p != path.npos)
	{
		workdir = path.substr(0, p);
	}
	CCLOG("getApplicationPath %s", workdir.c_str());
	//workdir += "\\res";
	CCLOG("workdir %s", workdir.c_str());
	return workdir;
}
char* convertTCharToUtf8(const TCHAR* src)
{
#ifdef UNICODE
	WCHAR* tmp = (WCHAR*)src;
	size_t size = wcslen(src) * 3 + 1;
	char* dest = new char[size];
	memset(dest, 0, size);
	WideCharToMultiByte(CP_UTF8, 0, tmp, -1, dest, size, NULL, NULL);
	return dest;
#else
	char* tmp = (char*)src;
	uint32 size = strlen(tmp) + 1;
	WCHAR* dest = new WCHAR[size];
	memset(dest, 0, sizeof(WCHAR)*size);
	MultiByteToWideChar(CP_ACP, 0, src, -1, dest, (int)size); // convert local code to unicode.

	size = wcslen(dest) * 3 + 1;
	char* dest2 = new char[size];

	memset(dest2, 0, size);
	WideCharToMultiByte(CP_UTF8, 0, dest, -1, dest2, size, NULL, NULL); // convert unicode to utf8.
	delete[] dest;
	return dest2;
#endif
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}


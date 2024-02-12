/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>
/**
 * Required to modify the MenuLayer class
 */
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <string_view>

/**
 * Brings cocos2d and all Geode namespaces 
 * to the current scope.
 */
using namespace geode::prelude;
std::string img{ (Mod::get()->getConfigDir() / "background.jpg").string() };
auto winSize = CCDirector::sharedDirector()->getWinSize();
int maam = Mod::get()->getSettingValue<int64_t>("maam");


void png() {
	if (!ghc::filesystem::exists(img)) {
		img = (Mod::get()->getConfigDir() / "background.png").string();
	}

}

/**
 * `$modify` lets you extend and modify GD's 
 * classes; to hook a function in Geode, 
 * simply $modify the class and write a new 
 * function definition with the signature of 
 * the one you want to hook.
 */
class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
		
		auto bg = this->getChildByID("main-menu-bg");
		auto spr = CCSprite::create(img.c_str());

		spr->setScaleY(winSize.height / spr->getContentSize().height);
		spr->setScaleX(winSize.width / spr->getContentSize().width);
		spr->setPositionX(winSize.width / 2);
		spr->setPositionY(winSize.height / 2);
		

		if (ghc::filesystem::exists(img)) {

			bg->setVisible(false);
			spr->setOpacity(maam);
			this->addChild(spr, -1);
			
		}

		bool disablelogo = Mod::get()->getSettingValue<bool>("pene");
		
		if (disablelogo) {
			this->removeChildByID("main-title");

		}
			
		return true;

	} 
};

class $modify(CreatorLayer) {
	bool init() {
		if (!CreatorLayer::init())
			return false;


		auto bg = this->getChildByID("background");
		auto spr = CCSprite::create(img.c_str());

		spr->setScaleY(winSize.height / spr->getContentSize().height);
		spr->setScaleX(winSize.width / spr->getContentSize().width);
		spr->setPositionX(winSize.width / 2);
		spr->setPositionY(winSize.height / 2);


		if (ghc::filesystem::exists(img)) {
			//god i wish there was an easier way to do this ����
			if (Mod::get()->getSettingValue<bool>("creatorlayer")) {  
				bg->setVisible(false);
				spr->setOpacity(maam);
				this->addChild(spr, -1);
			}

		}

		return true;
	}

	
};

//yes another copypaste
class $modify(LevelInfoLayer) {
	bool init(GJGameLevel * p0, bool p1) {
		if (!LevelInfoLayer::init(p0, p1))
			return false;


		auto bg = this->getChildByID("background");
		auto spr = CCSprite::create(img.c_str());

		spr->setScaleY(winSize.height / spr->getContentSize().height);
		spr->setScaleX(winSize.width / spr->getContentSize().width);
		spr->setPositionX(winSize.width / 2);
		spr->setPositionY(winSize.height / 2);


		if (ghc::filesystem::exists(img)) {
			
			if (Mod::get()->getSettingValue<bool>("levelinfolayer")) {
				bg->setVisible(false);
				spr->setOpacity(maam);
				this->addChild(spr, -1);
			}

		}

		return true;
	}


};

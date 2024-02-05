/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>
/**
 * Required to modify the MenuLayer class
 */
#include <Geode/modify/MenuLayer.hpp>

/**
 * Brings cocos2d and all Geode namespaces 
 * to the current scope.
 */
using namespace geode::prelude;

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
		std::string img{};
		img = (Mod::get()->getConfigDir() / "background.jpg").string();

		if (!ghc::filesystem::exists(img)) {
			img = (Mod::get()->getConfigDir() / "background.png").string();
		}

		if (ghc::filesystem::exists(img)) {

			auto spr = CCSprite::create(img.c_str());

			auto winSize = CCDirector::sharedDirector()->getWinSize();

			spr->setScaleY(winSize.height / spr->getContentSize().height);
			spr->setScaleX(winSize.width / spr->getContentSize().width);
			spr->setPositionX(winSize.width / 2);
			spr->setPositionY(winSize.height / 2);



			bg->setVisible(false);
			this->addChild(spr, -1);
			
		}

		bool setting = Mod::get()->getSettingValue<bool>("pene");
		
		if (setting) {
			this->removeChildByID("main-title");

		}
			
		return true;

	} 
};
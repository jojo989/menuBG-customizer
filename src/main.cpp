#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>

using namespace geode::prelude;

const char* getImage() {
	const char* img = (Mod::get()->getConfigDir() / "background.png").string().c_str();
	if (!std::filesystem::exists(img)) {
		img = (Mod::get()->getConfigDir() / "background.jpg").string().c_str();
	}
	return img;
}

void applyWallpaper(CCLayer* layer, const char* bgNodeID = "background") {
	auto img = getImage();
	auto spr = CCSprite::create(img);
	if (!std::filesystem::exists(img)) { return; }

	if (auto bg = layer->getChildByID(bgNodeID)) bg->setVisible(false);
	
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	auto sprSize = spr->getContentSize();
	
	spr->setScaleX(winSize.width / sprSize.width);
	spr->setScaleY(winSize.height / sprSize.height);
	spr->setPosition({winSize.width / 2.f, winSize.height / 2.f});
	spr->setOpacity(Mod::get()->getSettingValue<int64_t>("opacity"));
	
	layer->addChild(spr, -1);
}

class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) { return false; }
		
		applyWallpaper(this, "main-menu-bg");
		
		if (Mod::get()->getSettingValue<bool>("removeGDLogo")) { removeChildByID("main-title"); }
			
		return true;
	} 
};

class $modify(CreatorLayer) {
	bool init() {
		if (!CreatorLayer::init()) { return false; }
		if (!Mod::get()->getSettingValue<bool>("creatorLayer")) { return true; }
		
		applyWallpaper(this);
		
		return true;
	}
};

class $modify(LevelInfoLayer) {
	bool init(GJGameLevel * p0, bool p1) {
		if (!LevelInfoLayer::init(p0, p1)) { return false; }
		if (!Mod::get()->getSettingValue<bool>("levelInfoLayer")) { return true; }
		
		applyWallpaper(this);
		
		return true;
	}
};
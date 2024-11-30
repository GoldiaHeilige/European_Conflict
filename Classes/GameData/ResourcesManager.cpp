#include "ResourcesManager.h"
#include "AnimManager/AnimationUtils.h"

ResourcesManager* ResourcesManager::_instance = nullptr;

ResourcesManager* ResourcesManager::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new ResourcesManager();
    }
    return _instance;
}

void ResourcesManager::preloadAllSpritesFromDirectory(const std::string& directory)
{
    auto fileUtils = FileUtils::getInstance();
    auto fullPath = fileUtils->fullPathForFilename(directory);
    auto files = fileUtils->listFiles(fullPath);

    for (const auto& file : files)
    {
        if (file.find(".plist") != std::string::npos)
        {
            std::string plistPath = file;
            std::string texturePath = file;
            texturePath.replace(texturePath.find(".plist"), 6, ".png");

            SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistPath);
            Director::getInstance()->getTextureCache()->addImage(texturePath);

            addToGroup("AllSprites", plistPath);
            CCLOG("Preloaded sprite frames from plist: %s", plistPath.c_str());
        }
        else if (file.find(".png") != std::string::npos || file.find(".jpg") != std::string::npos)
        {
            Director::getInstance()->getTextureCache()->addImage(file);
            addToGroup("AllSprites", file);
            CCLOG("Preloaded texture: %s", file.c_str());
        }
    }

    CCLOG("Preloaded all sprites from directory: %s", directory.c_str());
}

void ResourcesManager::preloadSpritesFromDirectory(const std::string& directory)
{
    auto fileUtils = FileUtils::getInstance();
    auto fullPath = fileUtils->fullPathForFilename(directory);
    auto files = fileUtils->listFiles(fullPath);

    for (const auto& file : files)
    {
        if (file.find(".png") != std::string::npos)
        {
            Director::getInstance()->getTextureCache()->addImage(file);
        }
    }

    CCLOG("Preloaded sprites from directory: %s", directory.c_str());
}

void ResourcesManager::preloadPlist(const std::string& path, const std::string& fileName)
{
    if (AnimationUtils::loadSpriteFrameCache(path, fileName))
    {
        addToGroup("PlistFiles", path + fileName + ".plist");
        CCLOG("Preloaded plist: %s", (path + fileName).c_str());
    }
}

void ResourcesManager::preloadResourcesForGroup(const std::string& group)
{
    if (group == "Menu")
    {
        //preloadPlist("Map/MapHUD/", "menu_sprites");
        //preloadPlist("UI/", "menu_sprites");
        //preloadPlist("UI/Saving/", "menu_sprites");

        preloadSpritesFromDirectory("Map/LocationPortraits");
        preloadSpritesFromDirectory("UI/");
    }
    else if (group == "Game")
    {
        preloadPlist("Effects/Weapon Effect/", "LauncherExplosion");
        //preloadPlist("Effects/Roof_fire/", "game_sprites");
        
        // Entity Animation
        preloadPlist("Entity/Character/", "Hero");
        preloadPlist("Entity/Character/", "Hero_Death");
        preloadPlist("Entity/Enemy/", "Enemy3_Rifle_Death");
        preloadPlist("Entity/Enemy/", "Enemy4_Rifle_Death");

        // Building & Object Sprites
        //preloadAllSpritesFromDirectory("Building/Building Small");
        //preloadAllSpritesFromDirectory("Building/Building Small/Elements");
        //preloadAllSpritesFromDirectory("Building/Building Warehouses");
        //preloadAllSpritesFromDirectory("Building/Building Warehouses/Elements");
        //preloadAllSpritesFromDirectory("Building/building_industrial");
        //preloadAllSpritesFromDirectory("Building/building_industrial/Elements");
        //preloadAllSpritesFromDirectory("Bullet");

        //// Entity Sprites
        //preloadAllSpritesFromDirectory("Entity/Character");
        //preloadAllSpritesFromDirectory("Entity/Enemy");

        //// Vehicle Sprites
        //preloadAllSpritesFromDirectory("Vehicle/Civi Vehicle/Big Normal Vehicle_1");
        //preloadAllSpritesFromDirectory("Vehicle/Civi Vehicle/Broken Vehicle");
        //preloadAllSpritesFromDirectory("Vehicle/Civi Vehicle/Small Normal Vehicle_1");
        //preloadAllSpritesFromDirectory("Vehicle/Civi Vehicle/Small Normal Vehicle_2");
    }
}

void ResourcesManager::releaseResourcesForGroup(const std::string& group)
{
    if (_groupResources.find(group) == _groupResources.end())
        return;

    for (const auto& resource : _groupResources[group])
    {
        if (resource.find(".plist") != std::string::npos)
        {
            // Giải phóng các sprite frame
            SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(resource);

            // Xóa texture liên quan nếu có
            std::string textureFile = resource;
            textureFile.replace(textureFile.find(".plist"), 6, ".png");
            Director::getInstance()->getTextureCache()->removeTextureForKey(textureFile);

            CCLOG("Released sprite frames from plist: %s", resource.c_str());
        }
        else if (resource.find(".png") != std::string::npos)
        {
            // Giải phóng các texture riêng lẻ
            Director::getInstance()->getTextureCache()->removeTextureForKey(resource);
            CCLOG("Released texture: %s", resource.c_str());
        }
    }

    _groupResources[group].clear();
    CCLOG("Released resources for group: %s", group.c_str());
}

void ResourcesManager::addToGroup(const std::string& group, const std::string& resourcePath)
{
    _groupResources[group].push_back(resourcePath);
}

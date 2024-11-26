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
        preloadPlist("Resources/Map/MapHUD/", "menu_sprites");
        preloadPlist("Resources/UI/", "menu_sprites");
        preloadPlist("Resources/UI/Saving/", "menu_sprites");

        preloadSpritesFromDirectory("Resources/Map/LocationPortraits");
        preloadSpritesFromDirectory("Resources/UI/");
    }
    else if (group == "Game")
    {
        preloadPlist("Resources/Effects/Weapon Effect/", "game_sprites");
        preloadPlist("Resources/Effects/Roof_fire/", "game_sprites");
        preloadPlist("Resources/Entity/Character/", "game_sprites");
        preloadPlist("Resources/Entity/Enemy/", "game_sprites");

        preloadSpritesFromDirectory("Resources/Building");
        preloadSpritesFromDirectory("Resources/Building/Building Small");
        preloadSpritesFromDirectory("Resources/Building/Building Small/Elements");
        preloadSpritesFromDirectory("Resources/Building/Building Warehouses");
        preloadSpritesFromDirectory("Resources/Building/Building Warehouses/Elements");
        preloadSpritesFromDirectory("Resources/Building/building_industrial");
        preloadSpritesFromDirectory("Resources/Building/building_industrial/Elements");
        preloadSpritesFromDirectory("Resources/Bullet");

        preloadSpritesFromDirectory("Resources/Entity/Character");
        preloadSpritesFromDirectory("Resources/Entity/Enemy");

        preloadSpritesFromDirectory("Resources/Vehicle/Civi Vehicle/Big Normal Vehicle_1");
        preloadSpritesFromDirectory("Resources/Vehicle/Civi Vehicle/Broken Vehicle");
        preloadSpritesFromDirectory("Resources/Vehicle/Civi Vehicle/Small Normal Vehicle_1");
        preloadSpritesFromDirectory("Resources/Vehicle/Civi Vehicle/Small Normal Vehicle_2");
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
            SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(resource);
        }
        else if (resource.find(".png") != std::string::npos)
        {
            Director::getInstance()->getTextureCache()->removeTextureForKey(resource);
        }
    }

    _groupResources[group].clear();
    CCLOG("Released resources for group: %s", group.c_str());
}

void ResourcesManager::addToGroup(const std::string& group, const std::string& resourcePath)
{
    _groupResources[group].push_back(resourcePath);
}

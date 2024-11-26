#ifndef __RESOURCES_MANAGER_H__
#define __RESOURCES_MANAGER_H__

#include "cocos2d.h"
#include <unordered_map>
#include <string>
#include <vector>

USING_NS_CC;

class ResourcesManager
{
public:
    static ResourcesManager* getInstance();

    // Preload tất cả các sprite từ thư mục
    void preloadSpritesFromDirectory(const std::string& directory);

    // Preload plist
    void preloadPlist(const std::string& path, const std::string& fileName);

    // Preload nhóm tài nguyên
    void preloadResourcesForGroup(const std::string& group);

    // Giải phóng tài nguyên của nhóm
    void releaseResourcesForGroup(const std::string& group);

private:
    ResourcesManager() = default;

    static ResourcesManager* _instance;

    std::unordered_map<std::string, std::vector<std::string>> _groupResources;

    void addToGroup(const std::string& group, const std::string& resourcePath);
};

#endif // __RESOURCES_MANAGER_H__

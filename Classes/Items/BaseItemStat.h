#ifndef __BASE_ITEM_STAT_H__
#define __BASE_ITEM_STAT_H__

#include <string>

struct BaseItemStat {
    std::string _id;       
    std::string _name;       
    std::string _description;  
    float _weight;            
    int _stackSize;         
    std::string _icon;        
};

#endif // __BASE_ITEM_STAT_H__

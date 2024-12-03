#ifndef __MEDICAL_STAT_H__
#define __MEDICAL_STAT_H__

#include <string>

struct MedicalStat {
    std::string _id;           // ID của vật phẩm
    std::string _name;         // Tên dùng để spawn trong Tiled
    std::string _description;  // Mô tả vật phẩm
    int _healAmount;           // Lượng máu hồi phục
    int _stackSize;            // Số lượng tối đa trong một ô
    float _weight;             // Trọng lượng của vật phẩm
    std::string _icon;         // Đường dẫn tới icon trong inventory
    float _useTime;            // Thời gian sử dụng vật phẩm
    float _cooldown;           // Thời gian hồi sau khi dùng
    std::string _effectType;   // Loại hiệu ứng (vd: heal)
};

#endif // __MEDICAL_STAT_H__

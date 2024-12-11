#ifndef __PHYSICS_CATEGORY_H__
#define __PHYSICS_CATEGORY_H__

enum PhysicsCategory {
    NONE = 0,          // Không có va chạm
    ITEM = 1 << 0,     // 0x01 - Đồ vật (Item)
    PLAYER = 1 << 1,   // 0x02 - Nhân vật (Player)
    ENEMY = 1 << 2,    // 0x04 - Kẻ thù (Enemy)
    STATIC_OBJECT = 1 << 3, // 0x08 - Đối tượng tĩnh (Static Object)
    BULLET = 1 << 4,    // 0x10 - Đạn (Bullet)
};

#endif // __PHYSICS_CATEGORY_H__

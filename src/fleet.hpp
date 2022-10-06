#pragma once

#include"zxlb.hpp"
#include"ship.hpp"

class Fleet {
private:
    ID id;
    str desc;
    luptr<Ship> ships;
public:
    Fleet();
    Fleet(ID _id);
    Fleet(Fleet && f) = default;
    Fleet& operator=(Fleet && f) = default;
    ID GetID() const;
    str GetDesc() const;
    void SetDesc(str _desc);
    void AddShip(uptr<Ship> s);
    Ship * FindShip(ID id);
    uptr<Ship> RemoveShip(ID id);
};
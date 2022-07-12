#pragma once

#include<fstream>

#include"json.hpp"

#include"zxlb.hpp"
#include"ship.hpp"



namespace shipfactory {

    using namespace nlohmann;

    using ShipSysDict = umap<str,json>;
    using ShipDict = umap<str,json>;

    inline ShipSysDict ship_sys_dict;
    inline ShipDict ship_dict;

    bool LoadShipSysDict(str modname, str filename);
    bool LoadShipDict(str modname, str filename);

    uptr<Ship> BuildShip(str ship_name_unique);


};
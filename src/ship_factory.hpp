#pragma once

#include<fstream>

#include"json.hpp"

#include"zxlb.hpp"
#include"ship.hpp"



namespace shipfactory {

    using namespace nlohmann;

    /* -----------------------------------------------------------------
        Loading JSON ship and sys data. 
    ----------------------------------------------------------------- */
    using ShipSysDict = umap<str,json>;
    using ShipDict = umap<str,json>;

    inline ShipSysDict ship_sys_dict;
    inline ShipDict ship_dict;

    bool LoadShipSysDict(str modname, str filename);
    bool LoadShipDict(str modname, str filename);

    /* -----------------------------------------------------------------
        Builds ship systems from the JSON templates
    ----------------------------------------------------------------- */
    void InitBasicSysData(json obj, json sys_obj, SSys * sys);

    uptr<SBridge> BuildSys_Bridge(json obj, json sys_obj);
    uptr<SCargoHold> BuildSys_CargoHold(json obj, json sys_obj);
    uptr<SCloak> BuildSys_Cloak(json obj, json sys_obj);
    uptr<SCounterMeasure> BuildSys_CounterMeasure(json obj, json sys_obj);
    uptr<SFTLEngine> BuildSys_FTLEngine(json obj, json sys_obj);
    uptr<SHangar> BuildSys_Hangar(json obj, json sys_obj);
    uptr<SHull> BuildSys_Hull(json obj, json sys_obj);
    uptr<SMedbay> BuildSys_Medbay(json obj, json sys_obj);
    uptr<SQuarters> BuildSys_Quarters(json obj, json sys_obj);
    uptr<SReactor> BuildSys_Reactor(json obj, json sys_obj);
    uptr<SRepairStation> BuildSys_RepairStation(json obj, json sys_obj);
    uptr<SScanner> BuildSys_Scanner(json obj, json sys_obj);
    uptr<SSecStation> BuildSys_SecStation(json obj, json sys_obj);
    uptr<SShield> BuildSys_Shield(json obj, json sys_obj);
    uptr<SSTLEngine> BuildSys_STLEngine(json obj, json sys_obj);
    uptr<STroopHold> BuildSys_TroopHold(json obj, json sys_obj);
    uptr<SWeapon> BuildSys_Weapon(json obj, json sys_obj);
    uptr<SSys> BuildSys(json obj);
 
 
    /* -----------------------------------------------------------------
        Builds the ship
    ----------------------------------------------------------------- */
    uptr<Ship> BuildShip(str ship_name_unique);

    

};
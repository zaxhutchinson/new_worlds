#include"ship_factory.hpp"


namespace shipfactory {

    bool LoadShipSysDict(str modname, str filename) {
        bool good = true;

        str fullpath("mods/"+modname+"/"+filename);

        std::ifstream ifs(fullpath);
        if(!ifs.is_open()) return false;

        json j;
        ifs >> j;

        for(
            json::iterator it = j.begin();
            it != j.end();
            it++
        ) {
            if(it.value().is_object()) {

                // TODO: check object conforms to ship sys.
                ship_sys_dict.emplace(it.key(), it.value());
            } else {
                good &= false;
            }

        }

        return good;

    }

    bool LoadShipDict(str modname, str filename) {
        bool good = true;

        str fullpath("mods/"+modname+"/"+filename);

        std::ifstream ifs(fullpath);
        if(!ifs.is_open()) return false;

        json j;
        ifs >> j;

        for(
            json::iterator it = j.begin();
            it != j.end();
            it++
        ) {
            if(it.value().is_object()) {

                // TODO: check object conforms to ship.
                ship_dict.emplace(it.key(), it.value());
            } else {
                good &= false;
            }

        }

        return good;

    }







    void InitBasicSysData(json obj, json sys_obj, SSys * sys) {

        vec<i64> c = obj.at("room_location");
        Vec3i room_location(c[0],c[1],c[2]);

        vec<i64> d = obj.at("room_shape");
        Vec2i room_shape(d[0],d[1]);
        
        str name = sys_obj.at("name");
        SSysType type = sys_obj.at("type");
        i64 structural_health = sys_obj.at("structural_health");
        i64 system_health = sys_obj.at("system_health");
        i64 energy_req = sys_obj.at("energy_req");

        i64 num_crew = sys_obj.at("num_crew");
        SJobType job_type = sys_obj.at("job_type");

        sys->Init_SSys(
            name,
            type,
            structural_health,
            system_health,
            energy_req,
            num_crew,
            job_type
        );

        sys->SetRoomLocation(room_location);
        sys->SetRoomShape(room_shape);
    }



    uptr<SBridge> BuildSys_Bridge(json obj, json sys_obj) {

        uptr<SBridge> sys = std::make_unique<SBridge>();

        // Init the basic SSys parent data.
        InitBasicSysData(obj, sys_obj, sys.get());

        // Init SBridge data.
        // NONE

        return sys;
    }

    uptr<SCargoHold> BuildSys_CargoHold(json obj, json sys_obj) {

        uptr<SCargoHold> sys = std::make_unique<SCargoHold>();

        // Init the basic SSys parent data.
        InitBasicSysData(obj, sys_obj, sys.get());

        // Init specialized data.
        i64 storage = sys_obj.at("storage");
        sys->Init_SCargoHold(
            storage
        );

        return sys;
    }
    uptr<SCloak> BuildSys_Cloak(json obj, json sys_obj){

        uptr<SCloak> sys = std::make_unique<SCloak>();

        // Init the basic SSys parent data.
        InitBasicSysData(obj, sys_obj, sys.get());

        // Init specialized data.
        i64 cloak_level = sys_obj.at("cloak_level");
        sys->Init_SCloak(
            cloak_level
        );

        return sys;
    }
    uptr<SCounterMeasure> BuildSys_CounterMeasure(json obj, json sys_obj) {

        uptr<SCounterMeasure> sys = std::make_unique<SCounterMeasure>();

        // Init the basic SSys parent data.
        InitBasicSysData(obj, sys_obj, sys.get());

        // Init specialized data.
        i64 acc_reduction = sys_obj.at("accuracy_reduction");
        sys->Init_SCounterMeasure(
            acc_reduction
        );

        return sys;
    }
    uptr<SFTLEngine> BuildSys_FTLEngine(json obj, json sys_obj) {

        uptr<SFTLEngine> sys = std::make_unique<SFTLEngine>();

        // Init the basic SSys parent data.
        InitBasicSysData(obj, sys_obj, sys.get());

        // Init specialized data.
        i64 jump_distance = sys_obj.at("jump_distance");
        i64 charge_rate = sys_obj.at("charge_rate");
        sys->Init_SFTLEngine(
            jump_distance,
            charge_rate
        );

        return sys;
    }
    uptr<SHangar> BuildSys_Hangar(json obj, json sys_obj) {

        uptr<SHangar> sys = std::make_unique<SHangar>();

        // Init the basic SSys parent data.
        InitBasicSysData(obj, sys_obj, sys.get());

        // Init specialized data.
        i64 hangar_storage = sys_obj.at("hangar_storage");
        sys->Init_SHangar(
            hangar_storage
        );

        return sys;
    }
    uptr<SHull> BuildSys_Hull(json obj, json sys_obj) {

        uptr<SHull> sys = std::make_unique<SHull>();

        // Init the basic SSys parent data.
        InitBasicSysData(obj, sys_obj, sys.get());

        // Init specialized data.

        return sys;
    }
    uptr<SMedbay> BuildSys_Medbay(json obj, json sys_obj) {

        uptr<SMedbay> sys = std::make_unique<SMedbay>();

        // Init the basic SSys parent data.
        InitBasicSysData(obj, sys_obj, sys.get());

        // Init specialized data.
        i64 beds = sys_obj.at("beds");
        i64 healing_rate = sys_obj.at("healing_rate");
        sys->Init_SMedbay(
            beds,
            healing_rate
        );

        return sys;
    }
    uptr<SQuarters> BuildSys_Quarters(json obj, json sys_obj) {

        uptr<SQuarters> sys = std::make_unique<SQuarters>();

        // Init the basic SSys parent data.
        InitBasicSysData(obj, sys_obj, sys.get());

        // Init specialized data.
        i64 num_crew_beds = sys_obj.at("num_crew_beds");
        i64 morale_increase_prob = sys_obj.at("morale_increase_prob");
        i64 stamina_increase_per_hour = sys_obj.at("stamina_increase_per_hour");
        sys->Init_SQuarters(
            num_crew_beds,
            morale_increase_prob,
            stamina_increase_per_hour
        );

        return sys;
    }
    uptr<SReactor> BuildSys_Reactor(json obj, json sys_obj) {

        uptr<SReactor> sys = std::make_unique<SReactor>();

        // Init the basic SSys parent data.
        InitBasicSysData(obj, sys_obj, sys.get());

        // Init specialized data.
        i64 energy_prod = sys_obj.at("energy_prod");
        sys->Init_SReactor(
            energy_prod
        );

        return sys;
    }
    uptr<SRepairStation> BuildSys_RepairStation(json obj, json sys_obj) {

        uptr<SRepairStation> sys = std::make_unique<SRepairStation>();

        // Init the basic SSys parent data.
        InitBasicSysData(obj, sys_obj, sys.get());

        // Init specialized data.
        sys->Init_SRepairStation(
            
        );

        return sys;
    }
    uptr<SScanner> BuildSys_Scanner(json obj, json sys_obj) {

        uptr<SScanner> sys = std::make_unique<SScanner>();

        // Init the basic SSys parent data.
        InitBasicSysData(obj, sys_obj, sys.get());

        // Init specialized data.
        i64 scan_distance = sys_obj.at("scan_distance");
        i64 scan_penetration = sys_obj.at("scan_penetration");
        sys->Init_SScanner(
            scan_distance,
            scan_penetration
        );

        return sys;
    }
    uptr<SSecStation> BuildSys_SecStation(json obj, json sys_obj) {

        uptr<SSecStation> sys = std::make_unique<SSecStation>();

        // Init the basic SSys parent data.
        InitBasicSysData(obj, sys_obj, sys.get());

        // Init specialized data.
        sys->Init_SSecStation(
            
        );

        return sys;
    }
    uptr<SShield> BuildSys_Shield(json obj, json sys_obj) {

        uptr<SShield> sys = std::make_unique<SShield>();

        // Init the basic SSys parent data.
        InitBasicSysData(obj, sys_obj, sys.get());

        // Init specialized data.
        i64 max_shield = sys_obj.at("max_shield");
        i64 regen_shield = sys_obj.at("regen_shield");
        sys->Init_SShield(
            max_shield,
            regen_shield
        );

        return sys;
    }
    uptr<SSTLEngine> BuildSys_STLEngine(json obj, json sys_obj) {

        uptr<SSTLEngine> sys = std::make_unique<SSTLEngine>();

        // Init the basic SSys parent data.
        InitBasicSysData(obj, sys_obj, sys.get());

        // Init specialized data.
        i64 thrust = sys_obj.at("thrust");
        sys->Init_SEngine(
            thrust
        );

        return sys;
    }
    uptr<STroopHold> BuildSys_TroopHold(json obj, json sys_obj) {

        uptr<STroopHold> sys = std::make_unique<STroopHold>();

        // Init the basic SSys parent data.
        InitBasicSysData(obj, sys_obj, sys.get());

        // Init specialized data.
        i64 troops = sys_obj.at("troops");
        sys->Init_STroopHold(
            troops
        );

        return sys;
    }
    uptr<SWeapon> BuildSys_Weapon(json obj, json sys_obj) {

        uptr<SWeapon> sys = std::make_unique<SWeapon>();

        // Init the basic SSys parent data.
        InitBasicSysData(obj, sys_obj, sys.get());

        // Init specialized data.
        i64 dmg_structure = sys_obj.at("dmg_structure");
        i64 dmg_shields = sys_obj.at("dmg_shields");
        i64 dmg_systems = sys_obj.at("dmg_systems");
        i64 weapon_range = sys_obj.at("weapon_range");
        i64 target_size = sys_obj.at("target_size");
        i64 target_rate = sys_obj.at("target_rate");
        i64 rate_of_fire = sys_obj.at("rate_of_fire");
        sys->Init_SWeapon(
            dmg_structure,
            dmg_shields,
            dmg_systems,
            weapon_range,
            target_size,
            target_rate,
            rate_of_fire
        );

        return sys;
    }
    uptr<SSys> BuildSys(json obj) {
        if(!obj.contains("uname")) return nullptr;
        str uname = obj.at("uname");

        if(!ship_sys_dict.contains(uname)) return nullptr;
        json sys_obj = ship_sys_dict.at(uname);

        if(!sys_obj.contains("type")) return nullptr;
        str type_str = sys_obj.at("type");
        opt<SSysType> type = magic_enum::enum_cast<SSysType>(type_str);

        if(!type.has_value()) return nullptr;

        switch(type.value()) {
            case SSysType::Bridge: return BuildSys_Bridge(obj, sys_obj);
            case SSysType::CargoHold: return BuildSys_CargoHold(obj, sys_obj);
            case SSysType::Cloak: return BuildSys_Cloak(obj, sys_obj);
            case SSysType::CounterMeasure: return BuildSys_CounterMeasure(obj, sys_obj);
            case SSysType::FTLEngine: return BuildSys_FTLEngine(obj, sys_obj);
            case SSysType::Hangar: return BuildSys_Hangar(obj, sys_obj);
            case SSysType::Hull: return BuildSys_Hull(obj, sys_obj);
            case SSysType::Medbay: return BuildSys_Medbay(obj, sys_obj);
            case SSysType::Quarters: return BuildSys_Quarters(obj, sys_obj);
            case SSysType::Reactor: return BuildSys_Reactor(obj, sys_obj);
            case SSysType::RepairStation: return BuildSys_RepairStation(obj, sys_obj);
            case SSysType::Scanner: return BuildSys_Scanner(obj, sys_obj);
            case SSysType::SecStation: return BuildSys_SecStation(obj, sys_obj);
            case SSysType::Shield: return BuildSys_Shield(obj, sys_obj);
            case SSysType::STLEngine: return BuildSys_STLEngine(obj, sys_obj);
            case SSysType::TroopHold: return BuildSys_TroopHold(obj, sys_obj);
            case SSysType::Weapon: return BuildSys_Weapon(obj, sys_obj);
            default: return nullptr;
        }

    }



}
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









}
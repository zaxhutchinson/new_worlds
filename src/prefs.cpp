#include"prefs.hpp"


namespace prefs {

    void LoadPrefs(str modname) {
        std::ifstream ifs("mods/"+modname+"/general.json");
        nlohmann::json j;
        ifs >> j;

        random_galaxy = j.at("random_galaxy");

        if(random_galaxy) {
            LoadGalaxyPrefs(modname);
        }

        prefs_loaded = true;
    }




    void LoadGalaxyPrefs(str modname) {
        std::ifstream ifs("mods/"+modname+"/galaxy.json");
        nlohmann::json j;
        ifs >> j;

        galaxy_X = j.at("galaxy_X");
        galaxy_Y = j.at("galaxy_Y");
        number_of_systems = j.at("number_of_systems");
        system_names = j.at("system_names").get<vec<str>>();

        number_of_factions = j.at("number_of_factions");

    }

}


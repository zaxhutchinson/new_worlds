#include"galaxy_builder.hpp"

uptr<Galaxy> BuildNewGalaxy(str modname) {
    if(prefs::prefs_loaded) {
        if(prefs::random_galaxy) {
            return BuildRandomGalaxy(modname);
        } else {
            return BuildNewGalaxy(modname);
        }
    } else {
        return nullptr;
    }
}



uptr<Galaxy> BuildDefinedGalaxy(str modname) {
    uptr<Galaxy> galaxy = std::make_unique<Galaxy>();

    std::ifstream ifs("mods/"+modname+"/galaxy.json");
    nlohmann::json j;
    ifs >> j;

    for(
        nlohmann::json::iterator it = j.begin();
        it != j.end(); it++
    ) {
        str id = it.key();
        str name = it->at("name");
        str desc = it->at("desc");
        vec<int> coords = it->at("position");
        Vec2i pos(coords[0],coords[1]);
        vec<double> res = it->at("resources");
        vec<double> inf = it->at("infrastructure");
        double stability = it->at("stability");

        System s(
            id,
            name,
            desc,
            pos,
            res,
            inf,
            stability
        );

        galaxy->AddSystem(std::move(s));

    }

    return galaxy;
}



uptr<Galaxy> BuildRandomGalaxy(str modname) {
    uptr<Galaxy> galaxy = std::make_unique<Galaxy>();

    // Generate Systems

    // Select starting faction systems

    // Add starting facilities to faction systems

    return galaxy;
}
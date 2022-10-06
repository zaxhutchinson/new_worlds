#include"galaxy_builder.hpp"

uptr<Galaxy> BuildNewGalaxy(str modname) {
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
        vec<ID> conns = it->at("connections");
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
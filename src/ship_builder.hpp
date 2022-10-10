#pragma once

#include<fstream>

#include"zxlb.hpp"
#include"ship.hpp"


#include"json.hpp"

struct ShipSpec {
    ID ship_id;
    int min_xp;
    int max_xp;
};


class ShipBuilder {
private:

    RNG rng;

    umap<ID,nlohmann::json> shipcomp_templates;
    umap<ID,nlohmann::json> ship_templates;

    umap<ID,i64> ship_count;

public:
    ShipBuilder();

    void LoadTemplates(str modname);
    void LoadShipTemplates(str modname);
    void LoadShipCompTemplates(str modname);

    i64 GetNextShipCount(ID id);

    uptr<Ship> BuildShip(ShipSpec ss);

    Comp BuildComp(ID id);

    uptr<Engine> BuildEngine(nlohmann::json j);
    uptr<Weapon> BuildWeapon(nlohmann::json j);
    uptr<Reactor> BuildReactor(nlohmann::json j);
    uptr<Shields> BuildShields(nlohmann::json j);
    uptr<MogDrive> BuildMogDrive(nlohmann::json j);
};
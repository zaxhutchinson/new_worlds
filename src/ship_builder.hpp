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
    umap<ID,nlohmann::json> engine_templates;
    umap<ID,nlohmann::json> weapon_templates;
    umap<ID,nlohmann::json> reactor_templates;
    umap<ID,nlohmann::json> shield_templates;
    umap<ID,nlohmann::json> mogdrive_templates;
    umap<ID,nlohmann::json> ship_templates;

public:
    ShipBuilder();

    void LoadTemplates(str modname);
    void LoadShipTemplates(str modname);
    void LoadWeaponTemplates(str modname);
    void LoadEngineTemplates(str modname);
    void LoadReactorTemplates(str modname);
    void LoadShieldTemplates(str modname);
    void LoadMogDriveTemplates(str modname);

    Ship BuildShip(ShipSpec ss, RNG * rng);

    Comp BuildComp(ID id, CompType ct, nlohmann::json j);

    Comp BuildEngine(ID id);
    Comp BuildWeapon(ID id);
    Comp BuildReactor(ID id);
    Comp BuildShield(ID id);
    Comp BuildMogDrive(ID id);
};
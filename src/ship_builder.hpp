#pragma once

#include<fstream>

#include"zxlb.hpp"
#include"ship.hpp"


#include"json.hpp"

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

    Ship BuildShip(ID id);
    Engine BuildEngine(ID id);
    Weapon BuildWeapon(ID id);
    Reactor BuildReactor(ID id);
    Shields BuildShield(ID id);
    MogDrive BuildMogDrive(ID id);
};
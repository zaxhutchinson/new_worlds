#include"ship_builder.hpp"

ShipBuilder::ShipBuilder() {}

void ShipBuilder::LoadTemplates(str modname) {
    LoadShipTemplates(modname);
    LoadWeaponTemplates(modname);
    LoadEngineTemplates(modname);
    LoadReactorTemplates(modname);
    LoadShieldTemplates(modname);
    LoadMogDriveTemplates(modname);
}


void ShipBuilder::LoadShipTemplates(str modname) {
    std::ifstream ifs("mods/"+modname+"/ships.json");
    nlohmann::json j;
    ifs >> j;
    for(
        nlohmann::json::iterator it = j.begin();
        it != j.end(); it++
    ) {
        str id = it.key();
        nlohmann::json temp = it.value();
        ship_templates.emplace(id, temp);
    }
}
void ShipBuilder::LoadWeaponTemplates(str modname) {
    std::ifstream ifs("mods/"+modname+"/ship_comp_weapons.json");
    nlohmann::json j;
    ifs >> j;
    for(
        nlohmann::json::iterator it = j.begin();
        it != j.end(); it++
    ) {
        str id = it.key();
        nlohmann::json temp = it.value();
        weapon_templates.emplace(id, temp);
    }
}
void ShipBuilder::LoadEngineTemplates(str modname) {
    std::ifstream ifs("mods/"+modname+"/ship_comp_engines.json");
    nlohmann::json j;
    ifs >> j;
    for(
        nlohmann::json::iterator it = j.begin();
        it != j.end(); it++
    ) {
        str id = it.key();
        nlohmann::json temp = it.value();
        engine_templates.emplace(id, temp);
    }
}
void ShipBuilder::LoadReactorTemplates(str modname) {
    std::ifstream ifs("mods/"+modname+"/ship_comp_reactors.json");
    nlohmann::json j;
    ifs >> j;
    for(
        nlohmann::json::iterator it = j.begin();
        it != j.end(); it++
    ) {
        str id = it.key();
        nlohmann::json temp = it.value();
        reactor_templates.emplace(id, temp);
    }
}
void ShipBuilder::LoadShieldTemplates(str modname) {
    std::ifstream ifs("mods/"+modname+"/ship_comp_shields.json");
    nlohmann::json j;
    ifs >> j;
    for(
        nlohmann::json::iterator it = j.begin();
        it != j.end(); it++
    ) {
        str id = it.key();
        nlohmann::json temp = it.value();
        shield_templates.emplace(id, temp);
    }
}
void ShipBuilder::LoadMogDriveTemplates(str modname) {
    std::ifstream ifs("mods/"+modname+"/ship_comp_mogdrives.json");
    nlohmann::json j;
    ifs >> j;
    for(
        nlohmann::json::iterator it = j.begin();
        it != j.end(); it++
    ) {
        str id = it.key();
        nlohmann::json temp = it.value();
        mogdrive_templates.emplace(id, temp);
    }
}

Ship ShipBuilder::BuildShip(ID id) {

    

    nlohmann::json j = ship_templates.at(id);

    str name = j.at("name");

    Ship ship(id,name);

    vec<nlohmann::json> layer_temps = j.at("layers");
    vec<nlohmann::json> engine_temps = j.at("engines");
    vec<nlohmann::json> weapon_temps = j.at("weapons");
    vec<nlohmann::json> shield_temps = j.at("shields");
    vec<nlohmann::json> reactor_temps = j.at("reactors");
    vec<nlohmann::json> mogdrive_temps = j.at("mogdrives");

    // Build Layers
    for(
        vec<nlohmann::json>::iterator it = layer_temps.begin();
        it != layer_temps.end(); it++
    ) {
        int layer_num = it->at("layer");
        double layer_health = it->at("health");
        double layer_mass = it->at("mass");
        ship.AddShipLayer(ShipLayer(layer_num, layer_mass, layer_health));
    }

    // Add Engines
    for(
        vec<nlohmann::json>::iterator it = engine_temps.begin();
        it != engine_temps.end(); it++
    ) {
        int layer_num = it->at("layer");
        ID cid = it->at("id");
        int amt = it->at("amt");
        for(int i = 0; i < amt; i++) {
            Engine e = BuildEngine(cid);
            e.SetLayer(layer_num);
            ship.AddEngine(std::move(e));
        }
    }

    // Add Weapons
    for(
        vec<nlohmann::json>::iterator it = weapon_temps.begin();
        it != weapon_temps.end(); it++
    ) {
        int layer_num = it->at("layer");
        ID cid = it->at("id");
        int amt = it->at("amt");
        for(int i = 0; i < amt; i++) {
            Weapon w = BuildWeapon(cid);
            w.SetLayer(layer_num);
            ship.AddWeapon(std::move(w));
        }
    }

    // Add Reactor
    for(
        vec<nlohmann::json>::iterator it = reactor_temps.begin();
        it != reactor_temps.end(); it++
    ) {
        int layer_num = it->at("layer");
        ID cid = it->at("id");
        int amt = it->at("amt");
        for(int i = 0; i < amt; i++) {
            Reactor r = BuildReactor(cid);
            r.SetLayer(layer_num);
            ship.AddReactor(std::move(r));
        }
    }

    // Add Shields
    for(
        vec<nlohmann::json>::iterator it = shield_temps.begin();
        it != shield_temps.end(); it++
    ) {
        int layer_num = it->at("layer");
        ID cid = it->at("id");
        int amt = it->at("amt");
        for(int i = 0; i < amt; i++) {
            Shields s = BuildShield(cid);
            s.SetLayer(layer_num);
            ship.AddShields(std::move(s));
        }
    }

    // Add MogDrives
    for(
        vec<nlohmann::json>::iterator it = mogdrive_temps.begin();
        it != mogdrive_temps.end(); it++
    ) {
        int layer_num = it->at("layer");
        ID cid = it->at("id");
        int amt = it->at("amt");
        for(int i = 0; i < amt; i++) {
            MogDrive m = BuildMogDrive(cid);
            m.SetLayer(layer_num);
            ship.AddMogDrive(std::move(m));
        }
    }


    return ship;
}

Engine ShipBuilder::BuildEngine(ID id) {
    nlohmann::json j = engine_templates.at(id);

    str name = j.at("name");
    str desc = j.at("desc");
    int crew_size = j.at("crew_size");
    double max_health = j.at("max_health");
    double mass = j.at("mass");
    double energy_req = j.at("energy_req");
    double thrust = j.at("thrust");

    Crew crew(crew_size);

    Engine e(
        id, name, desc, crew, max_health, max_health,
        mass, energy_req, thrust
    );

    return e;

}
Weapon ShipBuilder::BuildWeapon(ID id) {
    nlohmann::json j = weapon_templates.at(id);

    str name = j.at("name");
    str desc = j.at("desc");
    int crew_size = j.at("crew_size");
    double max_health = j.at("max_health");
    double mass = j.at("mass");
    double energy_req = j.at("energy_req");
    double damage = j.at("damage");
    double target_speed = j.at("target_speed");
    double rate_of_fire = j.at("rate_of_fire");
    double range = j.at("range");
    double projectile_speed = j.at("projectile_speed");

    Crew crew(crew_size);

    Weapon w(
        id, name, desc, crew, max_health, max_health, mass, energy_req,
        damage, target_speed, rate_of_fire, range, projectile_speed
    );

    return w;
}
Reactor ShipBuilder::BuildReactor(ID id) {
    nlohmann::json j = reactor_templates.at(id);

    str name = j.at("name");
    str desc = j.at("desc");
    int crew_size = j.at("crew_size");
    double max_health = j.at("max_health");
    double mass = j.at("mass");
    double energy_req = j.at("energy_req");
    double energy_output = j.at("energy_output");
    double fuel_req = j.at("fuel_req");

    Crew crew(crew_size);

    Reactor r(
        id, name, desc, crew, max_health, max_health, mass, energy_req,
        energy_output, fuel_req
    );

    return r;
}
Shields ShipBuilder::BuildShield(ID id) {
    nlohmann::json j = shield_templates.at(id);

    str name = j.at("name");
    str desc = j.at("desc");
    int crew_size = j.at("crew_size");
    double max_health = j.at("max_health");
    double mass = j.at("mass");
    double energy_req = j.at("energy_req");
    double damage_reduction = j.at("damage_reduction");

    Crew crew(crew_size);

    Shields s(
        id, name, desc, crew, max_health, max_health, mass, energy_req,
        damage_reduction
    );

    return s;
}
MogDrive ShipBuilder::BuildMogDrive(ID id) {
    nlohmann::json j = mogdrive_templates.at(id);

    str name = j.at("name");
    str desc = j.at("desc");
    int crew_size = j.at("crew_size");
    double max_health = j.at("max_health");
    double mass = j.at("mass");
    double energy_req = j.at("energy_req");
    double carry_mass = j.at("carry_mass");
    double carry_range = j.at("carry_range");
    double charge_time = j.at("charge_time");

    Crew crew(crew_size);

    MogDrive m(
        id, name, desc, crew, max_health, max_health, mass, energy_req,
        carry_mass, carry_range, charge_time
    );

    return m;
}
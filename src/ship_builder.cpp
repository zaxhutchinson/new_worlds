#include"ship_builder.hpp"

ShipBuilder::ShipBuilder() {
    std::random_device rd;
    rng = RNG(rd());
}

void ShipBuilder::LoadTemplates(str modname) {
    LoadShipTemplates(modname);
    LoadShipCompTemplates(modname);
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
        ship_count.emplace(id,0);
    }
}
void ShipBuilder::LoadShipCompTemplates(str modname) {
    std::ifstream ifs("mods/"+modname+"/ship_comps.json");
    nlohmann::json j;
    ifs >> j;
    for(
        nlohmann::json::iterator it = j.begin();
        it != j.end(); it++
    ) {
        str id = it.key();
        nlohmann::json temp = it.value();
        shipcomp_templates.emplace(id, temp);
    }
}

i64 ShipBuilder::GetNextShipCount(ID id) {
    i64 next_id = ship_count.at(id);
    ship_count.insert_or_assign(id, next_id+1);
    return next_id;
}

uptr<Ship> ShipBuilder::BuildShip(ShipSpec ss) {

    std::uniform_int_distribution<int> xpDist(ss.min_xp, ss.max_xp);

    nlohmann::json j = ship_templates.at(ss.ship_id);

    i64 count = GetNextShipCount(ss.ship_id);
    ID id = ss.ship_id+"_"+std::to_string(count);

    str name = j.at("name");
    int ship_class  = j.at("class");

    uptr<Ship> ship = std::make_unique<Ship>(id,name,ship_class);

    vec<nlohmann::json> layer_temps = j.at("layers");
    vec<nlohmann::json> comp_temps = j.at("comps");
    // Build Layers
    for(
        vec<nlohmann::json>::iterator it = layer_temps.begin();
        it != layer_temps.end(); it++
    ) {
        int layer_num = it->at("layer");
        double layer_health = it->at("health");
        double layer_mass = it->at("mass");
        ship->AddShipLayer(ShipLayer(layer_num, layer_mass, layer_health));
    }

    // Add Comps
    for(
        vec<nlohmann::json>::iterator it = comp_temps.begin();
        it != comp_temps.end(); it++
    ) {
        int layer_num = it->at("layer");
        ID cid = it->at("id");
        int amt = it->at("amt");
        for(int i = 0; i < amt; i++) {
            Comp c = BuildComp(cid);
            c.GetCrew()->SetXP(xpDist(rng));
            c.SetLayer(layer_num);
            ship->AddComp(std::move(c));
        }
    }


    return ship;
}

Comp ShipBuilder::BuildComp(ID id) {

    nlohmann::json j = shipcomp_templates.at(id);

    str name = j.at("name");
    str desc = j.at("desc");
    vec<double> costs = j.at("costs");
    int crew_size = j.at("crew_size");
    double max_health = j.at("max_health");
    double mass = j.at("mass");
    double energy_req = j.at("energy_req");

    Crew crew(crew_size);

    Comp comp(id, name, desc, costs, crew, max_health, max_health,
        mass, energy_req);

    if(j.contains("engine")) {
        uptr<Engine> engine = BuildEngine(j.at("engine"));
        comp.SetEngine(std::move(engine));
    }

    if(j.contains("weapon")) {
        uptr<Weapon> weapon = BuildWeapon(j.at("weapon"));
        comp.SetWeapon(std::move(weapon));
    }

    if(j.contains("shields")) {
        uptr<Shields> shields = BuildShields(j.at("shields"));
        comp.SetShields(std::move(shields));
    }

    if(j.contains("reactor")) {
        uptr<Reactor> reactor = BuildReactor(j.at("reactor"));
        comp.SetReactor(std::move(reactor));
    }   

    if(j.contains("mogdrive")) {
        uptr<MogDrive> mogdrive = BuildMogDrive(j.at("mogdrive"));
        comp.SetMogDrive(std::move(mogdrive));
    }

    return comp;
}

uptr<Engine> ShipBuilder::BuildEngine(nlohmann::json j) {
    double thrust = j.at("thrust");
    uptr<Engine> engine = std::make_unique<Engine>(thrust);
    return engine;
}
uptr<Weapon> ShipBuilder::BuildWeapon(nlohmann::json j) {
    double damage = j.at("damage");
    double target_speed = j.at("target_speed");
    double rate_of_fire = j.at("rate_of_fire");
    double range = j.at("range");
    double projectile_speed = j.at("projectile_speed");
    uptr<Weapon> weapon = std::make_unique<Weapon>(
        damage, target_speed, rate_of_fire, range, projectile_speed
    );
    return weapon;
}
uptr<Reactor> ShipBuilder::BuildReactor(nlohmann::json j) {
    double energy_output = j.at("energy_output");
    double fuel_req = j.at("fuel_req");
    uptr<Reactor> reactor = std::make_unique<Reactor>(
        energy_output, fuel_req
    );
    return reactor;
}
uptr<Shields> ShipBuilder::BuildShields(nlohmann::json j) {
    double damage_reduction = j.at("damage_reduction");
    uptr<Shields> shields = std::make_unique<Shields>(
        damage_reduction
    );
    return shields;
}
uptr<MogDrive> ShipBuilder::BuildMogDrive(nlohmann::json j) {
    double carry_mass = j.at("carry_mass");
    double carry_range = j.at("carry_range");
    double charge_time = j.at("charge_time");
    uptr<MogDrive> mogdrive = std::make_unique<MogDrive>(
        carry_mass, carry_range, charge_time
    );
    return mogdrive;
}
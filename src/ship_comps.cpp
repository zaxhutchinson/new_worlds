#include"ship_comps.hpp"

Crew::Crew() {}
Crew::Crew(int _max_crew, int _xp)
    : cur_crew(_max_crew), max_crew(_max_crew), xp(_xp)
{
    crew_effectiveness = 
        (static_cast<double>(cur_crew) / static_cast<double>(max_crew)) *
        GetXPAsPercent();
}
int Crew::GetCurCrew() const { return cur_crew; }
int Crew::GetMaxCrew() const { return max_crew; }
double Crew::GetXP() const { return xp; }
double Crew::GetCrewEffectiveness() const { return crew_effectiveness; }
void Crew::SetCurCrew(int amt) {
    cur_crew = amt;
    if(cur_crew < 0) cur_crew = 0;
    else if(cur_crew > max_crew) cur_crew = max_crew;
}
void Crew::SetMaxCrew(int amt) {
    max_crew = amt;
    if(max_crew < 0) max_crew = 0;
}
void Crew::SetXP(double amt) {
    xp = amt;
}
double Crew::GetXPAsPercent() const {
    return xp / 100.0;
}
double Crew::CalculateCrewEffectiveness(RNG * rng) const {

    std::uniform_real_distribution<double> crewDist(cur_crew,max_crew);
    double able_to_fulfill_role = crewDist(*rng) / static_cast<double>(max_crew);
    return able_to_fulfill_role * GetXPAsPercent();

}









/* ENGINE
*/
Engine::Engine()
{}

Engine::Engine(
    double _thrust
)
    : thrust(_thrust)
{}
double Engine::GetThrust() const {
    return thrust;
}
void Engine::SetThrust(double amt) {
    thrust = amt;
    if(thrust < 0) thrust = 0;
}


/* WEAPON
*/
Weapon::Weapon() {}
Weapon::Weapon(
    double _damage,
    double _target_speed,
    double _rate_of_fire,
    double _range,
    double _projectile_speed
)
    : damage(_damage), target_speed(_target_speed), rate_of_fire(_rate_of_fire),
        range(_range), projectile_speed(_projectile_speed)
{}
double Weapon::GetDamage() const { return damage; }
double Weapon::GetTargetSpeed() const { return target_speed; }
double Weapon::GetRateOfFire() const { return rate_of_fire; }
double Weapon::GetRange() const { return range; }
double Weapon::GetProjectileSpeed() const { return projectile_speed; }
void Weapon::SetDamage(double amt) {
    damage = amt;
}
void Weapon::SetTargetSpeed(double amt) {
    target_speed = amt;
}
void Weapon::SetRateOfFire(double amt) {
    rate_of_fire = amt;
}
void Weapon::SetRange(double amt) {
    range = amt;
}
void Weapon::SetProjectileSpeed(double amt) { projectile_speed = amt; }

/* SHIELDS
*/

Shields::Shields() {}
Shields::Shields(
    double _damage_reduction
)
    : damage_reduction(_damage_reduction)
{}

double Shields::GetDamageReduction() const { return damage_reduction; }
void Shields::SetDamageReduction(double amt) {
    damage_reduction = amt;
    if(damage_reduction < 0) damage_reduction = 0;
}



/* MOGDRIVE
*/
MogDrive::MogDrive() {}
MogDrive::MogDrive(
    double _carry_mass,
    double _carry_range,
    double _charge_time
)
    : carry_mass(_carry_mass), carry_range(_carry_range),
        charge_time(_charge_time)
{}
double MogDrive::GetCarryMass() const { return carry_mass; }
double MogDrive::GetCarryRange() const { return carry_range; }
double MogDrive::GetChargeTime() const { return charge_time; }
void MogDrive::SetCarryMass(double amt) {
    carry_mass = amt;
}
void MogDrive::SetCarryRange(double amt) {
    carry_range = amt;
}
void MogDrive::SetChargeTime(double amt) {
    charge_time = amt;
}


/* REACTOR
*/
Reactor::Reactor() {}
Reactor::Reactor(
    double _energy_output,
    double _fuel_req
)
    : energy_output(_energy_output), fuel_req(_fuel_req)
{}
double Reactor::GetEnergyOutput() const { return energy_output; }
double Reactor::GetFuelReq() const { return fuel_req; }
void Reactor::SetEnergyOutput(double amt) {
    energy_output = amt;
}
void Reactor::SetFuelReq(double amt) {
    fuel_req = amt;
}





/* COMP
*/
Comp::Comp() 
    : id(ID()), name("NONE"), desc("NONE"),
        crew(Crew()), cur_health(0),
        max_health(0), mass(0), energy_req(0), layer(0),
        engine(nullptr), weapon(nullptr), shields(nullptr), 
        reactor(nullptr), mogdrive(nullptr)
{
    for(int i = 0; i < static_cast<int>(ResType::END); i++) {
        costs.push_back(0.0);
    }
}
Comp::Comp(
    ID _id,
    str _name,
    str _desc,
    vec<double> _costs,
    Crew _crew,
    double _cur_health,
    double _max_health,
    double _mass,
    double _energy_req
)
    : id(_id), name(_name), desc(_desc), costs(_costs),
        crew(_crew), cur_health(_cur_health),
        max_health(_max_health), mass(_mass), energy_req(_energy_req), layer(0),
        engine(nullptr), weapon(nullptr), shields(nullptr), 
        reactor(nullptr), mogdrive(nullptr)
{}
ID Comp::GetID() const { return id; }
str Comp::GetName() const { return name; }
str Comp::GetDesc() const { return desc; }
vec<double> & Comp::GetCosts() { return costs; }
double Comp::GetCost(ResType rt) const {
    return costs[static_cast<int>(rt)];
}
Crew * Comp::GetCrew() { return &crew; }
double Comp::GetCurHealth() const { return cur_health; }
double Comp::GetMaxHealth() const { return max_health; }
double Comp::GetMass() const { return mass; }
double Comp::GetEnergyReq() const { return energy_req; }
int Comp::GetLayer() const { return layer; }
void Comp::SetName(str n) { name = n; }
void Comp::SetDesc(str d) { desc = d; }
void Comp::SetCrew(Crew c) { crew = c; }
void Comp::SetCurHealth(double amt) {
    cur_health = amt;
    if(cur_health < 0) cur_health = 0;
    else if(cur_health > max_health) cur_health = max_health;
}
void Comp::SetMaxHealth(double amt) {
    max_health = amt;
    if(max_health < 0) max_health = 0;
}
void Comp::SetMass(double amt) {
    mass = amt;
    if(mass < 0) mass = 0;
}
void Comp::SetEnergyReq(double amt) {
    energy_req = amt;
}
void Comp::SetLayer(int l) {
    layer = l;
}
Engine * Comp::GetEngine() { return engine.get(); }
Weapon * Comp::GetWeapon() { return weapon.get(); }
Shields * Comp::GetShields() { return shields.get(); }
Reactor * Comp::GetReactor() { return reactor.get(); }
MogDrive * Comp::GetMogDrive() { return mogdrive.get(); }
void Comp::SetEngine(uptr<Engine> c) {
    engine = std::move(c);
}
void Comp::SetWeapon(uptr<Weapon> c) {
    weapon = std::move(c);
}
void Comp::SetShields(uptr<Shields> c) {
    shields = std::move(c);
}
void Comp::SetReactor(uptr<Reactor> c) {
    reactor = std::move(c);
}
void Comp::SetMogDrive(uptr<MogDrive> c) {
    mogdrive = std::move(c);
}
bool Comp::HasCompType(CompType ct) {
    switch(ct) {
        case CompType::Engine: return engine!=nullptr;
        case CompType::Weapon: return weapon!=nullptr;
        case CompType::Shields: return shields!=nullptr;
        case CompType::Reactor: return reactor!=nullptr;
        case CompType::MogDrive: return mogdrive!=nullptr;
        default: return false;
    }
}

// Engine Methods
double Comp::GetThrust() const {
    if(engine) {
        return crew.GetCrewEffectiveness() * engine->GetThrust();
    } else {
        return 0.0;
    }
}

// Weapon Methods
double Comp::GetDamage() const {
    if(weapon) {
        return crew.GetCrewEffectiveness() * weapon->GetDamage();
    } else {
        return 0.0;
    }
}
double Comp::GetTargetSpeed() const {
    if(weapon) {
        return crew.GetCrewEffectiveness() * weapon->GetTargetSpeed();
    } else {
        return 0.0;
    }
}
double Comp::GetRateOfFire() const {
    if(weapon) {
        return crew.GetCrewEffectiveness() * weapon->GetRateOfFire();
    } else {
        return 0.0;
    }
}
double Comp::GetRange() const {
    if(weapon) {
        return weapon->GetRange();
    } else {
        return 0.0;
    }
}
double Comp::GetProjectileSpeed() const {
    if(weapon) {
        return weapon->GetProjectileSpeed();
    } else {
        return 0.0;
    }
}

// Shields Methods
double Comp::GetDamageReduction() const {
    if(shields) {
        return crew.GetCrewEffectiveness() * shields->GetDamageReduction();
    } else {
        return 0.0;
    }
}

// Reactor Methods
double Comp::GetEnergyOutput() const {
    if(reactor) {
        return crew.GetCrewEffectiveness() * reactor->GetEnergyOutput();
    } else {
        return 0.0;
    }
}
double Comp::GetFuelReq() const {
    if(reactor) {
        return crew.GetCrewEffectiveness() * reactor->GetFuelReq();
    } else {
        return 0.0;
    }
}

// MogDrive
double Comp::GetCarryMass() const {
    if(mogdrive) {
        return crew.GetCrewEffectiveness() * mogdrive->GetCarryMass();
    } else {
        return 0.0;
    }
}
double Comp::GetCarryRange() const {
    if(mogdrive) {
        return crew.GetCrewEffectiveness() * mogdrive->GetCarryRange();
    } else {
        return 0.0;
    }
}
double Comp::GetChargeTime() const {
    if(mogdrive) {
        return crew.GetCrewEffectiveness() * mogdrive->GetChargeTime();
    } else {
        return 0.0;
    }
}
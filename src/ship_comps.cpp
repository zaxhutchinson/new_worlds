#include"ship_comps.hpp"

Crew::Crew() {}
Crew::Crew(int _max_crew, int _xp)
    : cur_crew(_max_crew), max_crew(_max_crew), xp(_xp)
{}
int Crew::GetCurCrew() const { return cur_crew; }
int Crew::GetMaxCrew() const { return max_crew; }
double Crew::GetXP() const { return xp; }
void Crew::SetCurCrew(int amt) {
    cur_crew = amt;
    if(cur_crew < 0) cur_crew = 0;
    else if(cur_crew > max_crew) cur_crew = max_crew;
}
void Crew::SetMaxCrew(int amt) {
    max_crew = max_crew;
    if(max_crew < 0) max_crew = 0;
}
void Crew::SetXP(double amt) {
    xp = amt;
}




/* COMP
*/
Comp::Comp() {}
Comp::Comp(
    ID _id,
    str _name,
    str _desc,
    Crew _crew,
    double _cur_health,
    double _max_health,
    double _mass,
    double _energy_req
)
    : id(_id), name(_name), desc(_desc), crew(_crew), cur_health(_cur_health),
    max_health(_max_health), mass(_mass), energy_req(_energy_req), layer(0)
{}

ID Comp::GetID() const { return id; }
str Comp::GetName() const { return name; }
str Comp::GetDesc() const { return desc; }
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


/* ENGINE
*/
Engine::Engine()
    : Comp()
{}

Engine::Engine(
    ID _id,
    str _name,
    str _desc,
    Crew _crew,
    double _cur_health,
    double _max_health,
    double _mass,
    double _energy_req,
    double _thrust
)
    : Comp(_id, _name, _desc, _crew, _cur_health, _max_health, _mass, _energy_req),
        thrust(_thrust)
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
    ID _id,
    str _name,
    str _desc,
    Crew _crew,
    double _cur_health,
    double _max_health,
    double _mass,
    double _energy_req,
    double _damage,
    double _target_speed,
    double _rate_of_fire,
    double _range,
    double _projectile_speed
)
    : Comp(_id, _name, _desc, _crew, _cur_health, _max_health, _mass, _energy_req),
        damage(_damage), target_speed(_target_speed), rate_of_fire(_rate_of_fire),
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
    ID _id,
    str _name,
    str _desc,
    Crew _crew,
    double _cur_health,
    double _max_health,
    double _mass,
    double _energy_req,
    double _damage_reduction
)
    : Comp(_id, _name, _desc, _crew, _cur_health, _max_health, _mass, _energy_req),
        damage_reduction(_damage_reduction)
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
    ID _id,
    str _name,
    str _desc,
    Crew _crew,
    double _cur_health,
    double _max_health,
    double _mass,
    double _energy_req,
    double _carry_mass,
    double _carry_range,
    double _charge_time
)
    : Comp(_id, _name, _desc, _crew, _cur_health, _max_health, _mass, _energy_req),
        carry_mass(_carry_mass), carry_range(_carry_range),
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
    ID _id,
    str _name,
    str _desc,
    Crew _crew,
    double _cur_health,
    double _max_health,
    double _mass,
    double _energy_req,
    double _energy_output,
    double _fuel_req
)
    : Comp(_id, _name, _desc, _crew, _cur_health, _max_health, _mass, _energy_req),
        energy_output(_energy_output), fuel_req(_fuel_req)
{}
double Reactor::GetEnergyOutput() const { return energy_output; }
double Reactor::GetFuelReq() const { return fuel_req; }
void Reactor::SetEnergyOutput(double amt) {
    energy_output = amt;
}
void Reactor::SetFuelReq(double amt) {
    fuel_req = amt;
}
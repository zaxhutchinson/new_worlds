#pragma once

#include"zxlb.hpp"

class Crew {
private:
    int cur_crew;
    int max_crew;
    double xp;
    double crew_effectiveness;
public:
    Crew();
    Crew(int _max_crew, int _xp=75);
    Crew(const Crew & c) = default;
    Crew(Crew && c) = default;
    Crew& operator=(const Crew & c) = default;
    Crew& operator=(Crew && c) = default;
    int GetCurCrew() const;
    int GetMaxCrew() const;
    double GetXP() const;
    double GetCrewEffectiveness() const;
    void SetCurCrew(int amt);
    void SetMaxCrew(int amt);
    void SetXP(double amt);

    double GetXPAsPercent() const;
    double CalculateCrewEffectiveness(RNG * rng) const;
};


enum class CompType {
    Weapon,
    Engine,
    Shields,
    Reactor,
    MogDrive,

    END
};


/* Engine Comp Class:
    Engines provide thrust. Thrust is the opposite of mass. 1 thrust will
    move 1 mass 1 unit during 1 turn. Thrust and engines only work in
    sublight situations, like combat. They are not used to move ships between
    systems.
*/
class Engine {
private:
    double thrust;
public:
    Engine();
    Engine(
        double _thrust
    );
    Engine(const Engine & e) = default;
    Engine(Engine && e) = default;
    Engine& operator=(const Engine & e) = default;
    Engine& operator=(Engine && e) = default;
    double GetThrust() const;
    void SetThrust(double amt);
};


/* Weapon Comp Class
    A weapon is the primary means of destruction.
        - damage is the maximum damage the weapon can inflict when 
            hitting a target.
        - target_speed is the speed at which the weapon can lock on or
            track a target. This is used in to-hit calculations and is
            directly comparable to the speed of the target.
        - rate_of_fire is how many times turns before it can fire again.
        - range is the distance within which it does not suffer accuracy
            penalties.
        - projectile_speed is how many kms the projectile travels in a turn.
*/
class Weapon {
private:
    double damage;
    double target_speed;
    double rate_of_fire;
    double range;
    double projectile_speed;
public:
    Weapon();
    Weapon(
        double _damage,
        double _target_speed,
        double _rate_of_fire,
        double _range,
        double _projectile_speed
    );
    Weapon(const Weapon & w) = default;
    Weapon(Weapon && w) = default;
    Weapon& operator=(const Weapon & w) = default;
    Weapon& operator=(Weapon && w) = default;
    double GetDamage() const;
    double GetTargetSpeed() const;
    double GetRateOfFire() const;
    double GetRange() const;
    double GetProjectileSpeed() const;
    void SetDamage(double amt);
    void SetTargetSpeed(double amt);
    void SetRateOfFire(double amt);
    void SetRange(double amt);
    void SetProjectileSpeed(double amt);

};

/* Shield Comp Class
    Shields are simple damage reducers. They do not diminish unless damaged
    or destroyed. They reduce the potential damage a projectile can inflict.
    Leaky, in other words.
*/

class Shields {
private:
    double damage_reduction;
public:
    Shields();
    Shields(
        double _damage_reduction
    );
    Shields(const Shields & s) = default;
    Shields(Shields && s) = default;
    Shields& operator=(const Shields & s) = default;
    Shields& operator=(Shields && s) = default;
    double GetDamageReduction() const;
    void SetDamageReduction(double amt);
};

/* MogDrive Comp Class
    MogDrives are how ships move between systems. It is a jump-like drive.
        - carry_mass is how much mass the drive can move at once. 
            A MogDrive can move multiple ships at once. So it works like 
            a field.
        - carry_range is how far it can move its carry mass.
        - charge_time. A MogDrive cannot work immediately. It takes this many
            turns to charge up before a jump.

        A ship with a mog drive cannot jump beyond its carry range. It
        cannot carry more than its carry mass. And it cannot jump before its
        charge time.

        Example: if a mog drive ship wanted to jump a fleet of 10,000 mass
            from one system to another, provided it was within range, and
            its carry mass was 3,000. It would take 3.5 * charge_time to jump
            the whole fleet if the mog drive ship remains with the fleet at the
            end.
        
*/
class MogDrive {
private:
    double carry_mass;
    double carry_range;
    double charge_time;
public:
    MogDrive();
    MogDrive(
        double _carry_mass,
        double _carry_range,
        double _charge_time
    );
    MogDrive(const MogDrive & m) = default;
    MogDrive(MogDrive && m) = default;
    MogDrive& operator=(const MogDrive & m) = default;
    MogDrive& operator=(MogDrive && m) = default;
    double GetCarryMass() const;
    double GetCarryRange() const;
    double GetChargeTime() const;
    void SetCarryMass(double amt);
    void SetCarryRange(double amt);
    void SetChargeTime(double amt);
};

/* Reactor Comp Class
*/
class Reactor {
private:
    double energy_output;
    double fuel_req;
public:
    Reactor();
    Reactor(
        double _energy_output,
        double _fuel_req
    );
    Reactor(const Reactor & r) = default;
    Reactor(Reactor && r) = default;
    Reactor& operator=(const Reactor & r) = default;
    Reactor& operator=(Reactor && r) = default;
    double GetEnergyOutput() const;
    double GetFuelReq() const;
    void SetEnergyOutput(double amt);
    void SetFuelReq(double amt);
};




class Comp {
protected:
    ID id;
    CompType type;
    str name;
    str desc;
    Crew crew;
    double cur_health;
    double max_health;
    double mass;
    double energy_req;
    int layer;
    uptr<Engine> engine;
    uptr<Weapon> weapon;
    uptr<Shields> shields;
    uptr<Reactor> reactor;
    uptr<MogDrive> mogdrive;
public:
    Comp();
    Comp(
        ID _id,
        CompType _type,
        str _name,
        str _desc,
        Crew _crew,
        double _cur_health,
        double _max_health,
        double _mass,
        double _energy_req
    );
    Comp(const Comp & c) = default;
    Comp(Comp && c) = default;
    Comp& operator=(const Comp & c) = default;
    Comp& operator=(Comp && c) = default;
    ID GetID() const;
    CompType GetCompType() const;
    str GetName() const;
    str GetDesc() const;
    Crew * GetCrew();
    double GetCurHealth() const;
    double GetMaxHealth() const;
    double GetMass() const;
    double GetEnergyReq() const;
    int GetLayer() const;
    void SetName(str n);
    void SetDesc(str d);
    void SetCrew(Crew c);
    void SetCurHealth(double amt);
    void SetMaxHealth(double amt);
    void SetMass(double amt);
    void SetEnergyReq(double amt);
    void SetLayer(int l);
    Engine * GetEngine();
    Weapon * GetWeapon();
    Shields * GetShields();
    Reactor * GetReactor();
    MogDrive * GetMogDrive();
    void SetEngine(uptr<Engine> c);
    void SetWeapon(uptr<Weapon> c);
    void SetShields(uptr<Shields> c);
    void SetReactor(uptr<Reactor> c);
    void SetMogDrive(uptr<MogDrive> c);

    // ENGINE METHODS
    double GetThrust() const;

    // WEAPON METHODS
    double GetDamage() const;
    double GetTargetSpeed() const;
    double GetRateOfFire() const;
    double GetRange() const;
    double GetProjectileSpeed() const;

    // SHIELDS METHODS
    double GetDamageReduction() const;

    // REACTOR METHODS
    double GetEnergyOutput() const;
    double GetFuelReq() const;

    // MOGDRIVE METHODS
    double GetCarryMass() const;
    double GetCarryRange() const;
    double GetChargeTime() const;

};


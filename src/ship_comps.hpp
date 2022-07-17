#pragma once

#include"magic_enum.hpp"

#include"zxlb.hpp"
#include"vec3i.hpp"
#include"vec2i.hpp"
#include"sole.hpp"

/* --------------------------------------------------------------------------
    STeamType
-------------------------------------------------------------------------- */

enum class SJobType {
    Command,
    Medic,
    Repair,
    Engineer,
    Gunner,
    Flight,
    Security,
    Science,
    Quartermaster,
    Steward,
    Inactive,
    Operator,
    Navigator,
    None,

    END
};



/* --------------------------------------------------------------------------
    SCompType
-------------------------------------------------------------------------- */

enum class SSysType {
    Bridge,
    CargoHold,
    Cloak,
    CounterMeasure,
    FTLEngine,
    Hangar,
    Hull,
    Medbay,
    Quarters,
    Reactor,
    RepairStation,
    Scanner,
    SecStation,
    Shield,
    STLEngine,
    TroopHold,
    Weapon,

    END
};

/* --------------------------------------------------------------------------
    SCompartment
-------------------------------------------------------------------------- */

class SCompartment {
private:
    Vec3i loc;
    i64 max_system_health;
    i64 cur_system_health;
    i64 max_structural_health;
    i64 cur_structural_health;
public:
    SCompartment();
    SCompartment(
        Vec3i _loc,
        i64 _max_system_health,
        i64 _max_structural_health
    );
    SCompartment(
        Vec3i _loc,
        i64 _max_system_health,
        i64 _cur_system_health,
        i64 _max_structural_health,
        i64 _cur_structural_health
    );

    i64 GetMaxSystemHealth();
    i64 GetCurSystemHealth();
    i64 GetMaxStructuralHealth();
    i64 GetCurStructuralHealth();
    void SetMaxSystemHealth(i64 h);
    void SetCurSystemHealth(i64 h);
    void SetMaxStructuralHealth(i64 h);
    void SetCurStructuralHealth(i64 h);
    void ChangeSystemHealth(i64 amt);
    void ChangeStructuralHealth(i64 amt);
};

/* --------------------------------------------------------------------------
    SCrew
-------------------------------------------------------------------------- */

class SCrew {
private:
    str name;
    // 100-80: Minor, 79-0: Major, < 0 Critical.
    // Above 80, no penalties.
    // From 79-0, still able but reduced: health / 80.
    // Below 0: unconscious. -100 = dead.
    i16 health;
    // Stamina: 100 to 0
    //  Stamina represents energy replenished by rest.
    //  Each hour on watch costs 5 stamina.
    //  Below 50: ability is reduced by stamina / 50.
    //  A crewman can do 10 hours without reduction.
    //  A crewman restores 5 stamina for each hour
    //      they can sleep in quarters. Without quarters
    //      they regain 3.
    i16 stamina;
    // Morale: 100 to 0
    //  Certain events trigger morale loss: deaths in the team, system.
    //  Loss happens by rand(0, ceil(morale/10)).
    //  Loss is regained slowly. For each off-duty watch where stamina
    //      equals 100 and health > 100, crewman have a:
    //      1 / 3 chance to gain:
    //      rand(0, ceil(morale/10)) morale.
    i16 morale;
    // Wounds reduce health by the wound amt every 5 minutes.
    i16 wounds; 
    SJobType job;
    // 0 to 100
    i16 xp;
    bool active;
public:
    SCrew();
    SCrew(
        str _name,
        SJobType _job
    );

    str GetName();
    i16 GetHealth();
    i16 GetStamina();
    i16 GetMorale();
    i16 GetWounds();
    SJobType GetSTeamType();
    i16 GetXP();
    bool GetActive();

    void SetName(str _name);
    void SetHealth(i16 v);
    void ChangeHealth(i16 v);
    void SetStamina(i16 v);
    void ChangeStamina(i16 v);
    void SetMorale(i16 v);
    void ChangeMorale(i16 v);
    void SetWounds(i16 v);
    void ChangeWounds(i16 v);
    void SetSJobType(SJobType t);
    void SetXP(i16 v);
    void ChangeXP(i16 v);
    void SetActive(bool v);

    i16 GetReadiness();
    void DecreaseMorale(RNG & rng);
    void IncreaseMorale(RNG & rng);
    void ApplyWoundsToHealth();
    
};
/* --------------------------------------------------------------------------
    STeam
-------------------------------------------------------------------------- */

class STeam {
private:
    i64 id;
    sizet crew_size;
    vec<SCrew*> crew;
    SJobType job;
    SCompartment* comp;
    bool onduty;
public:
    STeam();
    STeam(
        i64 _id,
        sizet _crew_size,
        SJobType _job
    );

    i64 GetID() const;
    sizet GetCrewSize() const;
    vec<SCrew*> GetCrew();
    SJobType GetTeamType() const;
    SCompartment* GetCompartment() const;
    bool GetOnduty() const;

    void SetCrewSize(sizet _crew_size);
    void AddCrew(SCrew * crewman);
    void RemoveCrew(sizet index);
    void RemoveAllCrew();
    void SetSTeamType(SJobType type);
    void SetCompartment(SCompartment * c);
    void SetOnduty(bool b);

    sizet GetNumAbleCrew();
    sizet GetNumDisableCrew();
    sizet GetNumMissingCrew();
    i64 GetAverageHealth();
    i64 GetAverageStamina();
    i64 GetAverageMorale();
    i64 GetAverageReadiness();
    i64 GetAverageXP();
};

/* --------------------------------------------------------------------------
    SSys
-------------------------------------------------------------------------- */
class SSys {
protected:
    str name;
    SSysType type;
    i64 structural_health;      // structural health of each compartment.
    i64 system_health;          // system health of each compartment.
    i64 energy_req;             // how much energy it needs from the reactor.
    Vec3i room_location;
    Vec2i room_shape;           // The 2d shape of the room.
    vec<SCompartment*> compartments;
    i64 num_crew;              // teams this sys should have.
    SJobType job_type;        // the type of teams this sys needs.
    vec<SCrew*> crew;          // the actual teams.

    i64 cur_avg_morale_of_all_crew;
    i64 cur_avg_health_of_all_crew;
    i64 cur_avg_stamina_of_all_crew;
    i64 cur_avg_readiness_of_all_crew;
    i64 cur_avg_xp_of_all_crew;
    double crew_stats_scalar_on_operations;

public:
    SSys();
    virtual ~SSys() = default;

    void Init_SSys(
        str _name,
        SSysType _type, 
        i64 _structural_health,
        i64 _system_health,
        i64 _energy_req,
        i64 _num_crew,
        SJobType _team_type
    );

    str GetName() const;
    SSysType GetSCompType() const;
    i64 GetStructuralHealth() const;
    i64 GetSystemHealth() const;
    i64 GetEnergyReq() const;
    Vec3i GetRoomLocation() const;
    Vec2i GetRoomShape() const;
    vec<SCompartment*>& GetCompartments();
    i64 GetNumCrew() const;
    SJobType GetJobType() const;
    vec<SCrew*>& GetCrew();

    void SetStructuralHealth(i64 _structural_health);
    void SetSystemHealth(i64 _system_health);
    void SetEnergyReq(i64 _energy_req);
    void SetRoomLocation(Vec3i _room_location);
    void SetRoomShape(Vec2i _room_shape);
    void SetNumCrew(i64 _num_crew);
    void AddCompartment(SCompartment * comp);
    SCompartment * GetRandomCompartment(RNG & rng);
    void RemoveCompartments();

    void AddCrew(SCrew * _crew);
    void RemoveCrew(sizet index);
    void RemoveAllCrew();
    i64 GetCrewDeficit();

    /* Updates the temp variables associated with team statistics. 
        This gets called each turn so that every time these aggregate
        stats are recomputed.
    */
    void UpdateCrewStats();

    i64 CurAvgReadinessOfAllCrew();
    i64 CurAvgHealthOfAllCrew();
    i64 CurAvgMoraleOfAllCrew();
    i64 CurAvgStaminaOfAllCrew();
    i64 CurAvgXPOfAllCrew();
    

    /* The team stats based scalar which impacts the operation of this system.
    */
    double Effective_GetCrewScalarOnOperations();

    /*----------------------------------------------------------------------*/
    // RepairStation
    virtual double Effective_RepairRate();

    // SecStation
    virtual double Effective_SecurityDefense();

    // Shields
    virtual i64 GetMaxShields();
    virtual i64 GetCurShields();
    virtual i64 GetRegenShields();
    virtual void SetMaxShields(i64 _max_shields);
    virtual void SetCurShields(i64 _cur_shields);
    virtual void SetRegenShields(i64 _regen_shields);
    virtual void RegenShields();
    virtual void ResetShields();

    virtual double Effective_ShieldRegenRate();
    virtual void Effective_RegenShields();

    // Reactor
    virtual i64 GetEnergyProd();
    virtual void SetEnergyProd(i64 _energy_prod);

    virtual double Effective_EnergyProduction();

    // Weapon
    virtual i64 GetDmgStructure();
    virtual i64 GetDmgShields();
    virtual i64 GetDmgSystems();
    virtual i64 GetWeaponRange();
    virtual i64 GetTargetSize();
    virtual i64 GetTargetRate();
    virtual i64 GetRateOfFire();
    virtual void SetDmgStructure(i64 _dmg_structure);
    virtual void SetDmgShields(i64 _dmg_shields);
    virtual void SetDmgSystems(i64 _dmg_systems);
    virtual void SetWeaponRange(i64 _weapon_range);
    virtual void SetTargetSize(i64 _target_size);
    virtual void SetTargetRate(i64 _target_rate);
    virtual void SetRateOfFire(i64 _rate_of_fire);

    virtual double Effective_WeaponRange();
    virtual double Effective_TargetRate();
    virtual double Effective_ToHitProbOfSize(i64 size_in_comps);

    // STL Engine
    virtual i64 GetThrust();
    virtual void SetThrust(i64 _thrust);

    virtual double Effective_STLEngineThrust();

    // FTL Engine
    virtual i64 GetJumpDistance();
    virtual i64 GetChargeRate();
    virtual void SetDistance(i64 _jump_distance);
    virtual void SetChargeRate(i64 _charge_rate);

    virtual double Effective_JumpDistance();
    virtual double Effective_ChargeRate();

    // Bridge
    virtual double Effective_BridgeCrewInitiative();

    // Medbay
    virtual i64 GetBeds();
    virtual i64 GetHealingRate();
    virtual void SetBeds(i64 _beds);
    virtual void SetHealingRate(i64 _healing_rate);
    virtual vec<SCrew*> * GetPatients();
    virtual void AddPatient(SCrew * c);
    virtual void RemovePatient(sizet index);
    virtual void RemoveAllPatients();

    virtual double Effective_HealingRate();

    // CargoHold
    virtual i64 GetStorage();
    virtual void SetStorage(i64 _storage);

    virtual double Effective_StorageSpace();

    // TroopHold
    virtual i64 GetTroops();
    virtual void SetTroops(i64 _troops);

    virtual double Effective_TroopCapacity();

    // Hangar
    virtual i64 GetHangarStorageInComps();
    virtual void SetHangarStorageInComps(i64 _hangar_storage);

    virtual double Effective_HangarStorageInComps();

    // Quarters
    virtual i64 GetNumCrewBeds();
    virtual double GetMoraleIncreaseProb();
    virtual i64 GetStaminaIncreasePerHour();
    virtual void SetNumCrewBeds(i64 _num_crew_beds);
    virtual void SetMoraleIncreaseProb(double _morale_increase_prob);
    virtual void SetStaminaIncreasePerHour(i64 _stamina_increase_per_hour);

    virtual double Effective_MoraleIncreaseProb();
    virtual double Effective_StaminaIncreasePerHour();

    // Scanner
    virtual i64 GetScanDistance();
    virtual i64 GetScanPenetration();
    virtual void SetScanDistance(i64 _scan_distance);
    virtual void SetScanPenetration(i64 _scan_penetration);

    virtual double Effective_ScanDistance();
    virtual double Effective_ScanPenetration();
};


/* --------------------------------------------------------------------------
    SRepairStation
-------------------------------------------------------------------------- */

class SRepairStation : public SSys {
protected:

public:
    SRepairStation();
    void Init_SRepairStation();

    double Effective_RepairRate() override;
};

/* --------------------------------------------------------------------------
    SSecStation
-------------------------------------------------------------------------- */

class SSecStation : public SSys {
protected:

public:
    SSecStation();
    void Init_SSecStation();

    double Effective_SecurityDefense() override;
};

/* --------------------------------------------------------------------------
    SShield
-------------------------------------------------------------------------- */

class SShield : public SSys {
protected:
    i64 max_shield;
    i64 cur_shield;
    i64 regen_shield;
public:
    SShield();
    void Init_SShield(
        i64 _max_shield,
        i64 _regen_shield
    );

    i64 GetMaxShields() override;
    i64 GetCurShields() override;
    i64 GetRegenShields() override;
    void SetMaxShields(i64 _max_shields) override;
    void SetCurShields(i64 _cur_shields) override;
    void SetRegenShields(i64 _regen_shields) override;
    void RegenShields() override;
    void ResetShields() override;

    double Effective_ShieldRegenRate() override;
    void Effective_RegenShields() override;
};

/* --------------------------------------------------------------------------
    SReactor
-------------------------------------------------------------------------- */

class SReactor : public SSys {
protected:
    i64 energy_prod;
public:
    SReactor();
    void Init_SReactor(
        i64 _energy_prod
    );
    
    i64 GetEnergyProd() override;
    void SetEnergyProd(i64 _energy_prod) override;

    double Effective_EnergyProduction() override;
};

/* --------------------------------------------------------------------------
    SWeapon
-------------------------------------------------------------------------- */

class SWeapon : public SSys {
protected:
    i64 dmg_structure;
    i64 dmg_shields;
    i64 dmg_systems;
    i64 weapon_range;
    i64 target_size;    // center of RBF
    i64 target_rate;    // b of RBF
    i64 rate_of_fire;
public:
    SWeapon();
    void Init_SWeapon(
        i64 _dmg_structure,
        i64 _dmg_shields,
        i64 _dmg_systems,
        i64 _weapon_range,
        i64 _target_size,
        i64 _target_rate,
        i64 _rate_of_fire
    );

    i64 GetDmgStructure() override;
    i64 GetDmgShields() override;
    i64 GetDmgSystems() override;
    i64 GetWeaponRange() override;
    i64 GetTargetSize() override;
    i64 GetTargetRate() override;
    i64 GetRateOfFire() override;
    void SetDmgStructure(i64 _dmg_structure) override;
    void SetDmgShields(i64 _dmg_shields) override;
    void SetDmgSystems(i64 _dmg_systems) override;
    void SetWeaponRange(i64 _weapon_range) override;
    void SetTargetSize(i64 _target_size) override;
    void SetTargetRate(i64 _target_rate) override;
    void SetRateOfFire(i64 _rate_of_fire) override;

    double Effective_WeaponRange() override;
    double Effective_TargetRate() override;
    double Effective_ToHitProbOfSize(i64 size_in_comps) override;
};

/* --------------------------------------------------------------------------
    SSTLEngine
-------------------------------------------------------------------------- */

class SSTLEngine : public SSys {
protected:
    i64 thrust;
public:
    SSTLEngine();
    void Init_SEngine(
        i64 _thrust
    );

    i64 GetThrust() override;
    void SetThrust(i64 _thrust) override;

    double Effective_STLEngineThrust() override;
};

/* --------------------------------------------------------------------------
    SFTLEngine
-------------------------------------------------------------------------- */

class SFTLEngine : public SSys {
protected:
    i64 jump_distance;
    i64 charge_rate;    // comps per hour.
public:
    SFTLEngine();
    void Init_SFTLEngine(
        i64 _jump_distance,
        i64 _charge_rate
    );

    i64 GetJumpDistance() override;
    i64 GetChargeRate() override;
    void SetDistance(i64 _jump_distance) override;
    void SetChargeRate(i64 _charge_rate) override;

    double Effective_JumpDistance() override;
    double Effective_ChargeRate() override;
};

/* --------------------------------------------------------------------------
    SBridge
-------------------------------------------------------------------------- */

// Bridge health determines initiative in battle.
class SBridge : public SSys {
protected:

public:
    SBridge();
    void Init_SBridge();

    double Effective_BridgeCrewInitiative() override;
};

/* --------------------------------------------------------------------------
    SMedbay
-------------------------------------------------------------------------- */

class SMedbay : public SSys {
protected:
    i64 beds;
    i64 healing_rate;       // same as wounds, rate of health restore.
    vec<SCrew*> patients;
public:
    SMedbay();
    void Init_SMedbay(
        i64 _beds,
        i64 _healing_rate
    );

    i64 GetBeds() override;
    i64 GetHealingRate() override;
    void SetBeds(i64 _beds) override;
    void SetHealingRate(i64 _healing_rate) override;
    vec<SCrew*> * GetPatients() override;
    void AddPatient(SCrew * c) override;
    void RemovePatient(sizet index) override;
    void RemoveAllPatients() override;

    double Effective_HealingRate() override;
};

/* --------------------------------------------------------------------------
    SCargoHold
-------------------------------------------------------------------------- */

class SCargoHold : public SSys {
protected:
    i64 storage;   // Amount of cargo
public:
    SCargoHold();
    void Init_SCargoHold(
        i64 _storage
    );

    i64 GetStorage() override;
    void SetStorage(i64 _storage) override;

    double Effective_StorageSpace() override;
};

/* --------------------------------------------------------------------------
    STroopHold
-------------------------------------------------------------------------- */

class STroopHold : public SSys {
protected:
    i64 troops;   // Number of troopers
public:
    STroopHold();
    void Init_STroopHold(
        i64 _troops
    );

    i64 GetTroops() override;
    void SetTroops(i64 _troops) override;

    double Effective_TroopCapacity() override;
};

/* --------------------------------------------------------------------------
    SHangar
-------------------------------------------------------------------------- */

class SHangar : public SSys {
protected:
    i64 hangar_storage;   // size of ships in comps.
public:
    SHangar();
    void Init_SHangar(
        i64 _hangar_storage
    );

    i64 GetHangarStorageInComps() override;
    void SetHangarStorageInComps(i64 _hangar_storage) override;

    double Effective_HangarStorageInComps() override;
};

/* --------------------------------------------------------------------------
    SQuarters
-------------------------------------------------------------------------- */

class SQuarters : public SSys {
protected:
    i64 num_crew_beds;
    double morale_increase_prob;
    i64 stamina_increase_per_hour;
public:
    SQuarters();
    void Init_SQuarters(
        i64 _num_crew_beds,
        double _morale_increase_prob,
        i64 _stamina_increase_per_hour
    );

    i64 GetNumCrewBeds() override;
    double GetMoraleIncreaseProb() override;
    i64 GetStaminaIncreasePerHour() override;
    void SetNumCrewBeds(i64 _num_crew_beds) override;
    void SetMoraleIncreaseProb(double _morale_increase_prob) override;
    void SetStaminaIncreasePerHour(i64 _stamina_increase_per_hour) override;

    double Effective_MoraleIncreaseProb() override;
    double Effective_StaminaIncreasePerHour() override;
};

/* --------------------------------------------------------------------------
    SScanner
-------------------------------------------------------------------------- */

class SScanner : public SSys {
protected:
    i64 scan_distance;
    i64 scan_penetration;
public:
    SScanner();
    void Init_SScanner(
        i64 _scan_distance,
        i64 _scan_penetration
    );

    i64 GetScanDistance() override;
    i64 GetScanPenetration() override;
    void SetScanDistance(i64 _scan_distance) override;
    void SetScanPenetration(i64 _scan_penetration) override;

    double Effective_ScanDistance() override;
    double Effective_ScanPenetration() override;

};

/* --------------------------------------------------------------------------
    SHull
-------------------------------------------------------------------------- */

class SHull : public SSys {
protected:

public:
    SHull();
    void Init_SHull();
};

/* --------------------------------------------------------------------------
    SCloak
-------------------------------------------------------------------------- */

class SCloak : public SSys {
protected:
    i64 cloak_level;

public:
    SCloak();
    void Init_SCloak(
        i64 _cloak_level
    );

    i64 GetCloakLevel();
    void SetCloakLevel(i64 _cloak_level);
};

/* --------------------------------------------------------------------------
    SCounterMeasure
-------------------------------------------------------------------------- */

class SCounterMeasure : public SSys {
    protected:
        double accuracy_reduction;
    public:
        SCounterMeasure();
        void Init_SCounterMeasure(
            double _accuracy_reduction
        );

        double GetAccuracyReduction();
        void SetAccuracyReduction(
            double _accuracy_reduction
        );
};
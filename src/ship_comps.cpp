#include"ship_comps.hpp"

/* --------------------------------------------------------------------------
    SCompartment
-------------------------------------------------------------------------- */
SCompartment::SCompartment()
    : loc(Vec3i()), max_system_health(0), cur_system_health(0),
    max_structural_health(0), cur_structural_health(0)
{}

SCompartment::SCompartment(
    Vec3i _loc,
    i64 _max_system_health,
    i64 _max_structural_health
)   : loc(_loc), max_system_health(_max_system_health),
    max_structural_health(_max_structural_health)
{}

SCompartment::SCompartment(
    Vec3i _loc,
    i64 _max_system_health,
    i64 _cur_system_health,
    i64 _max_structural_health,
    i64 _cur_structural_health
)   : loc(_loc), max_system_health(_max_system_health),
    cur_system_health(_cur_system_health), max_structural_health(_max_structural_health),
    cur_structural_health(_cur_structural_health)
{}

i64 SCompartment::GetMaxSystemHealth() {return max_system_health;}
i64 SCompartment::GetCurSystemHealth() {return cur_system_health;}
i64 SCompartment::GetMaxStructuralHealth() {return max_structural_health;}
i64 SCompartment::GetCurStructuralHealth() {return cur_structural_health;}
void SCompartment::SetMaxSystemHealth(i64 h) {max_system_health=h;}
void SCompartment::SetCurSystemHealth(i64 h) {
    cur_system_health=h;
    if(cur_system_health<0) cur_system_health=0;
    else if(cur_system_health>max_system_health) cur_system_health=max_system_health;
}
void SCompartment::SetMaxStructuralHealth(i64 h) {max_structural_health=h;}
void SCompartment::SetCurStructuralHealth(i64 h) {
    cur_structural_health = h;
    if(cur_structural_health < 0) cur_structural_health=0;
    else if(cur_structural_health > max_structural_health) {
        cur_structural_health = max_structural_health;
    }
}
void SCompartment::ChangeSystemHealth(i64 amt) {
    SetCurSystemHealth(cur_system_health+amt);
}
void SCompartment::ChangeStructuralHealth(i64 amt) {
    SetCurStructuralHealth(cur_structural_health+amt);
}


/* --------------------------------------------------------------------------
    SCrew
-------------------------------------------------------------------------- */
SCrew::SCrew()
    :name("NONAME"), health(100), stamina(100), morale(100), 
        wounds(0), job(SJobType::Inactive), xp(0), active(true)
{}
SCrew::SCrew(
    str _name,
    SJobType _job
)   :name(_name), health(INT8_MAX), stamina(100), morale(100), 
        wounds(0), job(_job), xp(0), active(true)
{}

str SCrew::GetName() { return name; }
i16 SCrew::GetHealth() { return health; }
i16 SCrew::GetStamina() { return stamina; }
i16 SCrew::GetMorale() { return morale; }
i16 SCrew::GetWounds() { return wounds; }
SJobType SCrew::GetSTeamType() { return job; }
i16 SCrew::GetXP() { return xp; }
bool SCrew::GetActive() { return active; }

void SCrew::SetName(str _name) { name = _name; }
void SCrew::SetHealth(i16 v) { 
    health = v;
    if(health < -100) health=-100;
    else if(health > 100) health = 100;
}
void SCrew::ChangeHealth(i16 v) {
    SetHealth(health+v);
}
void SCrew::SetStamina(i16 v) {
    stamina = v;
    if(stamina < 0) stamina=0;
    else if(stamina > 100) stamina = 100;
}
void SCrew::ChangeStamina(i16 v) {
    SetStamina(stamina+v);
}
void SCrew::SetMorale(i16 v) {
    morale = v;
    if(morale < 0) morale = 0;
    else if(morale > 100) morale = 100;
}
void SCrew::ChangeMorale(i16 v) {
    SetMorale(morale+v);
}
void SCrew::SetWounds(i16 v) {
    wounds = v;
    if(wounds < 0) wounds = 0;
    else if(wounds > 100) wounds = 100;
}
void SCrew::ChangeWounds(i16 v) {
    SetWounds(wounds+v);
}
void SCrew::SetSJobType(SJobType t) { job = t; }
void SCrew::SetXP(i16 v) {
    xp = v;
    if(xp < 0) xp = 0;
    else if(xp > 100) xp = 100;
}
void SCrew::ChangeXP(i16 v) {
    SetXP(xp+v);
}
void SCrew::SetActive(bool v) { active = v;}

i16 SCrew::GetReadiness() {
    if(!GetActive()) {
        return 0;
    } else {

        return std::cbrt(
            static_cast<i64>(health < 0 ? 0 : health) * // don't want -cube root. Badness.
            static_cast<i64>(morale) *
            static_cast<i64>(stamina)
        );
    }
}
void SCrew::DecreaseMorale(RNG & rng) {
    i16 upper = std::ceil(morale / 10.0);
    std::uniform_int_distribution<i16> d(0, upper);
    SetMorale(-d(rng));
}
void SCrew::IncreaseMorale(RNG & rng) {
    i16 upper = std::ceil(morale / 10.0);
    std::uniform_int_distribution<i16> d(0, upper);
    SetMorale(d(rng));
}
void SCrew::ApplyWoundsToHealth() {
    SetHealth(-GetWounds());
}
/* --------------------------------------------------------------------------
    STeam
-------------------------------------------------------------------------- */

STeam::STeam()
    : id(-1), crew_size(0), job(SJobType::Inactive), comp(nullptr), onduty(false)
{}

STeam::STeam(
    i64 _id,
    sizet _crew_size,
    SJobType _job
)
    : id(_id), crew_size(_crew_size), job(_job), comp(nullptr), onduty(false)
{}

i64 STeam::GetID() const { return id; }
sizet STeam::GetCrewSize() const { return crew_size; }
vec<SCrew*> STeam::GetCrew() { return crew; }
SJobType STeam::GetTeamType() const { return job; }
SCompartment* STeam::GetCompartment() const { return comp; }
bool STeam::GetOnduty() const { return onduty; }

void STeam::SetCrewSize(sizet _crew_size) { crew_size = _crew_size; }
void STeam::AddCrew(SCrew * crewman) { crew.push_back(crewman); }
void STeam::RemoveCrew(sizet index) {
    if(index < crew.size()) {
        vec<SCrew*>::iterator it = crew.begin() + index;
        crew.erase(it);
    }
}
void STeam::RemoveAllCrew() { crew.clear(); }
void STeam::SetSTeamType(SJobType type) { job = type; }
void STeam::SetCompartment(SCompartment * c) { comp = c; }
void STeam::SetOnduty(bool b) { onduty = b; }

sizet STeam::GetNumAbleCrew() {
    sizet n = 0;
    for(
        vec<SCrew*>::iterator it = crew.begin();
        it != crew.end();
        it++
    ) {
        if((*it)->GetActive()) n += 1;
    }
    return n;
}
sizet STeam::GetNumDisableCrew() {
    sizet n = 0;
    for(
        vec<SCrew*>::iterator it = crew.begin();
        it != crew.end();
        it++
    ) {
        if(!(*it)->GetActive()) n += 1;
    }
    return n;
}
sizet STeam::GetNumMissingCrew() {
    return crew_size - crew.size();
}
i64 STeam::GetAverageHealth() {
    i64 n = 0;
    for(
        vec<SCrew*>::iterator it = crew.begin();
        it != crew.end();
        it++
    ) {
        n += (*it)->GetHealth();
    }
    return n / crew_size;
}
i64 STeam::GetAverageStamina() {
    i64 n = 0;
    for(
        vec<SCrew*>::iterator it = crew.begin();
        it != crew.end();
        it++
    ) {
        n += (*it)->GetStamina();
    }
    return n / crew_size;
}
i64 STeam::GetAverageMorale() {
    i64 n = 0;
    for(
        vec<SCrew*>::iterator it = crew.begin();
        it != crew.end();
        it++
    ) {
        n += (*it)->GetMorale();
    }
    return n / crew_size;
}
i64 STeam::GetAverageReadiness() {
    i64 n = 0;
    for(
        vec<SCrew*>::iterator it = crew.begin();
        it != crew.end();
        it++
    ) {
        n += (*it)->GetReadiness();
    }
    return n / crew_size;
}
i64 STeam::GetAverageXP() {
    i64 n = 0;
    for(
        vec<SCrew*>::iterator it = crew.begin();
        it != crew.end();
        it++
    ) {
        n += (*it)->GetXP();
    }
    return n / crew_size;
}

/* --------------------------------------------------------------------------
    SSys
-------------------------------------------------------------------------- */
SSys::SSys()
    :name("MISSING"),type(SSysType::Hull), structural_health(0), system_health(0),
    energy_req(0), room_shape(Vec2i()), 
    num_crew(0),job_type(SJobType::None)
{}

void SSys::Init_SSys(
    str _name,
    SSysType _type, 
    i64 _structural_health,
    i64 _system_health,
    i64 _energy_req,
    i64 _num_crew,
    SJobType _job_type  
) {
    name=_name;
    type=_type; 
    structural_health=_structural_health; 
    system_health=_system_health;
    energy_req=_energy_req;
    num_crew=_num_crew; 
    job_type=_job_type;
}

//SSys::~SSys() {}

str SSys::GetName() const { return name; }
SSysType SSys::GetSSysType() const { return type; }
i64 SSys::GetStructuralHealth() const { return structural_health; }
i64 SSys::GetSystemHealth() const { return system_health; }
i64 SSys::GetEnergyReq() const { return energy_req; }
Vec3i SSys::GetRoomLocation() const { return room_location; }
Vec2i SSys::GetRoomShape() const { return room_shape; }
vec<SCompartment*>& SSys::GetCompartments() { return compartments; }
i64 SSys::GetNumCrew() const { return num_crew; }
SJobType SSys::GetJobType() const { return job_type; }
vec<SCrew*>& SSys::GetCrew() { return crew; }

void SSys::SetStructuralHealth(i64 _structural_health) {structural_health = _structural_health;}
void SSys::SetSystemHealth(i64 _system_health) {system_health=_system_health;}
void SSys::SetEnergyReq(i64 _energy_req) {energy_req=_energy_req;}
void SSys::SetRoomLocation(Vec3i _room_location) { room_location = _room_location; }
void SSys::SetRoomShape(Vec2i _room_shape) {room_shape=_room_shape;}
void SSys::SetNumCrew(i64 _num_teams) {num_crew=_num_teams;}

void SSys::AddCompartment(SCompartment * comp) {compartments.push_back(comp);}
SCompartment * SSys::GetRandomCompartment(RNG & rng) {
    std::uniform_int_distribution<sizet> d(0,compartments.size()-1);
    return compartments[d(rng)];
}
void SSys::RemoveCompartments() {compartments.clear();}

void SSys::AddCrew(SCrew * _crew) {crew.push_back(_crew);}
void SSys::RemoveCrew(sizet index) {
    if(index < crew.size() ) {
        vec<SCrew*>::iterator it = crew.begin()+index;
        crew.erase(it);
    }
}
void SSys::RemoveAllCrew() {crew.clear();}
i64 SSys::GetCrewDeficit() {
    i64 deficit = 0;
    for(
        vec<SCrew*>::iterator it = crew.begin();
        it != crew.end();
        it++
    ) {
        if(!(*it)->GetActive()) {
            deficit += 1;
        }
    }
    return deficit;
}


void SSys::UpdateCrewStats() {

    // Average team stats.
    cur_avg_readiness_of_all_crew = 0;
    cur_avg_health_of_all_crew = 0;
    cur_avg_morale_of_all_crew = 0;
    cur_avg_stamina_of_all_crew = 0;
    cur_avg_xp_of_all_crew = 0;

    for(
        vec<SCrew*>::iterator it = crew.begin();
        it != crew.end();
        it++
    ) {
        cur_avg_readiness_of_all_crew += (*it)->GetReadiness();
        cur_avg_health_of_all_crew += (*it)->GetHealth();
        cur_avg_morale_of_all_crew += (*it)->GetMorale();
        cur_avg_stamina_of_all_crew += (*it)->GetStamina();
        cur_avg_xp_of_all_crew += (*it)->GetXP();
    }
    cur_avg_readiness_of_all_crew /= num_crew;
    cur_avg_health_of_all_crew /= num_crew;
    cur_avg_morale_of_all_crew /= num_crew;
    cur_avg_stamina_of_all_crew /= num_crew;
    cur_avg_xp_of_all_crew /= num_crew;

    // operations scalar
    crew_stats_scalar_on_operations = 
        (static_cast<double>(cur_avg_readiness_of_all_crew) / 100.0) +
        (cur_avg_xp_of_all_crew / 1000.0);
}

i64 SSys::CurAvgXPOfAllCrew() { return cur_avg_xp_of_all_crew; }
i64 SSys::CurAvgReadinessOfAllCrew() {return cur_avg_readiness_of_all_crew;}
i64 SSys::CurAvgHealthOfAllCrew() {return cur_avg_health_of_all_crew;}
i64 SSys::CurAvgMoraleOfAllCrew() {return cur_avg_morale_of_all_crew;}
i64 SSys::CurAvgStaminaOfAllCrew() {return cur_avg_stamina_of_all_crew;}

double SSys::Effective_GetCrewScalarOnOperations() {
    return crew_stats_scalar_on_operations;
}

/*----------------------------------------------------------------------*/
// RepairStation
double SSys::Effective_RepairRate() { return 0.0; }

// SecStation
double SSys::Effective_SecurityDefense() { return 0.0; }

// Shields
i64 SSys::GetMaxShields() { return 0; }
i64 SSys::GetCurShields() { return 0; }
i64 SSys::GetRegenShields() { return 0; }
void SSys::SetMaxShields(i64 _max_shields) {}
void SSys::SetCurShields(i64 _cur_shields) {}
void SSys::SetRegenShields(i64 _regen_shields) {}
void SSys::RegenShields() {}
void SSys::ResetShields() {}

double SSys::Effective_ShieldRegenRate() { return 0.0; }
void SSys::Effective_RegenShields() {}

//Reactor
i64 SSys::GetEnergyProd() { return 0; }
void SSys::SetEnergyProd(i64 _energy_prod) {}

double SSys::Effective_EnergyProduction() { return 0.0; }

// Weapon
i64 SSys::GetDmgStructure() { return 0; }
i64 SSys::GetDmgShields() { return 0; }
i64 SSys::GetDmgSystems() {return 0;}
i64 SSys::GetWeaponRange() {return 0.0;}
i64 SSys::GetTargetSize() {return 0;}
i64 SSys::GetTargetRate() {return 0;}
i64 SSys::GetRateOfFire() {return 0;}
void SSys::SetDmgStructure(i64 _dmg_structure) {}
void SSys::SetDmgShields(i64 _dmg_shields) {}
void SSys::SetDmgSystems(i64 _dmg_systems) {}
void SSys::SetWeaponRange(i64 _weapon_range) {}
void SSys::SetTargetSize(i64 _target_size) {}
void SSys::SetTargetRate(i64 _target_rate) {}
void SSys::SetRateOfFire(i64 _rate_of_fire) {}

double SSys::Effective_WeaponRange() {return 0.0;}
double SSys::Effective_TargetRate() {return 0.0;}
double SSys::Effective_ToHitProbOfSize(i64 size_in_comps) {return 0.0;}

// STL Engine
i64 SSys::GetThrust() { return 0; }
void SSys::SetThrust(i64 _thrust) {}

double SSys::Effective_STLEngineThrust() {return 0.0;}

// FTL Engine
i64 SSys::GetJumpDistance() { return 0; }
i64 SSys::GetChargeRate() { return 0; }
void SSys::SetDistance(i64 _jump_distance) {}
void SSys::SetChargeRate(i64 _charge_rate) {}

double SSys::Effective_JumpDistance() { return 0.0; }
double SSys::Effective_ChargeRate() { return 0.0; }

// Bridge
double SSys::Effective_BridgeCrewInitiative() { return 0.0; }

// Medbay
i64 SSys::GetBeds() {return 0;}
i64 SSys::GetHealingRate() {return 0;}
void SSys::SetBeds(i64 _beds) {}
void SSys::SetHealingRate(i64 _healing_rate) {}
vec<SCrew*> * SSys::GetPatients() { return nullptr; }
void SSys::AddPatient(SCrew * c) {}
void SSys::RemovePatient(sizet index) {}
void SSys::RemoveAllPatients() {}

double SSys::Effective_HealingRate() {return 0.0;}

// CargoHold
i64 SSys::GetStorage() { return 0; }
void SSys::SetStorage(i64 _storage) {}

double SSys::Effective_StorageSpace() {return 0.0;}

// TroopHold
i64 SSys::GetTroops() { return 0; }
void SSys::SetTroops(i64 _troops) {}

double SSys::Effective_TroopCapacity() { return 0.0;}

// Hangar
i64 SSys::GetHangarStorageInComps() { return 0; }
void SSys::SetHangarStorageInComps(i64 _hangar_storage) {}

double SSys::Effective_HangarStorageInComps() { return 0.0;}

// Quarter
i64 SSys::GetNumCrewBeds() { return 0; }
double SSys::GetMoraleIncreaseProb() { return 0.0; }
i64 SSys::GetStaminaIncreasePerHour() { return 0;}
void SSys::SetNumCrewBeds(i64 _num_crew_beds) {}
void SSys::SetMoraleIncreaseProb(double _morale_increase_prob) {}
void SSys::SetStaminaIncreasePerHour(i64 _stamina_increase_per_hour) {}

double SSys::Effective_MoraleIncreaseProb() { return 0.0; }
double SSys::Effective_StaminaIncreasePerHour() { return 0.0; }

// Scanner
i64 SSys::GetScanDistance() { return 0; }
i64 SSys::GetScanPenetration() { return 0; }
void SSys::SetScanDistance(i64 _scan_distance) {}
void SSys::SetScanPenetration(i64 _scan_penetration) {}

double SSys::Effective_ScanDistance() { return 0.0; }
double SSys::Effective_ScanPenetration() {return 0.0;}

/* --------------------------------------------------------------------------
    SRepairStation
-------------------------------------------------------------------------- */

SRepairStation::SRepairStation()
    : SSys()
{}

void SRepairStation::Init_SRepairStation() {}

double SRepairStation::Effective_RepairRate() {
    return Effective_GetCrewScalarOnOperations();
}

/* --------------------------------------------------------------------------
    SSecStation
-------------------------------------------------------------------------- */

SSecStation::SSecStation()
    : SSys()
{}

void SSecStation::Init_SSecStation() {}

double SSecStation::Effective_SecurityDefense() {
    return Effective_GetCrewScalarOnOperations();
}

/* --------------------------------------------------------------------------
    SShield
-------------------------------------------------------------------------- */

SShield::SShield()
    : SSys(),
    max_shield(0), cur_shield(0), regen_shield(0)
{}

void SShield::Init_SShield(
    i64 _max_shield,
    i64 _regen_shield
) {
    max_shield=_max_shield; 
    cur_shield=_max_shield; 
    regen_shield=_regen_shield;
}

i64 SShield::GetMaxShields() { return max_shield; }
i64 SShield::GetCurShields() { return cur_shield; }
i64 SShield::GetRegenShields() { return regen_shield; }
void SShield::SetMaxShields(i64 _max_shields) {max_shield = _max_shields;}
void SShield::SetCurShields(i64 _cur_shields) {
    cur_shield = _cur_shields;
    if(cur_shield > max_shield) {
        cur_shield = max_shield;
    }
}
void SShield::SetRegenShields(i64 _regen_shields) {
    regen_shield = _regen_shields;
}
void SShield::RegenShields() {
    if(GetCurShields() < GetMaxShields()) {
        SetCurShields(GetCurShields() + GetRegenShields());
    }
}
void SShield::ResetShields() {
    SetCurShields(GetMaxShields());
}

double SShield::Effective_ShieldRegenRate() {
    return Effective_GetCrewScalarOnOperations() * GetRegenShields();
}
void SShield::Effective_RegenShields() {
    if(GetCurShields() < GetMaxShields()) {
        SetCurShields(GetCurShields() + Effective_ShieldRegenRate());
    }
}

/* --------------------------------------------------------------------------
    SReactor
-------------------------------------------------------------------------- */

SReactor::SReactor()
    : SSys(),
    energy_prod(0)
{}

void SReactor::Init_SReactor(
    i64 _energy_prod
) {
    energy_prod = _energy_prod;
}

i64 SReactor::GetEnergyProd() { return energy_prod; }
void SReactor::SetEnergyProd(i64 _energy_prod) {energy_prod = _energy_prod;}

double SReactor::Effective_EnergyProduction() {
    return Effective_GetCrewScalarOnOperations() * GetEnergyProd();
}

/* --------------------------------------------------------------------------
    SWeapon
-------------------------------------------------------------------------- */

SWeapon::SWeapon()
    : SSys(),
    dmg_structure(0), dmg_shields(0), dmg_systems(0),
    weapon_range(0), target_size(0), target_rate(0),
    rate_of_fire(0)
{}

void SWeapon::Init_SWeapon(
    i64 _dmg_structure,
    i64 _dmg_shields,
    i64 _dmg_systems,
    i64 _weapon_range,
    i64 _target_size,
    i64 _target_rate,
    i64 _rate_of_fire
) {
    dmg_structure=_dmg_structure; 
    dmg_shields=_dmg_shields; 
    dmg_systems=_dmg_systems;
    weapon_range=_weapon_range; 
    target_size=_target_size; 
    target_rate=_target_rate;
}
    

i64 SWeapon::GetDmgStructure() { return dmg_structure; }
i64 SWeapon::GetDmgShields() { return dmg_shields; }
i64 SWeapon::GetDmgSystems() { return dmg_systems; }
i64 SWeapon::GetWeaponRange() { return weapon_range; }
i64 SWeapon::GetTargetSize() { return target_size; }
i64 SWeapon::GetTargetRate() { return target_rate; }
i64 SWeapon::GetRateOfFire() { return rate_of_fire; }
void SWeapon::SetDmgStructure(i64 _dmg_structure) { dmg_structure = _dmg_structure; }
void SWeapon::SetDmgShields(i64 _dmg_shields) { dmg_shields = _dmg_shields; }
void SWeapon::SetDmgSystems(i64 _dmg_systems) { dmg_systems = _dmg_systems; }
void SWeapon::SetWeaponRange(i64 _weapon_range) { weapon_range = _weapon_range; }
void SWeapon::SetTargetSize(i64 _target_size) { target_size = _target_size; }
void SWeapon::SetTargetRate(i64 _target_rate) { target_rate = _target_rate; }
void SWeapon::SetRateOfFire(i64 _rate_of_fire) { rate_of_fire = _rate_of_fire; }

double SWeapon::Effective_WeaponRange() {
    return GetWeaponRange() * Effective_GetCrewScalarOnOperations();
}
double SWeapon::Effective_TargetRate() {
    return GetTargetRate() * Effective_GetCrewScalarOnOperations();
}
double SWeapon::Effective_ToHitProbOfSize(i64 size_in_comps) {
    return 1.0 /
        (
            std::pow( 
                (size_in_comps - GetTargetSize()) / Effective_TargetRate(),
                2.0 
            ) + 1.0
        );
}

/* --------------------------------------------------------------------------
    SSTLEngine
-------------------------------------------------------------------------- */

SSTLEngine::SSTLEngine()
    : SSys(),
    thrust(0)
{}

void SSTLEngine::Init_SEngine(
    i64 _thrust
) {
    thrust = _thrust;
}

i64 SSTLEngine::GetThrust() { return thrust; }
void SSTLEngine::SetThrust(i64 _thrust) { thrust = _thrust; }

double SSTLEngine::Effective_STLEngineThrust() {
    return GetThrust() * Effective_GetCrewScalarOnOperations();
}

/* --------------------------------------------------------------------------
    SFTLEngine
-------------------------------------------------------------------------- */

SFTLEngine::SFTLEngine()
    : SSys(),
    jump_distance(0), charge_rate(0)
{}

void SFTLEngine::Init_SFTLEngine(
    i64 _jump_distance,
    i64 _charge_rate
) {
    jump_distance=_jump_distance; 
    charge_rate=_charge_rate;
}

i64 SFTLEngine::GetJumpDistance() {return jump_distance;}
i64 SFTLEngine::GetChargeRate() {return charge_rate;}
void SFTLEngine::SetDistance(i64 _jump_distance) {jump_distance = _jump_distance;}
void SFTLEngine::SetChargeRate(i64 _charge_rate) {charge_rate=_charge_rate;}

double SFTLEngine::Effective_JumpDistance() {
    return GetJumpDistance() * Effective_GetCrewScalarOnOperations();
}
double SFTLEngine::Effective_ChargeRate() {
    return GetChargeRate() * Effective_GetCrewScalarOnOperations();
}

/* --------------------------------------------------------------------------
    SBridge
-------------------------------------------------------------------------- */

SBridge::SBridge()
    : SSys()
{}

void SBridge::Init_SBridge() {}

double SBridge::Effective_BridgeCrewInitiative() {
    return CurAvgXPOfAllCrew() * Effective_GetCrewScalarOnOperations();
}

/* --------------------------------------------------------------------------
    SMedbay
-------------------------------------------------------------------------- */

SMedbay::SMedbay()
    : SSys(),
    beds(0), healing_rate(0)
{}

void SMedbay::Init_SMedbay(
    i64 _beds,
    i64 _healing_rate
) {
    beds=_beds; 
    healing_rate=_healing_rate;
}
    

i64 SMedbay::GetBeds() { return beds; }
i64 SMedbay::GetHealingRate() { return healing_rate; }
void SMedbay::SetBeds(i64 _beds) { beds = _beds; }
void SMedbay::SetHealingRate(i64 _healing_rate) { healing_rate = _healing_rate; }
vec<SCrew*> * SMedbay::GetPatients() { return &patients; }
void SMedbay::AddPatient(SCrew * c) { patients.push_back(c); }
void SMedbay::RemovePatient(sizet index) {
    if(index < patients.size()) {
        vec<SCrew*>::iterator it = patients.begin()+index;
        patients.erase(it);
    }
}
void SMedbay::RemoveAllPatients() { patients.clear(); }

double SMedbay::Effective_HealingRate() {
    return GetHealingRate() * Effective_GetCrewScalarOnOperations();
}

/* --------------------------------------------------------------------------
    SCargoHold
-------------------------------------------------------------------------- */

SCargoHold::SCargoHold()
    : SSys(),
    storage(0)
{}

void SCargoHold::Init_SCargoHold(
    i64 _storage
) {
    storage=_storage;
}

i64 SCargoHold::GetStorage() { return storage; }
void SCargoHold::SetStorage(i64 _storage) { storage = _storage; }

double SCargoHold::Effective_StorageSpace() {
    return GetStorage() * Effective_GetCrewScalarOnOperations();
}

/* --------------------------------------------------------------------------
    STroopHold
-------------------------------------------------------------------------- */

STroopHold::STroopHold()
    : SSys(),
    troops(0)
{}

void STroopHold::Init_STroopHold(
    i64 _troops
) {
    troops=_troops;
}

i64 STroopHold::GetTroops() { return troops; }
void STroopHold::SetTroops(i64 _troops) { troops = _troops; }

double STroopHold::Effective_TroopCapacity() {
    return GetTroops() * Effective_GetCrewScalarOnOperations();
}

/* --------------------------------------------------------------------------
    SHangar
-------------------------------------------------------------------------- */

SHangar::SHangar()
    : SSys(),
    hangar_storage(0)
{}

void SHangar::Init_SHangar(
    i64 _hangar_storage
) {
    hangar_storage=_hangar_storage;
}

i64 SHangar::GetHangarStorageInComps() { return hangar_storage; }
void SHangar::SetHangarStorageInComps(i64 _hangar_storage) {hangar_storage = _hangar_storage;}

double SHangar::Effective_HangarStorageInComps() {
    return GetHangarStorageInComps() * Effective_GetCrewScalarOnOperations();
}

/* --------------------------------------------------------------------------
    SQuarters
-------------------------------------------------------------------------- */

SQuarters::SQuarters()
    : SSys(),
    num_crew_beds(0), morale_increase_prob(0.0), stamina_increase_per_hour(0)
{}

void SQuarters::Init_SQuarters(
    i64 _num_crew_beds,
    double _morale_increase_prob,
    i64 _stamina_increase_per_hour
) {
    num_crew_beds=_num_crew_beds;
    morale_increase_prob=_morale_increase_prob;
    stamina_increase_per_hour=_stamina_increase_per_hour;
}

i64 SQuarters::GetNumCrewBeds() { return num_crew_beds; }
double SQuarters::GetMoraleIncreaseProb() { return morale_increase_prob; }
i64 SQuarters::GetStaminaIncreasePerHour() {return stamina_increase_per_hour;}
void SQuarters::SetNumCrewBeds(i64 _num_crew_beds) { num_crew_beds = _num_crew_beds; }
void SQuarters::SetMoraleIncreaseProb(double _morale_increase_prob) {
    morale_increase_prob = _morale_increase_prob;
}
void SQuarters::SetStaminaIncreasePerHour(i64 _stamina_increase_per_hour) {
    stamina_increase_per_hour = _stamina_increase_per_hour;
}

double SQuarters::Effective_MoraleIncreaseProb() {
    return GetMoraleIncreaseProb() * Effective_GetCrewScalarOnOperations();
}
double SQuarters::Effective_StaminaIncreasePerHour() {
    return GetStaminaIncreasePerHour() * Effective_GetCrewScalarOnOperations();
}

/* --------------------------------------------------------------------------
    SScanner
-------------------------------------------------------------------------- */

SScanner::SScanner()
    : SSys(),
    scan_distance(0), scan_penetration(0)
{}

void SScanner::Init_SScanner(
    i64 _scan_distance,
    i64 _scan_penetration
) {
    scan_distance=_scan_distance; 
    scan_penetration=_scan_penetration;
}

i64 SScanner::GetScanDistance() { return scan_distance; }
i64 SScanner::GetScanPenetration() { return scan_penetration; }
void SScanner::SetScanDistance(i64 _scan_distance) { scan_distance = _scan_distance; }
void SScanner::SetScanPenetration(i64 _scan_penetration) { scan_penetration = _scan_penetration; }

double SScanner::Effective_ScanDistance() {
    return GetScanDistance() * Effective_GetCrewScalarOnOperations();
}
double SScanner::Effective_ScanPenetration() {
    return GetScanPenetration() * Effective_GetCrewScalarOnOperations();
}

/* --------------------------------------------------------------------------
    SHull
-------------------------------------------------------------------------- */

SHull::SHull()
    : SSys()
{}

void SHull::Init_SHull() {

}

/* --------------------------------------------------------------------------
    SCloak
-------------------------------------------------------------------------- */

SCloak::SCloak() 
    : SSys()
{}
void SCloak::Init_SCloak(
    i64 _cloak_level
) {
    cloak_level = _cloak_level;
}

i64 SCloak::GetCloakLevel() {
    return cloak_level;
}
void SCloak::SetCloakLevel(i64 _cloak_level) {
    cloak_level = _cloak_level;
}

/* --------------------------------------------------------------------------
    SCounterMeasure
-------------------------------------------------------------------------- */

SCounterMeasure::SCounterMeasure()
    : SSys()
{}
void SCounterMeasure::Init_SCounterMeasure(
    double _accuracy_reduction
) {
    accuracy_reduction = _accuracy_reduction;
}

double SCounterMeasure::GetAccuracyReduction() { 
    return accuracy_reduction; 
}
void SCounterMeasure::SetAccuracyReduction(
    double _accuracy_reduction
) {
    accuracy_reduction = _accuracy_reduction;
}
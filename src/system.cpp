#include"system.hpp"

// double System::INFRASTRUCTURE_MULTIPLIER_BASE = 10.0;
// const int MAX_STABILITY;
// static const int MAX_ECONOMY;

System::System() 
    : id(-1), name("NONE"), desc("NONE"),
        stability(0), economy(0.0)
{
    for(sizet i = 0; i < static_cast<sizet>(ResType::END); i++) {
        resources.push_back(0);
        infrastructure.push_back(0);
    }
}

System::System(
    ID _id, 
    str _name, 
    str _desc,
    vec<double> & _resources,
    vec<double> & _infrastructure,
    double _stability,
    double _economy
)
    : id(_id), name(_name), desc(_desc),
        resources(_resources), infrastructure(_infrastructure),
        stability(_stability), economy(_economy)
{}
ID System::GetID() const { return id; }
str System::GetName() const { return name; }
str System::GetDesc() const { return desc; }
double System::GetBaseResource(ResType t) const { 
    return resources[static_cast<int>(t)]; 
}
double System::GetEconomy() const { 
    return economy; 
}
double System::GetInfrastructure(ResType t) const { 
    return infrastructure[static_cast<int>(t)]; 
}
double System::GetStability() const { return stability; }
void System::InitLoyalty(vec<ID> & all_faction_ids) {
    for(
        vec<ID>::iterator it = all_faction_ids.begin();
        it != all_faction_ids.end(); it++
    ) {
        loyalty.emplace(*it, 0.0);
    }
}

double System::GetInfrastructureMultiplier(ResType t) const {
    return static_cast<double>(GetInfrastructure(t)) / 
        INFRASTRUCTURE_MULTIPLIER_BASE[static_cast<int>(t)];
}

double System::GetActualResource(ResType t) const {
    return GetBaseResource(t) * GetInfrastructureMultiplier(t);
}

double System::CalculateTaxes() {
    double taxes = 0.0;
    for(sizet i = 0; i < static_cast<sizet>(ResType::END); i++) {
        taxes += GetActualResource(static_cast<ResType>(i)) * GetEconomy();
    }
    return taxes;
}

void System::LowerStability(double amt) {
    stability -= amt;
    if(stability < 0) {
        stability = 0;
    }
}
void System::RaiseStability(double amt) {
    stability += amt;
    if(stability > MAX_STABILITY) {
        stability = MAX_STABILITY;
    }
}
void System::LowerEconomy(double amt) {
    economy -= amt;
    if(economy < 0) {
        economy = 0;
    }
}
void System::RaiseEconomy(double amt) {
    economy += amt;
    if(economy > MAX_ECONOMY) {
        economy = MAX_ECONOMY;
    }
}

void System::ChangeLoyalty(ID id, double amt) {
    int new_loyalty = loyalty.at(id) + amt;
    if(new_loyalty > MAX_LOYALTY) {
        new_loyalty = MAX_LOYALTY;
    } else if(new_loyalty < 0) {
        new_loyalty = 0;
    }
    loyalty[id] = new_loyalty;
}
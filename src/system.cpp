#include"system.hpp"

// double System::INFRASTRUCTURE_MULTIPLIER_BASE = 10.0;
// const int MAX_STABILITY;
// static const int MAX_ECONOMY;

System::System() 
    : id(ID()), name("NONE"), desc("NONE"),
        stability(0)
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
    Vec2i _position,
    vec<double> & _resources,
    vec<double> & _infrastructure,
    double _stability
)
    : id(_id), name(_name), desc(_desc), position(_position),
        resources(_resources), infrastructure(_infrastructure),
        stability(_stability)
{}
ID System::GetID() const { return id; }
str System::GetName() const { return name; }
str System::GetDesc() const { return desc; }
Vec2i System::GetPosition() const { return position; }
double System::GetBaseResource(ResType t) const { 
    return resources[static_cast<int>(t)]; 
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


double System::GetActualResource(ResType t) const {
    return GetBaseResource(t) * GetInfrastructure(t);
}

void System::ChangeStability(double amt) {
    stability += amt;
    if(stability < 0) {
        stability = 0;
    } else if(stability > MAX_STABILITY) {
        stability = MAX_STABILITY;
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
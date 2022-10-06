#include"facility.hpp"

FacAbility::FacAbility() 
    : id(ID()), type(FacAbilityType::END), health(0)
{
    data.push_back(0.0);
}
FacAbility::FacAbility(ID _id, FacAbilityType _type, vec<double> _data, double _health) 
    : id(_id), type(_type), data(_data), health(_health)
{}
ID FacAbility::GetID() const {
    return id;
}
FacAbilityType FacAbility::GetFacAbilityType() const {
    return type;
}
strv FacAbility::GetFacAbilityTypeAsString() {
    return magic_enum::enum_name(type);
}
vec<double> & FacAbility::GetData() {
    return data;
}
double FacAbility::GetHealth() const {
    return health;
}
void FacAbility::SetHealth(double _health) {
    health = _health;
}





Facility::Facility()
    : id(ID()), name("NONE")
{}
Facility::Facility(ID _id, str _name, vec<FacAbility> _abilities) 
    : id(_id), name(_name), abilities(_abilities)
{}
ID Facility::GetID() const {
    return id;
}
str Facility::GetName() const {
    return name;
}
str Facility::GetDesc() {
    return name;
}
vec<FacAbility> & Facility::GetAbilities() {
    return abilities;
}
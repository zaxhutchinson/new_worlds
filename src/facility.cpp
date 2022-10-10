#include"facility.hpp"





FacConstruction::FacConstruction() {
    for(int i = 0; i < static_cast<int>(ResType::END); i++) {
        reses_per_tick.push_back(0.0);
    }
}
FacConstruction::FacConstruction(
    vec<ShipClass> _ship_classes,
    vec<UnitClass> _unit_classes,
    vec<double> _reses_per_tick
)
    : ship_classes(_ship_classes),
        unit_classes(_unit_classes),
        reses_per_tick(_reses_per_tick)
{}
vec<ShipClass> & FacConstruction::GetShipClasses() {
    return ship_classes;
}
vec<UnitClass> & FacConstruction::GetUnitClasses() {
    return unit_classes;
}
bool FacConstruction::HasShipClass(int sc) const {
    for(sizet i = 0; i < ship_classes.size(); i++) {
        if(ship_classes[i]==sc) return true;
    }
    return false;
}
bool FacConstruction::HasUnitClass(int uc) const {
    for(sizet i = 0; i < unit_classes.size(); i++) {
        if(unit_classes[i]==uc) return true;
    }
    return false;
}
vec<double> & FacConstruction::GetResesPerTick() {
    return reses_per_tick;
}
double FacConstruction::GetResPerTick(ResType rt) {
    return reses_per_tick[static_cast<int>(rt)];
}



FacProduction::FacProduction()
{}
FacProduction::FacProduction(
    umap<ResType,double> _rates
)
    : rates(_rates)
{}
umap<ResType,double> & FacProduction::GetRates() {
    return rates;
}
double FacProduction::GetRate(ResType rt) {
    if(rates.contains(rt)) {
        return rates.at(rt);
    } else {
        return 0.0;
    }
}


FacGovernment::FacGovernment() {}
FacGovernment::FacGovernment(
    double _tax_rate
)
    : tax_rate(_tax_rate)
{}
double FacGovernment::GetTaxRate() const {
    return tax_rate;
}


Facility::Facility()
    : id(ID()), name("NONE")
{}
Facility::Facility(ID _id, str _name, vec<ID> _prereqs, vec<ID> _postreqs) 
    : id(_id), name(_name), prereqs(_prereqs), postreqs(_postreqs)
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
vec<ID> & Facility::GetPrereqs() {
    return prereqs;
}
vec<ID> & Facility::GetPostreqs() {
    return postreqs;
}
FacConstruction * Facility::GetFacConstruction() { 
    return construction.get();
}
FacProduction * Facility::GetFacProduction() {
    return production.get();
}
FacGovernment * Facility::GetFacGovernment() {
    return government.get();
}
void Facility::AddFacConstruction(uptr<FacConstruction> f) {
    construction = std::move(f);
}
void Facility::AddFacProduction(uptr<FacProduction> f) {
    production = std::move(f);
}
void Facility::AddFacGovernment(uptr<FacGovernment> f) {
    government = std::move(f);
}
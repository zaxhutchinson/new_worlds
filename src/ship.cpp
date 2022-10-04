#include"ship.hpp"

Ship::Ship() 
    : id(ID()), name("NONE")
{
    InitMaps();
}

Ship::Ship(ID _id, str _name)
    : id(_id), name(_name)
{
    InitMaps();
}
void Ship::InitMaps() {
    for(int i = 0; i < static_cast<int>(CompType::END); i++) {
        comps.emplace(static_cast<CompType>(i), vec<Comp>());
    }
}
ID Ship::GetID() const { return id; }
str Ship::GetName() const { return name; }
ShipLayer * Ship::GetShipLayer(int i) { return &(layers.at(i)); }
umap<int,ShipLayer>& Ship::GetShipLayers() { return layers; }
vec<Comp> * Ship::GetCompsOfType(CompType ct) { return &(comps.at(ct)); }
void Ship::AddShipLayer(ShipLayer l) {
    layers.emplace(l.GetLayer(), std::move(l));
}
void Ship::AddComp(Comp c) {
    CompType ct = c.GetCompType();
    comps.at(ct).push_back(std::move(c));
}


// Crew Methods
void Ship::CalculateCrewEffectiveness(RNG * rng) {
    for(
        umap<CompType,vec<Comp>>::iterator it = comps.begin();
        it != comps.end(); it++
    ) {
        for(
            vec<Comp>::iterator cit = it->second.begin();
            cit != it->second.end(); cit++
        ) {
            cit->GetCrew()->CalculateCrewEffectiveness(rng);
        }
    }
}



double Ship::GetTotalEnergyReq() {
    double energy_req_total = 0.0;
    for(
        umap<CompType,vec<Comp>>::iterator it = comps.begin();
        it != comps.end(); it++
    ) {
        for(
            vec<Comp>::iterator cit = it->second.begin();
            cit != it->second.end(); cit++
        ) {
            energy_req_total += cit->GetEnergyReq();
        }
    }
    return energy_req_total;
}
double Ship::GetTotalEnergyOutput() {
    double energy_output_total = 0.0;

    for(
        vec<Comp>::iterator it = GetCompsOfType(CompType::Reactor)->begin();
        it != GetCompsOfType(CompType::Reactor)->end(); it++
    ) {
        energy_output_total += it->GetReactor()->GetEnergyOutput();
    }
    
    return energy_output_total;
}
double Ship::GetEnergyComsumptionRatio() {
    return GetTotalEnergyReq() / GetTotalEnergyOutput();
}
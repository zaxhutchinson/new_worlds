#include"ship.hpp"

Ship::Ship() 
    : id(ID()), name("NONE")
{
    
}

Ship::Ship(ID _id, str _name, int _ship_class)
    : id(_id), name(_name), ship_class(_ship_class)
{
    
}
bool Ship::operator==(const Ship & s) {
    return id==s.id;
}

ID Ship::GetID() const { return id; }
str Ship::GetName() const { return name; }
int Ship::GetShipClass() const { return ship_class; }
ShipLayer * Ship::GetShipLayer(int i) { return &(layers.at(i)); }
umap<int,ShipLayer>& Ship::GetShipLayers() { return layers; }
vec<Comp*> Ship::GetCompsWithType(CompType ct) { 
    vec<Comp*> v;
    for(
        vec<Comp>::iterator it = comps.begin();
        it != comps.end(); it++
    ) {
        if(it->HasCompType(ct)) {
            v.push_back(&(*it));
        }
    }
    return v;
}
void Ship::AddShipLayer(ShipLayer l) {
    layers.emplace(l.GetLayer(), std::move(l));
}
void Ship::AddComp(Comp c) {
    comps.push_back(std::move(c));
}


// Crew Methods
void Ship::CalculateCrewEffectiveness(RNG * rng) {
    for(
        vec<Comp>::iterator it = comps.begin();
        it != comps.end(); it++
    ) {

        it->GetCrew()->CalculateCrewEffectiveness(rng);

    }
}

double Ship::GetTotalEnergyReq() {
    double energy_req_total = 0.0;

    for(
        vec<Comp>::iterator it = comps.begin();
        it != comps.end(); it++
    ) {
        energy_req_total += it->GetEnergyReq();
    }
    
    return energy_req_total;
}
double Ship::GetTotalEnergyOutput() {
    double energy_output_total = 0.0;

    for(
        vec<Comp>::iterator it = comps.begin();
        it != comps.end(); it++
    ) {
        energy_output_total += it->GetReactor()->GetEnergyOutput();
    }
    
    return energy_output_total;
}
double Ship::GetEnergyComsumptionRatio() {
    return GetTotalEnergyReq() / GetTotalEnergyOutput();
}
#include"ship.hpp"

Ship::Ship() 
    : id(ID()), name("NONE")
{}

Ship::Ship(ID _id, str _name)
    : id(_id), name(_name)
{}

ID Ship::GetID() const { return id; }
str Ship::GetName() const { return name; }
ShipLayer * Ship::GetShipLayer(int i) { return &(layers.at(i)); }
umap<int,ShipLayer>& Ship::GetShipLayers() { return layers; }
vec<Engine> & Ship::GetEngines() { return engines; }
vec<Weapon> & Ship::GetWeapons() { return weapons; }
vec<Shields> & Ship::GetShields() { return shields; }
vec<Reactor> & Ship::GetReactors() { return reactors; }
vec<MogDrive> & Ship::GetMogDrives() { return mogdrives; }
void Ship::AddShipLayer(ShipLayer l) {
    layers.emplace(l.GetLayer(), std::move(l));
}
void Ship::AddEngine(Engine e) {
    engines.push_back(std::move(e));
}
void Ship::AddWeapon(Weapon w) {
    weapons.push_back(std::move(w));
}
void Ship::AddShields(Shields s) {
    shields.push_back(std::move(s));
}
void Ship::AddReactor(Reactor r) {
    reactors.push_back(std::move(r));
}
void Ship::AddMogDrive(MogDrive m) {
    mogdrives.push_back(std::move(m));
}
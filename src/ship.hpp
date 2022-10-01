#pragma once

#include"zxlb.hpp"
#include"ship_layer.hpp"
#include"ship_comps.hpp"

class Ship {
private:
    ID id;
    str name;
    umap<int,ShipLayer> layers;
    vec<Engine> engines;
    vec<Weapon> weapons;
    vec<Shields> shields;
    vec<Reactor> reactors;
    vec<MogDrive> mogdrives;
public:
    Ship();
    Ship(ID _id, str _name);
    Ship(const Ship & s) = default;
    Ship(Ship && s) = default;
    Ship& operator=(const Ship & s) = default;
    Ship& operator=(Ship && s) = default;
    ID GetID() const;
    str GetName() const;
    ShipLayer * GetShipLayer(int i);
    umap<int,ShipLayer>& GetShipLayers();
    vec<Engine> & GetEngines();
    vec<Weapon> & GetWeapons();
    vec<Shields> & GetShields();
    vec<Reactor> & GetReactors();
    vec<MogDrive> & GetMogDrives();
    void AddShipLayer(ShipLayer l);
    void AddEngine(Engine e);
    void AddWeapon(Weapon w);
    void AddShields(Shields s);
    void AddReactor(Reactor r);
    void AddMogDrive(MogDrive m);
};
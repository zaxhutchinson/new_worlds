#pragma once

#include"zxlb.hpp"
#include"ship_layer.hpp"
#include"ship_comps.hpp"

class Ship {
private:
    ID id;
    str name;
    int ship_class;
    umap<int,ShipLayer> layers;
    vec<Comp> comps;
public:
    Ship();
    Ship(ID _id, str _name, int _ship_class);
    Ship(const Ship & s) = default;
    Ship(Ship && s) = default;
    Ship& operator=(const Ship & s) = default;
    Ship& operator=(Ship && s) = default;
    bool operator==(const Ship & s);
    void InitMaps();
    ID GetID() const;
    str GetName() const;
    int GetShipClass() const;
    ShipLayer * GetShipLayer(int i);
    umap<int,ShipLayer>& GetShipLayers();
    vec<Comp*> GetCompsWithType(CompType ct);
    void AddShipLayer(ShipLayer l);
    void AddComp(Comp c);
    

    // Crew Methods
    void CalculateCrewEffectiveness(RNG * rng);

    double GetTotalEnergyReq();
    double GetTotalEnergyOutput();
    double GetEnergyComsumptionRatio();
};
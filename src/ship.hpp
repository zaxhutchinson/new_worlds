#pragma once

#include"zxlb.hpp"
#include"ship_layer.hpp"
#include"ship_comps.hpp"

class Ship {
private:
    ID id;
    str name;
    umap<int,ShipLayer> layers;
    umap<CompType,vec<Comp>> comps;
public:
    Ship();
    Ship(ID _id, str _name);
    Ship(const Ship & s) = default;
    Ship(Ship && s) = default;
    Ship& operator=(const Ship & s) = default;
    Ship& operator=(Ship && s) = default;
    void InitMaps();
    ID GetID() const;
    str GetName() const;
    ShipLayer * GetShipLayer(int i);
    umap<int,ShipLayer>& GetShipLayers();
    vec<Comp> * GetCompsOfType(CompType ct);
    void AddShipLayer(ShipLayer l);
    void AddComp(Comp c);

    // Crew Methods
    void CalculateCrewEffectiveness(RNG * rng);

    double GetTotalEnergyReq();
    double GetTotalEnergyOutput();
    double GetEnergyComsumptionRatio();
};
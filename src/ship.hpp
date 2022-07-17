#pragma once


#include"zxlb.hpp"
#include"vec2i.hpp"
#include"vec3i.hpp"
#include"ship_comps.hpp"

using ShipSystems = umap<SSysType, vuptr<SSys>>;
using ShipCompartments = umap<Vec3i, uptr<SCompartment>>;

class Ship {
private:
    str name;

    vuptr<STeam> teams;
    vuptr<SCrew> crew;
    ShipSystems systems;
    ShipCompartments compartments;

public:

    Ship();
    void InitShip(
        str _name
    );

    str GetName() const;

    void AddSSys(uptr<SSys> sys);
    ShipSystems & GetShipSystems();

private:

    
    vuptr<SSys> & GetSysList(SSysType type);

    void BuildCompartments();

};

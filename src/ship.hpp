#pragma once


#include"zxlb.hpp"
#include"vec2i.hpp"
#include"vec3i.hpp"
#include"ship_comps.hpp"

using ShipSystems = umap<SSysType, vuptr<SSys>>;
using ShipCompartments = umap<Vec3i, uptr<SCompartment>>;

class Ship {
private:
    i64 id;
    str name;
    Vec3i shape;

    vuptr<STeam> teams;
    vuptr<SCrew> crew;
    ShipSystems systems;
    ShipCompartments compartments;

public:

    Ship();
    Ship(i64 _id, str _name, Vec3i _shape);

private:

    vuptr<SSys> & GetComponentList(SSysType type);

    void BuildCompartments();

};

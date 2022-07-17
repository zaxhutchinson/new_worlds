#include"ship.hpp"

Ship::Ship() 
    : name("NONAME")
{}

void Ship::InitShip(
    str _name
) {

    name = _name;

    for(int i = 0; i < static_cast<int>(SSysType::END); i++) {
        systems.emplace(
            static_cast<SSysType>(i), vuptr<SSys>()
        );
    }
}

str Ship::GetName() const {
    return name;
}

void Ship::AddSSys(uptr<SSys> sys) {
    SSysType t = sys->GetSSysType();
    vuptr<SSys> & l = GetSysList(t);
    l.push_back(std::move(sys));
}

ShipSystems & Ship::GetShipSystems() {
    return systems;
}



// PRIVATE
vuptr<SSys> & Ship::GetSysList(SSysType type) {
    return systems.at(type);
}


void Ship::BuildCompartments() {



    /* -----------------------------------------------------------------------
        Populate systems.
    ------------------------------------------------------------------------*/

    for(
        ShipSystems::iterator it = systems.begin();
        it != systems.end();
        it++
    ) {
        for(
            vuptr<SSys>::iterator sysit = it->second.begin();
            sysit != it->second.end(); sysit++
        ) {
            Vec3i corner = (*sysit)->GetRoomLocation();
            Vec2i shape = (*sysit)->GetRoomShape();
            for(i64 x = corner.X(); x < corner.X()+shape.X(); x++) {
                for(i64 y = corner.Y(); y < corner.Y()+shape.Y(); y++) {
                    uptr<SCompartment> comp = std::make_unique<SCompartment>(
                        Vec3i(x,y,corner.Z()),
                        (*sysit)->GetSystemHealth(),
                        (*sysit)->GetStructuralHealth()
                    );
                    compartments.emplace(Vec3i(x,y,corner.Z()), std::move(comp));
                }
            }
        }
    }

}
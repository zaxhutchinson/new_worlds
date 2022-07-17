#include"ship.hpp"

Ship::Ship() 
    :id(-1), name("NONAME")
{}
Ship::Ship(i64 _id, str _name) 
    :id(_id), name(_name)
{

    for(int i = 0; i < static_cast<int>(SSysType::END); i++) {
        systems.emplace(
            static_cast<SSysType>(i), vuptr<SSys>()
        );
    }
}

vuptr<SSys> & Ship::GetComponentList(SSysType type) {
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
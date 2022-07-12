#include"ship.hpp"

Ship::Ship() 
    :id(-1), name("NONAME"), shape(Vec3i())
{}
Ship::Ship(i64 _id, str _name, Vec3i _shape) 
    :id(_id), name(_name), shape(_shape)
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
        Build all compartments as hulls 
    ------------------------------------------------------------------------*/
    vuptr<SSys> & syslist = GetComponentList(SSysType::Hull);

    if(syslist.size()==0) return;   // design has empty hull syslist.

    SSys * sys = syslist[0].get();

    SHull * hull = dynamic_cast<SHull*>(sys);

    if(!hull) return;   // sys was not a hull.

    i64 system_health = hull->GetSystemHealth();
    i64 structural_health = hull->GetStructuralHealth();

    for(i64 x = 0; x < shape.X(); x++) {
        for(i64 y = 0; y < shape.Y(); y++) {
            for(i64 z = 0; z < shape.Z(); z++) {
                uptr<SCompartment> comp = std::make_unique<SCompartment>(
                    Vec3i(x,y,z),
                    system_health,
                    structural_health
                );
                compartments.emplace(Vec3i(x, y, z), std::move(comp));
            }
        }
    }

    /* -----------------------------------------------------------------------
        Populate other systems.
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
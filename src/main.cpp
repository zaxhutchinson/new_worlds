
#include<iostream>
#include"galaxy_builder.hpp"
#include"ship_builder.hpp"

int main(int argc, char** argv) {

    std::random_device rd;
    RNG rng(rd());

    uptr<Galaxy> galaxy = BuildNewGalaxy("default");
    std::cout << galaxy->GetSystem("cadia")->GetDesc() << std::endl;

    ShipBuilder sb;
    sb.LoadTemplates("default");

    ShipSpec ss;
    ss.ship_id = "ship_2";
    ss.min_xp = 70;
    ss.max_xp = 90;
    Ship ship = sb.BuildShip(ss,&rng);
    ship.CalculateCrewEffectiveness(&rng);
    std::cout << ship.GetName() << " " 
        << ship.GetCompsOfType(CompType::Engine)->at(0).GetCrew()->GetCrewEffectiveness()
        << std::endl;

    return 0;
}


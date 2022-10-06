
#include<iostream>
#include"galaxy_builder.hpp"
#include"ship_builder.hpp"
#include"fleet.hpp"

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
    uptr<Ship> shipA = sb.BuildShip(ss);
    uptr<Ship> shipB = sb.BuildShip(ss);

    Fleet fleet("TF 1");
    fleet.AddShip(std::move(shipA));
    fleet.AddShip(std::move(shipB));

    Ship * s1 = fleet.FindShip("ship_2_1");
    if(s1)
        std::cout << s1->GetName() << std::endl;
    else
        std::cout << "Not a valid ship\n";

    
    uptr<Ship> removed_ship = fleet.RemoveShip("ship_2_1");

    std::cout << removed_ship->GetName() << std::endl;

    s1 = fleet.FindShip("ship_2_1");
    if(s1)
        std::cout << s1->GetName() << std::endl;
    else
        std::cout << "Not a valid ship\n";

    // std::cout << shipA.GetID() << " " << shipB.GetID() << std::endl;
    // shipA.CalculateCrewEffectiveness(&rng);
    // std::cout << shipA.GetName() << " " 
    //     << shipA.GetCompsOfType(CompType::Engine)->at(0).GetCrew()->GetCrewEffectiveness()
    //     << std::endl;

    return 0;
}


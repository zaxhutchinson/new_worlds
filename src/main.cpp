
#include<iostream>
#include"galaxy_builder.hpp"
#include"ship_builder.hpp"

int main(int argc, char** argv) {

    uptr<Galaxy> galaxy = BuildNewGalaxy("default");
    std::cout << galaxy->GetSystem("cadia")->GetDesc() << std::endl;

    ShipBuilder sb;
    sb.LoadTemplates("default");
    Ship ship = sb.BuildShip("ship_2");
    std::cout << ship.GetName() << " " << ship.GetShields()[0].GetDesc() << std::endl;

    return 0;
}


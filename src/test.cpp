#include"test.hpp"


namespace test {

    void TestShipSysDictLoading() {

        bool sys_good = shipfactory::LoadShipSysDict("default","ship_sys.json");
        bool ship_good = shipfactory::LoadShipDict("default","ship_sys.json");

        std::cout << "TestShipSysDictLoading: ShipSys " << sys_good << std::endl;
        std::cout << "TestShipSysDictLoading: Ship    " << ship_good << std::endl;

    }



}
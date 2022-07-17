#include"test.hpp"


namespace test {

    void OutputEq(str msg, bool expected, bool actual) {
        if(expected==actual) {
            fmt::print(fg(fmt::color::green), msg+" {} == {}\n", expected, actual);
        } else {
            fmt::print(fg(fmt::color::red), msg+" {} != {}\n", expected, actual);
        }
        fg(fmt::color::white);
    }
    void OutputNeq(str msg, bool expected, bool actual) {
        if(expected!=actual) {
            fmt::print(fg(fmt::color::green), msg+" {} == {}\n", expected, actual);
        } else {
            fmt::print(fg(fmt::color::red), msg+" {} != {}\n", expected, actual);
        }
        fg(fmt::color::white);
    }
    void OutputEq(str msg, int expected, int actual) {
        if(expected==actual) {
            fmt::print(fg(fmt::color::green), msg+" {} == {}\n", expected, actual);
        } else {
            fmt::print(fg(fmt::color::red), msg+" {} != {}\n", expected, actual);
        }
        fg(fmt::color::white);
    }
    void OutputEq(str msg, double expected, double actual) {
        if(expected==actual) {
            fmt::print(fg(fmt::color::green), msg+" {} == {}\n", expected, actual);
        } else {
            fmt::print(fg(fmt::color::red), msg+" {} != {}\n", expected, actual);
        }
        fg(fmt::color::white);
    }
    void OutputEq(str msg, float expected, float actual) {
        if(expected==actual) {
            fmt::print(fg(fmt::color::green), msg+" {} == {}\n", expected, actual);
        } else {
            fmt::print(fg(fmt::color::red), msg+" {} != {}\n", expected, actual);
        }

        fg(fmt::color::white);
    }

    void RunAllTests() {
        TestShipSysDictLoading();
        TestBuildShip();
    }

    void TestShipSysDictLoading() {

        bool sys_good = shipfactory::LoadShipSysDict("default","ship_sys.json");
        bool ship_good = shipfactory::LoadShipDict("default","ship.json");

        OutputEq("TestShipSysDictLoading: ShipSys",true,sys_good);
        OutputEq("TestShipSysDictLoading: Ship",true,ship_good);

    }

    void TestBuildShip() {
        uptr<Ship> ship = shipfactory::BuildShip("ship_001");

        OutputEq("TestBuildShip: ",false,ship==nullptr);

        shipfactory::ShipToASCII(ship.get());
    }

}
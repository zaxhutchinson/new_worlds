#include"test.hpp"


namespace test {

    void Output(str msg, bool expected, bool actual) {
        if(expected==actual) {
            fmt::print(fg(fmt::color::green), msg+" {} == {}\n", expected, actual);
        } else {
            fmt::print(fg(fmt::color::red), msg+" {} != {}\n", expected, actual);
        }
    }
    void Output(str msg, int expected, int actual) {
        if(expected==actual) {
            fmt::print(fg(fmt::color::green), msg+" {} == {}\n", expected, actual);
        } else {
            fmt::print(fg(fmt::color::red), msg+" {} != {}\n", expected, actual);
        }
    }
    void Output(str msg, double expected, double actual) {
        if(expected==actual) {
            fmt::print(fg(fmt::color::green), msg+" {} == {}\n", expected, actual);
        } else {
            fmt::print(fg(fmt::color::red), msg+" {} != {}\n", expected, actual);
        }
    }
    void Output(str msg, float expected, float actual) {
        if(expected==actual) {
            fmt::print(fg(fmt::color::green), msg+" {} == {}\n", expected, actual);
        } else {
            fmt::print(fg(fmt::color::red), msg+" {} != {}\n", expected, actual);
        }
    }

    void TestShipSysDictLoading() {

        bool sys_good = shipfactory::LoadShipSysDict("default","ship_sys.json");
        bool ship_good = shipfactory::LoadShipDict("default","ship_sys.json");

        Output("TestShipSysDictLoading: ShipSys",true,sys_good);
        Output("TestShipSysDictLoading: Ship",true,ship_good);

    }



}
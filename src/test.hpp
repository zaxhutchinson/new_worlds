#pragma once

#include<iostream>

#include"ship_factory.hpp"


namespace test {

    void Output(str msg, bool expected, bool actual);
    void Output(str msg, int expected, int actual);
    void Output(str msg, double expected, double actual);
    void Output(str msg, float expected, float actual);

    // Test Loading ship_sys json files
    void TestShipSysDictLoading();

}
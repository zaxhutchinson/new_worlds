#pragma once

#include<iostream>

#include"ship_factory.hpp"


namespace test {

    void OutputEq(str msg, bool expected, bool actual);
    void OutputNeq(str msg, bool expected, bool actual);
    void OutputEq(str msg, int expected, int actual);
    void OutputEq(str msg, double expected, double actual);
    void OutputEq(str msg, float expected, float actual);

    void RunAllTests();

    // Test Loading ship_sys json files
    void TestShipSysDictLoading();

    // Test loading the test ship from the default mod
    void TestBuildShip();

}
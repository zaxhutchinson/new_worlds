
#include<iostream>

#include"test.hpp"

void RunTests();

int main(int argc, char** argv) {

    RunTests();

    // uptr<SScanner> scanner = std::make_unique<SScanner>();
    // scanner->Init_SSys(
    //     SSysType::Scanner,
    //     100,
    //     100,
    //     10,
    //     Vec3i(),
    //     Vec2i(),
    //     1,
    //     STeamType::Command
    // );
    // scanner->Init_SScanner(
    //     100.0,
    //     1
    // );

    // uptr<SSys> sys = std::move(scanner);

    // SScanner * s = dynamic_cast<SScanner*>(sys.get());
    // std::cout << s->GetScanDistance() << std::endl;



    return 0;
}





void RunTests() {
    test::TestShipSysDictLoading();
}
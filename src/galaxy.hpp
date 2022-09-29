#pragma once

#include"zxlb.hpp"
#include"system.hpp"
#include"vec2i.hpp"

class Galaxy {
private:
    umap<ID, System> systems;
public:
    Galaxy();

    void AddSystem(System sys);
    System * GetSystem(ID id);
};
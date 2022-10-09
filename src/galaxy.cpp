#include"galaxy.hpp"

Galaxy::Galaxy() {}



void Galaxy::AddSystem(System sys) {
    systems.emplace(sys.GetID(), std::move(sys));
}
System * Galaxy::GetSystem(ID id) {
    try {
        return &(systems.at(id));
    } catch(std::out_of_range & e) {
        return nullptr;
    }
}
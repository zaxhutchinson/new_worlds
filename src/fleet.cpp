#include"fleet.hpp"


Fleet::Fleet() 
    : id("NONE")
{}

Fleet::Fleet(ID _id)
    : id(_id)
{}

ID Fleet::GetID() const {
    return id;
}
str Fleet::GetDesc() const {
    return desc;
}
void Fleet::SetDesc(str _desc) {
    desc = _desc;
}
void Fleet::AddShip(uptr<Ship> s) {
    ships.push_back(std::move(s));
}
Ship * Fleet::FindShip(ID id) {
    for(
        luptr<Ship>::iterator it = ships.begin();
        it != ships.end(); it++
    ) {
        if(id == (*it)->GetID()) {
            return it->get();
        }
    }
    return nullptr;
}
uptr<Ship> Fleet::RemoveShip(ID id) {
    for(
        luptr<Ship>::iterator it = ships.begin();
        it != ships.end(); it++
    ) {
        if(id == (*it)->GetID()) {
            uptr<Ship> s = std::move(*it);
            ships.erase(it);
            return s;
        }
    }
    return nullptr;
}
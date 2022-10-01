#include"ship_layer.hpp"


ShipLayer::ShipLayer() {}
ShipLayer::ShipLayer(
    int _layer,
    double _mass,
    double _health
)
    : layer(_layer), mass(_mass), health(_health)
{}

int ShipLayer::GetLayer() const { return layer; }
double ShipLayer::GetMass() const { return mass; }
double ShipLayer::GetHealth() const { return health; }
void ShipLayer::SetHealth(double amt) {
    health = amt;
}
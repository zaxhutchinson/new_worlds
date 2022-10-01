#pragma once

#include"zxlb.hpp"
#include"ship_comps.hpp"

class ShipLayer {
private:
    int layer;
    double mass;
    double health;
    vec<Engine*> engines;
    vec<Weapon*> weapons;
    vec<Shields*> shields;
    vec<Reactor*> reactors;
    vec<MogDrive*> mogdrives;
public:
    ShipLayer();
    ShipLayer(
        int _layer,
        double _mass,
        double _health
    );
    ShipLayer(const ShipLayer & s) = default;
    ShipLayer(ShipLayer && s) = default;
    ShipLayer& operator=(const ShipLayer & s) = default;
    ShipLayer& operator=(ShipLayer && s) = default;
    int GetLayer() const;
    double GetMass() const;
    double GetHealth() const;
    void SetHealth(double amt);
};

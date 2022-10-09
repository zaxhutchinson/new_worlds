#pragma once

#include"zxlb.hpp"
#include"magic_enum.hpp"
enum class FacAbilityType {
    ShipConstruction,
    ArmyTraining,
    Mining,
    Extraction,
    Recruitment,
    END
};

class FacAbility {
private:
    ID id;
    FacAbilityType type;
    vec<double> data;
    double health;
public:
    FacAbility();
    FacAbility(ID _id, FacAbilityType _type, vec<double> _data, double _health);
    FacAbility(const FacAbility & f) = default;
    FacAbility(FacAbility && f) = default;
    FacAbility& operator=(const FacAbility & f) = default;
    FacAbility& operator=(FacAbility && f) = default;
    ID GetID() const;
    FacAbilityType GetFacAbilityType() const;
    strv GetFacAbilityTypeAsString();
    vec<double> & GetData();
    double GetHealth() const;
    void SetHealth(double _health);
};

class Facility {
private:
    ID id;
    str name;
    str desc;
    vec<FacAbility> abilities;
public:
    Facility();
    Facility(ID _id, str _name, vec<FacAbility> _abilities);
    Facility(const Facility & f) = default;
    Facility(Facility && f) = default;
    Facility& operator=(const Facility & f) = default;
    Facility& operator=(Facility && f) = default;
    ID GetID() const;
    str GetName() const;
    str GetDesc();
    vec<FacAbility> & GetAbilities();
    bool HasAbilityType(FacAbilityType fat);
};
#pragma once

#include"zxlb.hpp"
#include"enums.hpp"


class FacConstruction {
private:
    vec<ShipClass> ship_classes;
    vec<UnitClass> unit_classes;
    vec<double> reses_per_tick;
public:
    FacConstruction();
    FacConstruction(
        vec<ShipClass> _ship_classes,
        vec<UnitClass> _unit_classes,
        vec<double> _reses_per_tick
    );
    FacConstruction(const FacConstruction & f) = default;
    FacConstruction(FacConstruction && f) = default;
    FacConstruction& operator=(const FacConstruction & f) = default;
    FacConstruction& operator=(FacConstruction && f) = default;
    vec<ShipClass> & GetShipClasses();
    vec<UnitClass> & GetUnitClasses();
    bool HasShipClass(int sc) const;
    bool HasUnitClass(int uc) const;
    vec<double> & GetResesPerTick();
    double GetResPerTick(ResType rt);
};

class FacProduction {
private:
    umap<ResType,double> rates;
public:
    FacProduction();
    FacProduction(
        umap<ResType,double> _rates
    );
    FacProduction(const FacProduction & f) = default;
    FacProduction(FacProduction && f) = default;
    FacProduction& operator=(const FacProduction & f) = default;
    FacProduction& operator=(FacProduction && f) = default;
    umap<ResType,double> & GetRates();
    double GetRate(ResType rt);
};


class FacGovernment {
private:
    double tax_rate;
public:
    FacGovernment();
    FacGovernment(
        double _tax_rate
    );
    FacGovernment(const FacGovernment & f) = default;
    FacGovernment(FacGovernment && f) = default;
    FacGovernment& operator=(const FacGovernment & f) = default;
    FacGovernment& operator=(FacGovernment && f) = default;
    double GetTaxRate() const;
};

class Facility {
private:
    ID id;
    str name;
    str desc;
    vec<ID> prereqs;
    vec<ID> postreqs;
    uptr<FacConstruction> construction;
    uptr<FacProduction> production;
    uptr<FacGovernment> government;
public:
    Facility();
    Facility(ID _id, str _name, vec<ID> _prereqs, vec<ID> _postreqs);
    Facility(Facility && f) = default;
    Facility& operator=(Facility && f) = default;
    ID GetID() const;
    str GetName() const;
    str GetDesc();
    vec<ID> & GetPrereqs();
    vec<ID> & GetPostreqs();
};
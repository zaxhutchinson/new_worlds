#pragma once

#include"zxlb.hpp"


enum class ResType {
    Population,
    Materiel,
    Fuel,

    END
};


class System {
private:
    static constexpr double INFRASTRUCTURE_MULTIPLIER_BASE[3] = {
        10.0,
        10.0,
        10.0
    };
    static constexpr double MAX_STABILITY = 100.0;
    static constexpr double MAX_ECONOMY = 100.0;
    static constexpr double MAX_LOYALTY = 100.0;

    ID id;
    str name;
    str desc;
    vec<double> resources;
    vec<double> infrastructure;
    double stability;
    double economy;
    umap<ID,double> loyalty;
public:
    System();
    System(
        ID _id, 
        str _name, 
        str _desc,
        vec<double> & _resources,
        vec<double> & _infrastructure,
        double _stability,
        double _economy
    );
    System(const System & system) = default;
    System(System && system) = default;
    System& operator=(const System & system) = default;
    System& operator=(System && system) = default;
    ID GetID() const;
    str GetName() const;
    str GetDesc() const;
    double GetBaseResource(ResType t) const;
    double GetEconomy() const;
    double GetInfrastructure(ResType t) const;
    double GetStability() const;
   
    void InitLoyalty(vec<ID> & all_faction_ids);

    double GetInfrastructureMultiplier(ResType t) const;
    double GetActualResource(ResType t) const;

    double CalculateTaxes();

    void LowerStability(double amt);
    void RaiseStability(double amt);
    void LowerEconomy(double amt);
    void RaiseEconomy(double amt);
    void ChangeLoyalty(ID id, double amt);

};
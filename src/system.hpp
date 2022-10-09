#pragma once

#include"zxlb.hpp"
#include"enums.hpp"
#include"vec2i.hpp"
#include"facility.hpp"


class System {
private:
    static constexpr double MAX_STABILITY = 100.0;
    static constexpr double MAX_LOYALTY = 100.0;

    ID id;
    str name;
    str desc;
    Vec2i position;
    vec<double> resources;
    vec<double> infrastructure;
    double stability;
    umap<ID,double> loyalty;
    vec<Facility> facilities;
public:
    System();
    System(
        ID _id, 
        str _name, 
        str _desc,
        Vec2i _position,
        vec<double> & _resources,
        vec<double> & _infrastructure,
        double _stability
    );
    System(const System & system) = default;
    System(System && system) = default;
    System& operator=(const System & system) = default;
    System& operator=(System && system) = default;
    ID GetID() const;
    str GetName() const;
    str GetDesc() const;
    Vec2i GetPosition() const;
    double GetBaseResource(ResType t) const;
    double GetInfrastructure(ResType t) const;
    double GetStability() const;
    vec<Facility> & GetFacilities();
    void InitLoyalty(vec<ID> & all_faction_ids);
    void AddFacility(Facility facility);


    double GetActualResource(ResType t) const;

    void ChangeStability(double amt);
    void ChangeLoyalty(ID id, double amt);

};
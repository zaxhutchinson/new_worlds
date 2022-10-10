/*! \file galaxy.hpp
*/
#pragma once


#include"zxlb.hpp"
#include"system.hpp"
#include"vec2i.hpp"

/*! \class Galaxy galaxy.hpp
    \brief Galaxy stores and manages System objects.
    
    \details Something more detailed about galaxies.

*/

class Galaxy {
private:
    /*! \var umap<ID, System> systems
        \brief unordered_map of Systems stored by their IDs. 
    */
    umap<ID, System> systems; 
public:
    Galaxy();

    /*! \fn void AddSystem(System sys)
        \brief Adds a System to the Galaxy.
        \param sys A System object.
        \return none.
    */
    void AddSystem(System sys);

    /*! \fn System * GetSystem(ID id)
        \brief Gets a pointer to the System object with the specified ID.
        \param id A valid ID.
        \return A pointer to a System object, or nullptr if the ID does not exist.
    */
    System * GetSystem(ID id);
};
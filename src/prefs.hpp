#pragma once

#include<fstream>

#include"zxlb.hpp"
#include"json.hpp"

namespace prefs {

    inline bool prefs_loaded = false;

    void LoadPrefs(str modname);
    void LoadGalaxyPrefs(str modname);


    /* ------------------ GENERAL PREFERENCES ------------------ */
    /* Is this a random game? If it is, the galaxy.json will have prefs
        for these variables which determine the look of the randomly generated
        galaxy. If false, then the galaxy.json file will spell out a galaxy
        exactly. */

    inline bool random_galaxy = true;

    /* ------------------ RANDOM GALAXY PREFERENCES ------------------ */

    /* Size of the galaxy */
    inline int galaxy_X = 1000;
    inline int galaxy_Y = 1000;

    /* Number of systems in the galaxy */
    inline int number_of_systems = 200;

    /* System names: This list of names is given to the systems. You don't
        need more than the number of systems. */
    inline vec<str> system_names;

    /* Number of Factions */
    inline int number_of_factions = 10;
}
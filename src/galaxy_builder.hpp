#pragma once

#include<fstream>
#include<iostream>

#include"zxlb.hpp"
#include"prefs.hpp"
#include"galaxy.hpp"
#include"json.hpp"

uptr<Galaxy> BuildNewGalaxy(str modname);
uptr<Galaxy> BuildDefinedGalaxy(str modname);
uptr<Galaxy> BuildRandomGalaxy(str modname);
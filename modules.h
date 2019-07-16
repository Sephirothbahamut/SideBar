#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

#include <algorithm>
#include <dwmapi.h>
#include "settings.h"

#pragma comment (lib, "dwmapi.lib")

//myincludes
#include "Win.h"
#include "defines.h"
#include "PartSystem.h"
//#include "OldPartSystem.h"
#include "BarnackClock.h"
#include "BarButton.h"

int bar_main();
int prompt_main();
int bottom_main();
int wallpaper_main();
//int mouse_effects_main();
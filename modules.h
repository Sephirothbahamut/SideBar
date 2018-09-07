#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <dwmapi.h>
#include "tinyxml2.h"

#define xml tinyxml2

#pragma comment (lib, "dwmapi.lib")

//myincludes
#include "Screen.h"
#include "Win.h"
#include "autorun.h"
#include "defines.h"
#include "PartSystem.h"
//#include "OldPartSystem.h"
#include "BarnackClock.h"
#include "BarButton.h"

int bar_main();
int prompt_main();
int bottom_main();
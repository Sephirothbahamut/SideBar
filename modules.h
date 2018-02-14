#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <dwmapi.h>
#include "tinyxml2.h"
#include <thread>

#define xml tinyxml2

#pragma comment (lib, "dwmapi.lib")

//myincludes
#include "Screen.h"
#include "Win.h"
#include "autorun.h"
#include "defines.h"
#include "PartSystem.h"
#include "BarnackClock.h"
#include "BarButton.h"
#include "modules.h"

int bar_main();
int prompt_main();
int bottom_main();
#pragma once

// Windows specific Includes
#ifdef RAD_PLATFORM_WINDOWS
//#include <Windows.h>
#endif

#include <stdint.h>

// STL Includes
#include <iostream>
#include <memory>
#include <functional>
#include <fstream>
#include <mutex>

// STL Datastructure & Algorithms
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>

// Vendors
#include <imgui.h>
#include <glm/glm.hpp>

#include "Radiance/Base.h"
#include "Radiance/Core/Logger.h"
#include "Radiance/Core/Time.h"
#include "Radiance/Input.h"
#include "Radiance/KeyCodes.h"
#include "Radiance/MouseButtonCodes.h"
#include "Radiance/Core/Locator.h"
#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif // Windows Platform

#include <utility>
#include <stdlib.h>
#include <functional>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <iostream>

#include <string>
#include <queue>
#include <deque>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <unordered_map>
#include <list>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "IO/Logger.h"
#include "IO/GL_Logger.h"

//Defines
#define BIT(x) 1 << x
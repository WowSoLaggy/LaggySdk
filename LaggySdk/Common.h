#pragma once

#define NOMINMAX
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#define _ENABLE_EXTENDED_ALIGNED_STORAGE
#include <Windows.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <functional>
#include <future>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <random>
#include <regex>
#include <set>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>
#include <vector>

#include "dirent.h"


namespace fs = std::experimental::filesystem;
using namespace std::literals;

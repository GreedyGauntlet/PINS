#pragma once

// standard
#include <functional>
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <stdint.h>
#include <cstring>
#include <random>
#include <thread>

// windows only
#if _WIN32
#include <Windows.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

// needles
#include "Internal/Log.h"

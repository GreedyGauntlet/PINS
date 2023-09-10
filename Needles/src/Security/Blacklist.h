#pragma once
#include <vector>
#include "Core/Structures.h"

namespace Needles {
	class Blacklist {
	public:
		static void Add(IPAddress ip);
		static void Remove(IPAddress ip);
		static void Clear();
		static bool Has(IPAddress ip);
		static bool Authorize(IPAddress ip);
		static std::vector<IPAddress> GetAll();
	};
}
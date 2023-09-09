#include "ndlpch.h"
#include "Blacklist.h"

namespace Needles {
	std::vector<IPAddress> s_BlacklistedAddresses;

	void Blacklist::Add(IPAddress ip) {
		s_BlacklistedAddresses.push_back(ip);
	}

	void Blacklist::Remove(IPAddress ip) {
		for (int i = 0; i < s_BlacklistedAddresses.size(); i++) {
			IPAddress tmp = s_BlacklistedAddresses[i];
			if (std::equal(std::begin(ip.IPv4), std::end(ip.IPv4), std::begin(tmp.IPv4)) &&
				std::equal(std::begin(ip.IPv6), std::end(ip.IPv6), std::begin(tmp.IPv6))) {
				s_BlacklistedAddresses.erase(s_BlacklistedAddresses.begin() + i);
				if (Has(ip))
					i--;
				else return;
			}
		}
	}

	void Blacklist::Clear() {
		s_BlacklistedAddresses.clear();
	}

	bool Blacklist::Has(IPAddress ip) {
		for (int i = 0; i < s_BlacklistedAddresses.size(); i++)
			if (std::equal(std::begin(ip.IPv4), std::end(ip.IPv4), std::begin(s_BlacklistedAddresses[i].IPv4)) &&
				std::equal(std::begin(ip.IPv6), std::end(ip.IPv6), std::begin(s_BlacklistedAddresses[i].IPv6)))
				return true;
		return false;
	}

	bool Blacklist::Authorize(IPAddress ip) {
		return !Has(ip);
	}

	std::vector<IPAddress> Blacklist::GetAll() {
		return s_BlacklistedAddresses;
	}
}
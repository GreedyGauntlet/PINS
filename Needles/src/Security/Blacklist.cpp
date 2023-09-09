#include "ndlpch.h"
#include "Blacklist.h"

namespace Needles {
	std::vector<IPAddress> s_IPAddresses;

	void Blacklist::Add(IPAddress ip) {
		s_IPAddresses.push_back(ip);
	}

	void Blacklist::Remove(IPAddress ip) {
		for (int i = 0; i < s_IPAddresses.size(); i++) {
			IPAddress tmp = s_IPAddresses[i];
			if (std::equal(std::begin(ip.IPv4), std::end(ip.IPv4), std::begin(tmp.IPv4)) &&
				std::equal(std::begin(ip.IPv6), std::end(ip.IPv6), std::begin(tmp.IPv6))) {
				s_IPAddresses.erase(s_IPAddresses.begin() + i);
				if (Has(ip))
					i--;
				else return;
			}
		}
	}

	void Blacklist::Clear() {
		s_IPAddresses.clear();
	}

	bool Blacklist::Has(IPAddress ip) {
		for (int i = 0; i < s_IPAddresses.size(); i++)
			if (std::equal(std::begin(ip.IPv4), std::end(ip.IPv4), std::begin(s_IPAddresses[i].IPv4)) &&
				std::equal(std::begin(ip.IPv6), std::end(ip.IPv6), std::begin(s_IPAddresses[i].IPv6)))
				return true;
		return false;
	}

	bool Blacklist::Authorize(IPAddress ip) {
		return !Has(ip);
	}

	std::vector<IPAddress> Blacklist::GetAll() {
		return s_IPAddresses;
	}
}
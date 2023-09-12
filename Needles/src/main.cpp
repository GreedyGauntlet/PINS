#include "ndlpch.h"
#include "Testing/TestHandler.h"
#include "Security/Encryption.h"
#include "Security/Whitelist.h"
#include "Security/Blacklist.h"
#include "Utils/DataUtils.h"
#include "Core/Packet.h"
#include "Core/Client.h"
#include "Core/Server.h"

using namespace Needles;

#define TEST(name, code) TestHandler::AddTest(name, [=]() -> bool { code });

int main() {
	Log::Init();

	TestHandler::AddTest("generate encryption seed test", [=]() -> bool {
		Seed seed = Encryption::GenerateSeed();
		if (seed.Size != 32 && seed.Size != 16 && seed.Size != 24)
			return false;
		bool nonzero = false;
		for (uint8_t i = 0; i < seed.Size; i++)
			if (seed.Bytes[i] != 0)
				nonzero = true;
		return nonzero;
	});

	TestHandler::AddTest("get/set encryption seed test", [=]() -> bool {
		Seed prior_seed = Encryption::GenerateSeed();
		Encryption::SetSeed(prior_seed);
		Seed post_seed = Encryption::GetSeed();
		bool verified = true;
		if (prior_seed.Size != post_seed.Size)
			verified = false;
		for (uint8_t i = 0; i < post_seed.Size; i++)
			if (post_seed.Bytes[i] != prior_seed.Bytes[i])
				verified = false;
		return verified;
	});

	TestHandler::AddTest("encrypt/decrypt test", [=]() -> bool {
		Seed seed = Encryption::GenerateSeed();
		Encryption::SetSeed(seed);

		Data data;
		data.Size = 16;
		uint8_t base_string[16] = "Hello, World!";
		uint8_t data_string[16] = "Hello, World!";
		data.Bytes = data_string;

		Encryption::Encrypt(data);
		bool encrypted = false;
		for (int i = 0; i < data.Size; i++)
			if (data.Bytes[i] != base_string[i])
				encrypted = true;
		if (!encrypted) return false;

		Encryption::Decrypt(data);
		bool decrypted = true;
		for (int i = 0; i < data.Size; i++)
			if (data.Bytes[i] != base_string[i])
				decrypted = false;
		return decrypted;
	});

	TestHandler::AddTest("data utils test", [=]() -> bool {
		int numeric_data = 69;
		std::string string_data = "This is a string of data I want to turn into a data object!!";
		char array_data[38] = "Bro this is not a huge amount of data";
	
		Data ndata = DataUtils::ToData<int>(numeric_data);
		Data sdata = DataUtils::ToData<std::string>(string_data);
		Data adata = DataUtils::ToData<char[38]>(array_data);
		if (ndata.Size == 1 ||
			sdata.Size == 0 ||
			adata.Size != 38 ||
			ndata.Bytes == nullptr ||
			sdata.Bytes == nullptr ||
			adata.Bytes == nullptr)
			return false;
	
		int end_numeric_data = DataUtils::FromData<int>(ndata);
		std::string end_string_data = DataUtils::FromData<std::string>(sdata);
		char* end_array_data = (char*)DataUtils::FromData(adata);
		if (end_numeric_data != numeric_data ||
			end_string_data != string_data ||
			std::string(end_array_data) != std::string(array_data))
			return false;
		return true;
	});

	TestHandler::AddTest("packet bytes test", [=]() -> bool {
		PacketConfig config;
		config.Guest = true;
		config.Type = PacketType::UDP;
		char authkey[AUTH_KEY_SIZE] = "this is a sweet key";
		char uid[UID_SIZE] = "username Jason";
		memcpy(config.Authentication, authkey, AUTH_KEY_SIZE);
		memcpy(config.UID, uid, UID_SIZE);
		Data data = DataUtils::ToData<std::string>("This is my cool packet data, isn't it awesome?!?");
	
		Packet packet = Packet(data, config);
		uint8_t* bytes = packet.Bytes();
		uint16_t size = DataUtils::FromBytes<uint16_t>(bytes);
		if (size != packet.Size())
			return false;

		uint8_t flags = DataUtils::FromBytes<uint8_t>(bytes + 2);
		if (flags != 0x01)
			return false;

		char* p_uid = DataUtils::FromBytes<char*>(bytes + 3, UID_SIZE);
		char* p_authkey = DataUtils::FromBytes<char*>(bytes + 3 + UID_SIZE, AUTH_KEY_SIZE);
		if (std::string(p_uid) != std::string(uid) || std::string(p_authkey) != std::string(authkey))
			return false;

		for (int i = 0; i < data.Size; i++)
			if (data.Bytes[i] != bytes[i + 3 + UID_SIZE + AUTH_KEY_SIZE])
				return false;

		return true;
	});

	TestHandler::AddTest("load packet test", [=]() -> bool {
		PacketConfig config;
		config.Guest = true;
		config.Type = PacketType::UDP;
		char authkey[AUTH_KEY_SIZE] = "this is a sweet key";
		char uid[UID_SIZE] = "username Jason";
		memcpy(config.Authentication, authkey, AUTH_KEY_SIZE);
		memcpy(config.UID, uid, UID_SIZE);
		Data data = DataUtils::ToData<std::string>("This is my cool packet data, isn't it awesome?!?");
		Packet packet = Packet(data, config);
		uint8_t* bytes = packet.Bytes();

		Packet loaded = Packet::LoadPacket(bytes);
		if (loaded.Size() != packet.Size()) return false;
		uint8_t* loaded_bytes = loaded.Bytes();
		for (int i = 0; i < loaded.Size(); i++)
			if (bytes[i] != loaded_bytes[i])
				return false;
		return true;
	});

	TestHandler::AddTest("whitelist test", [=]() -> bool {  
		uint8_t ipv4_example_1[] = { 0x0f, 0x50, 0xab, 0x6f };
		uint8_t ipv4_example_2[] = { 0x8b, 0x56, 0xfa, 0xaa };
		uint8_t ipv4_example_3[] = { 0x76, 0x56, 0xbb, 0xa9 };
		uint8_t ipv6_example_1[] = { 0x10, 0x23, 0x45, 0x6f, 0x12, 0x26, 0x4f, 0x6a, 0xd0, 0xb3, 0xef, 0x66, 0x6f, 0x23, 0x45, 0x6f, };
		uint8_t ipv6_example_2[] = { 0x10, 0x53, 0x66, 0x90, 0x9a, 0x9b, 0x4f, 0x6a, 0xd4, 0xb3, 0xef, 0x86, 0x6f, 0x77, 0x45, 0x7a, };
		uint8_t ipv6_example_3[] = { 0x12, 0x53, 0x66, 0x90, 0x9a, 0xfb, 0x4f, 0x6a, 0xd4, 0xb3, 0xaf, 0x86, 0x6f, 0x72, 0x45, 0x7a, };

		IPAddress ipv4;
		IPAddress ipv6;
		IPAddress ipvBoth;
		memcpy(ipv4.IPv4, ipv4_example_1, 4);
		memcpy(ipvBoth.IPv4, ipv4_example_2, 4);
		memcpy(ipv6.IPv6, ipv6_example_1, 16);
		memcpy(ipvBoth.IPv6, ipv6_example_2, 16);

		IPAddress test_ipv4;
		IPAddress test_ipv6;
		IPAddress test_ipvBoth;
		IPAddress newIP;
		memcpy(test_ipv4.IPv4, ipv4_example_1, 4);
		memcpy(test_ipvBoth.IPv4, ipv4_example_2, 4);
		memcpy(newIP.IPv4, ipv4_example_3, 4);
		memcpy(test_ipv6.IPv6, ipv6_example_1, 16);
		memcpy(test_ipvBoth.IPv6, ipv6_example_2, 16);
		memcpy(newIP.IPv6, ipv6_example_3, 16);

		Whitelist::Clear();
		Whitelist::Add(ipv4);
		Whitelist::Add(ipv6);
		Whitelist::Add(ipvBoth);

		if (!Whitelist::Authorize(test_ipv4))
			return false;
		if (!Whitelist::Authorize(test_ipv6))
			return false;
		if (!Whitelist::Authorize(test_ipvBoth))
			return false;
		if (Whitelist::Authorize(newIP))
			return false;

		Whitelist::Clear();
		return true;
	});

	TestHandler::AddTest("blacklist test", [=]() -> bool {
		uint8_t ipv4_example_1[] = { 0x0f, 0x50, 0xab, 0x6f };
		uint8_t ipv4_example_2[] = { 0x8b, 0x56, 0xfa, 0xaa };
		uint8_t ipv4_example_3[] = { 0x76, 0x56, 0xbb, 0xa9 };
		uint8_t ipv6_example_1[] = { 0x10, 0x23, 0x45, 0x6f, 0x12, 0x26, 0x4f, 0x6a, 0xd0, 0xb3, 0xef, 0x66, 0x6f, 0x23, 0x45, 0x6f, };
		uint8_t ipv6_example_2[] = { 0x10, 0x53, 0x66, 0x90, 0x9a, 0x9b, 0x4f, 0x6a, 0xd4, 0xb3, 0xef, 0x86, 0x6f, 0x77, 0x45, 0x7a, };
		uint8_t ipv6_example_3[] = { 0x12, 0x53, 0x66, 0x90, 0x9a, 0xfb, 0x4f, 0x6a, 0xd4, 0xb3, 0xaf, 0x86, 0x6f, 0x72, 0x45, 0x7a, };

		IPAddress ipv4;
		IPAddress ipv6;
		IPAddress ipvBoth;
		memcpy(ipv4.IPv4, ipv4_example_1, 4);
		memcpy(ipvBoth.IPv4, ipv4_example_2, 4);
		memcpy(ipv6.IPv6, ipv6_example_1, 16);
		memcpy(ipvBoth.IPv6, ipv6_example_2, 16);

		IPAddress test_ipv4;
		IPAddress test_ipv6;
		IPAddress test_ipvBoth;
		IPAddress newIP;
		memcpy(test_ipv4.IPv4, ipv4_example_1, 4);
		memcpy(test_ipvBoth.IPv4, ipv4_example_2, 4);
		memcpy(newIP.IPv4, ipv4_example_3, 4);
		memcpy(test_ipv6.IPv6, ipv6_example_1, 16);
		memcpy(test_ipvBoth.IPv6, ipv6_example_2, 16);
		memcpy(newIP.IPv6, ipv6_example_3, 16);

		Blacklist::Clear();
		Blacklist::Add(ipv4);
		Blacklist::Add(ipv6);
		Blacklist::Add(ipvBoth);

		if (Blacklist::Authorize(test_ipv4))
			return false;
		if (Blacklist::Authorize(test_ipv6))
			return false;
		if (Blacklist::Authorize(test_ipvBoth))
			return false;
		if (!Blacklist::Authorize(newIP))
			return false;

		Blacklist::Clear();
		return true;
	});

	//initialize network and make client
	NetworkUtils::Initialize();
	Client client = Client();

	//create server and open it
	Server server = Server();
	server.Open(6000);

	//create the network address 127.0.0.1 on port 6000 (local on port 6000)
	NetworkAddress netad = { 0 };
	uint8_t ipv4[] = { 127, 0, 0, 1 };
	memcpy(netad.IP.IPv4, ipv4, 4);
	netad.Port = 6000;

	//wait like 2 seconds just in case for the thread to pick up
	uint64_t i = 0;
	while (i < 5000000000) {
		i++;
	}

	//try connecting
	client.Connect(netad);

	//clean up 
	client.Disconnect();
	server.Close();
	NetworkUtils::Shutdown();

	TestHandler::RunTests();

	return 0;
}
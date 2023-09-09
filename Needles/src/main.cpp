#include "ndlpch.h"
#include "Testing/TestHandler.h"
#include "Security/Encryption.h"
#include "Utils/DataUtils.h"

using namespace Needles;

#define TEST(name, code) TestHandler::AddTest(name, [=]() -> bool { code });

int main() {
	Log::Init();

	TEST("generate encryption seed test",
	Seed seed = Encryption::GenerateSeed();
	if (seed.Size != 32 && seed.Size != 16 && seed.Size != 24)
		return false;
	bool nonzero = false;
	for (uint8_t i = 0; i < seed.Size; i++)
		if (seed.Bytes[i] != 0)
			nonzero = true;
	return nonzero;
	);

	TEST("get/set encryption seed test",
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
	);

	TEST("encrypt/decrypt test",
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
	);

	TEST("data utils test", 
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
	);

	TestHandler::RunTests();
	return 0;
}
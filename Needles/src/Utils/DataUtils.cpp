#include "ndlpch.h"
#include "DataUtils.h"

namespace Needles {
    Data& DataUtils::ToData(const void* ptr, size_t size) {
        Data data;
        data.Size = size;
        data.Bytes = new uint8_t[size];
        std::memcpy(data.Bytes, ptr, size);
        return data;
    }

    void* DataUtils::FromData(const Data& data) {
        void* ptr = new uint8_t[data.Size];
        std::memcpy(ptr, data.Bytes, data.Size);
        return ptr;
    }
}
#include "ndlpch.h"
#include "DataUtils.h"

namespace Needles {

    template <typename T>
    Data& DataUtils::ToData(const T& typedata) {
        Data data;
        const uint8_t byte_array = reinterpret_cast<const uint8_t*>(&typedata);
        data.Size = sizeof(T);
        data.Bytes = new uint8_t[data.Size];
        std::memcpy(data.Bytes, byte_array, data.Size);
        return data;
    }

    template <typename T>
    T DataUtils::FromData(const Data& data) {
        T result;
        std::memcpy(&result, data.Bytes, data.Size);
        return result;
    }

}
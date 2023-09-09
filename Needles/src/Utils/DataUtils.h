#pragma once
#include "Core/Structures.h"

namespace Needles {
    class DataUtils {
    public:
        static Data& ToData(const void* ptr, size_t size);
        static void* FromData(const Data& data);
    public:
        template <typename T>
        static Data& ToData(const T& typedata) {
            return ToDataHelper<T>::ToData(typedata);
        }

        template <typename T>
        static T FromData(const Data& data) {
            return FromDataHelper<T>::FromData(data);
        }
    private:
        template <typename T>
        struct ToDataHelper {
            static Data& ToData(const T& typedata) {
                Data data;
                const uint8_t* byte_array = reinterpret_cast<const uint8_t*>(&typedata);
                data.Size = sizeof(T);
                data.Bytes = new uint8_t[data.Size];
                std::memcpy(data.Bytes, byte_array, data.Size);
                return data;
            }
        };

        template <>
        struct ToDataHelper<std::string> {
            static Data& ToData(const std::string& typedata) {
                Data data;
                data.Size = typedata.size();
                data.Bytes = new uint8_t[data.Size];
                std::memcpy(data.Bytes, typedata.data(), data.Size);
                return data;
            }
        };

        template <typename T, std::size_t N>
        struct ToDataHelper<T[N]> {
            static Data& ToData(const T(&typedata)[N]) {
                Data data;
                data.Size = N * sizeof(T);
                data.Bytes = new uint8_t[data.Size];
                std::memcpy(data.Bytes, typedata, data.Size);
                return data;
            }
        };

        template <typename T>
        struct FromDataHelper {
            static T FromData(const Data& data) {
                T result;
                std::memcpy(&result, data.Bytes, data.Size);
                return result;
            }
        };

        template <>
        struct FromDataHelper<std::string> {
            static std::string FromData(const Data& data) {
                return std::string(reinterpret_cast<const char*>(data.Bytes), data.Size);
            }
        };

        template <typename T, std::size_t N>
        struct FromDataHelper<T[N]> {
            static std::array<T, N> FromData(const Data& data) {
                std::array<T, N> result;
                std::memcpy(result.data(), data.Bytes, data.Size);
                return result;
            }
        };
    };
}
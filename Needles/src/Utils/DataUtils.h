#pragma once
#include "Core/Structures.h"

namespace Needles {
    class DataUtils {
    public:
        template <typename T>
        static Data& ToData(const T& typedata);

        template <typename T>
        static T FromData(const Data& data);
    };
}
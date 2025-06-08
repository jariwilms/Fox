#pragma once

#include "stdafx.hpp"

namespace fox::io::uuid
{
    static inline fox::uuid_t generate()
    {
        fox::uuid_t uuid{};

        uuid  |= distribution(generator);;
        uuid <<= 64;
        uuid  |= distribution(generator);

        //Version Signature (0b0100)
        uuid.set(51, false);
        uuid.set(50, true);
        uuid.set(49, false);
        uuid.set(48, false);

        //Variant Signature (0b10xx)
        uuid.set(65, true);
        uuid.set(64, false);

        return uuid;
    }

    static inline std::random_device                           device{};
    static inline std::mt19937                                 generator{ device() };
    static inline std::uniform_int_distribution<std::uint64_t> distribution{ 0, std::numeric_limits<std::uint64_t>::max() };
}

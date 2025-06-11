#pragma once

#include <bitset>

#include <fox/core/types/fundamental/fundamental.hpp>
//#include <fox/random/random.hpp>

namespace fox
{
    using uuid_t = std::bitset<128u>;
}
namespace fox::uuid
{
    //static inline auto generate() -> fox::uuid_t
    //{
    //    auto uuid  = fox::uuid_t{};
    //    auto upper = random::next<fox::uint64_t>();
    //    auto lower = random::next<fox::uint64_t>();
    //    
    //    uuid  |= upper;
    //    uuid <<= 64u;
    //    uuid  |= lower;

    //    //Version Signature (0b0100)
    //    uuid.set(51u, fox::False);
    //    uuid.set(50u, fox::True );
    //    uuid.set(49u, fox::False);
    //    uuid.set(48u, fox::False);

    //    //Variant Signature (0b10xx)
    //    uuid.set(65, true);
    //    uuid.set(64, false);

    //    return uuid;
    //}
}

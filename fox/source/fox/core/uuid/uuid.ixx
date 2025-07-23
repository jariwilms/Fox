export module fox.core.uuid;

import std;
import fox.core.types;
import fox.random;

export namespace fox::uuid
{
    auto generate() -> fox::uuid_t
    {
        auto uuid  = fox::uuid_t{};
        auto upper = random::next<fox::uint64_t>();
        auto lower = random::next<fox::uint64_t>();
        
        uuid  |= upper;
        uuid <<= fox::size_t{ 64u };
        uuid  |= lower;
        
        //Version Signature: 0b0100
        uuid.set(48u, fox::false_);
        uuid.set(49u, fox::false_);
        uuid.set(50u, fox::true_ );
        uuid.set(51u, fox::false_);

        //Variant Signature: 0b10xx
        uuid.set(64u, fox::false_);
        uuid.set(65u, fox::true_ );

        return uuid;
    }
}

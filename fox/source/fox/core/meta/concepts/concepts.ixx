export module fox.core.meta.concepts;

export namespace fox::meta
{
    inline namespace concepts
    {
        template<auto value, auto min, auto max>
        concept within_open_interval = requires
        {
            value > min and value < max;
        };
        template<auto value, auto min, auto max>
        concept within_closed_interval = requires
        {
            value >= min and value <= max;
        };
    }
}

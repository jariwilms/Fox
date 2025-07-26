export module fox.config;

import fox.core.types;

export namespace fox::cfg
{
    enum class build_configuration_e
    {
        debug, 
        release, 
    };

    constexpr auto flip_images         = fox::true_;
    constexpr auto build_configuration = cfg::build_configuration_e::debug;
}

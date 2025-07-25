export module fox.ecs.api;

import std;
import fox.core.types;
import vendor.entt;

export namespace fox::ecs::api
{
    using registry_t    = vendor::entt::registry;
    const auto registry = std::make_unique<api::registry_t>();
}

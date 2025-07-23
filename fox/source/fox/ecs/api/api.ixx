export module fox.ecs.api;

import std;
import fox.core.types;
import fox.ecs.api.entt;

export namespace fox::ecs::api
{
    using registry_t = entt::registry;
    auto  registry   = std::make_unique<api::registry_t>();
}

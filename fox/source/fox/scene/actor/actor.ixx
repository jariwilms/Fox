export module fox.scene.actor;

import fox.ecs.components;
import fox.ecs.entity;

export namespace fox
{
    class actor : public ecs::entity
    {
    public:
        actor()
        {
            add_component<ecs::relationship_component>();
            add_component<ecs::transform_component   >();
        }
    };
}

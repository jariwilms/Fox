#pragma once

#include <fox/ecs/system/system.hpp>

namespace fox
{
    class RenderSystem : public fox::System
    {
    public:
        void update() override
        {
            //start rendering here, iterate all components, then finish as shown in main()
        }
    };
}

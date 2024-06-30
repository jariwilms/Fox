#pragma once

#include "stdafx.hpp"

#include "System.hpp"

namespace fox
{
    class RenderSystem : public System
    {
    public:
        void update() override
        {
            //start rendering here, iterate all components, then finish as shown in main()
        }
    };
}

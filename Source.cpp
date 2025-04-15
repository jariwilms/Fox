#include <iostream>

#include "Fox/Core/Library/Transform/Transform.hpp"

int main()
{
    fox::Transform t{};
    t.translate({ 1.0f, 2.0f, 3.0f });

    std::cout << t.x;
}

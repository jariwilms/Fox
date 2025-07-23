export module fox.rendering.base.pipeline;

import std;

export namespace fox::gfx::api
{
    class pipeline
    {
    public:
        template<typename T>
        struct Layout
        {
            std::shared_ptr<T> vert{};
            std::shared_ptr<T> tesc{};
            std::shared_ptr<T> tese{};
            std::shared_ptr<T> geom{};
            std::shared_ptr<T> frag{};
        };
    };
}

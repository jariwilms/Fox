export module fox.rendering.api.opengl.lock;

import std;
import fox.rendering.api.opengl.domain;
import fox.rendering.api.opengl.types;

export namespace fox::gfx::api::gl
{
    using sync_lock_t = std::tuple<gl::sync_t, gl::range>;
}

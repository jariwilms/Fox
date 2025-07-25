export module fox.rendering.api.opengl.structures;

import std;

import fox.rendering.api.opengl.flags;
import fox.rendering.api.opengl.types;

export namespace fox::gfx::api::gl
{
    struct message_log
    {
        gl ::uint32_t        id;
        std::string          message;
        gl::debug_source_e   source;
        gl::debug_type_e     type;
        gl::debug_severity_e severity;
    };
    struct binary_info
    {
        gl::enum_t               format;
        std::vector<gl::uint8_t> binary; 
    };
    struct indirect_command
    {
        gl::count_t  count;
        gl::count_t  instances;
        gl::index_t  index;
        gl::int32_t  baseVertex;
        gl::uint32_t baseInstance;
    };
}

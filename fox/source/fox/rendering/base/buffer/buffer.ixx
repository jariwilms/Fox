export module fox.rendering.base.buffer;

export namespace fox::gfx::api
{
    struct buffer
    {
        enum class access
        {
            read, 
            write, 
            read_write, 
            persistent, 
            coherent, 
        };
    };
}

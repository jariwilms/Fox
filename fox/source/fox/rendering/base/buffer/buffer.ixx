export module fox.rendering.base.buffer;

export namespace fox::gfx::api
{
    class Buffer
    {
    public:
        enum class Access
        {
            Read, 
            Write, 
            ReadWrite, 

            Persistent, 
            Coherent, 
        };
    };
}

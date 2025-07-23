export module fox.rendering.api.opengl.concepts;

import std;
import fox.rendering.api.opengl.flags;
import fox.rendering.api.opengl.types;

export namespace fox::gfx::api::gl
{
    template<typename T>
    concept arithmetic_type = std::integral<T> || std::floating_point<T>;

    template<typename T, typename... Ts>
    constexpr auto all_same_type = gl::bool_t{ std::conjunction_v<std::is_same<T, Ts>...> };



    template<glf::Feature F>
    concept indexed_feature_c = 
        (
               F == glf::Feature::Blending 
            || F == glf::Feature::ScissorTest
        );
    template<glf::Data D>
    concept indexed_data_c =
        (
               D == glf::Data::MaximumComputeWorkGroupCount
            || D == glf::Data::MaximumComputeWorkGroupSize
            || D == glf::Data::SampleMaskValue
            || D == glf::Data::ShaderStorageBufferSize
            || D == glf::Data::ShaderStorageBufferStart
            || D == glf::Data::TransformfeedbackBufferSize
            || D == glf::Data::TransformFeedbackBufferStart
            || D == glf::Data::UniformBufferSize
            || D == glf::Data::UniformBufferStart
            || D == glf::Data::VertexBindingDivisor
            || D == glf::Data::VertexBindingOffset
            || D == glf::Data::VertexBindingStride
            || D == glf::Data::VertexBindingBuffer
        );
    template<glf::Texture::Target T, glf::Texture::Target U>
    concept valid_texture_view_c = 
           (T == glf::Texture::Target::_1D                 && (U == glf::Texture::Target::_1D            || U == glf::Texture::Target::_1DArray                                                                                             ))
        || (T == glf::Texture::Target::_2D                 && (U == glf::Texture::Target::_2D            || U == glf::Texture::Target::_2DArray                                                                                             ))
        || (T == glf::Texture::Target::_3D                 && (U == glf::Texture::Target::_3D                                                                                                                                               ))
        || (T == glf::Texture::Target::CubeMap             && (U == glf::Texture::Target::CubeMap        || U == glf::Texture::Target::_2D                 || U == glf::Texture::Target::_2DArray || U == glf::Texture::Target::CubeMapArray))
        || (T == glf::Texture::Target::Rectangle           && (U == glf::Texture::Target::Rectangle                                                                                                                                         ))
        || (T == glf::Texture::Target::_1DArray            && (U == glf::Texture::Target::_1D            || U == glf::Texture::Target::_1DArray                                                                                             ))
        || (T == glf::Texture::Target::_2DArray            && (U == glf::Texture::Target::_2D            || U == glf::Texture::Target::_2DArray                                                                                             ))
        || (T == glf::Texture::Target::CubeMapArray        && (U == glf::Texture::Target::_2D            || U == glf::Texture::Target::_2DArray            || U == glf::Texture::Target::CubeMap  || U == glf::Texture::Target::CubeMapArray))
        || (T == glf::Texture::Target::_2DMultisample      && (U == glf::Texture::Target::_2DMultisample || U == glf::Texture::Target::_2DMultisampleArray                                                                                  ))
        || (T == glf::Texture::Target::_2DMultisampleArray && (U == glf::Texture::Target::_2DMultisample || U == glf::Texture::Target::_2DMultisampleArray                                                                                  ));
}

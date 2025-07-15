#pragma once

import fox.rendering.api.opengl.flags;
import fox.rendering.api.opengl.types;

namespace fox::gfx::api::gl
{
    template<glf::Feature F>
    concept indexed_feature_c = 
        (
               F == glf::Feature::Blending 
            or F == glf::Feature::ScissorTest
        );

    template<glf::Data D>
    concept indexed_data_c =
        (
               D == glf::Data::MaximumComputeWorkGroupCount
            or D == glf::Data::MaximumComputeWorkGroupSize
            or D == glf::Data::SampleMaskValue
            or D == glf::Data::ShaderStorageBufferSize
            or D == glf::Data::ShaderStorageBufferStart
            or D == glf::Data::TransformfeedbackBufferSize
            or D == glf::Data::TransformFeedbackBufferStart
            or D == glf::Data::UniformBufferSize
            or D == glf::Data::UniformBufferStart
            or D == glf::Data::VertexBindingDivisor
            or D == glf::Data::VertexBindingOffset
            or D == glf::Data::VertexBindingStride
            or D == glf::Data::VertexBindingBuffer
        );

    template<typename T>
    concept arithmetic_type_c =
        (
               std::is_same_v<T, gl::int8_t   >  
            or std::is_same_v<T, gl::uint8_t  >
            or std::is_same_v<T, gl::int16_t  >
            or std::is_same_v<T, gl::uint16_t >
            or std::is_same_v<T, gl::int32_t  >
            or std::is_same_v<T, gl::uint32_t >
            or std::is_same_v<T, gl::int64_t  >
            or std::is_same_v<T, gl::uint64_t >
            or std::is_same_v<T, gl::float16_t>
            or std::is_same_v<T, gl::float32_t>
            or std::is_same_v<T, gl::float64_t>
        );

    template<glf::Texture::Target T, glf::Texture::Target U>
    concept valid_texture_view_c = 
           (T == glf::Texture::Target::_1D                 and (U == glf::Texture::Target::_1D            or U == glf::Texture::Target::_1DArray                                                                                             ))
        or (T == glf::Texture::Target::_2D                 and (U == glf::Texture::Target::_2D            or U == glf::Texture::Target::_2DArray                                                                                             ))
        or (T == glf::Texture::Target::_3D                 and (U == glf::Texture::Target::_3D                                                                                                                                               ))
        or (T == glf::Texture::Target::CubeMap             and (U == glf::Texture::Target::CubeMap        or U == glf::Texture::Target::_2D                 or U == glf::Texture::Target::_2DArray or U == glf::Texture::Target::CubeMapArray))
        or (T == glf::Texture::Target::Rectangle           and (U == glf::Texture::Target::Rectangle                                                                                                                                         ))
        or (T == glf::Texture::Target::_1DArray            and (U == glf::Texture::Target::_1D            or U == glf::Texture::Target::_1DArray                                                                                             ))
        or (T == glf::Texture::Target::_2DArray            and (U == glf::Texture::Target::_2D            or U == glf::Texture::Target::_2DArray                                                                                             ))
        or (T == glf::Texture::Target::CubeMapArray        and (U == glf::Texture::Target::_2D            or U == glf::Texture::Target::_2DArray            or U == glf::Texture::Target::CubeMap  or U == glf::Texture::Target::CubeMapArray))
        or (T == glf::Texture::Target::_2DMultisample      and (U == glf::Texture::Target::_2DMultisample or U == glf::Texture::Target::_2DMultisampleArray                                                                                  ))
        or (T == glf::Texture::Target::_2DMultisampleArray and (U == glf::Texture::Target::_2DMultisample or U == glf::Texture::Target::_2DMultisampleArray                                                                                  ));
}

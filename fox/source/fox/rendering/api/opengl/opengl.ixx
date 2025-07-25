export module fox.rendering.api.opengl;
export import fox.rendering.api.opengl.domain;
export import fox.rendering.api.opengl.flags;
export import fox.rendering.api.opengl.lock;
export import fox.rendering.api.opengl.mapping;
export import fox.rendering.api.opengl.meta;
export import fox.rendering.api.opengl.object;
export import fox.rendering.api.opengl.parameters;
export import fox.rendering.api.opengl.proxy;
export import fox.rendering.api.opengl.structures;
export import fox.rendering.api.opengl.types;
export import fox.rendering.api.opengl.utility;

import std;
import <glad/gl.h>;

export namespace fox::gfx::api::gl
{
    //C++ OpenGL Wrapper Library
    //
    //This library provides a modern, robust, and user-friendly interface for OpenGL.
    //Its primary goals are to:
    //    * Offer a more intuitive and correct interface for development.
    //    * Encapsulate existing OpenGL functions, simplifying integration of custom logic.
    //    * Implement state caching to eliminate redundant driver calls.
    //    * Ensure compile-time and runtime safety through comprehensive input validation.
    //
    //Functions are organized based on their appearance in the OpenGL 4.6 Core Profile Specification.
    //Reference: https://registry.khronos.org/OpenGL/specs/gl/glspec46.core.pdf


    




    //Chapter 22 - Context State Queries
    template<gl::data_e D>    requires (not gl::indexed_data_c<D>)
    auto get_value                                  () -> auto
    {
        auto get_boolean_v            = [](gl::data_e data) -> gl::bool_t
            {
                auto value = gl::boolean_t{};
                return glGetBooleanv(gl::to_underlying(data), &value), value;
            };
        auto get_integer32_v          = [](gl::data_e data) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return glGetIntegerv(gl::to_underlying(data), &value), value;
            };
        auto get_integer64_v          = [](gl::data_e data) -> gl::int64_t
            {
                auto value = gl::int64_t{};
                return glGetInteger64v(gl::to_underlying(data), &value), value;
            };
        auto get_unsigned_integer32_v = [](gl::data_e data) -> gl::uint32_t
            {
                auto value = gl::int32_t{};
                return glGetIntegerv(gl::to_underlying(data), &value), static_cast<gl::int32_t>(value);
            };
        auto get_unsigned_integer64_v = [](gl::data_e data) -> gl::uint64_t
            {
                auto value = gl::int64_t{};
                return glGetInteger64v(gl::to_underlying(data), &value), static_cast<gl::uint64_t>(value);
            };
        auto get_floating_point32_v   = [](gl::data_e data) -> gl::float32_t
            {
                auto value = gl::float32_t{};
                return glGetFloatv(gl::to_underlying(data), &value), value;
            };
        auto get_floating_point64_v   = [](gl::data_e data) -> gl::float64_t
            {
                auto value = gl::float64_t{};
                return glGetDoublev(gl::to_underlying(data), &value), value;
            };
        auto get_vector4b_v           = [](gl::data_e data) -> gl::vector4b
            {
                auto value = gl::vector4b{};
                return glGetBooleanv(gl::to_underlying(data), glm::value_ptr(value)), value;
            };
        auto get_vector2i_v           = [](gl::data_e data) -> gl::vector2i
            {
                auto value = gl::vector2i{};
                return glGetIntegerv(gl::to_underlying(data), glm::value_ptr(value)), value;
            };
        auto get_vector2f_v           = [](gl::data_e data) -> gl::vector2f
            {
                auto value = gl::vector2f{};
                return glGetFloatv(gl::to_underlying(data), glm::value_ptr(value)), value;
            };
        auto get_vector4f_v           = [](gl::data_e data) -> gl::vector4f
            {
                auto value = gl::vector4f{};
                return glGetFloatv(gl::to_underlying(data), glm::value_ptr(value)), value;
            };
        auto get_handle_v             = [](gl::data_e data) -> gl::handle_t
            {
                auto value = gl::int32_t{};
                return glGetIntegerv(gl::to_underlying(data), &value), static_cast<gl::handle_t>(value);
            };
        auto get_index_v              = [](gl::data_e data) -> gl::index_t
            {
                auto value = gl::int32_t{};
                return glGetIntegerv(gl::to_underlying(data), &value), static_cast<gl::index_t>(value);
            };
        auto get_bitfield_v           = [](gl::data_e data) -> gl::bitfield_t
            {
                auto value = gl::int32_t{};
                return glGetIntegerv(gl::to_underlying(data), &value), static_cast<gl::bitfield_t>(value);
            };
        auto get_binary_formats_v     = [](gl::data_e data) -> std::vector<gl::enum_t>
            {
                auto numberProgramBinaryFormats = gl::int32_t{};
                glGetIntegerv(gl::to_underlying(gl::data_e::number_program_binary_formats), &numberProgramBinaryFormats);

                auto programBinaryFormats = std::vector<gl::enum_t>(static_cast<gl::uint32_t>(numberProgramBinaryFormats));
                glGetIntegerv(gl::to_underlying(data), std::bit_cast<gl::int32_t*>(programBinaryFormats.data()));

                return programBinaryFormats;
            };
        auto get_area_v               = [](gl::data_e data) -> gl::area_t
            {
                auto value = gl::vector4u{};
                glGetIntegerv(gl::to_underlying(data), std::bit_cast<gl::int32_t*>(glm::value_ptr(value)));

                return gl::area_t{ gl::vector2u{ value.z, value.w }, gl::vector2u{ value.x, value.y } };
            };

        if constexpr (D == gl::data_e::aliased_line_width_range                             ) return get_vector2f_v(D);
        if constexpr (D == gl::data_e::blend_color                                          ) return get_vector4f_v(D);
        if constexpr (D == gl::data_e::blend_destination_alpha                              ) return static_cast<gl::blending_factor_e>           (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::blend_destination_rgb                                ) return static_cast<gl::blending_factor_e>           (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::blend_destination_alpha                              ) return static_cast<gl::blending_equation_e>         (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::blend_equation_rgb                                   ) return static_cast<gl::blending_equation_e>         (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::blend_source_alpha                                   ) return static_cast<gl::blending_factor_e>           (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::blend_source_rgb                                     ) return static_cast<gl::blending_factor_e>           (get_unsigned_integer32_v(D));
        //if constexpr (D == gl::data_e::clip_depth_mode
        //if constexpr (D == gl::data_e::clip_origin
        if constexpr (D == gl::data_e::color_clear_value                                    ) return get_vector4f_v(D);
        if constexpr (D == gl::data_e::color_write_mask                                     ) return get_vector4b_v(D);
        if constexpr (D == gl::data_e::context_flags                                        ) return static_cast<gl::context_flag_e>              (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::context_profile_mask                                 ) return static_cast<gl::context_profile_e>           (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::copy_read_buffer_binding                             ) return get_handle_v(D);
        if constexpr (D == gl::data_e::copy_write_buffer_binding                            ) return get_handle_v(D);
        if constexpr (D == gl::data_e::current_program                                      ) return get_handle_v(D);
        if constexpr (D == gl::data_e::debug_group_stack_depth                              ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::debug_logged_messages                                ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::depth_clear_value                                    ) return get_floating_point64_v(D);
        if constexpr (D == gl::data_e::depth_function                                       ) return static_cast<gl::depth_function_e>              (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::depth_range                                          ) return get_vector2f_v(D);
        if constexpr (D == gl::data_e::dispatch_indirect_buffer_binding                     ) return get_handle_v(D);
        if constexpr (D == gl::data_e::double_buffer                                        ) return get_boolean_v  (D);
        if constexpr (D == gl::data_e::draw_buffer                                          ) return static_cast<gl::frame_buffer_source_e>        (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::draw_frame_buffer_binding                            ) return get_handle_v(D);
        if constexpr (D == gl::data_e::draw_indirect_buffer_binding                         ) return get_handle_v(D);
        if constexpr (D == gl::data_e::fragment_shader_derivative_hint                      ) return static_cast<gl::hint_mode_e>                 (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::implementation_color_read_format                     ) return static_cast<gl::pixel_data_format_e>          (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::implementation_color_read_type                       ) return static_cast<gl::pixel_data_type_e>            (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::index_array_buffer_binding                           ) return get_handle_v(D);
        if constexpr (D == gl::data_e::layer_provoking_vertex                               ) return static_cast<gl::provoking_vertex_mode_e>      (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::line_smooth_hint                                     ) return static_cast<gl::hint_mode_e>                 (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::line_width                                           ) return get_floating_point64_v(D);
        if constexpr (D == gl::data_e::logic_operation_mode                                 ) return static_cast<gl::logical_pixel_operation_e>      (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::major_version                                        ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_3d_texture_size                              ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_array_texture_layers                         ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_clip_distances                               ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_color_attachments                            ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_color_texture_samples                        ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_combined_atomic_counters                     ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_combined_compute_uniform_components          ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_combined_fragment_uniform_components         ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_combined_geometry_uniform_components         ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_combined_shader_storage_blocks               ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_combined_texture_image_units                 ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_combined_uniform_blocks                      ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_combined_vertex_uniform_components           ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_compute_atomic_counter_buffers               ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_compute_atomic_counters                      ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_compute_shader_storage_blocks                ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_compute_texture_image_units                  ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_compute_uniform_blocks                       ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_compute_uniform_components                   ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_compute_work_group_count                     ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_compute_work_group_invocations               ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_compute_work_group_size                      ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_cubemap_texture_size                         ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_debug_group_stack_depth                      ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_debug_message_length                         ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_depth_texture_samples                        ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_draw_buffers                                 ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_dual_source_draw_buffers                     ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_element_index                                ) return get_index_v(D);
        if constexpr (D == gl::data_e::maximum_fragment_atomic_counters                     ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_fragment_input_components                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_fragment_shader_storage_blocks               ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_fragment_uniform_blocks                      ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_fragment_uniform_components                  ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_fragment_uniform_vectors                     ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_frame_buffer_height                          ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_frame_buffer_layers                          ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_frame_buffer_samples                         ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_frame_buffer_width                           ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_geometry_atomic_counters                     ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_geometry_input_components                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_geometry_output_components                   ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_geometry_shader_storage_blocks               ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_geometry_texture_image_units                 ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_geometry_uniform_blocks                      ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_geometry_uniform_components                  ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_index_elements                               ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_integer_samples                              ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_label_length                                 ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_program_texel_offset                         ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_rectangle_texture_size                       ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_render_buffer_size                           ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_sample_mask_words                            ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_server_wait_timeout                          ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_shader_storage_buffer_bindings               ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_tessellation_control_atomic_counters         ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_tessellation_control_shaders_torageblocks    ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_tessellation_evaluation_atomic_counters      ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_tessellation_evaluation_shader_storage_blocks) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_texture_buffer_size                          ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_texture_image_units                          ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_texture_lod_bias                             ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_texture_size                                 ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_uniform_block_size                           ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_uniform_buffer_bindings                      ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_uniform_locations                            ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_varying_components                           ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_varying_floats                               ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_varying_vectors                              ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_vertex_atomic_counters                       ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_vertex_attribute_bindings                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_vertex_attribute_relative_offset             ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_vertex_attributes                            ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_vertex_elements                              ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_vertex_output_components                     ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_vertex_shader_storage_blocks                 ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_vertex_texture_image_units                   ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_vertex_uniform_blocks                        ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_vertex_uniform_components                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_vertex_uniform_vectors                       ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_viewport_dimensions                          ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::maximum_viewports                                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::minimum_map_buffer_alignment                         ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::minimum_program_texel_offset                         ) return get_integer32_v(D);
        if constexpr (D == gl::data_e::minor_version                                        ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::number_compressed_texture_formats                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::number_extensions                                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::number_program_binary_formats                        ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::number_shader_binary_formats                         ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::pack_alignment                                       ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::pack_image_height                                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::pack_row_length                                      ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::pack_skip_images                                     ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::pack_skip_pixels                                     ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::pack_skip_rows                                       ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::pack_swap_bytes                                      ) return get_boolean_v(D);
        //parameter_buffer_binding
        //patch_default_inner_level 
        //patch_default_outer_level 
        if constexpr (D == gl::data_e::pixel_pack_buffer_binding                            ) return get_handle_v(D);
        if constexpr (D == gl::data_e::pixel_unpack_buffer_binding                          ) return get_handle_v(D);
        if constexpr (D == gl::data_e::point_fade_threshold_size                            ) return get_floating_point32_v(D);
        if constexpr (D == gl::data_e::point_size                                           ) return get_floating_point32_v(D);
        if constexpr (D == gl::data_e::point_size_granularity                               ) return get_floating_point32_v(D);
        if constexpr (D == gl::data_e::point_size_range                                     ) return get_vector2f_v(D);
        if constexpr (D == gl::data_e::polygon_offset_factor                                ) return get_floating_point32_v(D);
        if constexpr (D == gl::data_e::polygon_offset_units                                 ) return get_floating_point32_v(D);
        if constexpr (D == gl::data_e::polygon_smooth_hint                                  ) return static_cast<gl::hint_mode_e>                 (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::primitive_restart_index                              ) return get_index_v(D);
        if constexpr (D == gl::data_e::program_binary_formats                               ) return get_binary_formats_v(D);
        if constexpr (D == gl::data_e::program_pipeline_binding                             ) return get_handle_v(D);
        if constexpr (D == gl::data_e::provoking_vertex                                     ) return static_cast<gl::provoking_vertex_mode_e>      (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::query_buffer_binding                                 ) return get_handle_v(D);
        if constexpr (D == gl::data_e::read_buffer                                          ) return static_cast<gl::frame_buffer_source_e>        (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::read_frame_buffer_binding                            ) return get_handle_v(D);
        if constexpr (D == gl::data_e::render_buffer_binding                                ) return get_handle_v(D);
        //reset_notification_strategy
        if constexpr (D == gl::data_e::sample_buffers                                       ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::sample_coverage_invert                               ) return get_boolean_v(D);
        if constexpr (D == gl::data_e::sample_coverage_value                                ) return get_floating_point32_v(D);
        //sample_mask_value
        if constexpr (D == gl::data_e::sampler_binding                                      ) return get_handle_v(D);
        if constexpr (D == gl::data_e::samples                                              ) return get_bitfield_v(D);
        if constexpr (D == gl::data_e::scissor_box                                          ) return get_area_v(D);
        if constexpr (D == gl::data_e::shader_compiler                                      ) return get_boolean_v(D);
        if constexpr (D == gl::data_e::shader_storage_buffer_binding                        ) return get_handle_v(D);
        if constexpr (D == gl::data_e::shader_storage_buffer_offset_alignment               ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::smooth_line_width_granularity                        ) return get_floating_point32_v(D);
        if constexpr (D == gl::data_e::smooth_line_width_range                              ) return get_vector2f_v(D);
        if constexpr (D == gl::data_e::stencil_back_fail                                    ) return static_cast<gl::stencil_action_e>            (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::stencil_back_function                                ) return static_cast<gl::stencil_function_e>          (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::stencil_back_pass_depth_fail                         ) return static_cast<gl::stencil_action_e>            (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::stencil_back_pass_depth_pass                         ) return static_cast<gl::stencil_action_e>            (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::stencil_back_reference                               ) return get_integer32_v(D);
        if constexpr (D == gl::data_e::stencil_back_value_mask                              ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::stencil_back_write_mask                              ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::stencil_clear_value                                  ) return get_index_v(D);
        if constexpr (D == gl::data_e::stencil_fail                                         ) return static_cast<gl::stencil_action_e>            (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::stencil_function                                     ) return static_cast<gl::stencil_function_e>          (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::stencil_pass_depth_fail                              ) return static_cast<gl::stencil_action_e>            (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::stencil_pass_depth_pass                              ) return static_cast<gl::stencil_action_e>            (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::stencil_reference                                    ) return get_integer32_v(D);
        if constexpr (D == gl::data_e::stencil_value_mask                                   ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::stencil_write_mask                                   ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::stereo                                               ) return get_boolean_v(D);
        if constexpr (D == gl::data_e::sub_pixel_bits                                       ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::texture_binding_1d                                   ) return get_handle_v(D);
        if constexpr (D == gl::data_e::texture_binding_1d_array                             ) return get_handle_v(D);
        if constexpr (D == gl::data_e::texture_binding_2d                                   ) return get_handle_v(D);
        if constexpr (D == gl::data_e::texture_binding_2d_array                             ) return get_handle_v(D);
        if constexpr (D == gl::data_e::texture_binding_2d_multisample                       ) return get_handle_v(D);
        if constexpr (D == gl::data_e::texture_binding_2d_multisample_array                 ) return get_handle_v(D);
        if constexpr (D == gl::data_e::texture_binding_3d                                   ) return get_handle_v(D);
        if constexpr (D == gl::data_e::texture_binding_buffer                               ) return get_handle_v(D);
        if constexpr (D == gl::data_e::texture_binding_cubemap                              ) return get_handle_v(D);
        if constexpr (D == gl::data_e::texture_binding_rectangle                            ) return get_handle_v(D);
        if constexpr (D == gl::data_e::texture_buffer_binding                               ) return get_handle_v(D);
        if constexpr (D == gl::data_e::texture_buffer_offset_alignment                      ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::texture_compression_hint                             ) return static_cast<gl::hint_mode_e>                 (get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::timestamp                                            ) return get_integer64_v(D);
        //transform_feedback_binding
        if constexpr (D == gl::data_e::transform_feedback_buffer_binding                    ) return get_handle_v(D);
        if constexpr (D == gl::data_e::uniform_buffer_binding                               ) return get_handle_v(D);
        if constexpr (D == gl::data_e::uniform_buffer_offset_alignment                      ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::unpack_alignment                                     ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::unpack_image_height                                  ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::unpack_row_length                                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::unpack_skip_images                                   ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::unpack_skip_pixels                                   ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::unpack_skip_rows                                     ) return get_unsigned_integer32_v(D);
        if constexpr (D == gl::data_e::unpack_swap_bytes                                    ) return get_boolean_v(D);
        if constexpr (D == gl::data_e::vertex_array_binding                                 ) return get_handle_v(D);
        if constexpr (D == gl::data_e::viewport                                             ) return get_area_v(D);
        if constexpr (D == gl::data_e::viewport_bounds_range                                ) return get_vector2i_v(D);
        if constexpr (D == gl::data_e::viewport_index_provoking_vertex                      ) return static_cast<gl::provoking_vertex_convention_e>(get_unsigned_integer32_v(D));
        if constexpr (D == gl::data_e::viewport_sub_pixel_bits                              ) return get_unsigned_integer32_v(D);
    }
    template<gl::data_e D>    requires (gl::indexed_data_c<D>)
    auto get_value_index                            (gl::index_t index) -> auto
    {
        auto get_unsigned_integer32_v = [](gl::data_e data, gl::index_t index) -> gl::uint32_t
            {
                auto value = gl::int32_t{};
                return glGetIntegeri_v(gl::to_underlying(data), index, &value), static_cast<gl::uint32_t>(value);
            };
        auto get_unsigned_integer64_v = [](gl::data_e data, gl::index_t index) -> gl::uint64_t
            {
                auto value = gl::int64_t{};
                return glGetInteger64i_v(gl::to_underlying(data), index, &value), static_cast<gl::uint64_t>(value);
            };
        auto get_handle_v             = [](gl::data_e data, gl::index_t index) -> gl::handle_t
            {
                auto value = gl::int32_t{};
                return glGetIntegeri_v(gl::to_underlying(data), index, &value), static_cast<gl::handle_t>(value);
            };
        auto get_area_v               = [](gl::data_e data, gl::index_t index) -> gl::area_t
            {
                auto value = gl::vector4u{};
                glGetIntegeri_v(gl::to_underlying(data), index, std::bit_cast<gl::int32_t*>(glm::value_ptr(value)));

                return gl::area_t{ gl::vector2u{ value.z, value.w }, gl::vector2u{ value.x, value.y } };
            };
        
        if constexpr (D == gl::data_e::maximum_compute_work_group_count ) return get_unsigned_integer32_v(D, index);
        if constexpr (D == gl::data_e::maximum_compute_work_group_size  ) return get_unsigned_integer32_v(D, index);
        if constexpr (D == gl::data_e::shader_storage_buffer_binding    ) return get_handle_v            (D, index);
        if constexpr (D == gl::data_e::shader_storage_buffer_size       ) return get_unsigned_integer64_v(D, index);
        if constexpr (D == gl::data_e::shader_storage_buffer_start      ) return get_unsigned_integer64_v(D, index);
        if constexpr (D == gl::data_e::transform_feedback_buffer_binding) return get_handle_v            (D, index);
        if constexpr (D == gl::data_e::transform_feedback_buffer_size   ) return get_unsigned_integer64_v(D, index);
        if constexpr (D == gl::data_e::transform_feedback_buffer_start  ) return get_unsigned_integer64_v(D, index);
        if constexpr (D == gl::data_e::uniform_buffer_binding           ) return get_handle_v            (D, index);
        if constexpr (D == gl::data_e::uniform_buffer_size              ) return get_unsigned_integer64_v(D, index);
        if constexpr (D == gl::data_e::uniform_buffer_start             ) return get_unsigned_integer64_v(D, index);
        if constexpr (D == gl::data_e::vertex_binding_buffer            ) return get_handle_v            (D, index);
        if constexpr (D == gl::data_e::vertex_binding_divisor           ) return get_unsigned_integer32_v(D, index);
        if constexpr (D == gl::data_e::vertex_binding_offset            ) return get_unsigned_integer32_v(D, index);
        if constexpr (D == gl::data_e::vertex_binding_stride            ) return get_unsigned_integer32_v(D, index);
        if constexpr (D == gl::data_e::viewport                         ) return get_area_v              (D, index);
    }
    template<gl::feature_e F>
    void enable                                     ()
    {
        glEnable(gl::to_underlying(F));
    }
    template<gl::feature_e F> requires (gl::indexed_feature_c<F>)
    void enable_index                               (gl::index_t index)
    {
        glEnablei(gl::to_underlying(F), index);
    }
    template<gl::feature_e F>
    void disable                                    ()
    {
        glDisable(gl::to_underlying(F));
    }
    template<gl::feature_e F> requires (gl::indexed_feature_c<F>)
    void disable_index                              (gl::index_t index)
    {
        glDisablei(gl::to_underlying(F), index);
    }
    template<gl::feature_e F>
    auto is_enabled                                 () -> gl::bool_t
    {
        return glIsEnabled(gl::to_underlying(F));
    }
    template<gl::feature_e F> requires (gl::indexed_feature_c<F>)
    auto is_enabled_index                           (gl::index_t index) -> gl::bool_t
    {
        return glIsEnabledi(gl::to_underlying(F));
    }
    template<gl::callback_pointer_e P>
    auto get_pointer_value                          () -> gl::pointer_t
    {
        auto value = gl::pointer_t{};
        return glGetPointerv(gl::to_underlying(P), &value), value;
    }
    template<gl::context_property_e P>
    auto get_string                                 () -> std::string
    {
        return std::string{ std::bit_cast<const gl::char_t*>(glGetString(gl::to_underlying(P))) };
    }
    template<gl::context_property_e P>
    auto get_string_index                           (gl::index_t index) -> std::string
    {
        return std::string{ std::bit_cast<const gl::char_t*>(glGetStringi(gl::to_underlying(P), index)) };
    }
    auto get_internal_format_value                  () -> auto
    {
        gl::todo();
    }



    //Chapter 4 - Event Model
    template<gl::synchronization_property_e P>
    auto get_sync_value                             (gl::sync_t sync) -> auto
    {
        auto get_sync_iv = [](gl::sync_t sync, gl::synchronization_property_e property) -> gl::int32_t
            {
                gl::int32_t value{};
                return glGetSynciv(sync, gl::to_underlying(property), gl::sizei_t{ 1 }, nullptr, &value), value;
            };

        if constexpr (P == gl::synchronization_property_e::type     ) return static_cast<gl::synchronization_object_type_e>     (get_sync_iv(sync, P));
        if constexpr (P == gl::synchronization_property_e::status   ) return static_cast<gl::synchronization_object_status_e>   (get_sync_iv(sync, P));
        if constexpr (P == gl::synchronization_property_e::condition) return static_cast<gl::synchronization_object_condition_e>(get_sync_iv(sync, P));
        if constexpr (P == gl::synchronization_property_e::flags    ) return gl::bitfield_t{ 0u };
    }
    template<gl::query_symbol_e S>
    auto get_query_value                            (gl::query_target_e target) -> gl::uint32_t
    {
        auto value = gl::int32_t{};
        return glGetQueryiv(gl::to_underlying(target), gl::to_underlying(S), &value), static_cast<gl::uint32_t>(value);
    }
    template<gl::query_symbol_e S>
    auto get_query_value_index                      (gl::query_target_e target, gl::index_t index) -> gl::uint32_t
    {
        auto value = gl::int32_t{};
        return glGetQueryIndexediv(gl::to_underlying(target), index, gl::to_underlying(S), &value), static_cast<gl::uint32_t>(value);
    }
    template<gl::query_parameter_e P>
    auto get_query_object_value                     (gl::handle_t query) -> auto
    {
        auto get_query_object_iv  = [](gl::handle_t query, gl::query_parameter_e parameter) -> gl::int32_t
            {
                gl::int32_t value{};
                return glGetQueryObjectiv(gl::to_underlying(query), gl::to_underlying(parameter), &value), value;
            };
        auto get_query_object_uiv = [](gl::handle_t query, gl::query_parameter_e parameter) -> gl::uint32_t
            {
                gl::uint32_t value{};
                return glGetQueryObjectuiv(gl::to_underlying(query), gl::to_underlying(parameter), &value), value;
            };

        if constexpr (P == gl::query_parameter_e::result          ) return                                 get_query_object_uiv(query, P) ;
        if constexpr (P == gl::query_parameter_e::result_no_wait  ) return                                 get_query_object_uiv(query, P) ;
        if constexpr (P == gl::query_parameter_e::result_available) return static_cast<gl::bool_t>        (get_query_object_iv (query, P));
        if constexpr (P == gl::query_parameter_e::target          ) return static_cast<gl::query_target_e>(get_query_object_iv (query, P));
    }
    template<gl::query_parameter_e P>
    void get_query_buffer_object_value              (gl::handle_t query, gl::handle_t buffer, gl::offset_t offset)
    {
        auto get_query_buffer_object_iv  = [](gl::handle_t query, gl::handle_t buffer, gl::query_parameter_e parameter, gl::offset_t offset)
            {
                glGetQueryBufferObjectiv(gl::to_underlying(query), gl::to_underlying(buffer), gl::to_underlying(parameter), offset);
            };
        auto get_query_buffer_object_uiv = [](gl::handle_t query, gl::handle_t buffer, gl::query_parameter_e parameter, gl::offset_t offset)
            {
                glGetQueryBufferObjectuiv(gl::to_underlying(query), gl::to_underlying(buffer), gl::to_underlying(parameter), offset);
            };

        if constexpr (P == gl::query_parameter_e::result          ) get_query_buffer_object_uiv(query, buffer, P, offset);
        if constexpr (P == gl::query_parameter_e::result_no_wait  ) get_query_buffer_object_uiv(query, buffer, P, offset);
        if constexpr (P == gl::query_parameter_e::result_available) get_query_buffer_object_iv (query, buffer, P, offset);
        if constexpr (P == gl::query_parameter_e::target          ) get_query_buffer_object_iv (query, buffer, P, offset);
    }



    //Chapter 6 - Buffer Objects
    template<gl::buffer_parameter_e P>
    auto get_buffer_parameter_value                 (gl::handle_t buffer) -> auto
    {
        auto get_buffer_parameter_iv   = [](gl::handle_t buffer, gl::buffer_parameter_e parameter) -> gl::int32_t
            {
                gl::int32_t value{};
                return glGetNamedBufferParameteriv(gl::to_underlying(buffer), gl::to_underlying(parameter), &value), value;
            };
        auto get_buffer_parameter_i64v = [](gl::handle_t buffer, gl::buffer_parameter_e parameter) -> gl::int64_t
            {
                gl::int64_t value{};
                return glGetNamedBufferParameteri64v(gl::to_underlying(buffer), gl::to_underlying(parameter), &value), value;
            };

        if constexpr (P == gl::buffer_parameter_e::access       ) return static_cast<gl::buffer_mapping_access_e>      (get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == gl::buffer_parameter_e::access_flags ) return static_cast<gl::buffer_mapping_access_flags_e>(get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == gl::buffer_parameter_e::immutable    ) return static_cast<gl::bool_t>                       (get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == gl::buffer_parameter_e::is_mapped    ) return static_cast<gl::bool_t>                       (get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == gl::buffer_parameter_e::map_length   ) return static_cast<gl::uint64_t>                     (get_buffer_parameter_i64v(buffer, P));
        if constexpr (P == gl::buffer_parameter_e::map_offset   ) return static_cast<gl::uint64_t>                     (get_buffer_parameter_i64v(buffer, P));
        if constexpr (P == gl::buffer_parameter_e::size         ) return static_cast<gl::size_t>                       (get_buffer_parameter_i64v(buffer, P));
        if constexpr (P == gl::buffer_parameter_e::storage_flags) return static_cast<gl::buffer_storage_flags_e>       (get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == gl::buffer_parameter_e::usage        ) return static_cast<gl::buffer_usage_e>               (get_buffer_parameter_iv  (buffer, P));
    }
    template<typename T>
    auto get_buffer_data                            (gl::handle_t buffer) -> std::vector<T>
    {
        auto size = gl::get_buffer_parameter_value(buffer, gl::buffer_parameter_e::size);
        auto data = std::vector<T>(size);
        return glGetNamedBufferSubData(gl::to_underlying(buffer), gl::offset_t{ 0 }, size, data.data()), data;
    }
    template<typename T>
    auto get_buffer_sub_data                        (gl::handle_t buffer, gl::range range) -> std::vector<T>
    {
        auto byterange = gl::convert_range<T>(range);
        auto data      = std::vector<T>(range.count);
        return glGetNamedBufferSubData(gl::to_underlying(buffer), byterange.offset, byterange.size, data.data()), data;
    }
    


    //Chapter 7 - Programs and Shaders
    template<gl::shader_parameter_e P>
    auto get_shader_value                           (gl::handle_t shader) -> auto
    {
        auto get_shader_iv = [](gl::handle_t shader, gl::shader_parameter_e parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return glGetShaderiv(gl::to_underlying(shader), gl::to_underlying(parameter), &value), value;
            };

        if constexpr (P == gl::shader_parameter_e::type           ) return static_cast<gl::shader_type_e>(get_shader_iv(shader, P));
        if constexpr (P == gl::shader_parameter_e::delete_status  ) return static_cast<gl::bool_t>       (get_shader_iv(shader, P));
        if constexpr (P == gl::shader_parameter_e::compile_status ) return static_cast<gl::bool_t>       (get_shader_iv(shader, P));
        if constexpr (P == gl::shader_parameter_e::info_log_length) return static_cast<gl::uint32_t>     (get_shader_iv(shader, P));
        if constexpr (P == gl::shader_parameter_e::source_length  ) return static_cast<gl::uint32_t>     (get_shader_iv(shader, P));
    }
    template<gl::program_parameter_e P>
    auto get_program_value                          (gl::handle_t program) -> auto
    {
        auto get_program_iv = [](gl::handle_t program, gl::program_parameter_e parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return glGetProgramiv(gl::to_underlying(program), gl::to_underlying(parameter), &value), value;
            };

        if constexpr (P == gl::program_parameter_e::active_atomic_counter_buffers            ) return static_cast<gl::uint32_t                        >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::active_attribute_maximum_length          ) return static_cast<gl::uint32_t                        >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::active_attributes                        ) return static_cast<gl::uint32_t                        >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::active_uniform_block_maximum_name_length ) return static_cast<gl::uint32_t                        >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::active_uniform_blocks                    ) return static_cast<gl::uint32_t                        >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::active_uniform_maximum_length            ) return static_cast<gl::uint32_t                        >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::active_uniforms                          ) return static_cast<gl::uint32_t                        >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::attached_shaders                         ) return static_cast<gl::uint32_t                        >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::binary_length                            ) return static_cast<gl::uint32_t                        >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::compute_work_group_size                  ) return static_cast<gl::uint32_t                        >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::delete_status                            ) return static_cast<gl::bool_t                          >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::geometry_input_type                      ) return static_cast<gl::draw_mode_e                     >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::geometry_output_type                     ) return static_cast<gl::draw_mode_e                     >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::geometry_shader_invocations              ) return static_cast<gl::uint32_t                        >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::geometry_vertices_out                    ) return static_cast<gl::uint32_t                        >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::info_log_length                          ) return static_cast<gl::uint32_t                        >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::is_binary_retrievable                    ) return static_cast<gl::bool_t                          >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::is_separable                             ) return static_cast<gl::bool_t                          >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::link_status                              ) return static_cast<gl::bool_t                          >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::tessellation_control_output_vertices     ) return static_cast<gl::uint32_t                        >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::tessellation_generation_mode             ) return static_cast<gl::tessellation_generation_e       >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::tessellation_generation_point_mode       ) return static_cast<gl::bool_t                          >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::tessellation_generation_spacing          ) return static_cast<gl::tessellation_spacing_e          >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::tessellation_generation_vertex_order     ) return static_cast<gl::tessellation_vertex_order_e     >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::transform_feedback_buffer_mode           ) return static_cast<gl::transform_feedback_buffer_mode_e>(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::transform_feedback_varying_maximum_length) return static_cast<gl::uint32_t                        >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::transform_feedback_varyings              ) return static_cast<gl::uint32_t                        >(get_program_iv(program, P));
        if constexpr (P == gl::program_parameter_e::validate_status                          ) return static_cast<gl::bool_t                          >(get_program_iv(program, P));
    }
    template<gl::pipeline_property_e P>
    auto get_program_pipeline_value                 (gl::handle_t pipeline) -> auto
    {
        auto get_program_pipeline_iv = [](gl::handle_t pipeline, gl::pipeline_property_e property) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return glGetProgramPipelineiv(gl::to_underlying(pipeline), gl::to_underlying(property), &value), value;
            };

        if   constexpr (P == gl::pipeline_property_e::validate_status) return static_cast<gl::bool_t  >(get_program_pipeline_iv(pipeline, P));
        if   constexpr (P == gl::pipeline_property_e::info_log_length) return static_cast<gl::uint32_t>(get_program_pipeline_iv(pipeline, P));
        else                                                           return static_cast<gl::handle_t>(get_program_pipeline_iv(pipeline, P));
    }
    auto get_attached_shaders                       (gl::handle_t program) -> std::vector<gl::handle_t>
    {
        auto attachedShaders = gl::get_program_value<gl::program_parameter_e::attached_shaders>(program);
        auto shaders         = std::vector<gl::handle_t>(attachedShaders);
        return glGetAttachedShaders(gl::to_underlying(program), attachedShaders, nullptr, gl::to_underlying_ptr(shaders.data())), shaders;
    }
    auto get_shader_info_log                        (gl::handle_t shader) -> std::string
    {
        auto infoLogLength = get_shader_value<gl::shader_parameter_e::info_log_length>(shader);
        auto infoLog       = std::string(infoLogLength, '\0');

        if (!infoLog.empty())
        {
            glGetShaderInfoLog(gl::to_underlying(shader), infoLogLength, nullptr, infoLog.data());
            infoLog.pop_back();
        }

        return infoLog;
    }
    auto get_program_info_log                       (gl::handle_t program) -> std::string
    {
        auto infoLogLength = gl::get_program_value<gl::program_parameter_e::info_log_length>(program);
        auto infoLog       = std::string(infoLogLength, '\0');

        if (!infoLog.empty())
        {
            glGetProgramInfoLog(gl::to_underlying(program), infoLogLength, nullptr, infoLog.data());
            infoLog.pop_back();
        }

        return infoLog;
    }
    auto get_pipeline_info_log                      (gl::handle_t pipeline) -> std::string
    {
        auto infoLogLength = gl::get_program_pipeline_value<gl::pipeline_property_e::info_log_length>(pipeline);
        auto infoLog       = std::string(infoLogLength, '\0');

        if (!infoLog.empty())
        {
            glGetProgramPipelineInfoLog(gl::to_underlying(pipeline), infoLogLength, nullptr, infoLog.data());
            infoLog.pop_back();
        }

        return infoLog;
    }
    auto get_shader_source                          (gl::handle_t shader) -> std::string
    {
        auto sourceLength = get_shader_value<gl::shader_parameter_e::source_length>(shader);
        auto shaderSource = std::string(sourceLength, '\0');

        if (!shaderSource.empty())
        {
            glGetShaderSource(gl::to_underlying(shader), sourceLength, nullptr, shaderSource.data());
            shaderSource.pop_back();
        }

        return shaderSource;
    }
    auto get_shader_precision_format                (gl::shader_type_e type, gl::shader_precision_format_e format) -> std::tuple<std::array<gl::int32_t, 2u>, gl::int32_t>
    {
        auto range     = std::array<gl::int32_t, 2u>{};
        auto precision = gl::int32_t{};
        return glGetShaderPrecisionFormat(gl::to_underlying(type), gl::to_underlying(format), range.data(), &precision), std::make_tuple(range, precision);
    }



    //Chapter 8 - Textures and Samplers
    template<gl::sampler_parameter_e P>
    auto get_sampler_parameter_value                (gl::handle_t sampler) -> auto
    {
        auto get_sampler_parameter_iv  = [](gl::handle_t sampler, gl::sampler_parameter_e parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return glGetSamplerParameteriv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value), value;
            };
        auto get_sampler_parameter_uiv = [](gl::handle_t sampler, gl::sampler_parameter_e parameter) -> gl::uint32_t
            {
                auto value = gl::uint32_t{};
                return glGetSamplerParameterIuiv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value), value;
            };
        auto get_sampler_parameter_fv  = [](gl::handle_t sampler, gl::sampler_parameter_e parameter) -> gl::float32_t
            {
                auto value = gl::float32_t{};
                return glGetSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value), value;
            };
        auto get_border_color          = [](gl::handle_t sampler) -> gl::vector4f
            {
                auto value = gl::vector4f{};
                return glGetSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(gl::sampler_parameter_e::border_color), glm::value_ptr(value)), value;
            };

        if constexpr (P == gl::sampler_parameter_e::border_color        ) return                                                (get_border_color         (sampler   ));
        if constexpr (P == gl::sampler_parameter_e::compare_function    ) return static_cast<gl::texture_compare_function_e>    (get_sampler_parameter_uiv(sampler, P));
        if constexpr (P == gl::sampler_parameter_e::compare_mode        ) return static_cast<gl::texture_compare_mode_e>        (get_sampler_parameter_uiv(sampler, P));
        if constexpr (P == gl::sampler_parameter_e::lod_bias            ) return                                                (get_sampler_parameter_fv (sampler, P));
        if constexpr (P == gl::sampler_parameter_e::magnification_filter) return static_cast<gl::texture_magnification_filter_e>(get_sampler_parameter_uiv(sampler, P));
        if constexpr (P == gl::sampler_parameter_e::maximum_anisotropy  ) return                                                (get_sampler_parameter_fv (sampler, P));
        if constexpr (P == gl::sampler_parameter_e::maximum_lod         ) return                                                (get_sampler_parameter_fv (sampler, P));
        if constexpr (P == gl::sampler_parameter_e::minification_filter ) return static_cast<gl::texture_minification_filter_e> (get_sampler_parameter_uiv(sampler, P));
        if constexpr (P == gl::sampler_parameter_e::minimum_lod         ) return                                                (get_sampler_parameter_fv (sampler, P));
        if constexpr (P == gl::sampler_parameter_e::wrapping_r          ) return static_cast<gl::texture_wrapping_e>            (get_sampler_parameter_uiv(sampler, P));
        if constexpr (P == gl::sampler_parameter_e::wrapping_s          ) return static_cast<gl::texture_wrapping_e>            (get_sampler_parameter_uiv(sampler, P));
        if constexpr (P == gl::sampler_parameter_e::wrapping_t          ) return static_cast<gl::texture_wrapping_e>            (get_sampler_parameter_uiv(sampler, P));
    }
    template<gl::texture_format_e F>
    auto get_texture_image                          (gl::handle_t texture, gl::uint32_t level, gl::size_t size) -> auto
    {
        if constexpr (F == gl::texture_format_e::rgba8_unorm )
        {
            auto value = std::vector<gl::vector4u>(size);

            glGetTextureImage(
                gl::to_underlying       (texture)                      , 
                static_cast<gl::int32_t>(level)                        , 
                gl::to_underlying       (gl::buffer_base_format_e::rgba), gl::to_underlying(gl::pixel_data_type_e::unsigned_byte_), 
                static_cast<gl::sizei_t>(value.size())                 , value.data());

            return value;
        }
        if constexpr (F == gl::texture_format_e::rgba32_float)
        {
            gl::todo();
        }
    }
    template<gl::texture_format_e F>
    auto get_texture_sub_image                      (gl::handle_t texture, gl::uint32_t level, gl::volume_t region, gl::size_t size) -> auto
    {
        if constexpr (F == gl::texture_format_e::rgba8_unorm )
        {
            auto value = std::vector<gl::vector4u>(size);

            glGetTextureSubImage(
                gl::to_underlying       (texture)                       , 
                static_cast<gl::int32_t>(level)                         , 
                static_cast<gl::int32_t>(region.origin.x)               , static_cast<gl::int32_t>(region.origin.y)               , static_cast<gl::int32_t>(region.origin.z), 
                static_cast<gl::sizei_t>(region.extent.x)               , static_cast<gl::sizei_t>(region.extent.y)               , static_cast<gl::sizei_t>(region.extent.z), 
                gl::to_underlying       (gl::buffer_base_format_e::rgba), gl::to_underlying(gl::pixel_data_type_e::unsigned_byte_), 
                static_cast<gl::sizei_t>(value.size())                  , value.data());

            return value;
        }
        if constexpr (F == gl::texture_format_e::rgba32_float)
        {
            gl::todo();
        }
    }
    template<gl::texture_format_e F>
    auto get_compressed_texture_image               (gl::handle_t texture, gl::uint32_t level, gl::size_t size) -> auto
    {
        if constexpr (F == gl::texture_format_e::rgba8_unorm )
        {
            auto value = std::vector<gl::vector4u>(size);

            glGetCompressedTextureImage(
                gl::to_underlying       (texture)                      , 
                static_cast<gl::int32_t>(level)                        , 
                static_cast<gl::sizei_t>(value.size())                 , value.data());

            return value;
        }
        if constexpr (F == gl::texture_format_e::rgba32_float)
        {
            gl::todo();
        }
    }
    template<gl::texture_format_e F>
    auto get_compressed_texture_sub_image           (gl::handle_t texture, gl::uint32_t level, gl::volume_t region, gl::size_t size) -> auto
    {
        if constexpr (F == gl::texture_format_e::rgba8_unorm )
        {
            auto value = std::vector<gl::vector4u>(size);

            glGetCompressedTextureSubImage(
                gl::to_underlying       (texture)        , 
                static_cast<gl::int32_t>(level)          , 
                static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z), 
                static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), static_cast<gl::sizei_t>(region.extent.z), 
                static_cast<gl::sizei_t>(value.size())   , value.data());

            return value;
        }
        if constexpr (F == gl::texture_format_e::rgba32_float)
        {
            gl::todo();
        }
    }



    //Chapter 9 - FrameBuffer and FrameBuffer Objects
    template<gl::frame_buffer_parameter_e P>
    auto get_frame_buffer_parameter_value           (gl::handle_t frameBuffer) -> auto
    {
        auto get_frame_buffer_parameter_iv = [](gl::handle_t frameBuffer, gl::frame_buffer_parameter_e parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return glGetNamedFramebufferParameteriv(gl::to_underlying(frameBuffer), gl::to_underlying(parameter), &value), value;
            };

        if constexpr (P == gl::frame_buffer_parameter_e::default_width                 ) return static_cast<gl::uint32_t>           (get_frame_buffer_parameter_iv(frameBuffer, P));
        if constexpr (P == gl::frame_buffer_parameter_e::default_height                ) return static_cast<gl::uint32_t>           (get_frame_buffer_parameter_iv(frameBuffer, P));
        if constexpr (P == gl::frame_buffer_parameter_e::default_layers                ) return static_cast<gl::uint32_t>           (get_frame_buffer_parameter_iv(frameBuffer, P));
        if constexpr (P == gl::frame_buffer_parameter_e::default_samples               ) return static_cast<gl::uint32_t>           (get_frame_buffer_parameter_iv(frameBuffer, P));
        if constexpr (P == gl::frame_buffer_parameter_e::default_fixed_sample_locations) return static_cast<gl::bool_t>             (get_frame_buffer_parameter_iv(frameBuffer, P));

        if (frameBuffer == gl::default_frame_buffer) throw std::invalid_argument{ "Operation may not be called on the default framebuffer!" };

        if constexpr (P == gl::frame_buffer_parameter_e::color_read_format             ) return static_cast<gl::pixel_data_format_e>(get_frame_buffer_parameter_iv(frameBuffer, P));
        if constexpr (P == gl::frame_buffer_parameter_e::color_read_type               ) return static_cast<gl::pixel_data_type_e>  (get_frame_buffer_parameter_iv(frameBuffer, P));
        if constexpr (P == gl::frame_buffer_parameter_e::doublebuffer                  ) return static_cast<gl::bool_t>             (get_frame_buffer_parameter_iv(frameBuffer, P));
        if constexpr (P == gl::frame_buffer_parameter_e::samplebuffers                 ) return static_cast<gl::uint32_t>           (get_frame_buffer_parameter_iv(frameBuffer, P));
        if constexpr (P == gl::frame_buffer_parameter_e::samples                       ) return static_cast<gl::uint32_t>           (get_frame_buffer_parameter_iv(frameBuffer, P));
        if constexpr (P == gl::frame_buffer_parameter_e::stereo                        ) return static_cast<gl::bool_t>             (get_frame_buffer_parameter_iv(frameBuffer, P));
    }
    template<gl::frame_buffer_parameter_e P>
    auto get_frame_buffer_attachment_parameter_value(gl::handle_t frameBuffer) -> auto
    {
        auto get_frame_buffer_attachment_parameter_iv = [](gl::handle_t frameBuffer, gl::frame_buffer_attachment_e attachment, gl::frame_buffer_parameter_e parameter)
            {
                auto value = gl::int32_t{};
                return glGetNamedFramebufferAttachmentParameteriv(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), gl::to_underlying(parameter), &value), value;
            };

        gl::todo();
    }
    template<gl::render_buffer_parameter_e P>
    auto get_render_buffer_parameter_value          (gl::handle_t renderBuffer) -> auto
    {
        auto get_render_buffer_parameter_iv = [](gl::handle_t renderBuffer, gl::render_buffer_parameter_e parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return glGetNamedRenderbufferParameteriv(gl::to_underlying(renderBuffer), gl::to_underlying(parameter), &value), value;
            };

        if constexpr (P == gl::render_buffer_parameter_e::width          ) return static_cast<gl::uint32_t>             (get_render_buffer_parameter_iv(renderBuffer, P));
        if constexpr (P == gl::render_buffer_parameter_e::height         ) return static_cast<gl::uint32_t>             (get_render_buffer_parameter_iv(renderBuffer, P));
        if constexpr (P == gl::render_buffer_parameter_e::internal_format) return static_cast<gl::frame_buffer_format_e>(get_render_buffer_parameter_iv(renderBuffer, P));
        if constexpr (P == gl::render_buffer_parameter_e::samples        ) return static_cast<gl::uint32_t>             (get_render_buffer_parameter_iv(renderBuffer, P));
        if constexpr (P == gl::render_buffer_parameter_e::red_size       ) return static_cast<gl::uint32_t>             (get_render_buffer_parameter_iv(renderBuffer, P));
        if constexpr (P == gl::render_buffer_parameter_e::green_size     ) return static_cast<gl::uint32_t>             (get_render_buffer_parameter_iv(renderBuffer, P));
        if constexpr (P == gl::render_buffer_parameter_e::blue_size      ) return static_cast<gl::uint32_t>             (get_render_buffer_parameter_iv(renderBuffer, P));
        if constexpr (P == gl::render_buffer_parameter_e::alpha_size     ) return static_cast<gl::uint32_t>             (get_render_buffer_parameter_iv(renderBuffer, P));
        if constexpr (P == gl::render_buffer_parameter_e::depth_size     ) return static_cast<gl::uint32_t>             (get_render_buffer_parameter_iv(renderBuffer, P));
        if constexpr (P == gl::render_buffer_parameter_e::stencil_size   ) return static_cast<gl::uint32_t>             (get_render_buffer_parameter_iv(renderBuffer, P));
    }



    //Chapter 10 - Vertex Specification and Drawing Commands
    template<gl::vertex_array_parameter_e P>
    auto get_vertex_array_indexed_value             (gl::handle_t vertexArray) -> gl::handle_t
    {
        if constexpr (P == gl::vertex_array_parameter_e::element_array_buffer_binding)
        {
            auto value = gl::int32_t{};
            return glGetVertexArrayiv(gl::to_underlying(vertexArray), gl::to_underlying(P), &value), static_cast<gl::handle_t>(value);
        }
    }
    template<gl::vertex_array_parameter_e P>
    auto get_vertex_array_indexed_value             (gl::handle_t vertexArray, gl::index_t index) -> auto
    {
        auto get_vertex_array_indexed32_iv = [](gl::handle_t vertexArray, gl::vertex_array_parameter_e parameter, gl::index_t index) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return glGetVertexArrayIndexediv(gl::to_underlying(vertexArray), index, gl::to_underlying(parameter), &value), value;
            };
        auto get_vertex_array_indexed64_iv = [](gl::handle_t vertexArray, gl::vertex_array_parameter_e parameter, gl::index_t index) -> gl::int32_t
            {
                auto value = gl::int64_t{};
                return glGetVertexArrayIndexed64iv(gl::to_underlying(vertexArray), index, gl::to_underlying(parameter), &value), value;
            };
        
        auto maximumVertexAttributes = gl::get_value<gl::data_e::maximum_vertex_attributes>();
        if (gl::compare<std::greater>(index, maximumVertexAttributes - gl::uint32_t{ 1u })) throw std::out_of_range{"The given index is out of range!"};
        
        if constexpr (P == gl::vertex_array_parameter_e::binding_offset ) return static_cast<gl::uint64_t>                     (get_vertex_array_indexed64_iv(vertexArray, P, index));
        if constexpr (P == gl::vertex_array_parameter_e::divisor        ) return static_cast<gl::uint32_t>                     (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == gl::vertex_array_parameter_e::enabled        ) return static_cast<gl::bool_t>                       (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == gl::vertex_array_parameter_e::is_integer_data) return static_cast<gl::bool_t>                       (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == gl::vertex_array_parameter_e::is_long_data   ) return static_cast<gl::bool_t>                       (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == gl::vertex_array_parameter_e::is_normalized  ) return static_cast<gl::bool_t>                       (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == gl::vertex_array_parameter_e::relative_offset) return static_cast<gl::uint32_t>                     (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == gl::vertex_array_parameter_e::size           ) return static_cast<gl::uint32_t>                     (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == gl::vertex_array_parameter_e::stride         ) return static_cast<gl::uint32_t>                     (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == gl::vertex_array_parameter_e::type           ) return static_cast<gl::vertex_array_attribute_type_e>(get_vertex_array_indexed32_iv(vertexArray, P, index));
    }



    //Chapter 20 - Debug Output
    auto get_debug_message_log                      (gl::count_t count) -> std::vector<gl::message_log>
    {
        auto get_debug_message_log = [](gl::count_t count, std::span<gl::debug_source_e> sources, std::span<gl::debug_type_e> types, std::span<gl::uint32_t> ids, std::span<gl::debug_severity_e> severities, std::span<gl::sizei_t> lengths, std::string& messageLog)
            {
                auto maximumLength = gl::get_value<gl::data_e::maximum_debug_message_length>();
                     messageLog    = std::string(count * maximumLength, '\0');

                return glGetDebugMessageLog(
                    count, static_cast<gl::sizei_t>(maximumLength), 
                    gl::to_underlying_ptr(sources   .data()), 
                    gl::to_underlying_ptr(types     .data()), 
                                          ids       .data(), 
                    gl::to_underlying_ptr(severities.data()), 
                                          lengths   .data(), 
                                          messageLog.data());
            };
        
        auto sources     = std::vector<gl::debug_source_e>  (count);
        auto types       = std::vector<gl::debug_type_e>    (count);
        auto ids         = std::vector<gl::uint32_t>        (count);
        auto severities  = std::vector<gl::debug_severity_e>(count);
        auto lengths     = std::vector<gl::sizei_t>         (count);
        auto messageLog  = std::string{};

        auto amount      = get_debug_message_log(count, sources, types, ids, severities, lengths, messageLog);
        auto messageLogs = std::vector<gl::message_log>(amount);

        if (!messageLogs.empty())
        {
            for (auto offset = gl::offset_t{}; auto index : std::views::iota(0u, amount))
            {
                auto length = lengths.at(index);
                auto log    = std::string{ messageLog.data() + offset, static_cast<std::size_t>(length) - 1u };

                offset += length;

                messageLogs.emplace_back(
                    ids       .at(index),
                    std::move(log), 
                    sources   .at(index),
                    types     .at(index),
                    severities.at(index));
            }
        }

        return messageLogs;
    }







    //Chapter 2 - OpenGL Fundamentals
    auto get_graphics_reset_status                  () -> gl::error_graphics_reset_status_e
    {
        return static_cast<gl::error_graphics_reset_status_e>(glGetGraphicsResetStatus());
    }
    void flush                                      ()
    {
        glFlush();
    }
    void finish                                     ()
    {
        glFinish();
    }



    //Chapter 4 - Event Model
    auto fence_sync                                 () -> gl::sync_t
    {
        return static_cast<gl::sync_t>(glFenceSync(gl::to_underlying(gl::synchronization_object_condition_e::gpu_commands_complete), gl::bitfield_t{ 0u }));
    }
    void delete_sync                                (gl::sync_t sync)
    {
        if (sync) glDeleteSync(sync);
    }
    auto client_wait_sync                           (gl::sync_t sync, gl::synchronization_command_e command, gl::time_t timeout) -> gl::synchronization_status_e
    {
        return static_cast<gl::synchronization_status_e>(glClientWaitSync(sync, gl::to_underlying(command), timeout));
    }
    void server_wait_sync                           (gl::sync_t sync)
    {
        glWaitSync(sync, gl::bitfield_t{ 0u }, gl::to_underlying(gl::synchronization_timeout_e::ignored));
    }
    auto create_query                               (gl::query_target_e target) -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return glCreateQueries(gl::to_underlying(target), gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle)), handle;
    }
    auto create_queries                             (gl::query_target_e target, gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return glCreateQueries(gl::to_underlying(target), static_cast<gl::sizei_t>(count), gl::to_underlying_ptr(handles.data())), handles;
    }
    void delete_query                               (gl::handle_t query)
    {
        glDeleteQueries(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&query));
    }
    void delete_queries                             (std::span<const gl::handle_t> queries)
    {
        glDeleteQueries(static_cast<gl::sizei_t>(queries.size()), gl::to_underlying_ptr(queries.data()));
    }
    void begin_query                                (gl::handle_t query, gl::query_target_e target)
    {
        glBeginQuery(gl::to_underlying(target), gl::to_underlying(query));
    }
    void begin_query_index                          (gl::handle_t query, gl::query_target_e target, gl::index_t index)
    {
        glBeginQueryIndexed(gl::to_underlying(target), index, gl::to_underlying(query));
    }
    void end_query                                  (gl::query_target_e target)
    {
        glEndQuery(gl::to_underlying(target));
    }
    void end_query_index                            (gl::query_target_e target, gl::index_t index)
    {
        glEndQueryIndexed(gl::to_underlying(target), index);
    }
    void query_counter                              (gl::handle_t query)
    {
        glQueryCounter(gl::to_underlying(query), gl::to_underlying(gl::query_counter_e::timestamp));
    }



    //Chapter 6 - Buffer Objects
    auto create_buffer                              () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return glCreateBuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle)), handle;
    }
    auto create_buffers                             (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return glCreateBuffers(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data())), handles;
    }
    void delete_buffer                              (gl::handle_t buffer)
    {
        glDeleteBuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&buffer));
    }
    void delete_buffers                             (std::span<const gl::handle_t> buffers)
    {
        glDeleteBuffers(static_cast<gl::sizei_t>(buffers.size()), gl::to_underlying_ptr(buffers.data()));
    }
    void bind_buffer_base                           (gl::handle_t buffer, gl::buffer_base_target_e target, gl::binding_t binding)
    {
        glBindBufferBase(gl::to_underlying(target), gl::to_underlying(binding), gl::to_underlying(buffer));
    }
    void bind_buffers_base                          (std::span<const gl::handle_t> buffers, gl::buffer_base_target_e target, gl::binding_t binding)
    {
        glBindBuffersBase(gl::to_underlying(target), gl::to_underlying(binding), static_cast<gl::sizei_t>(buffers.size()), gl::to_underlying_ptr(buffers.data()));
    }
    template<typename T>
    void bind_buffer_range                          (gl::handle_t buffer, gl::buffer_base_target_e target, gl::binding_t binding, gl::range range)
    {
        auto byterange = gl::convert_range<T>(range);
        glBindBufferRange(gl::to_underlying(target), gl::to_underlying(binding), gl::to_underlying(buffer), byterange.offset, byterange.size);
    }
    template<typename T>
    void bind_buffers_range                         (std::span<const gl::handle_t> buffers, std::span<const gl::range> ranges, gl::buffer_base_target_e target, gl::binding_t binding)
    {
        auto sizes   = std::vector<gl::size_t>  (ranges.size());
        auto offsets = std::vector<gl::offset_t>(ranges.size());

        std::ranges::for_each(ranges, [&](const gl::range& range)
            {
                auto byterange = gl::convert_range<T>(range);

                sizes  .emplace_back(byterange.size  );
                offsets.emplace_back(byterange.offset);
            });

        glBindBuffersRange(gl::to_underlying(target), gl::to_underlying(binding), static_cast<gl::sizei_t>(buffers.size()), gl::to_underlying_ptr(buffers.data()), offsets.data(), sizes.data());
    }
    template<typename T>
    void buffer_storage                             (gl::handle_t buffer, gl::buffer_storage_flags_e flags, gl::count_t count)
    {
        glNamedBufferStorage(gl::to_underlying(buffer), static_cast<gl::size_t>(count * sizeof(T)), nullptr, gl::to_underlying(flags));
    }
    template<typename T>                  
    void buffer_storage                             (gl::handle_t buffer, gl::buffer_storage_flags_e flags, std::span<const T> data)
    {
        glNamedBufferStorage(gl::to_underlying(buffer), static_cast<gl::size_t>(data.size_bytes()), data.data(), gl::to_underlying(flags));
    }
    template<typename T>
    void buffer_data                                (gl::handle_t buffer, gl::index_t index, std::span<const T> data)
    {
        glNamedBufferSubData(gl::to_underlying(buffer), static_cast<gl::offset_t>(index * sizeof(T)), static_cast<gl::size_t>(data.size_bytes()), data.data());
    }
    template<typename T>
    void clear_buffer_data                          (gl::handle_t buffer, gl::buffer_base_format_e baseFormat, gl::buffer_format_e format, gl::data_type_e type, std::span<const T> data)
    {
        gl::todo();
        glClearNamedBufferData(gl::to_underlying(buffer), gl::to_underlying(format), gl::to_underlying(baseFormat), gl::to_underlying(type), data.data());
    }
    template<typename T>
    void clear_buffer_sub_data                      (gl::handle_t buffer, gl::buffer_base_format_e baseFormat, gl::buffer_format_e format, gl::data_type_e type, gl::range range)
    {
        auto byterange = gl::convert_range<T>(range);
        glClearNamedBufferSubData(gl::to_underlying(buffer), gl::to_underlying(format), byterange.offset, byterange.size, gl::to_underlying(baseFormat), gl::to_underlying(type), nullptr);
    }
    template<typename T>
    auto map_buffer                                 (gl::handle_t buffer, gl::buffer_mapping_access_flags_e access, gl::count_t count) -> std::span<T>
    {
        return std::span{ std::bit_cast<T*>(glMapNamedBuffer(gl::to_underlying(buffer), gl::to_underlying(access))), count };
    }
    template<typename T>
    auto map_buffer_range                           (gl::handle_t buffer, gl::buffer_mapping_range_access_flags_e access, gl::range range) -> std::span<T>
    {
        auto byterange = gl::convert_range<T>(range);
        return std::span{ std::bit_cast<T*>(glMapNamedBufferRange(gl::to_underlying(buffer), byterange.offset, byterange.size, gl::to_underlying(access))), range.count };
    }
    template<typename T>
    void flush_buffer_range                         (gl::handle_t buffer, gl::range range)
    {
        auto byterange = gl::convert_range<T>(range);
        glFlushMappedNamedBufferRange(gl::to_underlying(buffer), byterange.offset, byterange.size);
    }
    auto unmap_buffer                               (gl::handle_t buffer) -> gl::bool_t
    {
        return glUnmapNamedBuffer(gl::to_underlying(buffer));
    }
    void invalidate_buffer_data                     (gl::handle_t buffer)
    {
        glInvalidateBufferData(gl::to_underlying(buffer));
    }
    template<typename T>
    void invalidate_buffer_sub_data                 (gl::handle_t buffer, gl::range range)
    {
        auto byterange = gl::convert_range<T>(range);
        glInvalidateBufferSubData(gl::to_underlying(buffer), byterange.offset, byterange.size);
    }
    template<typename T>
    void copy_buffer_sub_data                       (gl::handle_t source, gl::handle_t destination, gl::range sourceRange, gl::range destinationRange)
    {
        auto sourceByterange      = gl::convert_range<T>(sourceRange     );
        auto destinationByterange = gl::convert_range<T>(destinationRange);
        glCopyNamedBufferSubData(gl::to_underlying(source), gl::to_underlying(destination), sourceByterange.offset, destinationByterange.offset, sourceByterange.size);
    }
    


    //Chapter 7 - Programs and Shaders
    auto create_shader                              (gl::shader_type_e type) -> gl::handle_t
    {
        return static_cast<gl::handle_t>(glCreateShader(gl::to_underlying(type)));
    }
    void shader_source                              (gl::handle_t shader, const std::string& source)
    {
        const auto* cstr = source.c_str();
        glShaderSource(gl::to_underlying(shader), gl::sizei_t{ 1 }, &cstr, nullptr);
    }
    void compile_shader                             (gl::handle_t shader)
    {
        glCompileShader(gl::to_underlying(shader));
    }
    void release_shader_compiler                    ()
    {
        glReleaseShaderCompiler();
    }
    void delete_shader                              (gl::handle_t shader)
    {
        glDeleteShader(gl::to_underlying(shader));
    }
    void shader_binary                              (gl::handle_t shader, gl::enum_t format, std::span<const gl::byte_t> binary)
    {
        glShaderBinary(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&shader), format, binary.data(), static_cast<gl::sizei_t>(binary.size_bytes()));
    }
    void shader_binaries                            (std::span<const gl::handle_t> shaders, gl::enum_t format, std::span<const gl::byte_t> binary)
    {
        glShaderBinary(static_cast<gl::sizei_t>(shaders.size()), gl::to_underlying_ptr(shaders.data()), format, binary.data(), static_cast<gl::sizei_t>(binary.size_bytes()));
    }
    template<gl::count_t N = 0>
    void specialize_shader                          (gl::handle_t shader, const std::string& entry, std::span<const gl::uint32_t, N> indices = {}, std::span<const gl::uint32_t, N> values = {})
    {
        const auto* cstr = entry.c_str();
        glSpecializeShader(gl::to_underlying(shader), cstr, N, indices.data(), values.data());
    }
    auto create_program                             () -> gl::handle_t
    {
        return static_cast<gl::handle_t>(glCreateProgram());
    }
    void attach_shader                              (gl::handle_t program, gl::handle_t shader)
    {
        glAttachShader(gl::to_underlying(program), gl::to_underlying(shader));
    }
    void detach_shader                              (gl::handle_t program, gl::handle_t shader)
    {
        glDetachShader(gl::to_underlying(program), gl::to_underlying(shader));
    }
    void link_program                               (gl::handle_t program)
    {
        glLinkProgram(gl::to_underlying(program));
    }
    template<gl::program_specification_e S>
    void program_parameter                          (gl::handle_t program, gl::bool_t value)
    {
        glProgramParameteri(gl::to_underlying(program), gl::to_underlying(S), value);
    }
    void delete_program                             (gl::handle_t program)
    {
        glDeleteProgram(gl::to_underlying(program));
    }
    auto create_shader_program                      (gl::shader_type_e type, const std::string& source) -> gl::handle_t
    {
        const auto* cstr = source.c_str();
        return static_cast<gl::handle_t>(glCreateShaderProgramv(gl::to_underlying(type), gl::sizei_t{ 1 }, &cstr));
    }
    auto create_program_pipeline                    () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return glCreateProgramPipelines(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle)), handle;
    }
    auto create_program_pipelines                   (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return glCreateProgramPipelines(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data())), handles;
    }
    void delete_program_pipeline                    (gl::handle_t pipeline)
    {
        glDeleteProgramPipelines(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&pipeline));
    }
    void delete_program_pipelines                   (std::span<const gl::handle_t> pipeline)
    {
        glDeleteProgramPipelines(static_cast<gl::sizei_t>(pipeline.size()), gl::to_underlying_ptr(pipeline.data()));
    }
    void bind_program_pipeline                      (gl::handle_t pipeline)
    {
        glBindProgramPipeline(gl::to_underlying(pipeline));
    }
    void use_program_stages                         (gl::handle_t pipeline, gl::handle_t program, gl::program_stage_e stages)
    {
        glUseProgramStages(gl::to_underlying(pipeline), gl::to_underlying(stages), gl::to_underlying(program));
    }
    auto get_program_binary                         (gl::handle_t program) -> gl::binary_info
    {
        auto binaryLength = gl::get_program_value<gl::program_parameter_e::binary_length>(program);
        auto info         = gl::binary_info{};
        return glGetProgramBinary(gl::to_underlying(program), binaryLength, nullptr, &info.format, info.binary.data()), info;
    }
    void program_binary                             (gl::handle_t program, gl::enum_t format, std::span<const gl::byte_t> binary)
    {
        glProgramBinary(gl::to_underlying(program), format, binary.data(), static_cast<gl::sizei_t>(binary.size()));
    }
    void memory_barrier                             (gl::memory_barrier_e         barrier)
    {
        glMemoryBarrier(gl::to_underlying(barrier));
    }
    void memory_barrier_by_region                   (gl::memory_regional_barrier_e barrier)
    {
        glMemoryBarrierByRegion(gl::to_underlying(barrier));
    }



    //Chapter 8 - Textures and Samplers
    auto create_texture                             (gl::texture_target_e target) -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return glCreateTextures(gl::to_underlying(target), gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle)), handle;
    }
    auto create_textures                            (gl::texture_target_e target, gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return glCreateTextures(gl::to_underlying(target), static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data())), handles;
    }
    void delete_texture                             (gl::handle_t texture)
    {
        glDeleteTextures(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&texture));
    }
    void delete_textures                            (std::span<const gl::handle_t> textures)
    {
        glDeleteTextures(static_cast<gl::sizei_t>(textures.size()), gl::to_underlying_ptr(textures.data()));
    }
    void bind_texture_unit                          (gl::handle_t texture, gl::binding_t binding)
    {
        glBindTextureUnit(gl::to_underlying(binding), gl::to_underlying(texture));
    }
    auto create_sampler                             () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return glCreateSamplers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle)), handle;
    }
    auto create_samplers                            (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return glCreateSamplers(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data())), handles;
    }
    void delete_sampler                             (gl::handle_t sampler)
    {
        glDeleteSamplers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&sampler));
    }
    void delete_samplers                            (std::span<const gl::handle_t> samplers)
    {
        glDeleteSamplers(static_cast<gl::sizei_t>(samplers.size()), gl::to_underlying_ptr(samplers.data()));
    }
    void bind_sampler                               (gl::handle_t sampler, gl::binding_t binding)
    {
        glBindSampler(gl::to_underlying(binding), gl::to_underlying(sampler));
    }
    void bind_samplers                              (std::span<const gl::handle_t> samplers, gl::range range)
    {
        glBindSamplers(range.index, range.count, gl::to_underlying_ptr(samplers.data()));
    }
    auto sampler_parameter                          (gl::handle_t sampler, glp::sampler_parameter_v parameter) -> auto
    {
        auto sampler_parameter_iv  = [](gl::handle_t sampler, gl::sampler_parameter_e parameter, gl::int32_t   value)
            {
                glSamplerParameterIiv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);
            };
        auto sampler_parameter_uiv = [](gl::handle_t sampler, gl::sampler_parameter_e parameter, gl::uint32_t  value)
            {
                glSamplerParameterIuiv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);
            };
        auto sampler_parameter_fv  = [](gl::handle_t sampler, gl::sampler_parameter_e parameter, gl::float32_t value)
            {
                glSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);
            };

        const auto overload = gl::overload
        {
            [=](glp::compare_mode         _) { sampler_parameter_uiv(sampler, gl::sampler_parameter_e::compare_mode        , gl::to_underlying(_.value)); }, 
            [=](glp::compare_function     _) { sampler_parameter_uiv(sampler, gl::sampler_parameter_e::compare_function    , gl::to_underlying(_.value)); },
            [=](glp::magnification_filter _) { sampler_parameter_uiv(sampler, gl::sampler_parameter_e::magnification_filter, gl::to_underlying(_.value)); },
            [=](glp::minification_filter  _) { sampler_parameter_uiv(sampler, gl::sampler_parameter_e::minification_filter , gl::to_underlying(_.value)); },
            [=](glp::wrapping_r           _) { sampler_parameter_uiv(sampler, gl::sampler_parameter_e::wrapping_r          , gl::to_underlying(_.value)); },
            [=](glp::wrapping_s           _) { sampler_parameter_uiv(sampler, gl::sampler_parameter_e::wrapping_s          , gl::to_underlying(_.value)); },
            [=](glp::wrapping_t           _) { sampler_parameter_uiv(sampler, gl::sampler_parameter_e::wrapping_t          , gl::to_underlying(_.value)); },
            [=](glp::border_color         _) 
                {
                    const auto overload = gl::overload
                    {
                        [=](std::array<gl::int32_t  , 4u> _) { glSamplerParameterIiv (gl::to_underlying(sampler), gl::to_underlying(gl::sampler_parameter_e::border_color), _.data()); }, 
                        [=](std::array<gl::uint32_t , 4u> _) { glSamplerParameterIuiv(gl::to_underlying(sampler), gl::to_underlying(gl::sampler_parameter_e::border_color), _.data()); }, 
                        [=](std::array<gl::float32_t, 4u> _) { glSamplerParameterfv  (gl::to_underlying(sampler), gl::to_underlying(gl::sampler_parameter_e::border_color), _.data()); }, 
                    };

                    std::visit(overload, _.value);
                }, 
            [=](glp::maximum_lod          _) { sampler_parameter_fv (sampler, gl::sampler_parameter_e::maximum_lod         ,                   _.value ); }, 
            [=](glp::minimum_lod          _) { sampler_parameter_fv (sampler, gl::sampler_parameter_e::minimum_lod         ,                   _.value ); }, 
        };

        std::visit(overload, parameter);
    }
    template<gl::packing_mode_e P>
    void pixel_store                                (gl::int32_t parameter)
    {
        glPixelStorei(gl::to_underlying(P), parameter);
    }
    void texture_sub_image_1d                       (gl::handle_t texture, gl::texture_base_format_e format, gl::pixel_data_type_e type, gl::uint32_t level, gl::length_t region, std::span<const gl::byte_t> data)
    {
        glTextureSubImage1D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level), 
            static_cast<gl::int32_t>(region.origin.x), 
            static_cast<gl::sizei_t>(region.extent.x), 
            gl::to_underlying       (format)         , gl::to_underlying(type)        , 
            data.data());
    }
    void texture_sub_image_2d                       (gl::handle_t texture, gl::texture_base_format_e format, gl::pixel_data_type_e type, gl::uint32_t level, gl::area_t   region, std::span<const gl::byte_t> data)
    {
        glTextureSubImage2D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level), 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), 
            gl::to_underlying       (format)         , gl::to_underlying(type), 
            data.data());
    }
    void texture_sub_image_3d                       (gl::handle_t texture, gl::texture_base_format_e format, gl::pixel_data_type_e type, gl::uint32_t level, gl::volume_t region, std::span<const gl::byte_t> data)
    {
        glTextureSubImage3D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), static_cast<gl::sizei_t>(region.extent.z), 
            gl::to_underlying       (format)         , gl::to_underlying(type)                  , 
            data.data());
    }
    void copy_texture_sub_image_1d                  (gl::handle_t texture, gl::uint32_t level, gl::length_t region, const gl::vector2u& coordinates)
    {
        glCopyTextureSubImage1D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)        , 
            static_cast<gl::int32_t>(region.origin.x), 
            static_cast<gl::int32_t>(coordinates  .x), static_cast<gl::int32_t>(coordinates.y), 
            static_cast<gl::sizei_t>(region.extent.x));
    }
    void copy_texture_sub_image_2d                  (gl::handle_t texture, gl::uint32_t level, gl::area_t   region, const gl::vector2u& coordinates)
    {
        glCopyTextureSubImage2D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), 
            static_cast<gl::int32_t>(coordinates  .x), static_cast<gl::int32_t>(coordinates  .y), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y));
    }
    void copy_texture_sub_image_3d                  (gl::handle_t texture, gl::uint32_t level, gl::volume_t region, const gl::vector2u& coordinates)
    {
        glCopyTextureSubImage3D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z), 
            static_cast<gl::int32_t>(coordinates  .x), static_cast<gl::int32_t>(coordinates  .y), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y));
    }
    void compressed_texture_sub_image_1d            (gl::handle_t texture, gl::texture_compressed_format_e format, gl::uint32_t level, gl::length_t region, std::span<const gl::byte_t> data)
    {
        glCompressedTextureSubImage1D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level), 
            static_cast<gl::int32_t>(region.origin.x), 
            static_cast<gl::sizei_t>(region.extent.x), 
            gl::to_underlying       (format)         , 
            static_cast<gl::sizei_t>(data.size())    , data.data());
    }
    void compressed_texture_sub_image_2d            (gl::handle_t texture, gl::texture_compressed_format_e format, gl::uint32_t level, gl::area_t   region, std::span<const gl::byte_t> data)
    {
        glCompressedTextureSubImage2D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), 
            gl::to_underlying       (format)         , 
            static_cast<gl::sizei_t>(data.size())    , data.data());
    }
    void compressed_texture_sub_image_3d            (gl::handle_t texture, gl::texture_compressed_format_e format, gl::uint32_t level, gl::volume_t region, std::span<const gl::byte_t> data)
    {
        glCompressedTextureSubImage3D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), static_cast<gl::sizei_t>(region.extent.z), 
            gl::to_underlying       (format)         , 
            static_cast<gl::sizei_t>(data.size())    , data.data());
    }
    void texture_buffer                             (gl::handle_t texture, gl::handle_t buffer, gl::buffer_format_e format)
    {
        glTextureBuffer(gl::to_underlying(texture), gl::to_underlying(format), gl::to_underlying(buffer));
    }
    template<typename T>
    void texture_buffer_range                       (gl::handle_t texture, gl::handle_t buffer, gl::buffer_format_e format, gl::range range)
    {
        auto byterange = gl::convert_range<T>(range);
        glTextureBufferRange(gl::to_underlying(texture), gl::to_underlying(format), gl::to_underlying(buffer), byterange.offset, byterange.size);
    }
    void texture_parameter                          (gl::handle_t texture, glp::texture_parameter_v parameter)
    {
        auto texture_parameter_iv  = [](gl::handle_t texture, gl::texture_parameter_e parameter, gl::int32_t   value) -> gl::void_t
            {
                glTextureParameteri(gl::to_underlying(texture), gl::to_underlying(parameter), value);
            };
        auto texture_parameter_uiv = [](gl::handle_t texture, gl::texture_parameter_e parameter, gl::uint32_t  value) -> gl::void_t
            {
                glTextureParameteri(gl::to_underlying(texture), gl::to_underlying(parameter), static_cast<gl::int32_t>(value));
            };
        auto texture_parameter_fv  = [](gl::handle_t texture, gl::texture_parameter_e parameter, gl::float32_t value) -> gl::void_t
            {
                glTextureParameterfv(gl::to_underlying(texture), gl::to_underlying(parameter), &value);
            };
        auto get_swizzle_rgba      = [](gl::handle_t texture, gl::texture_parameter_e parameter, std::array<gl::texture_swizzle_e, 4u>& value)
            {
                return glTextureParameterIuiv(gl::to_underlying(texture), gl::to_underlying(gl::texture_parameter_e::swizzle_rgba), gl::to_underlying_ptr(value.data()));
            };

        auto overload = gl::overload
        {
            [=](glp::compare_function     _) { texture_parameter_uiv(texture, gl::texture_parameter_e::compare_function    , gl::to_underlying(_.value)); }, 
            [=](glp::compare_mode         _) { texture_parameter_uiv(texture, gl::texture_parameter_e::compare_mode        , gl::to_underlying(_.value)); },
            [=](glp::base_level           _) { texture_parameter_uiv(texture, gl::texture_parameter_e::base_level          ,                   _.value ); },
            [=](glp::maximum_level        _) { texture_parameter_uiv(texture, gl::texture_parameter_e::maximum_level       ,                   _.value ); },
            [=](glp::border_color         _)
            {
                auto overload = gl::overload
                {
                    [=](std::array<gl::int32_t  , 4u> __) { glTextureParameterIiv (gl::to_underlying(texture), gl::to_underlying(gl::texture_parameter_e::border_color), __.data()); }, 
                    [=](std::array<gl::uint32_t , 4u> __) { glTextureParameterIuiv(gl::to_underlying(texture), gl::to_underlying(gl::texture_parameter_e::border_color), __.data()); }, 
                    [=](std::array<gl::float32_t, 4u> __) { glTextureParameterfv  (gl::to_underlying(texture), gl::to_underlying(gl::texture_parameter_e::border_color), __.data()); }, 
                };

                std::visit(overload, _.value);
            }, 
            [=](glp::depth_stencil_mode   _) { texture_parameter_uiv(texture, gl::texture_parameter_e::depth_stencil_mode  , gl::to_underlying(_.value)); },
            [=](glp::magnification_filter _) { texture_parameter_uiv(texture, gl::texture_parameter_e::magnification_filter, gl::to_underlying(_.value)); },
            [=](glp::minification_filter  _) { texture_parameter_uiv(texture, gl::texture_parameter_e::minification_filter , gl::to_underlying(_.value)); },
            [=](glp::maximum_anisotropy   _) { texture_parameter_fv (texture, gl::texture_parameter_e::maximum_anisotropy  ,                   _.value ); },
            [=](glp::wrapping_s           _) { texture_parameter_uiv(texture, gl::texture_parameter_e::wrapping_s          , gl::to_underlying(_.value)); },
            [=](glp::wrapping_t           _) { texture_parameter_uiv(texture, gl::texture_parameter_e::wrapping_t          , gl::to_underlying(_.value)); },
            [=](glp::wrapping_r           _) { texture_parameter_uiv(texture, gl::texture_parameter_e::wrapping_r          , gl::to_underlying(_.value)); },
            [=](glp::swizzle_r            _) { texture_parameter_uiv(texture, gl::texture_parameter_e::swizzle_red         , gl::to_underlying(_.value)); },
            [=](glp::swizzle_g            _) { texture_parameter_uiv(texture, gl::texture_parameter_e::swizzle_green       , gl::to_underlying(_.value)); },
            [=](glp::swizzle_b            _) { texture_parameter_uiv(texture, gl::texture_parameter_e::swizzle_blue        , gl::to_underlying(_.value)); },
            [=](glp::swizzle_a            _) { texture_parameter_uiv(texture, gl::texture_parameter_e::swizzle_alpha       , gl::to_underlying(_.value)); },
            [=](glp::swizzle_rgba         _) { get_swizzle_rgba     (texture, gl::texture_parameter_e::swizzle_rgba        ,                   _.value ); },
            [=](glp::maximum_lod          _) { texture_parameter_fv (texture, gl::texture_parameter_e::maximum_lod         ,                   _.value ); },
            [=](glp::minimum_lod          _) { texture_parameter_fv (texture, gl::texture_parameter_e::minimum_lod         ,                   _.value ); },
            [=](glp::lod_bias             _) { texture_parameter_fv (texture, gl::texture_parameter_e::lod_bias            ,                   _.value ); },
        };

        std::visit(overload, parameter);
    }
    void generate_texture_mipmap                    (gl::handle_t texture)
    {
        glGenerateTextureMipmap(gl::to_underlying(texture));
    }
    template<gl::texture_target_e T, gl::texture_target_e U> requires (valid_texture_view_c<T, U>)
    void texture_view                               (gl::handle_t source, gl::handle_t destination, gl::texture_format_e format, gl::uint32_t minimumLevel, gl::uint32_t levels, gl::uint32_t minimumLayer, gl::uint32_t layers)
    {
        glTextureView(gl::to_underlying(destination), gl::to_underlying(U), gl::to_underlying(source), gl::to_underlying(format), minimumLevel, levels, minimumLayer, layers);
    }
    void texture_storage_1d                         (gl::handle_t texture, gl::texture_format_e format, const gl::vector1u& dimensions, gl::uint32_t levels)
    {
        glTextureStorage1D(
            gl::to_underlying       (texture)      , 
            static_cast<gl::sizei_t>(levels)       , 
            gl::to_underlying       (format)       , 
            static_cast<gl::sizei_t>(dimensions.x));
    }
    void texture_storage_2d                         (gl::handle_t texture, gl::texture_format_e format, const gl::vector2u& dimensions, gl::uint32_t levels)
    {
        glTextureStorage2D(
            gl::to_underlying       (texture)     , 
            static_cast<gl::sizei_t>(levels)      , 
            gl::to_underlying       (format)      , 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y));
    }
    void texture_storage_3d                         (gl::handle_t texture, gl::texture_format_e format, const gl::vector3u& dimensions, gl::uint32_t levels)
    {
        glTextureStorage3D(
            gl::to_underlying       (texture)     , 
            static_cast<gl::sizei_t>(levels)      , 
            gl::to_underlying       (format)      , 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), static_cast<gl::sizei_t>(dimensions.z));
    }
    void texture_storage_2d_multisample             (gl::handle_t texture, gl::texture_format_e format, const gl::vector2u& dimensions, gl::uint32_t samples, gl::bool_t fixed = gl::true_)
    {
        glTextureStorage2DMultisample(
            gl::to_underlying       (texture)     , 
            static_cast<gl::sizei_t>(samples)     , gl::to_underlying       (format)      , 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), 
            fixed);
    }
    void texture_storage_3d_multisample             (gl::handle_t texture, gl::texture_format_e format, const gl::vector3u& dimensions, gl::uint32_t samples, gl::bool_t fixed = gl::true_)
    {
        glTextureStorage3DMultisample(
            gl::to_underlying       (texture)     , 
            static_cast<gl::sizei_t>(samples)     , gl::to_underlying       (format)      , 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), static_cast<gl::sizei_t>(dimensions.z), 
            fixed);
    }
    void invalidate_texture_image                   (gl::handle_t texture, gl::uint32_t level)
    {
        glInvalidateTexImage(
            gl::to_underlying       (texture), 
            static_cast<gl::int32_t>(level) );
    }
    void invalidate_texture_sub_image               (gl::handle_t texture, gl::uint32_t level, gl::volume_t region)
    {
        glInvalidateTexSubImage(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z) , 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), static_cast<gl::sizei_t>(region.extent.z));
    }
    void clear_texture_image                        (gl::handle_t texture, gl::texture_base_format_e format, gl::texture_type_e type, gl::uint32_t level, std::span<const gl::byte_t> data)
    {
        glClearTexImage(
            gl::to_underlying(texture), static_cast<gl::int32_t>(level), 
            gl::to_underlying(format) , gl::to_underlying       (type) , data.data());
    }
    void clear_texture_sub_image                    (gl::handle_t texture, gl::texture_base_format_e format, gl::texture_type_e type, gl::uint32_t level, gl::volume_t region, std::span<const gl::byte_t> data)
    {
        glClearTexSubImage(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), static_cast<gl::sizei_t>(region.extent.z), 
            gl::to_underlying       (format)         , gl::to_underlying       (type)           , data.data());
    }



    //Chapter 9 - FrameBuffers and FrameBuffer Objects
    auto create_frame_buffer                        () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return glCreateFramebuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle)), handle;
    }
    auto create_frame_buffer                        (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return glCreateFramebuffers(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data())), handles;
    }
    void delete_frame_buffer                        (gl::handle_t frameBuffer)
    {
        glDeleteFramebuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&frameBuffer));
    }
    void delete_frame_buffers                       (std::span<const gl::handle_t> frameBuffers)
    {
        glDeleteFramebuffers(static_cast<gl::sizei_t>(frameBuffers.size()), gl::to_underlying_ptr(frameBuffers.data()));
    }
    void bind_frame_buffer                          (gl::handle_t frameBuffer, gl::frame_buffer_target_e target)
    {
        glBindFramebuffer(gl::to_underlying(target), gl::to_underlying(frameBuffer));
    }
    template<gl::frame_buffer_parameter_e P>
    void frame_buffer_parameter                     (gl::handle_t frameBuffer, gl::uint32_t value)
    {
        auto frame_buffer_parameter_i = [](gl::handle_t frameBuffer, gl::frame_buffer_parameter_e parameter, gl::uint32_t value) -> gl::void_t
            {
                glNamedFramebufferParameteri(gl::to_underlying(frameBuffer), gl::to_underlying(parameter), static_cast<gl::int32_t>(value));
            };

        if constexpr (
               P == gl::frame_buffer_parameter_e::default_width               
            || P == gl::frame_buffer_parameter_e::default_height
            || P == gl::frame_buffer_parameter_e::default_layers
            || P == gl::frame_buffer_parameter_e::default_samples
            || P == gl::frame_buffer_parameter_e::default_fixed_sample_locations
            || P == gl::frame_buffer_parameter_e::default_width                 ) frame_buffer_parameter_i(frameBuffer, P, value);
        else static_assert(gl::false_, "Invalid FrameBuffer Parameter!");
    }
    auto create_render_buffer                       () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return glCreateRenderbuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle)), handle;
    }
    auto create_render_buffers                      (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return glCreateRenderbuffers(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data())), handles;
    }
    void delete_render_buffer                       (gl::handle_t renderBuffer)
    {
        glDeleteRenderbuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&renderBuffer));
    }
    void delete_render_buffers                      (std::span<const gl::handle_t> renderBuffers)
    {
        glDeleteRenderbuffers(static_cast<gl::sizei_t>(renderBuffers.size()), gl::to_underlying_ptr(renderBuffers.data()));
    }
    void render_buffer_storage                      (gl::handle_t renderBuffer, gl::render_buffer_format_e format, const gl::vector2u& dimensions)
    {
        glNamedRenderbufferStorage(
            gl::to_underlying       (renderBuffer),
            gl::to_underlying       (format)      ,
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y));
    }
    void render_buffer_storage_multisample          (gl::handle_t renderBuffer, gl::render_buffer_format_e format, const gl::vector2u& dimensions, gl::uint32_t samples)
    {
        glNamedRenderbufferStorageMultisample(
            gl::to_underlying       (renderBuffer),
            static_cast<gl::sizei_t>(samples)     ,
            gl::to_underlying       (format)      ,
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y));
    }
    void frame_buffer_render_buffer                 (gl::handle_t frameBuffer, gl::handle_t renderBuffer, gl::frame_buffer_attachment_e attachment)
    {
        glNamedFramebufferRenderbuffer(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), gl::to_underlying(gl::render_buffer_target_e::render_buffer), gl::to_underlying(renderBuffer));
    }
    void frame_buffer_texture                       (gl::handle_t frameBuffer, gl::handle_t texture, gl::frame_buffer_attachment_e attachment, gl::uint32_t level)
    {
        glNamedFramebufferTexture(
            gl::to_underlying       (frameBuffer), gl::to_underlying(attachment), 
            gl::to_underlying       (texture)    , 
            static_cast<gl::int32_t>(level)     );
    }
    void frame_buffer_texture_layer                 (gl::handle_t frameBuffer, gl::handle_t texture, gl::frame_buffer_attachment_e attachment, gl::uint32_t level, gl::uint32_t layer)
    {
        glNamedFramebufferTextureLayer(
            gl::to_underlying       (frameBuffer), gl::to_underlying       (attachment), 
            gl::to_underlying       (texture)    , 
            static_cast<gl::int32_t>(level)      , static_cast<gl::int32_t>(layer)    );
    }
    void texture_barrier                            ()
    {
        glTextureBarrier();
    }
    auto check_frame_buffer_status                  (gl::handle_t frameBuffer) -> gl::frame_buffer_status_e
    {
        return static_cast<gl::frame_buffer_status_e>(glCheckNamedFramebufferStatus(gl::to_underlying(frameBuffer), gl::to_underlying(gl::frame_buffer_target_e::write)));
    }



    //Chapter 10 - Vertex Specification and Drawing Commands
    void patch_parameter                            (glp::patch_parameter_v parameter)
    {
        auto patch_parameter_i = [](gl::patch_parameter_e parameter, gl::int32_t   value)
            {
                glPatchParameteri(gl::to_underlying(parameter), value);
            };
        auto patch_parameter_f = [](gl::patch_parameter_e parameter, gl::float32_t value)
            {
                glPatchParameterfv(gl::to_underlying(parameter), &value);
            };

        auto overload = gl::overload
        {
            [=](glp::patch_vertices            _) { patch_parameter_i (                  gl::patch_parameter_e::patch_vertices            , _.value)       ; }, 
            [=](glp::patch_default_outer_level _) { glPatchParameterfv(gl::to_underlying(gl::patch_parameter_e::patch_default_outer_level), _.value.data()); }, 
            [=](glp::patch_default_inner_level _) { glPatchParameterfv(gl::to_underlying(gl::patch_parameter_e::patch_default_inner_level), _.value.data()); }, 
        };

        std::visit(overload, parameter);
    }
    template<typename T, gl::uint32_t N, gl::bool_t NORM = gl::false_>
    void vertex_attribute                           (gl::index_t index, const gl::vector_t<T, N>& value)
    {
        auto maximumAttributes = gl::get_value<gl::data_e::maximum_vertex_attributes>();
        if (gl::compare<std::greater>(index, maximumAttributes)) throw std::invalid_argument{ "Index exceeds the maximum amount of vertex attributes!" };
        
        if   constexpr (std::is_same_v<T, gl::uint8_t  >)
        {
            if constexpr (N == 4 && NORM == gl::true_ ) glVertexAttrib4Nub(index, value.x, value.y, value.z, value.w);
        }
        if   constexpr (std::is_same_v<T, gl::int16_t  >)
        {
            if constexpr (N == 1 && NORM == gl::false_) glVertexAttrib1s  (index, value.x                           );
            if constexpr (N == 2 && NORM == gl::false_) glVertexAttrib2s  (index, value.x, value.y                  );
            if constexpr (N == 3 && NORM == gl::false_) glVertexAttrib3s  (index, value.x, value.y, value.z         );
            if constexpr (N == 4 && NORM == gl::false_) glVertexAttrib4s  (index, value.x, value.y, value.z, value.w);
        }
        if   constexpr (std::is_same_v<T, gl::int32_t  >)
        {
            if constexpr (N == 1 && NORM == gl::false_) glVertexAttribI1i (index, value.x                           );
            if constexpr (N == 2 && NORM == gl::false_) glVertexAttribI2i (index, value.x, value.y                  );
            if constexpr (N == 3 && NORM == gl::false_) glVertexAttribI3i (index, value.x, value.y, value.z         );
            if constexpr (N == 4 && NORM == gl::false_) glVertexAttribI4i (index, value.x, value.y, value.z, value.w);
        }
        if   constexpr (std::is_same_v<T, gl::uint32_t >)
        {
            if constexpr (N == 1 && NORM == gl::false_) glVertexAttribI1ui(index, value.x                           );
            if constexpr (N == 2 && NORM == gl::false_) glVertexAttribI2ui(index, value.x, value.y                  );
            if constexpr (N == 3 && NORM == gl::false_) glVertexAttribI3ui(index, value.x, value.y, value.z         );
            if constexpr (N == 4 && NORM == gl::false_) glVertexAttribI4ui(index, value.x, value.y, value.z, value.w);
        }
        if   constexpr (std::is_same_v<T, gl::float32_t>)
        {
            if constexpr (N == 1 && NORM == gl::false_) glVertexAttrib1f  (index, value.x                           );
            if constexpr (N == 2 && NORM == gl::false_) glVertexAttrib2f  (index, value.x, value.y                  );
            if constexpr (N == 3 && NORM == gl::false_) glVertexAttrib3f  (index, value.x, value.y, value.z         );
            if constexpr (N == 4 && NORM == gl::false_) glVertexAttrib4f  (index, value.x, value.y, value.z, value.w);
        }
        if   constexpr (std::is_same_v<T, gl::float64_t>)
        {
            if constexpr (N == 1 && NORM == gl::false_) glVertexAttribL1d (index, value.x                           );
            if constexpr (N == 2 && NORM == gl::false_) glVertexAttribL2d (index, value.x, value.y                  );
            if constexpr (N == 3 && NORM == gl::false_) glVertexAttribL3d (index, value.x, value.y, value.z         );
            if constexpr (N == 4 && NORM == gl::false_) glVertexAttribL4d (index, value.x, value.y, value.z, value.w);
        }
        else static_assert(gl::false_, "The given input does not match a valid vertex attribute function!");
    }
    auto create_vertex_array                        () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return glCreateVertexArrays(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle)), handle;
    }
    auto create_vertex_arrays                       (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return glCreateVertexArrays(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data())), handles;
    }
    void delete_vertex_array                        (gl::handle_t vertexArray)
    {
        glDeleteVertexArrays(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&vertexArray));
    }
    void delete_vertex_arrays                       (std::span<const gl::handle_t> vertexArrays)
    {
        glDeleteVertexArrays(static_cast<gl::sizei_t>(vertexArrays.size()), gl::to_underlying_ptr(vertexArrays.data()));
    }
    void bind_vertex_array                          (gl::handle_t vertexArray)
    {
        glBindVertexArray(gl::to_underlying(vertexArray));
    }
    void vertex_array_element_buffer                (gl::handle_t vertexArray, gl::handle_t elementBuffer)
    {
        glVertexArrayElementBuffer(gl::to_underlying(vertexArray), gl::to_underlying(elementBuffer));
    }
    void vertex_array_attribute_format              (gl::handle_t vertexArray, gl::index_t attribute, gl::offset_t offset, gl::vertex_array_attribute_type_e type, gl::count_t count, gl::bool_t normalized = gl::false_)
    {
        auto vertex_array_attribute_format_i = [](gl::handle_t vertexArray, gl::index_t attribute, gl::vertex_array_attribute_type_e type, gl::count_t count, gl::offset_t offset) -> gl::void_t
            {
                glVertexArrayAttribIFormat(gl::to_underlying(vertexArray), attribute, static_cast<gl::int32_t>(count), gl::to_underlying(type), static_cast<gl::uint32_t>(offset));
            };
        auto vertex_array_attribute_format_f = [](gl::handle_t vertexArray, gl::index_t attribute, gl::vertex_array_attribute_type_e type, gl::count_t count, gl::offset_t offset, gl::bool_t normalized)
            {
                glVertexArrayAttribFormat(gl::to_underlying(vertexArray), attribute, static_cast<gl::int32_t>(count), gl::to_underlying(type), normalized, static_cast<gl::uint32_t>(offset));
            };
        auto vertex_array_attribute_format_l = [](gl::handle_t vertexArray, gl::index_t attribute, gl::vertex_array_attribute_type_e type, gl::count_t count, gl::offset_t offset)
            {
                glVertexArrayAttribLFormat(gl::to_underlying(vertexArray), attribute, static_cast<gl::int32_t>(count), gl::to_underlying(type), static_cast<gl::uint32_t>(offset));
            };

        auto maximumVertexAttributes = gl::get_value<gl::data_e::maximum_vertex_attributes>();
        if (gl::compare<std::greater>(attribute, maximumVertexAttributes)) throw std::invalid_argument{ "Index exceeds the maximum amount of vertex attributes!" };
        
        switch (type)
        {
            case gl::vertex_array_attribute_type_e::byte                                  : 
            case gl::vertex_array_attribute_type_e::unsigned_byte                         : 
            case gl::vertex_array_attribute_type_e::short_                                : 
            case gl::vertex_array_attribute_type_e::unsigned_short                        : 
            case gl::vertex_array_attribute_type_e::integer                               : 
            case gl::vertex_array_attribute_type_e::unsigned_integer                      : 
            case gl::vertex_array_attribute_type_e::int_2_10_10_10_rev                    : 
            case gl::vertex_array_attribute_type_e::unsigned_integer_2_10_10_10_rev       : 
            case gl::vertex_array_attribute_type_e::unsigned_integer_10_11_11_11_float_rev:
            {
                vertex_array_attribute_format_i(vertexArray, attribute, type, count, offset);
                break;
            }

            case gl::vertex_array_attribute_type_e::float_                               : 
            case gl::vertex_array_attribute_type_e::half_float                           : 
            case gl::vertex_array_attribute_type_e::fixed                                : 
            {
                vertex_array_attribute_format_f(vertexArray, attribute, type, count, offset, normalized);
                break;
            }

            case gl::vertex_array_attribute_type_e::double_                              : 
            {
                vertex_array_attribute_format_l(vertexArray, attribute, type, count, offset);
                break;
            }
        }
    }
    void vertex_array_vertex_buffer                 (gl::handle_t vertexArray, gl::handle_t buffer, gl::binding_t binding, gl::size_t stride, gl::index_t index)
    {
        glVertexArrayVertexBuffer(gl::to_underlying(vertexArray), gl::to_underlying(binding), gl::to_underlying(buffer), static_cast<gl::offset_t>(index), static_cast<gl::sizei_t>(stride));
    }
    void vertex_array_vertex_buffers                (gl::handle_t vertexArray, std::span<const gl::handle_t> buffers, std::span<const gl::byterange> strides, gl::range range)
    {
        gl::todo();
        //glVertexArrayVertexBuffers(gl::to_underlying(vertexArray), range.index, range.count, gl::to_underlying_ptr(buffers.data()), );
    }
    void vertex_array_attribute_binding             (gl::handle_t vertexArray, gl::index_t attribute, gl::binding_t binding)
    {
        glVertexArrayAttribBinding(gl::to_underlying(vertexArray), attribute, gl::to_underlying(binding));
    }
    void enable_vertex_array_attribute              (gl::handle_t vertexArray, gl::index_t index)
    {
        glEnableVertexArrayAttrib(gl::to_underlying(vertexArray), index);
    }
    void disable_vertex_array_attribute             (gl::handle_t vertexArray, gl::index_t index)
    {
        glDisableVertexArrayAttrib(gl::to_underlying(vertexArray), index);
    }
    void vertex_array_binding_divisor               (gl::handle_t vertexArray, gl::binding_t binding, gl::uint32_t divisor)
    {
        glVertexArrayBindingDivisor(gl::to_underlying(vertexArray), gl::to_underlying(binding), divisor);
    }
    void primitive_restart_index                    (gl::index_t index)
    {
        glPrimitiveRestartIndex(index);
    }
    void draw_arrays                                (gl::draw_mode_e mode, gl::range range)
    {
        glDrawArrays(gl::to_underlying(mode), static_cast<gl::int32_t>(range.index), static_cast<gl::sizei_t>(range.count));
    }
    void draw_arrays_instanced                      (gl::draw_mode_e mode, gl::range range, gl::count_t instances)
    {
        glDrawArraysInstanced(gl::to_underlying(mode), static_cast<gl::int32_t>(range.index), static_cast<gl::sizei_t>(range.count), static_cast<gl::sizei_t>(instances));
    }
    void draw_arrays_instanced_base_instance        (gl::draw_mode_e mode, gl::range range, gl::count_t instances, gl::index_t base)
    {
        glDrawArraysInstancedBaseInstance(gl::to_underlying(mode), static_cast<gl::int32_t>(range.index), static_cast<gl::sizei_t>(range.count), static_cast<gl::sizei_t>(instances), base);
    }
    void draw_elements                              (gl::draw_mode_e mode, gl::draw_type_e type, gl::count_t count)
    {
        glDrawElements(gl::to_underlying(mode), static_cast<gl::sizei_t>(count), gl::to_underlying(type), nullptr);
    }
    void draw_elements_instanced                    (gl::draw_mode_e mode, gl::draw_type_e type, gl::count_t count, gl::count_t instances)
    {
        glDrawElementsInstanced(gl::to_underlying(mode), static_cast<gl::sizei_t>(count), gl::to_underlying(type), nullptr, static_cast<gl::sizei_t>(instances));
    }
    void draw_elements_instanced_base_instance      (gl::draw_mode_e mode, gl::draw_type_e type, gl::count_t count, gl::count_t instances, gl::index_t base)
    {
        glDrawElementsInstancedBaseInstance(gl::to_underlying(mode), static_cast<gl::sizei_t>(count), gl::to_underlying(type), nullptr, static_cast<gl::sizei_t>(instances), base);
    }
    void begin_conditional_render                   (gl::handle_t query, gl::query_mode_e mode)
    {
        glBeginConditionalRender(gl::to_underlying(query), gl::to_underlying(mode));
    }
    void end_conditional_render                     ()
    {
        glEndConditionalRender();
    }



    //Chapter 11 - Programmable Vertex Processing
    void validate_program                           (gl::handle_t program)
    {
        glValidateProgram(gl::to_underlying(program));
    }
    void validate_program_pipeline                  (gl::handle_t pipeline)
    {
        glValidateProgramPipeline(gl::to_underlying(pipeline));
    }



    //Chapter 13 - Fixed-Function Vertex Post-Processing
    void provoking_vertex                           (gl::provoking_vertex_mode_e mode)
    {
        glProvokingVertex(gl::to_underlying(mode));
    }
    void clip_control                               (gl::clipping_origin_e origin, gl::clipping_depth_mode_e mode)
    {
        glClipControl(gl::to_underlying(origin), gl::to_underlying(mode));
    }
    void depth_range_array_value                    (gl::index_t index, std::span<const gl::vector2d> ranges)
    {
        glDepthRangeArrayv(index, static_cast<gl::sizei_t>(ranges.size()), glm::value_ptr(*ranges.data()));
    }
    void depth_range_indexed                        (gl::index_t index, const gl::vector2d& range)
    {
        glDepthRangeIndexed(index, range.x, range.y);
    }
    void depth_range                                (const gl::vector2f& range)
    {
        glDepthRangef(range.x, range.y);
    }
    void viewport_array_value                       (gl::index_t index, std::span<const gl::vector2f> ranges)
    {
        glViewportArrayv(index, static_cast<gl::sizei_t>(ranges.size()), glm::value_ptr(*ranges.data()));
    }
    void viewport_indexed                           (gl::index_t index, const gl::region<gl::float32_t, 2u> region)
    {
        glViewportIndexedf(index, region.origin.x, region.origin.y, region.extent.x, region.extent.y);
    }
    void viewport                                   (gl::area_t region)
    {
        glViewport(
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y));
    }



    //Chapter 14 - Fixed-Function Primitive Assembly and Rasterization
    auto get_multisample_value                      (gl::index_t index) -> gl::vector2f
    {
        auto value = gl::vector2f{};
        return glGetMultisamplefv(gl::to_underlying(gl::multisample_parameter_e::sample_position), index, glm::value_ptr(value)), value;
    }
    void minimum_sample_shading                     (gl::float32_t value)
    {
        glMinSampleShading(value);
    }
    void point_size                                 (gl::float32_t size)
    {
        glPointSize(size);
    }
    void point_parameter                            (glp::point_parameter_v parameter)
    {
        auto point_parameter_i = [](gl::point_parameter_e parameter, gl::int32_t value) -> gl::void_t
            {
                glPointParameteri(gl::to_underlying(parameter), value);
            };
        auto point_parameter_f = [](gl::point_parameter_e parameter, gl::float32_t value) -> gl::void_t
            {
                glPointParameterf(gl::to_underlying(parameter), value);
            };

        auto overload = gl::overload
        {
            [=](glp::fade_threshold_size      _) { point_parameter_f(gl::point_parameter_e::fade_threshold_size     ,                   _.value ); }, 
            [=](glp::sprite_coordinate_origin _) { point_parameter_i(gl::point_parameter_e::sprite_coordinate_origin, gl::to_underlying(_.value)); }, 
        };

        std::visit(overload, parameter);
    }
    void line_width                                 (gl::float32_t value)
    {
        glLineWidth(value);
    }
    void front_face                                 (gl::orientation_e orientation)
    {
        glFrontFace(gl::to_underlying(orientation));
    }
    void cull_face                                  (gl::culling_facet_e face)
    {
        glCullFace(gl::to_underlying(face));
    }
    void polygon_mode                               (gl::polygon_mode_e mode)
    {
        glPolygonMode(gl::to_underlying(gl::polygon_face_e::front_back), gl::to_underlying(mode));
    }
    void polygon_offset_clamp                       (gl::float32_t factor, gl::float32_t units, gl::float32_t clamp)
    {
        glPolygonOffsetClamp(factor, units, clamp);
    }
    void scissor_array                              (gl::index_t index, std::span<const gl::uint32_t, 4u> values)
    {
        glScissorArrayv(
            index                                            , 
            static_cast<gl::sizei_t>         (values.size()) , 
            std::bit_cast<const gl::int32_t*>(values.data())); 
    }
    void scissor_indexed                            (gl::index_t index, gl::area_t region)
    {
        glScissorIndexed(
            index                                                                                , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y) ,  
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y));
    }
    void scissor                                    (gl::area_t region)
    {
        glScissor(
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y) , 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y));
    }
    void sample_coverage                            (gl::float32_t value, gl::bool_t invert)
    {
        glSampleCoverage(value, invert);
    }
    void sample_mask_index                          (gl::uint32_t mask, gl::uint32_t value)
    {
        glSampleMaski(mask, value);
    }



    //Chapter 17 - Writing Fragments and Samples to the Framebuffer
    void stencil_function                           (gl::stencil_function_e function, gl::uint32_t reference, gl::uint32_t mask)
    {
        glStencilFunc(gl::to_underlying(function), static_cast<gl::int32_t>(reference), mask);
    }
    void stencil_function_separate                  (gl::stencil_face_e face, gl::stencil_function_e function, gl::uint32_t reference, gl::uint32_t mask)
    {
        glStencilFuncSeparate(gl::to_underlying(face), gl::to_underlying(function), static_cast<gl::int32_t>(reference), mask);
    }
    void stencil_operation                          (gl::stencil_action_e stencil, gl::stencil_action_e depth, gl::stencil_action_e depthStencil)
    {
        glStencilOp(gl::to_underlying(stencil), gl::to_underlying(depth), gl::to_underlying(depthStencil));
    }
    void stencil_operation_separate                 (gl::stencil_face_e face, gl::stencil_action_e stencil, gl::stencil_action_e depth, gl::stencil_action_e depthStencil)
    {
        glStencilOpSeparate(gl::to_underlying(face), gl::to_underlying(stencil), gl::to_underlying(depth), gl::to_underlying(depthStencil));
    }
    void depth_function                             (gl::depth_function_e function)
    {
        glDepthFunc(gl::to_underlying(function));
    }
    void blend_equation                             (gl::blending_equation_e equation)
    {
        glBlendEquation(gl::to_underlying(equation));
    }
    void blend_equation_indexed                     (gl::blending_equation_e equation, gl::index_t index)
    {
        glBlendEquationi(index, gl::to_underlying(equation));
    }
    void blend_equation_separate                    (gl::blending_equation_e equationRGB, gl::blending_equation_e equationAlpha)
    {
        glBlendEquationSeparate(gl::to_underlying(equationRGB), gl::to_underlying(equationAlpha));
    }
    void blend_equation_separate_indexed            (gl::blending_equation_e color, gl::blending_equation_e alpha, gl::index_t index)
    {
        glBlendEquationSeparatei(index, gl::to_underlying(color), gl::to_underlying(alpha));
    }
    void blend_function                             (gl::blending_factor_e source, gl::blending_factor_e destination)
    {
        glBlendFunc(gl::to_underlying(source), gl::to_underlying(destination));
    }
    void blend_function_indexed                     (gl::blending_factor_e sourceColor, gl::blending_factor_e sourceAlpha, gl::blending_factor_e destinationColor, gl::blending_factor_e destinationAlpha, gl::index_t index)
    {
        glBlendFuncSeparatei(index, gl::to_underlying(sourceColor), gl::to_underlying(destinationColor), gl::to_underlying(sourceAlpha), gl::to_underlying(destinationAlpha));
    }
    void blend_function_separate                    (gl::blending_factor_e sourceColor, gl::blending_factor_e sourceAlpha, gl::blending_factor_e destinationColor, gl::blending_factor_e destinationAlpha)
    {
        glBlendFuncSeparate(gl::to_underlying(sourceColor), gl::to_underlying(destinationColor), gl::to_underlying(sourceAlpha), gl::to_underlying(destinationAlpha));
    }
    void blend_function_separate_indexed            (gl::blending_factor_e sourceColor, gl::blending_factor_e sourceAlpha, gl::blending_factor_e destinationColor, gl::blending_factor_e destinationAlpha, gl::index_t index)
    {
        glBlendFuncSeparatei(index, gl::to_underlying(sourceColor), gl::to_underlying(destinationColor), gl::to_underlying(sourceAlpha), gl::to_underlying(destinationAlpha));
    }
    void blend_color                                (const gl::vector4f& color)
    {
        glBlendColor(color.r, color.g, color.b, color.a);
    }
    void logical_pixel_operation                    (gl::logical_pixel_operation_e operation)
    {
        glLogicOp(gl::to_underlying(operation));
    }
    void frame_buffer_draw_buffer                   (gl::handle_t frameBuffer, gl::frame_buffer_source_e source)
    {
        glNamedFramebufferDrawBuffer(gl::to_underlying(frameBuffer), gl::to_underlying(source));
    }
    void frame_buffer_draw_buffers                  (gl::handle_t frameBuffer, std::span<const gl::frame_buffer_source_e> sources)
    {
        glNamedFramebufferDrawBuffers(gl::to_underlying(frameBuffer), static_cast<gl::sizei_t>(sources.size()), gl::to_underlying_ptr(sources.data()));
    }
    void color_mask                                 (const gl::vector4b& mask)
    {
        glColorMask(mask.r, mask.g, mask.b, mask.a);
    }
    void color_mask_index                           (gl::handle_t buffer, const gl::vector4b& mask)
    {
        glColorMaski(gl::to_underlying(buffer), mask.r, mask.g, mask.b, mask.a);
    }
    void depth_mask                                 (gl::bool_t flag)
    {
        glDepthMask(flag);
    }
    void stencil_mask                               (gl::uint32_t mask)
    {
        glStencilMask(mask);
    }
    void stencil_mask_separate                      (gl::stencil_face_e face, gl::uint32_t mask)
    {
        glStencilMaskSeparate(gl::to_underlying(face), mask);
    }
    void clear                                      (gl::buffer_mask_e mask)
    {
        glClear(gl::to_underlying(mask));
    }
    void clear_color                                (const gl::vector4f& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
    void clear_depth                                (gl::float32_t depth)
    {
        glClearDepthf(depth);
    }
    void clear_stencil                              (gl::index_t index)
    {
        glClearStencil(static_cast<gl::int32_t>(index));
    }
    void clear_frame_buffer_value                   (gl::handle_t frameBuffer, glp::clear_v parameter)
    {
        auto clear_frame_buffer_iv  = [](gl::handle_t frameBuffer, gl::frame_buffer_attachment_e attachment, gl::index_t index, const gl::int32_t* value)
            {
                glClearNamedFramebufferiv(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), value);
            };
        auto clear_frame_buffer_uiv = [](gl::handle_t frameBuffer, gl::frame_buffer_attachment_e attachment, gl::index_t index, const gl::uint32_t* value)
            {
                glClearNamedFramebufferuiv(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), value);
            };
        auto clear_frame_buffer_fv  = [](gl::handle_t frameBuffer, gl::frame_buffer_attachment_e attachment, gl::index_t index, const gl::float32_t* value)
            {
                glClearNamedFramebufferfv(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), value);
            };
        auto clear_frame_buffer_fi  = [](gl::handle_t frameBuffer, gl::frame_buffer_attachment_e attachment, gl::index_t index, gl::float32_t depth, gl::int32_t stencil)
            {
                glClearNamedFramebufferfi(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), depth, stencil);
            };

        auto overload = gl::overload
        {
            [=](glp::color_index  _)
            {
                auto overload = gl::overload
                {
                    [=](gl::vector4i __) { clear_frame_buffer_iv (frameBuffer, gl::frame_buffer_attachment_e::color0, _.index, glm::value_ptr(__)); }, 
                    [=](gl::vector4u __) { clear_frame_buffer_uiv(frameBuffer, gl::frame_buffer_attachment_e::color0, _.index, glm::value_ptr(__)); }, 
                    [=](gl::vector4f __) { clear_frame_buffer_fv (frameBuffer, gl::frame_buffer_attachment_e::color0, _.index, glm::value_ptr(__)); }, 
                };

                std::visit(overload, _.color);
            }, 
            [=](glp::depth        _)
            {
                auto overload = gl::overload
                {
                    [=](gl::int32_t   __) { clear_frame_buffer_iv (frameBuffer, gl::frame_buffer_attachment_e::depth, gl::uint32_t{ 0u }, &__); }, 
                    [=](gl::uint32_t  __) { clear_frame_buffer_uiv(frameBuffer, gl::frame_buffer_attachment_e::depth, gl::uint32_t{ 0u }, &__); }, 
                    [=](gl::float32_t __) { clear_frame_buffer_fv (frameBuffer, gl::frame_buffer_attachment_e::depth, gl::uint32_t{ 0u }, &__); }, 
                };

                std::visit(overload, _.value);
            }, 
            [=](glp::stencil      _)
            {
                auto overload = gl::overload
                {
                    [=](gl::int32_t   __) { clear_frame_buffer_iv (frameBuffer, gl::frame_buffer_attachment_e::stencil, gl::uint32_t{ 0u }, &__); }, 
                    [=](gl::uint32_t  __) { clear_frame_buffer_uiv(frameBuffer, gl::frame_buffer_attachment_e::stencil, gl::uint32_t{ 0u }, &__); }, 
                    [=](gl::float32_t __) { clear_frame_buffer_fv (frameBuffer, gl::frame_buffer_attachment_e::stencil, gl::uint32_t{ 0u }, &__); }, 
                };

                std::visit(overload, _.value);
            },
            [=](glp::depthstencil _)
            {
                clear_frame_buffer_fi(frameBuffer, gl::frame_buffer_attachment_e::depth_stencil, gl::uint32_t{ 0u }, _.depth, _.stencil);
            }, 
        };

        std::visit(overload, parameter);
    }
    void invalidate_frame_buffer_data               (gl::handle_t frameBuffer, std::span<const gl::frame_buffer_attachment_e> attachments)
    {
        glInvalidateNamedFramebufferData(
            gl::to_underlying       (frameBuffer)        , 
            static_cast<gl::sizei_t>(attachments.size()) , 
            gl::to_underlying_ptr   (attachments.data()));
    }
    void invalidate_frame_buffer_sub_data           (gl::handle_t frameBuffer, std::span<const gl::frame_buffer_attachment_e> attachments, gl::area_t region)
    {
        glInvalidateNamedFramebufferSubData(
            gl::to_underlying       (frameBuffer)       , 
            static_cast<gl::sizei_t>(attachments.size()), gl::to_underlying_ptr   (attachments.data()), 
            static_cast<gl::int32_t>(region.origin.x)   , static_cast<gl::int32_t>(region.origin.y)   , 
            static_cast<gl::sizei_t>(region.extent.x)   , static_cast<gl::sizei_t>(region.extent.y)  );
    }



    //Chapter 18 - Reading and Copying Pixels
    void frame_buffer_read_buffer                   (gl::handle_t frameBuffer, gl::frame_buffer_source_e source)
    {
        glNamedFramebufferReadBuffer(gl::to_underlying(frameBuffer), gl::to_underlying(source));
    }
    template<gl::pixel_data_format_e F, gl::pixel_data_type_e T>
    void read_pixels                                (gl::area_t region)
    {
        gl::todo();

        //const auto& map_format_size = []<gl::pixel_data_format_e F>() constexpr
        //    {
        //        if (F == gl::pixel_data_format_e::R             ) return 0;
        //        if (F == gl::pixel_data_format_e::G             ) return 0;
        //        if (F == gl::pixel_data_format_e::B             ) return 0;
        //        if (F == gl::pixel_data_format_e::RGB           ) return 0;
        //        if (F == gl::pixel_data_format_e::RGBA          ) return 0;
        //        if (F == gl::pixel_data_format_e::BGR           ) return 0;
        //        if (F == gl::pixel_data_format_e::BGRA          ) return 0;
        //        if (F == gl::pixel_data_format_e::StencilIndex  ) return 0;
        //        if (F == gl::pixel_data_format_e::DepthComponent) return 0;
        //        if (F == gl::pixel_data_format_e::DepthStencil  ) return 0;
        //    };

        //const auto& binding = gl::get_value<gl::data_e::PixelPackBufferBinding>();

        //if (binding == gl::NullObject)
        //{
        //    const auto& size = region.extent.x * region.extent.y;
        //    std::vector<T> value(size);

        //    glReadnPixels(
        //        static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), 
        //        static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), 
        //        gl::to_underlying       (format)         , gl::to_underlying       (type)           , 
        //        static_cast<gl::sizei_t>(value.size())   , 
        //        value.data());

        //    return value;
        //}
    }
    void clamp_color                                (gl::bool_t value)
    {
        glClampColor(gl::to_underlying(gl::clamp_color_e::read), value);
    }
    void blit_frame_buffer                          (gl::handle_t source, gl::handle_t destination, gl::buffer_mask_e mask, gl::frame_buffer_filter_e filter, gl::area_t sourceRegion, gl::area_t destinationRegion)
    {
        glBlitNamedFramebuffer(
            gl::to_underlying       (source)                    ,
            gl::to_underlying       (destination)               ,
            static_cast<gl::int32_t>(sourceRegion     .origin.x), static_cast<gl::int32_t>(sourceRegion     .origin.y), static_cast<gl::int32_t>(sourceRegion     .extent.x), static_cast<gl::int32_t>(sourceRegion     .extent.y),
            static_cast<gl::int32_t>(destinationRegion.origin.x), static_cast<gl::int32_t>(destinationRegion.origin.y), static_cast<gl::int32_t>(destinationRegion.extent.x), static_cast<gl::int32_t>(destinationRegion.extent.y),
            gl::to_underlying       (mask)                      , gl::to_underlying       (filter)                   );
    }
    void copy_image_sub_data                        (gl::handle_t source, gl::handle_t destination, gl::texture_target_e sourceTarget, gl::texture_target_e destinationTarget, gl::hypervolume_t sourceRegion, gl::hypervolume_t destinationRegion)
    {
        glCopyImageSubData(
            gl::to_underlying       (source                    ), gl::to_underlying       (sourceTarget              ), static_cast<gl::int32_t>(sourceRegion     .extent.w), 
            static_cast<gl::int32_t>(sourceRegion     .origin.x), static_cast<gl::int32_t>(sourceRegion     .origin.y), static_cast<gl::int32_t>(sourceRegion     .origin.z), 
            gl::to_underlying       (destination               ), gl::to_underlying       (destinationTarget         ), static_cast<gl::int32_t>(destinationRegion.extent.w), 
            static_cast<gl::int32_t>(destinationRegion.origin.x), static_cast<gl::int32_t>(destinationRegion.origin.y), static_cast<gl::int32_t>(destinationRegion.origin.z), 
            static_cast<gl::sizei_t>(sourceRegion     .extent.x), static_cast<gl::sizei_t>(sourceRegion     .extent.y), static_cast<gl::sizei_t>(sourceRegion     .extent.z));
    }



    //Chapter 19 - Compute Shaders
    void dispatch_compute                           (glp::dispatch_v parameter)
    {
        auto overload = gl::overload
        {
            [=](gl::vector3u _) { glDispatchCompute        (_.x, _.y, _.z); }, 
            [=](gl::offset_t _) { glDispatchComputeIndirect(_            ); }, 
        };
        
        std::visit(overload, parameter);
    }



    //Chapter 20 - Debug Output
    void debug_message_callback                     (gl::debug_callback_t callback, const gl::pointer_t parameter = nullptr)
    {
        glDebugMessageCallback(callback, parameter);
    }
    void debug_message_control                      (gl::debug_source_e source, gl::debug_type_e type, gl::debug_severity_e severity, gl::bool_t state)
    {
        glDebugMessageControl(gl::to_underlying(source), gl::to_underlying(type), gl::to_underlying(severity), gl::sizei_t{ 0 }, nullptr, state);
    }
    void debug_message_insert                       (gl::handle_t identifier, gl::debug_type_e type, gl::debug_severity_e severity, const std::string& message)
    {
        glDebugMessageInsert(
            gl::to_underlying(gl::debug_source_e::application), 
            gl::to_underlying(type)                           , gl::to_underlying(identifier), gl::to_underlying(severity),
            static_cast<gl::sizei_t>(message.length())        , message.data()              );
    }
    void push_debug_group                           (gl::handle_t identifier, const std::string& message)
    {
        const auto* cstr = message.c_str();
        glPushDebugGroup(gl::to_underlying(gl::debug_source_e::application), gl::to_underlying(identifier), gl::sizei_t{ -1 }, cstr);
    }
    void pop_debug_group                            ()
    {
        glPopDebugGroup();
    }
    void object_label                               (gl::handle_t identifier, gl::object_type_e type, const std::string& label)
    {
        const auto* cstr = label.c_str();
        glObjectLabel(gl::to_underlying(type), gl::to_underlying(identifier), gl::sizei_t{ -1 }, cstr);
    }
    void object_pointer_label                       (gl::sync_t sync, const std::string& identifier)
    {
        const auto* cstr = identifier.c_str();
        glObjectPtrLabel(sync, gl::sizei_t{ -1 }, cstr);
    }
    

    
    //Chapter 21 - Special Functions
    void hint                                       (gl::hint_target_e target, gl::hint_mode_e mode)
    {
        glHint(gl::to_underlying(target), gl::to_underlying(mode));
    }


    


#ifdef GL_EXTENDED
    namespace ext
    {

    }
#endif
#ifdef GL_LEGACY
    namespace lgc
    {
        auto get_error() -> gl::error_flag_e
        {
            return static_cast<gl::error_flag_e>(glGetError());
        }
        auto is_sync(gl::sync_t sync) -> gl::bool_t
        {
            return static_cast<gl::bool_t>(glIsSync(sync));
        }
    }
#endif
}

#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/Mesh/Mesh.hpp"

namespace fox::gfx
{
    struct Geometry
    {
    public:
        static void init()
        {
            Plane ::init();
            Cube  ::init();
            Sphere::init();
        }

        struct Plane
        {
        public:
            friend Geometry;

            static std::shared_ptr<gfx::Mesh> mesh()
            {
                return s_mesh;
            }

            static inline const std::array<fox::float32_t, 12> positions
            {
                 1.0f,  1.0f,  0.0f,
                -1.0f,  1.0f,  0.0f,
                -1.0f, -1.0f,  0.0f,
                 1.0f, -1.0f,  0.0f,
            };
            static inline const std::array<fox::float32_t, 12> normals
            {
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
            };
            static inline const std::array<fox::float32_t, 12> tangents
            {
                1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
            };
            static inline const std::array<fox::float32_t, 8>  coordinates
            {
                1.0f, 1.0f,
                0.0f, 1.0f,
                0.0f, 0.0f,
                1.0f, 0.0f,
            };
            static inline const std::array<fox::uint32_t, 6>   indices
            {
                0, 1, 2,
                0, 2, 3,
            };

        private:
            static void init();

            static inline std::shared_ptr<gfx::Mesh> s_mesh{};
        };
        struct Cube
        {
        public:
            friend Geometry;

            static const std::shared_ptr<gfx::Mesh> mesh()
            {
                return s_mesh;
            }

            //Right, Left, Top, Bottom, Front, Back
            static inline const std::array<fox::float32_t, 72> positions
            {
                 0.5f,  0.5f, -0.5f,  
                 0.5f,  0.5f,  0.5f,  
                 0.5f, -0.5f,  0.5f,  
                 0.5f, -0.5f, -0.5f,  
                                     
                -0.5f,  0.5f,  0.5f, 
                -0.5f,  0.5f, -0.5f, 
                -0.5f, -0.5f, -0.5f, 
                -0.5f, -0.5f,  0.5f, 
                                     
                 0.5f,  0.5f, -0.5f, 
                -0.5f,  0.5f, -0.5f, 
                -0.5f,  0.5f,  0.5f, 
                 0.5f,  0.5f,  0.5f, 
                                     
                 0.5f, -0.5f,  0.5f, 
                -0.5f, -0.5f,  0.5f, 
                -0.5f, -0.5f, -0.5f, 
                 0.5f, -0.5f, -0.5f, 
                                     
                 0.5f,  0.5f,  0.5f, 
                -0.5f,  0.5f,  0.5f, 
                -0.5f, -0.5f,  0.5f, 
                 0.5f, -0.5f,  0.5f, 
                                     
                -0.5f,  0.5f, -0.5f, 
                 0.5f,  0.5f, -0.5f, 
                 0.5f, -0.5f, -0.5f, 
                -0.5f, -0.5f, -0.5f, 
            };
            static inline const std::array<fox::float32_t, 72> normals
            {
                 1.0f,  0.0f,  0.0f,
                 1.0f,  0.0f,  0.0f,
                 1.0f,  0.0f,  0.0f,
                 1.0f,  0.0f,  0.0f,

                -1.0f,  0.0f,  0.0f,
                -1.0f,  0.0f,  0.0f,
                -1.0f,  0.0f,  0.0f,
                -1.0f,  0.0f,  0.0f,

                 0.0f,  1.0f,  0.0f,
                 0.0f,  1.0f,  0.0f,
                 0.0f,  1.0f,  0.0f,
                 0.0f,  1.0f,  0.0f,

                 0.0f, -1.0f,  0.0f,
                 0.0f, -1.0f,  0.0f,
                 0.0f, -1.0f,  0.0f,
                 0.0f, -1.0f,  0.0f,

                 0.0f,  0.0f,  1.0f,
                 0.0f,  0.0f,  1.0f,
                 0.0f,  0.0f,  1.0f,
                 0.0f,  0.0f,  1.0f,

                 0.0f,  0.0f, -1.0f,
                 0.0f,  0.0f, -1.0f,
                 0.0f,  0.0f, -1.0f,
                 0.0f,  0.0f, -1.0f,
            };
            static inline const std::array<fox::float32_t, 72> tangents
            {
                 0.0f,  0.0f, -1.0f,   
                 0.0f,  0.0f, -1.0f,   
                 0.0f,  0.0f, -1.0f,   
                 0.0f,  0.0f, -1.0f,
                        
                 0.0f,  0.0f,  1.0f,  
                 0.0f,  0.0f,  1.0f,  
                 0.0f,  0.0f,  1.0f,  
                 0.0f,  0.0f,  1.0f,
                        
                 1.0f,  0.0f,  0.0f,   
                 1.0f,  0.0f,  0.0f,   
                 1.0f,  0.0f,  0.0f,   
                 1.0f,  0.0f,  0.0f,
                               
                 1.0f,  0.0f,  0.0f,   
                 1.0f,  0.0f,  0.0f,   
                 1.0f,  0.0f,  0.0f,   
                 1.0f,  0.0f,  0.0f,
                               
                 1.0f,  0.0f,  0.0f,   
                 1.0f,  0.0f,  0.0f,   
                 1.0f,  0.0f,  0.0f,   
                 1.0f,  0.0f,  0.0f,
                               
                -1.0f,  0.0f,  0.0f,  
                -1.0f,  0.0f,  0.0f,  
                -1.0f,  0.0f,  0.0f,  
                -1.0f,  0.0f,  0.0f
            };
            static inline const std::array<fox::float32_t, 48> coordinates
            {
                 1.0f, 1.0f,
                 0.0f, 1.0f,
                 0.0f, 0.0f,
                 1.0f, 0.0f,

                 1.0f, 1.0f,
                 0.0f, 1.0f,
                 0.0f, 0.0f,
                 1.0f, 0.0f,

                 1.0f, 1.0f,
                 0.0f, 1.0f,
                 0.0f, 0.0f,
                 1.0f, 0.0f,

                 1.0f, 1.0f,
                 0.0f, 1.0f,
                 0.0f, 0.0f,
                 1.0f, 0.0f,

                 1.0f, 1.0f,
                 0.0f, 1.0f,
                 0.0f, 0.0f,
                 1.0f, 0.0f,

                 1.0f, 1.0f,
                 0.0f, 1.0f,
                 0.0f, 0.0f,
                 1.0f, 0.0f,
            };
            static inline const std::array<fox::uint32_t, 36> indices
            {
                 0,  1,  2,
                 0,  2,  3,

                 4,  5,  6,
                 4,  6,  7,

                 8,  9, 10,
                 8, 10, 11,

                12, 13, 14,
                12, 14, 15,

                16, 17, 18,
                16, 18, 19,

                20, 21, 22,
                20, 22, 23,
            };

        private:
            static void init();

            static inline std::shared_ptr<Mesh> s_mesh{};
        };
        struct Sphere
        {
            friend Geometry;

            static const std::shared_ptr<gfx::Mesh> mesh()
            {
                return s_mesh;
            }

        private:
            static void init();

            static inline std::shared_ptr<gfx::Mesh> s_mesh{};
        };
    };
}
#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/ECS/Components/Camera.hpp"
#include "Helix/Input/Input.hpp"
#include "Helix/IO/Import/Model/GLTFImporter.hpp"
#include "Helix/IO/IO.hpp"
#include "Helix/Rendering/API/GraphicsAPI.hpp"
#include "Helix/Rendering/Blueprint/TextureBlueprint.hpp"
#include "Helix/Window/Window.hpp"

int main()
{
	using namespace hlx;

    auto window = Window::create("Helix", glm::uvec2{ 1280, 720 });

    

	Camera camera{};

    std::vector<float> vertices = 
	{
		//Positions            //Normals           //TexCoords
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f
    };
	std::vector<unsigned int> indices =
	{
		0, 1, 2, //First triangle
		0, 2, 3, //Second triangle
	};

	auto vboV = GraphicsAPI::create_vbo<float>(vertices);
	auto ibo  = GraphicsAPI::create_ibo(indices);

    auto layout = std::make_shared<VertexLayout>();
    layout->specify<float>(3);
    layout->specify<float>(3);
    layout->specify<float>(2);

	auto vao = GraphicsAPI::create_vao();
	vao->tie(vboV, layout);
	vao->tie(ibo);





    const auto vertexSource   = IO::load<File>("shaders/compiled/vert.spv")->read();
    const auto fragmentSource = IO::load<File>("shaders/compiled/frag.spv")->read();

    auto vertexShader = GraphicsAPI::create_sho(Shader::Type::Vertex, *vertexSource);
    if (!vertexShader->valid()) throw std::runtime_error{ vertexShader->error().data() };

    auto fragmentShader = GraphicsAPI::create_sho(Shader::Type::Fragment, *fragmentSource);
    if (!fragmentShader->valid()) throw std::runtime_error{ fragmentShader->error().data() };

    auto pipeline = GraphicsAPI::create_plo({ vertexShader, fragmentShader });





	struct Matrices
	{
		glm::mat4 view{};
		glm::mat4 projection{};
	};
	Matrices mts{ camera.view(), camera.projection() };
	auto ubo = GraphicsAPI::create_ubo(mts);
	ubo->bind_base(0);



	TextureBlueprint bp{};
	auto kiryuImage = IO::load<Image>("textures/Kiryu.png");
	auto kiryuTexture = bp.build<Texture2D>(kiryuImage);
	kiryuTexture->bind(0);





	vao->bind();
    pipeline->bind();

	while (true)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 36);

		window->refresh();
	}
}

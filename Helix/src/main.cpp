#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/IO/IO.hpp"
#include "Helix/Window/Window.hpp"
#include "Helix/Rendering/API/GraphicsAPI.hpp"
#include "Helix/Rendering/Blueprint/TextureBlueprint.hpp"
#include "Helix/ECS/Components/Camera.hpp"

#include "Helix/EXP/Buffer/VertexBuffer.hpp"

int main()
{
	using namespace hlx;

	glm::uvec2 dimensions{ 1280, 720 };
	auto properties = Window::Properties{ "Helix", dimensions };
	auto window = Window::create(properties);


	hlx::exp::test();

	//Camera camera{};




	//std::vector<float> positions =
	//{
	//	-0.5f,  0.5f, //Top middle
	//	-0.5f, -0.5f, //Bottom left
	//	 0.5f, -0.5f, //Bottom right
	//	 0.5f,  0.5f, //Top right
	//};
	//std::vector<float> colors =
	//{
	//	1.0f, 0.0f, 0.0f, 
	//	0.0f, 1.0f, 0.0f, 
	//	0.0f, 0.0f, 1.0f, 
	//	0.0f, 1.0f, 0.0f, 
	//};
	//std::vector<float> texCoords =
	//{
	//	0.0f, 1.0f,
	//	0.0f, 0.0f,
	//	1.0f, 0.0f,
	//	1.0f, 1.0f,
	//};
	//std::vector<unsigned int> indices =
	//{
	//	0, 1, 2, //First triangle
	//	0, 2, 3, //Second triangle
	//};

	//auto layout2f = GraphicsAPI::create_vlo();
	//layout2f->specify<float>(2);

	//auto layout3f = GraphicsAPI::create_vlo();
	//layout3f->specify<float>(3);



	//auto vboP = GraphicsAPI::create_vbo(positions);
	//auto vboC = GraphicsAPI::create_vbo(colors);
	//auto vboT = GraphicsAPI::create_vbo(texCoords);
	//auto ibo  = GraphicsAPI::create_ibo(indices);

	//auto vao = GraphicsAPI::create_vao();
	//vao->tie(vboP, layout2f);
	//vao->tie(vboC, layout3f);
	//vao->tie(vboT, layout2f);
	//vao->tie(ibo);



 //   const auto vertexSource   = IO::load<File>("shaders/compiled/vert.spv")->read();
 //   const auto fragmentSource = IO::load<File>("shaders/compiled/frag.spv")->read();

 //   auto vertexShader = GraphicsAPI::create_sho(Shader::Type::Vertex, *vertexSource);
 //   if (!vertexShader->valid()) throw std::runtime_error{ vertexShader->error().data() };

 //   auto fragmentShader = GraphicsAPI::create_sho(Shader::Type::Fragment, *fragmentSource);
 //   if (!fragmentShader->valid()) throw std::runtime_error{ fragmentShader->error().data() };

 //   auto pipeline = GraphicsAPI::create_plo({ vertexShader, fragmentShader });



	//std::array<glm::mat4, 2> matrices{ camera.view(), camera.projection() };
	//auto ubo = GraphicsAPI::create_ubo(matrices);
	//ubo->bind_base(0);
	//


	//TextureBlueprint bp{};
	//auto kiryuImage = IO::load<Image>("textures/Kiryu.png");
	//auto kiryuTexture = bp.build<Texture2D>(kiryuImage);



	//kiryuTexture->bind(0);
	//vao->bind();
 //   pipeline->bind();





	//while (true)
	//{
	//	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);



	//	window->refresh();
	//}
}

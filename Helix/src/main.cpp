#include "stdafx.hpp"

#include "Helix/IO/IO.hpp"
#include "Helix/Window/Window.hpp"
#include "Helix/Rendering/Buffer/VertexArray.hpp"
#include "Helix/Rendering/Buffer/VertexBuffer.hpp"
#include "Helix/Rendering/Buffer/IndexBuffer.hpp"
#include "Helix/Rendering/Shader/Shader.hpp"
#include "Helix/Rendering/Shader/Pipeline.hpp"
#include "Helix/ECS/Registry.hpp"
#include "Helix/ECS/Components/Components.hpp"
#include "Helix/Rendering/API/GraphicsAPI.hpp"

int main()
{
	using namespace hlx;

	glm::uvec2 dimensions{ 1280, 720 };
	auto properties = Window::Properties{ "Helix", dimensions };
	auto window = Window::create(properties);





	std::vector<float> positions =
	{
		 0.0f,  0.5f, //Top middle
		-0.5f, -0.5f, //Bottom left
		 0.5f, -0.5f, //Bottom right
	};
	std::vector<float> colors =
	{
		1.0f, 0.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 
		0.0f, 0.0f, 1.0f, 
	};
	std::vector<unsigned int> indices =
	{
		0, 1, 2, //First triangle
	};

	auto positionLayout = VertexLayout::create();
	positionLayout->specify<float>(2);

	auto colorLayout = VertexLayout::create();
	colorLayout->specify<float>(3);



	auto vboP = GraphicsAPI::create_t<VertexBuffer>(positions);
	auto vboC = GraphicsAPI::create_t<VertexBuffer>(colors);
	auto ibo  = GraphicsAPI::create_s(indices);

	auto vao = GraphicsAPI::create<VertexArray>();
	vao->tie(vboP, positionLayout);
	vao->tie(vboC, colorLayout);
	vao->tie(ibo);



    const auto vertexFile = IO::load<File>("shaders/vertex.glsl");
    const auto fragmentFile = IO::load<File>("shaders/fragment.glsl");
    const auto vertexSource = vertexFile->read();
    const auto fragmentSource = fragmentFile->read();

    auto vertexShader = Shader::create(Shader::Type::Vertex, *vertexSource);
    if (!vertexShader->valid()) throw std::runtime_error{ vertexShader->error().data() };

    auto fragmentShader = Shader::create(Shader::Type::Fragment, *fragmentSource);
    if (!fragmentShader->valid()) throw std::runtime_error{ fragmentShader->error().data() };

    auto pipeline = Pipeline::create({ vertexShader, fragmentShader });



    vao->bind();
    pipeline->bind();



	while (true)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);



		window->refresh();
	}
}

#include "stdafx.hpp"

#include "RenderContextAPI.hpp"

namespace hlx
{
	const RenderContextAPI::Attributes& RenderContextAPI::attributes()
	{
		//return m_attributes;
		throw std::runtime_error{ "This is not implemented for some reason" };
		return {};
	}

	RenderContextAPI::RenderContextAPI()
	{

	}
}

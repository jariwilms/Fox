#pragma once

#include "stdafx.hpp"

#include "Filesystem/File.hpp"
#include "Filesystem/Image.hpp"
#include "Filesystem/Directory.hpp"

namespace hlx
{
	class IO
	{
	public:
		static void init()
		{
			std::cout << "Initializing IO";

			stbi_set_flip_vertically_on_load(true);
		}
		
		template<typename T>
		static std::shared_ptr<T> load(const std::filesystem::path& path) = delete;
		template<> static std::shared_ptr<File> load<File>(const std::filesystem::path& path)
		{
			const auto fPath = from_root(path);

			return std::make_shared<File>(fPath);
		}
		template<> static std::shared_ptr<Image> load<Image>(const std::filesystem::path& path)
		{
			const auto fPath = from_root(path);

			return std::make_shared<Image>(fPath);
		}

		static Directory& root()
		{
			return s_root;
		}

	private:
		static std::filesystem::path from_root(const std::filesystem::path& path)
		{
			return root().path() / path;
		}
		static void check_exists(const std::filesystem::path& path)
		{
			if (!std::filesystem::exists(path)) throw std::runtime_error{ "Path does not exist!" };
		}

		static inline Directory s_root{ R"(C:\dev\C++\Helix\Helix\assets)" };
	};
}

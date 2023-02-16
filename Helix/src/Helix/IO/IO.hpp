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

		}
		
        template<typename T>
        static std::shared_ptr<T> load(const std::filesystem::path& path) = delete;
        template<> static std::shared_ptr<File>  load(const std::filesystem::path& path)
        {
            const auto cumulativePath = (s_root / path).lexically_normal();

            const auto it = m_files.find(cumulativePath);
            if (it != m_files.end() && !it->second.expired()) return it->second.lock();

            const auto file = std::make_shared<File>(cumulativePath);
            m_files.emplace(cumulativePath, file);

            return file;
        }
        template<> static std::shared_ptr<Image> load(const std::filesystem::path& path)
        {
            const auto cumulativePath = s_root / path;

            const auto it = m_images.find(cumulativePath);
            if (it != m_images.end() && !it->second.expired()) return it->second.lock();

            const auto image = std::make_shared<Image>(cumulativePath);
            m_images.emplace(cumulativePath, image);

            return image;
        }

		static Directory& root()
		{
			return s_root;
		}

	private:
		static inline Directory s_root{ ASSET_DIR };

		static inline std::unordered_map<std::filesystem::path, std::weak_ptr<File>> m_files{};
		static inline std::unordered_map<std::filesystem::path, std::weak_ptr<Image>> m_images{};
	};
}

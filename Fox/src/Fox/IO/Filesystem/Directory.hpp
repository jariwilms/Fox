#pragma once

#include "stdafx.hpp"

#include "Entry.hpp"
#include "File.hpp"

namespace fox
{
	class Directory : public Entry
	{
	public:
		using Children = std::tuple<std::vector<std::shared_ptr<Directory>>, std::vector<std::shared_ptr<io::File>>>;

		explicit Directory(const std::filesystem::path& path, bool explore = false)
			: Entry{ path }
		{
			if (!std::filesystem::is_directory(path)) throw std::invalid_argument{ "The given path does not reference a directory!" };

			if (explore) this->explore();
		}

		void refresh()
		{
			explore();
		}
        void explore()
        {
            auto& [directories, files] = m_children;
            directories.clear();
            files.clear();

            std::filesystem::directory_iterator it{ m_path };
            for (const auto& entry : it)
            {
                if (entry.is_directory())    directories.emplace_back(std::make_shared<Directory>(entry.path()));
                if (entry.is_regular_file()) files.emplace_back(std::make_shared<io::File>(entry.path()));
            }

            m_count = directories.size() + files.size();
        }

		template<typename T, typename... Args>
		std::shared_ptr<T> create(Args... args) = delete;
        template<> std::shared_ptr<Directory> create(const std::string& identifier)
        {
            const auto aggregatePath = m_path / identifier;
			if (!std::filesystem::exists(aggregatePath)) std::filesystem::create_directory(aggregatePath);

            return std::make_shared<Directory>(aggregatePath);
        }
		template<> std::shared_ptr<io::File> create(const std::string& identifier, const std::string& extension)
		{
            const auto aggregatePath = m_path / identifier;
			if (!std::filesystem::exists(aggregatePath)) std::ofstream{ aggregatePath };

            return std::make_shared<io::File>(aggregatePath);
		}

		template<typename T, typename... Args>
		bool remove(Args... args) = delete;
		template<> bool remove<Directory>(const std::filesystem::path& path, bool recursive)
		{
			if (!std::filesystem::is_directory(path)) throw std::invalid_argument{ "The given path is not a directory!" };

			if (recursive) return std::filesystem::remove_all(path);
			else           return std::filesystem::remove(path);
		}
        template<> bool remove<io::File>(const std::filesystem::path& path)
        {
			if (!std::filesystem::is_regular_file(path)) throw std::invalid_argument{ "The given path is not a file!" };

			return std::filesystem::remove(path);
        }

		const Children& children() const
		{
			return m_children;
		}
		size_t count() const
		{
			return m_count;
		}

		std::filesystem::path operator/(const std::filesystem::path& rhs) const
		{
			return m_path / rhs;
		}

	private:
		Children m_children{};
		size_t   m_count{};
	};
}

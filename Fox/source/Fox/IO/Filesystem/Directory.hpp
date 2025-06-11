#pragma once

#include <variant>

#include <fox/io/filesystem/entry.hpp>
#include <fox/io/filesystem/file.hpp>

namespace fox::io
{
    class Directory : public io::Entry
    {
    public:
        using entry_t = std::variant<io::Directory, io::File>;

        Directory(const std::filesystem::path& path)
            : io::Entry{ path } {}

        void explore()
        {
            m_children.clear();

            for (std::filesystem::directory_iterator iterator{ m_path }; auto const& entry : iterator)
            {
                     if (entry.is_directory   ()) m_children.emplace_back(std::make_shared<entry_t>(io::Directory{ entry.path() }));
                else if (entry.is_regular_file()) m_children.emplace_back(std::make_shared<entry_t>(io::File     { entry.path() }));
            }
        }

        auto children() const -> const std::vector<std::shared_ptr<entry_t>>&
        {
            return m_children;
        }

        std::filesystem::path operator/(const std::filesystem::path& other) const
        {
            return m_path / other;
        }

    private:
        std::vector<std::shared_ptr<entry_t>> m_children{};
    };
}

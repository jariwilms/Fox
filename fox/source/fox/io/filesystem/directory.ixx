export module fox.io.filesystem.directory;

import std;

import fox.io.filesystem.entry;
import fox.io.filesystem.file;

export namespace fox::io
{
    class Directory : public io::Entry
    {
    public:
        using entry_t = std::variant<io::Directory, io::File>;

        Directory(const std::filesystem::path& path)
            : io::Entry{ path } {}

        void explore()
        {
            children_.clear();

            for (const auto& entry : std::filesystem::directory_iterator{ path_ })
            {
                     if (entry.is_directory   ()) children_.emplace_back(std::make_shared<entry_t>(io::Directory{ entry.path() }));
                else if (entry.is_regular_file()) children_.emplace_back(std::make_shared<entry_t>(io::File     { entry.path() }));
            }
        }

        auto children() const -> const std::vector<std::shared_ptr<entry_t>>&
        {
            return children_;
        }

        std::filesystem::path operator/(const std::filesystem::path& other) const
        {
            return path_ / other;
        }

    private:
        std::vector<std::shared_ptr<entry_t>> children_{};
    };
}

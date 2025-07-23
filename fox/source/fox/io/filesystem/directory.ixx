export module fox.io.filesystem.directory;

import std;
import fox.io.filesystem.entry;
import fox.io.filesystem.file;

export namespace fox::io
{
    class directory : public io::entry
    {
    public:
        using entry_t = std::variant<io::directory, io::file>;

        explicit directory(const std::filesystem::path& path)
            : io::entry{ path } {}

        void explore()
        {
            children_.clear();
            std::ranges::for_each(std::filesystem::directory_iterator{ path() }, [&](const auto& entry)
                {
                         if (entry.is_directory   ()) children_.emplace_back(std::make_shared<entry_t>(io::directory{ entry.path() }));
                    else if (entry.is_regular_file()) children_.emplace_back(std::make_shared<entry_t>(io::file     { entry.path() }));
                });
        }

        auto children(this auto&& self) -> auto&&
        {
            return self.children_;
        }

        auto operator/(const std::filesystem::path& other) const -> std::filesystem::path
        {
            return path() / other;
        }

    private:
        std::vector<std::shared_ptr<entry_t>> children_;
    };
}

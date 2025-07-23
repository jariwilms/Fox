export module fox.io.filesystem.entry;

import std;

export namespace fox::io
{
	class entry
	{
	public:
		auto path     () const -> const std::filesystem::path&
		{
			return path_;
		}
		auto name     () const -> std::filesystem::path
		{
			return path_.filename();
		}
		auto stem     () const -> std::filesystem::path
		{
			return path_.stem();
		}
		auto extension() const -> std::filesystem::path
		{
			return path_.extension();
		}

		void rename(const std::string& name)
		{
			auto parent = path_.parent_path();
			auto target = parent / name;

			std::filesystem::rename(path_, target);

			path_ = target;
		}

	protected:
		explicit entry(const std::filesystem::path& path)
			: path_{ path.lexically_normal().make_preferred() } { }

	private:
		std::filesystem::path path_{};
	};
}

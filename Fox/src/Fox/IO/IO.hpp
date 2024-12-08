#pragma once

#include "stdafx.hpp"

#include "Filesystem/File.hpp"
#include "Filesystem/Directory.hpp"

namespace fox::io
{
    template<typename T>
    concept PathConstructible = requires (T t)
    {
        T{ std::filesystem::path{} };
    };

    static const Directory& root()
    {
        static Directory rootDirectory{ ASSET_DIR };

        return rootDirectory;
    }

    static std::shared_ptr<File> load(const std::filesystem::path& path)
    {
        const auto& filePath = (root().path() / path).lexically_normal();

        return std::make_shared<File>(filePath);
    }
}

#pragma once

#include "stdafx.hpp"

#include "Fox/IO/Import/Model/ModelImporter.hpp"

namespace fox::io::import::api
{
    using importer_t = io::ModelImporter;
}
namespace fox::io::import
{
    class ModelImporter2
    {
    public:
        void init()
        {
            importer = std::make_unique<api::importer_t>();
        }

        auto load(const std::filesystem::path& path)
        {
            importer->import(path);
        }
        auto load(std::span<const fox::byte_t> data)
        {

        }

    private:
        static inline auto importer = std::unique_ptr<api::importer_t>{};
    };
}

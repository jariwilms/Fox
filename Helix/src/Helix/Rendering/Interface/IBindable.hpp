#pragma once

#include "stdafx.hpp"

namespace hlx
{
    class IBindable
    {
    public:
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual bool is_bound() const = 0;

        Id id() const
        {
            return m_id;
        }

    protected:
        Id m_id{};
    };
}
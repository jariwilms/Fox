//#pragma once
//
//#include "stdafx.hpp"
//
//#include "Helix/Core/Type.hpp"
//
//namespace hlx
//{
    //class VertexLayout
    //{
    //public:
    //	struct Attribute
    //	{
    //	public:
    //		Attribute() = default;
    //		Attribute(unsigned int internalType, unsigned int count, size_t tSize, bool normalized = false)
    //			: count{ count }, internalType{ internalType }, tSize{tSize}, isNormalized{ normalized } {}

    //		const unsigned int internalType{};
    //		const unsigned int count{};
    //		const size_t tSize{};
    //		const bool isNormalized{};
    //	};

    //	virtual ~VertexLayout() = default;

    //	template<typename T>
    //	void specify(unsigned int count) = delete;
    //	template<> void specify<bool>              (unsigned int count)
    //	{
    //		specify_bool(count);
    //	}
    //	template<> void specify<char>              (unsigned int count)
    //	{
    //		specify_char(count);
    //	}
    //	template<> void specify<unsigned char>     (unsigned int count)
    //	{
    //		specify_unsigned_char(count);
    //	}
    //	template<> void specify<short>             (unsigned int count)
    //	{
    //		specify_short(count);
    //	}
    //	template<> void specify<unsigned short>    (unsigned int count)
    //	{
    //		specify_unsigned_short(count);
    //	}
    //	template<> void specify<int>               (unsigned int count)
    //	{
    //		specify_int(count);
    //	}
    //	template<> void specify<unsigned int>      (unsigned int count)
    //	{
    //		specify_unsigned_int(count);
    //	}
    //	template<> void specify<float>             (unsigned int count)
    //	{
    //		specify_float(count);
    //	}
    //	template<> void specify<double>            (unsigned int count)
    //	{
    //		specify_float(count);
    //	}

    //	const std::vector<Attribute>& attributes() const
    //	{
    //		return m_attributes;
    //	}
    //	size_t stride() const
    //	{
    //		return m_stride;
    //	}

    //protected:
    //	VertexLayout() = default;

    //	virtual void specify_bool             (unsigned int count) = 0;
    //	virtual void specify_char             (unsigned int count) = 0;
    //	virtual void specify_unsigned_char    (unsigned int count) = 0;
    //	virtual void specify_short            (unsigned int count) = 0;
    //	virtual void specify_unsigned_short   (unsigned int count) = 0;
    //	virtual void specify_int              (unsigned int count) = 0;
    //	virtual void specify_unsigned_int     (unsigned int count) = 0;
    //	virtual void specify_float            (unsigned int count) = 0;
    //	virtual void specify_double           (unsigned int count) = 0;

    //	std::vector<Attribute> m_attributes{};
    //	size_t m_stride{};
    //};
//}

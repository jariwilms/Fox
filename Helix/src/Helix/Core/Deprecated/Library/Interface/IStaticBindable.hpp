//#pragma once
//
//#include "IBindable.hpp"
//
//namespace hlx
//{
//	template<typename T>
//	class IStaticBindable : public IBindable
//	{
//	public:
//		virtual ~IStaticBindable() = default;
//
//        Id bound_id() const
//        {
//            return s_id;
//        }
//
//	protected:
//		IStaticBindable() = default;
//
//		static inline unsigned int s_id{};
//	};
//}

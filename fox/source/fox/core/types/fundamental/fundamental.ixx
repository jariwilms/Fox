export module fox.core.types.fundamental;

export namespace fox
{
	using void_t    =          void     ;
	using bool_t    =          bool     ;
	using char_t    =          char     ;
	using schar_t   =   signed char     ;
	using uchar_t   = unsigned char     ;
	using int8_t    =   signed char     ;
	using uint8_t   = unsigned char     ;
	using int16_t   =   signed short    ;
	using uint16_t  = unsigned short    ;
	using int32_t   =   signed int      ;
	using uint32_t  = unsigned int      ;
	using int64_t   =   signed long long;
	using uint64_t  = unsigned long long;
	using float32_t =          float    ;
	using float64_t =          double   ;

	enum : fox::bool_t
	{
		false_ = false,
		true_  = true,
	};

	

	template<typename T> struct fundamental{};

	template<> struct fox::fundamental<         void     > { using type = fox::void_t   ; };
	template<> struct fox::fundamental<         bool     > { using type = fox::bool_t   ; };
	template<> struct fox::fundamental<         char     > { using type = fox::char_t   ; };
	template<> struct fox::fundamental<  signed char     > { using type = fox::int8_t   ; };
	template<> struct fox::fundamental<unsigned char     > { using type = fox::uint8_t  ; };
	template<> struct fox::fundamental<  signed short    > { using type = fox::int16_t  ; };
	template<> struct fox::fundamental<unsigned short    > { using type = fox::uint16_t ; };
	template<> struct fox::fundamental<  signed int      > { using type = fox::int32_t  ; };
	template<> struct fox::fundamental<unsigned int      > { using type = fox::uint32_t ; };
	template<> struct fox::fundamental<  signed long long> { using type = fox::int64_t  ; };
	template<> struct fox::fundamental<unsigned long long> { using type = fox::uint64_t ; };
	template<> struct fox::fundamental<         float    > { using type = fox::float32_t; };
	template<> struct fox::fundamental<         double   > { using type = fox::float64_t; };

	template<typename T>
	using fundamental_t = fox::fundamental<T>::type;

	template<typename T>
	constexpr auto to_fundamental_type(T value) -> fox::fundamental_t<T>
	{
		return value;
	}
}

export module fox.core.types.semantic;

import fox.core.types.fundamental;

export namespace fox
{
	enum class result_e : fox::bool_t
	{
		failure = fox::false_,
		success = fox::true_,
	};
}

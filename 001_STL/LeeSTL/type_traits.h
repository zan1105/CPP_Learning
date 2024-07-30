// 提取类型信息

#ifndef _LEESTL_TYPE_TRAITS_H_
#define _LEESTL_TYPE_TRAITS_H_ 1

// 引入 GCC type_traits
#include <type_traits>

namespace leestl {

	// integral_constant
	template <typename T, T v>
	struct integral_constant {
		static constexpr T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
		constexpr operator value_type() const noexcept { return value; }
	};

	using true_type = integral_constant<bool, true>;
	using false_type = integral_constant<bool, false>;

	template <bool b>
	using bool_constant = integral_constant<bool, b>;
}

#endif

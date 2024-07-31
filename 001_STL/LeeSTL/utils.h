/** @file utils.h
 * 	这个文件包含通用工具的实现，如move， forward等
 */

#ifndef _LEESTL_UTILS_H_
#define _LEESTL_UTILS_H_ 1

#include <stddef.h>
#include "type_traits.h"

namespace leestl {

	/**
	 *  @brief 转为右值引用
	 *  @param  _t  原始引用
	 *  @return 由参数转换的右值引用
	 */
	template <typename T>
	constexpr typename std::remove_reference<T>::type &&move(T &&_t) noexcept {
		return static_cast<typename std::remove_reference<T>::type &&>(_t);
	}

	/**
	 *  @brief Forward an value
	 *  @return The parameter cast to the specified type.
	 *
	 *  这个函数实现 “完美转发”，即保持参数的左右值等属性，避免拷贝或移动
	 */
	template <typename T>
	constexpr T &&forward(std::remove_reference<T>::type &arg) noexcept {
		return static_cast<T &&>(arg);
	};

	/**
	 *  @brief Forward an value
	 *  @return The parameter cast to the specified type.
	 *
	 *  这个函数实现 “完美转发”，即保持参数的左右值等属性，避免拷贝或移动
	 */
	template <typename T>
	constexpr T &&forward(std::remove_reference<T>::type &&arg) noexcept {
		static_assert(
		    !std::is_lvalue_reference<T>::value,
		    "forward must not be used to convert an rvalue to an lvalue");
		return static_cast<T &&>(arg);
	};

}    // namespace leestl

#endif

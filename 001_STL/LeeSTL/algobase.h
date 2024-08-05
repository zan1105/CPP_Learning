/** @file algobase.h
 * 	这个文件实现 stl 基础算法
 */

#ifndef _LEESTL_ALGOBASE_H_
#define _LEESTL_ALGOBASE_H_

#include "iterator.h"
#include "utils.h"

namespace leestl {

	/**
	 * @brief 取二者中较大者，两者相等取第一个参数
	 *
	 * @tparam T 要比较的对象类型
	 * @param a 类型为 T 的第一个对象
	 * @param b 类型为 T 的第二个对象
	 * @return T& 较大对象的引用
	 */
	template <typename T>
	constexpr inline const T &max(const T &a, const T &b) {
		return b > a ? b : a;
	}

	/**
	 * @brief  取二者中较大者，两者相等取第一个参数
	 *
	 * @tparam T 要比较的对象类型
	 * @tparam Compare 比较两个 T 类型对象的仿函数
	 * @param a 类型为 T 的第一个对象
	 * @param b 类型为 T 的第二个对象
	 * @param comp
	 * @return constexpr const T& 较大对象的引用
	 */
	template <typename T, typename Compare>
	constexpr inline const T &max(const T &a, const T &b, Compare comp) {
		return comp(a, b) ? b : a;
	}

	/**
	 * @brief 取二者中较小者，两者相等取第一个参数
	 *
	 * @tparam T 要比较的对象类型
	 * @param a 类型为 T 的第一个对象
	 * @param b 类型为 T 的第二个对象
	 * @return T& 较小对象的引用
	 */
	template <typename T>
	constexpr inline const T &min(const T &a, const T &b) {
		return b < a ? b : a;
	}

	/**
	 * @brief  取二者中较小者，两者相等取第一个参数
	 *
	 * @tparam T 要比较的对象类型
	 * @tparam Compare 比较两个 T 类型对象的仿函数
	 * @param a 类型为 T 的第一个对象
	 * @param b 类型为 T 的第二个对象
	 * @param comp
	 * @return constexpr const T& 较小对象的引用
	 */
	template <typename T, typename Compare>
	constexpr inline const T &min(const T &a, const T &b, Compare comp) {
		return comp(a, b) ? b : a;
	}

	// 适用于输入迭代器的对象复制
	template <typename _II, typename _OI>
	_OI _unchecked_copy_a(_II first, _II last, _OI result, leestl::input_interator_tag) {
		for (; first != last; ++result, (void)++first) *result = *first;
		return result;
	}

	// 针对随机访问迭代器优化的对象复制
	template <typename _RI, typename _OI>
	_OI _unchecked_copy_a(_RI first, _RI last, _OI result, leestl::random_acess_interator_tag) {
		for (auto n = last - first; n > 0; --n, ++result, ++first) *result = *first;
		return result;
	}

	// 不检查合法性的对象复制实现
	template <typename _II, typename _OI>
	constexpr inline _OI _unchecked_copy(_II first, _II last, _OI result) {
		return _unchecked_copy_a(first, last, result, iterator_traits<_II>::iterator_category);
	}

	// 针对trivially_copy_assignable提供特化版本的不检查合法性的对象复制实现
	template <typename _II, typename _OI>
	constexpr inline typename std::enable_if<
	    std::is_same<typename std::remove_const<_II>::type, _OI>::value &&
	        std::is_trivially_copy_assignable<_OI>::value,
	    _OI *>::type
	_unchecked_copy(_II first, _II last, _OI result) {
		for (; first != last; ++result, (void)++first) *result = leestl::move(*first);
		return result;
	}

	/**
	 * @brief 把 [first, last) 上的内容复制到以 result 为起始处的空间
	 *
	 * @tparam _II 原始空间的迭代器类型
	 * @tparam _OI 目标空间的迭代器类型
	 * @param first 原始空间的起始位置
	 * @param last 原始空间的终止位置
	 * @param result 目标空间的起始位置
	 * @return _OI 目标空间的尾部
	 */
	template <typename _II, typename _OI>
	constexpr inline _OI copy(_II first, _II last, _OI result) {
		_unchecked_copy(first, last, result);
	}

}    // namespace leestl

#endif

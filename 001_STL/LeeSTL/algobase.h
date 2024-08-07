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
	constexpr inline _OI _unchecked_copy(_II first, _II last, _OI result, std::false_type) {
		return _unchecked_copy_a(first, last, result, leestl::iterator_category_types<_II>());
	}

	// 针对trivially_copy_assignable提供特化版本的不检查合法性的对象复制实现
	template <typename _II, typename _OI>
	constexpr inline _OI _unchecked_copy(_II first, _II last, _OI result, std::true_type) {
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
		return _unchecked_copy(
		    first, last, result,
		    std::conditional_t < std::is_same_v<std::remove_const_t<_II>, _OI> &&
		        std::is_trivially_copy_assignable_v<_OI>,
		    std::true_type, std::false_type > ());
	}

	// 用于非标量的 unchecked_fill 实现
	template <typename _FI, typename T>
	inline typename std::enable_if_t<!std::is_scalar_v<T>, void> _unchecked_fill(
	    _FI first, _FI last, const T &value) {
		for (; first != last; ++first) *first = value;
	}

	// 用于标量的 unchecked_fill 实现
	template <typename _FI, typename T>
	inline typename std::enable_if_t<std::is_scalar_v<T>, void> _unchecked_fill(
	    _FI first, _FI last, const T &value) {
		const T tmp = value;
		for (; first != last; ++first) *first = tmp;
	}

	// 针对 单字节类型 提供特化版本的 unchecked_fill 实现
	template <typename _FI, typename T>
	inline typename std::enable_if_t<leestl::is_byte_v<T>, void> _unchecked_fill(
	    _FI first, _FI last, const T &value) {
		const T tmp = value;
		if (const size_t n = last - first)
			__builtin_memset(first, static_cast<unsigned char>(tmp), n);
	}

	/**
	 * @brief 把 [first, last) 上的内容都填充为 value
	 *
	 * @tparam _FI 目标空间的迭代器类型
	 * @tparam T 填充的值的类型
	 * @param first 目标空间的起始位置
	 * @param last 目标空间的终止位置
	 * @param value 填充的值
	 */
	template <typename _FI, typename T>
	inline void fill(_FI first, _FI last, const T &value) {
		_unchecked_fill(first, last, value);
	}

	// 适用于非标量的 unchecked_fill_n 实现
	template <typename _OI, typename _Size, typename T>
	inline typename std::enable_if_t<!std::is_scalar_v<T>, _OI> _unchecked_fill_n_a(
	    _OI first, _Size n, const T &value) {
		for (; n > 0; --n, (void)++first) *first = value;
		return first;
	}

	// 适用于标量的 unchecked_fill_n 实现
	template <typename _OI, typename _Size, typename T>
	inline typename std::enable_if_t<std::is_scalar_v<T>, _OI> _unchecked_fill_n_a(
	    _OI first, _Size n, const T &value) {
		const T tmp = value;
		for (; n > 0; --n, (void)++first) *first = tmp;
		return first;
	}

	// 适用于输入迭代器的对象填充
	template <typename _OI, typename _Size, typename T>
	inline _OI _unchecked_fill_n(_OI first, _Size n, const T &value, leestl::input_interator_tag) {
		return _unchecked_fill_n_a(first, n, value);
	}

	// 适用于输出迭代器的对象填充
	template <typename _OI, typename _Size, typename T>
	inline _OI _unchecked_fill_n(_OI first, _Size n, const T &value, leestl::output_interator_tag) {
		return _unchecked_fill_n_a(first, n, value);
	}

	// 适用于随机访问迭代器优化的对象填充
	template <typename _OI, typename _Size, typename T>
	inline _OI _unchecked_fill_n(
	    _OI first, _Size n, const T &value, leestl::random_acess_interator_tag) {
		if (n <= 0) return first;
		_unchecked_fill(first, first + n, value);
		return first + n;
	}

	/**
	 * @brief 把 [first, first + n) 上的内容都填充为 value
	 *
	 * @tparam _OI 目标空间的迭代器类型
	 * @tparam _Size 填充的数量
	 * @tparam T 填充的值的类型
	 * @param first 目标空间的起始位置
	 * @param n 填充的数量
	 * @param value 填充的值
	 * @return _OI 目标空间的尾部
	 */
	template <typename _OI, typename _Size, typename T>
	inline _OI fill_n(_OI first, _Size n, const T &value) {
		return _unchecked_fill_n(first, n, value, leestl::iterator_category_types<_OI>());
	}

}    // namespace leestl

#endif

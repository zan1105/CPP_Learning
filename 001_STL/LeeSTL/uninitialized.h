/** @file uninitialized.h
 * 	这个文件实现在未初始化空间构造对象的相关方法
 */

#ifndef _LEESTL_UNINITIALIZED_H_
#define _LEESTL_UNINITIALIZED_H_ 1

#include "algobase.h"
#include "construct.h"
#include "utils.h"
#include "iterator.h"

namespace leestl {

	// 未做初始化的的复制构造方法(可基于移动的复制)
	template <typename _II, typename _FI>
	_FI _unchecked_uninit_copy(_II first, _II last, _FI result, std::true_type) {
		return leestl::copy(first, last, result);
	}

	// 未做初始化的的复制构造方法
	template <typename _II, typename _FI>
	_FI _unchecked_uninit_copy(_II first, _II last, _FI result, std::false_type) {
		auto curr = result;
		try {
			for (; first != last; ++first, (void)++curr)
				leestl::construct(leestl::address_of(*curr), *first);
			return curr;
		} catch (...) {
			leestl::destory(result, curr);
			throw;
		}
	}

	/**
	 * @brief 批量复制构造方法，把 [first, last) 上的内容复制到以 result 为起始处的空间
	 *
	 * @tparam _II 原始空间的迭代器类型
	 * @tparam _FI 目标空间的迭代器类型
	 * @param first 原始空间的起始位置
	 * @param last	原始空间的终止位置
	 * @param result 目标空间的起始位置
	 * @return _FI 目标空间尾部 result + (last - first)
	 */
	template <typename _II, typename _FI>
	inline _FI uninitialized_copy(_II first, _II last, _FI result) {
		return leestl::_unchecked_uninit_copy(
		    first, last, result,
		    std::is_trivially_copy_assignable<typename iterator_traits<_FI>::value_type>{});
	}

	/**
	 * @brief 移动（复制）构造方法，把 [first, last) 上的内容移动复制到以 result 为起始处的空间
	 *
	 * @tparam _II 原始空间的迭代器类型
	 * @tparam _FI 目标空间的迭代器类型
	 * @param first 原始空间的起始位置
	 * @param last	原始空间的终止位置
	 * @param result 目标空间的起始位置
	 * @return _FI 目标空间尾部 result + (last - first)
	 */
	template <typename _II, typename _FI>
	inline _FI uninitialized_move(_II first, _II last, _FI result) {
		return uninitialized_copy(first, last, result);
	}

	// 可直接使用 fill 的 unchecked_uninit_fill 实现
	template <typename _FI, typename T>
	inline void _unchecked_uninit_fill(_FI first, _FI last, const T &value, std::true_type) {
		leestl::fill(first, last, value);
	}

	// 显示调用构造函数的 unchecked_uninit_fill 实现
	template <typename _FI, typename T>
	inline void _unchecked_uninit_fill(_FI first, _FI last, const T &value, std::false_type) {
		auto curr = first;
		try {
			for (; curr != last; ++curr) leestl::construct(leestl::address_of(*curr), value);
		} catch (...) {
			leestl::destory(first, curr);
			throw;
		}
	}

	/**
	 * @brief 未初始化空间[first, last)上填充值为 value 的对象
	 *
	 * @tparam _FI 迭代器类型
	 * @tparam T 填充值类型
	 * @param first 起始位置迭代器
	 * @param last 终止位置迭代器
	 * @param value 填充值
	 */
	template <typename _FI, typename T>
	inline void uninitialized_fill(_FI first, _FI last, const T &value) {
		leestl::_unchecked_uninit_fill(
		    first, last, value,
		    std::is_trivially_copy_assignable<typename iterator_traits<_FI>::value_type>{});
	}

	// 可直接使用 fill_n 的 unchecked_uninit_fill_n 实现
	template <typename _FI, typename _Size, typename T>
	inline _FI _unchecked_uninit_fill_n(_FI first, _Size n, const T &value, std::true_type) {
		return leestl::fill_n(first, n, value);
	}

	// 显示调用构造函数的 unchecked_uninit_fill_n 实现
	template <typename _FI, typename _Size, typename T>
	inline _FI _unchecked_uninit_fill_n(_FI first, _Size n, const T &value, std::false_type) {
		auto curr = first;
		try {
			for (; n > 0; --n, ++curr) leestl::construct(leestl::address_of(*curr), value);
			return curr;
		} catch (...) {
			leestl::destory(first, curr);
			throw;
		}
	}

	/**
	 * @brief 未初始化空间[first, first + n)上填充值为 value 的对象
	 *
	 * @tparam _FI 迭代器类型
	 * @tparam _Size 填充数量类型
	 * @tparam T 填充值类型
	 * @param first 起始位置迭代器
	 * @param n 填充数量
	 * @param value 填充值
	 * @return _FI 返回填充结束位置迭代器
	 */
	template <typename _FI, typename _Size, typename T>
	inline _FI uninitialized_fill_n(_FI first, _Size n, const T &value) {    // todo
		return leestl::_unchecked_uninit_fill_n(
		    first, n, value,
		    std::is_trivially_copy_assignable<typename iterator_traits<_FI>::value_type>{});
	}

	// 一个对象的移动构造方法
	template <typename Tp, typename Up>
	inline void _relocate_object(Tp *dest, Up *orig) {
		leestl::construct(dest, leestl::move(*orig));
		leestl::destory(leestl::address_of(*orig));
	}

	/**
	 * @brief 移动构造方法，把 [first, last) 上的内容移动到以 result 为起始处的空间
	 *
	 * @tparam _II 原始空间的迭代器类型
	 * @tparam _FI 目标空间的迭代器类型
	 * @param first 原始空间的起始位置
	 * @param last	原始空间的终止位置
	 * @param result 目标空间的起始位置
	 * @return _FI 目标空间尾部 result + (last - first)
	 */
	template <typename _II, typename _FI>
	inline _FI relocate(_II first, _II last, _FI result) {
		typedef typename iterator_traits<_II>::value_type type1;
		typedef typename iterator_traits<_FI>::value_type type2;
		static_assert(
		    std::is_same<type1, type2>::value,
		    "relocation is only possible for values of the same type");

		_FI curr = result;
		for (; first != last; ++first, (void)++curr)
			leestl::_relocate_object(leestl::address_of(*curr), leestl::address_of(*first));

		return curr;
	}

}    // namespace leestl

#endif

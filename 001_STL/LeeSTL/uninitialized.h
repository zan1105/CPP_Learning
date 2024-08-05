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
	_FI _unchecked_uninit_copy(_II first, _II last, _FI result, leestl::true_type) {
		return leestl::copy(first, last, result);
	}

	// 未做初始化的的复制构造方法
	template <typename _II, typename _FI>
	_FI _unchecked_uninit_copy(_II first, _II last, _FI result, leestl::false_type) {
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
	inline _FI uninitialized_move(_II first, _II last, _FI result) {}

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
		typedef typename iterator_traits<_FI>::value_type type1;
		static_assert(
		    std::is_same<type1, type1>::value,
		    "relocation is only possible for values of the same type");

		_FI curr = result;
		for (; first != last; ++first, (void)++curr;)
			leestl::_relocate_object(leestl::address_of(*curr), leestl::address_of(*first));

		return curr;
	}

}    // namespace leestl

#endif

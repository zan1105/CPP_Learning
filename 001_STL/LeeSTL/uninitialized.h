/** @file uninitialized.h
 * 	这个文件实现在未初始化空间构造对象
 */

#ifndef _LEESTL_UNINITIALIZED_H_
#define _LEESTL_UNINITIALIZED_H_ 1

#include "utils.h"
#include "iterator.h"

namespace leestl {

	template <typename _InputIterator, typename _ForwardIterator>
	inline _ForwardIterator uninitialized_copy(
	    _InputIterator first, _InputIterator last, _ForwardIterator result) {}

	/**
	 * @brief 批量复制构造方法，把 [first, last) 上的内容复制到以 result 为起始处的空间
	 *
	 * @tparam _InputIterator 输入迭代器类型
	 * @tparam _ForwardIterator 前向迭代器类型
	 * @param first 原始空间的起始位置
	 * @param last	原始空间的终止位置
	 * @param result 目标空间的起始位置
	 * @return _ForwardIterator 目标空间尾部 result + (last - first)
	 */
	template <typename _InputIterator, typename _ForwardIterator>
	inline _ForwardIterator uninitialized_move(
	    _InputIterator first, _InputIterator last, _ForwardIterator result) {}

	template <typename Tp, typename Up>
	inline void _relocate_object(Tp *dest, Up *orig) {
		leestl::construct(dest, leestl::move(*orig));
		leestl::destory(leestl::address_of(*orig));
	}

	/**
	 * @brief 批量移动构造方法，把 [first, last) 上的内容移动到以 result 为起始处的空间
	 *
	 * @tparam _InputIterator 输入迭代器类型
	 * @tparam _ForwardIterator 前向迭代器类型
	 * @param first 原始空间的起始位置
	 * @param last	原始空间的终止位置
	 * @param result 目标空间的起始位置
	 * @return _ForwardIterator 目标空间尾部 result + (last - first)
	 */
	template <typename _InputIterator, typename _ForwardIterator>
	inline _ForwardIterator relocate(
	    _InputIterator first, _InputIterator last, _ForwardIterator result) {
		typedef typename iterator_traits<_InputIterator>::value_type type1;
		typedef typename iterator_traits<_InputIterator>::value_type type1;
		static_assert(
		    std::is_same<type1, type1>::value,
		    "relocation is only possible for values of the same type");

		_ForwardIterator curr = result;
		for (; first != last; ++first, (void)++curr;)
			leestl::_relocate_object(leestl::address_of(*curr), leestl::address_of(*first));

		return curr;
	}

}    // namespace leestl

#endif

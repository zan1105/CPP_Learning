/** @file iterator_base_types.h
 * 	这个文件实现迭代器类型 traits 和通用迭代器
 */

#ifndef _LEESTL_ITERATOR_BASE_TYPES_H_
#define _LEESTL_ITERATOR_BASE_TYPES_H_ 1

#include "type_traits.h"
#include <stddef.h>

namespace leestl {

	// 5 种迭代器类型
	struct input_interator_tag {};
	struct output_interator_tag {};
	struct forward_interator_tag : public input_interator_tag {};
	struct bidirectional_interator_tag : public forward_interator_tag {};
	struct random_acess_interator_tag : public bidirectional_interator_tag {};

	template <
	    typename _Category, typename T, typename _Distance = ptrdiff_t, typename _Pointer = T *,
	    typename _Reference = T &>
	struct iterator {
		typedef _Category  iterator_category;
		typedef T          value_type;
		typedef _Distance  difference_type;
		typedef _Pointer   pointer;
		typedef _Reference reference;
	};

	template <typename _Iterator, typename = void_type<>>
	struct _iterator_traits {};

	template <typename _Iterator>
	struct _iterator_traits<
	    _Iterator,
	    void_type<
	        typename _Iterator::iterator_category, typename _Iterator::value_type,
	        typename _Iterator::difference_type, typename _Iterator::pointer,
	        typename _Iterator::reference>> {
		typedef typename _Iterator::iterator_category iterator_category;
		typedef typename _Iterator::value_type        value_type;
		typedef typename _Iterator::difference_type   difference_type;
		typedef typename _Iterator::pointer           pointer;
		typedef typename _Iterator::reference         reference;
	};

	// 通用类型提取
	template <typename _Iterator>
	struct iterator_traits : public _iterator_traits<_Iterator> {};

	// 原生指针偏特化类型提取
	template <typename T>
	struct iterator_traits<T *> {
		typedef random_acess_interator_tag iterator_category;
		typedef T                          value_type;
		typedef ptrdiff_t                  difference_type;
		typedef T                         *pointer;
		typedef T                         &reference;
	};

	// 常量原生指针偏特化类型提取
	template <typename T>
	struct iterator_traits<const T *> {
		typedef random_acess_interator_tag iterator_category;
		typedef T                          value_type;
		typedef ptrdiff_t                  difference_type;
		typedef const T                   *pointer;
		typedef const T                   &reference;
	};

	// 获取迭代器类型
	template <typename _Iter>
	using iterator_category_types = typename iterator_traits<_Iter>::iterator_category;

	template <typename _Iter>
	using RequireInputIterator = typename std::enable_if<
	    std::is_convertible<iterator_category_types<_Iter>, input_interator_tag>::value>::type;

	// 使用于输入迭代器的 distance 实现
	template <typename _IT>
	inline constexpr typename iterator_traits<_IT>::difference_type _distance(
	    _IT first, _IT last, input_interator_tag) {
		typename iterator_traits<_IT>::difference_type n = 0;
		while (first != last) {
			++first;
			++n;
		}
		return n;
	}

	// 适用于随机访问迭代器的 distance 实现
	template <typename _RT>
	inline constexpr typename iterator_traits<_RT>::difference_type _distance(
	    _RT first, _RT last, random_acess_interator_tag) {
		return last - first;
	}

	/**
	 * @brief 计算两个迭代器之间的距离
	 *
	 * @tparam _Iter 迭代器类型
	 * @param first 起始位置迭代器
	 * @param last 终止位置迭代器
	 * @return 两个迭代器之间的距离
	 */
	template <typename _Iter>
	inline constexpr typename iterator_traits<_Iter>::difference_type distance(
	    _Iter first, _Iter last) {
		return _distance(first, last, iterator_category_types<_Iter>{});
	}

}    // namespace leestl
#endif

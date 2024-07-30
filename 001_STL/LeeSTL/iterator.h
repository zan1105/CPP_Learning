/** @file iterator.h
 * 	实现 reverse_iterator, back_insert_iterator,
 * 	front_insert_iterator, insert_iterator, __normal_iterator
 * 	迭代器、相关函数、运算符重载
 */

#ifndef _LEESTL_ITERATOR_H_
#define _LEESTL_ITERATOR_H_ 1

#include "type_traits.h"
#include "iterator_base_types.h"

namespace leestl {

	template <typename _Iterator>
	class reverse_iterator : public iterator<
	                             typename iterator_traits<_Iterator>::iterator_category,
	                             typename iterator_traits<_Iterator>::value_type,
	                             typename iterator_traits<_Iterator>::difference_type,
	                             typename iterator_traits<_Iterator>::pointer,
	                             typename iterator_traits<_Iterator>::reference> {
		template <typename _Iter>
		friend class reverse_iterator;
	};

}    // namespace leestl

#endif

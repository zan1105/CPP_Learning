/** @file iterator.h
 * 	这个文件实现 reverse_iterator, back_insert_iterator,
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

	protected:
		_Iterator current;    // 当前迭代器

		typedef iterator_traits<_Iterator> _traits_type;

	public:
		typedef _Iterator                              iterator_type;
		typedef typename _traits_type::pointer         pointer;
		typedef typename _traits_type::difference_type difference_type;
		typedef typename _traits_type::reference       reference;

		// 构造、复制、移动、析构函数
		reverse_iterator() : current() {}
		explicit reverse_iterator(iterator_type __x) : current(__x) {}
		template <typename _Iter>
		reverse_iterator(const reverse_iterator<_Iter>& __x) : current(__x.base()) {}

		// 获取当前迭代器
		iterator_type base() const { return current; }

		// 重载运算符
		reference operator*() const {
			_Iterator __tmp = current;
			return *--__tmp;
		}

		pointer operator->() const { return &(operator*()); }

		reverse_iterator& operator++() {
			--current;
			return *this;
		}

		reverse_iterator operator++(int) {
			reverse_iterator __tmp = *this;
			--current;
			return __tmp;
		}

		reverse_iterator& operator--() {
			++current;
			return *this;
		}

		reverse_iterator operator--(int) {
			reverse_iterator __tmp = *this;
			++current;
			return __tmp;
		}

		reverse_iterator operator+(difference_type __n) const {
			return reverse_iterator(current - __n);
		}

		reverse_iterator& operator+=(difference_type __n) {
			current -= __n;
			return *this;
		}

		reverse_iterator operator-(difference_type __n) const {
			return reverse_iterator(current + __n);
		}

		reverse_iterator& operator-=(difference_type __n) {
			current += __n;
			return *this;
		}

		reference operator[](difference_type __n) const { return *(*this + __n); }
	};

	template <typename _Iterator>
	inline bool operator==(
	    const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator>& __y) {
		return __x.base() == __y.base();
	}

	template <typename _Iterator>
	inline bool operator<(
	    const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator>& __y) {
		return __y.base() < __x.base();
	}

	template <typename _Iterator>
	inline bool operator!=(
	    const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator>& __y) {
		return !(__x == __y);
	}

	template <typename _Iterator>
	inline bool operator>(
	    const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator>& __y) {
		return __y < __x;
	}

	template <typename _Iterator>
	inline bool operator<=(
	    const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator>& __y) {
		return !(__y < __x);
	}

	template <typename _Iterator>
	inline bool operator>=(
	    const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator>& __y) {
		return !(__x < __y);
	}

	template <typename _Iterator>
	inline typename reverse_iterator<_Iterator>::difference_type operator-(
	    const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator>& __y) {
		return __y.base() - __x.base();
	}

	template <typename _Iterator>
	inline reverse_iterator<_Iterator> operator+(
	    typename reverse_iterator<_Iterator>::difference_type __n,
	    const reverse_iterator<_Iterator>&                    __x) {
		return reverse_iterator<_Iterator>(__x.base() - __n);
	}

	template <typename _Iterator>
	inline reverse_iterator<_Iterator> make_reverse_iterator(_Iterator __i) {
		return reverse_iterator<_Iterator>(__i);
	}

}    // namespace leestl

#endif

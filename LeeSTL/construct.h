/** @file construct.h
 * 	这个文件实现对象的构造函数和析构函数
 */

#ifndef _LEESTL_CONSTRUCT_H_
#define _LEESTL_CONSTRUCT_H_ 1

#include <new>

#include "type_traits.h"
#include "iterator.h"

namespace leestl {

	// 构造对象
	template <typename T>
	void construct(T *ptr) {
		::new ((void *)ptr) T();
	}

	template <typename T, typename VT>
	void construct(T *ptr, VT &v) {
		::new ((void *)ptr) T(v);
	}

	template <typename T, typename... Args>
	void construct(T *ptr, Args &&...args) {
		::new ((void *)ptr) T(leestl::forward<Args>(args)...);
	}

	// 析构对象
	template <typename T>
	void _destory(T *, leestl::true_type) {}

	template <typename T>
	void _destory(T *ptr, leestl::false_type) {
		if (ptr != nullptr) ptr->~T();
	}

	template <typename T>
	void destory(T *ptr) {
		_destory(ptr, std::is_trivially_destructible<T>{});
	}

	template <typename _ForwardIterator>
	void __destory(_ForwardIterator, _ForwardIterator, std::true_type) {}

	template <typename _ForwardIterator>
	void __destory(_ForwardIterator first, _ForwardIterator last, std::false_type) {
		for (; first != last; ++first) destory(&*first);
	}

	template <typename _ForwardIterator>
	void destory(_ForwardIterator first, _ForwardIterator last) {
		__destory(
		    first, last,
		    std::is_trivially_destructible<
		        typename iterator_traits<_ForwardIterator>::value_type>{});
	}

}    // namespace leestl

#endif

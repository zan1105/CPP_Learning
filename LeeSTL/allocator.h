/** @file allocator.h
 * 	这个文件是配置器的实现，负责对象的内存管理
 */

#ifndef _LEESTL_ALLOCATOR_H_
#define _LEESTL_ALLOCATOR_H_ 1

#include "construct.h"
#include "utils.h"

namespace leestl {

	template <typename T>
	class allocator {
	public:
		typedef T         value_type;
		typedef size_t    size_type;
		typedef ptrdiff_t difference_type;
		typedef T*        pointer;
		typedef const T*  const_pointer;
		typedef T&        reference;
		typedef const T&  const_reference;

	public:
		static T* allocate();
		static T* allocate(size_type n);

		static void deallocate(T* ptr);
		static void deallocate(T* ptr, size_type n);

		static void construct(T* ptr);
		static void construct(T* ptr, const T& _t);
		static void construct(T* ptr, T&& _t);

		template <typename... Args>
		static void construct(T* ptr, Args&&... args);

		static void destory(T* ptr);
		static void destory(T* first, T* last);
	};

	template <typename T>
	T* allocator<T>::allocate() {
		return static_cast<T*>(::operator new(sizeof(T)));
	}

	template <typename T>
	T* allocator<T>::allocate(size_type n) {
		if (n == 0) return nullptr;
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}

	template <typename T>
	void allocator<T>::deallocate(T* ptr) {
		if (ptr == nullptr) return;
		::operator delete(ptr);
	}

	template <typename T>
	void allocator<T>::deallocate(T* ptr, size_type n) {
		if (ptr == nullptr) return;
		::operator delete(ptr, n * sizeof(T));
	}

	template <typename T>
	void allocator<T>::construct(T* ptr) {
		leestl::construct(ptr);
	}

	template <typename T>
	void allocator<T>::construct(T* ptr, const T& _t) {
		leestl::construct(ptr, _t);
	}

	template <typename T>
	void allocator<T>::construct(T* ptr, T&& _t) {
		leestl::construct(ptr, leestl::move(_t));
	}

	template <typename T>
	template <typename... Args>
	void allocator<T>::construct(T* ptr, Args&&... args) {
		leestl::construct(ptr, leestl::forward<Args>(args)...);
	}

	template <typename T>
	void allocator<T>::destory(T* ptr) {
		leestl::destory(ptr);
	}

	template <typename T>
	void allocator<T>::destory(T* first, T* last) {
		leestl::destory(first, last);
	}

}    // namespace leestl

#endif
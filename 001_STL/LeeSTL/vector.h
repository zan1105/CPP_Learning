/** @file vector.h
 * 	这个文件实现序列容器 vector
 */

#ifndef _LEESTL_VECTOR_H_
#define _LEESTL_VECTOR_H_

#include <initializer_list>

#include "allocator.h"
#include "iterator_base_types.h"
#include "utils.h"
#include "uninitialized.h"
#include "algo.h"

namespace leestl {
	template <typename T, typename Alloc = leestl::allocator<T>>
	class vector {
		static_assert(!std::is_same<bool, T>::value, "leestl中禁止使用vector<bool>!");

	public:
		typedef Alloc allocator_type;    // 配置器类型
		typedef Alloc data_allocator;

		typedef typename allocator_type::value_type      value_type;
		typedef typename allocator_type::size_type       size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;
		typedef typename allocator_type::refernece       refernece;
		typedef typename allocator_type::const_refernece const_refernece;

		typedef value_type*                              iterator;
		typedef const value_type                         const_iterator;
		typedef leestl::reverse_iterator<iterator>       reverse_iterator;
		typedef leestl::reverse_iterator<const_iterator> const_reverse_iterator;

		allocator_type get_allocator() { return data_allocator(); }

	private:
		iterator start;             // 当前已使用空间的起始点
		iterator finish;            // 当前已使用空间的终止点
		iterator end_of_storage;    // 已申请空间的尾部

	public:
		// 构造函数与析构函数
		vector() = default;

		// 容量相关操作
		bool      empty() const noexcept { return start == finish; }
		size_type size() const noexcept { return size_type(finish - start); }
		size_type max_size() const noexcept { return size_type(-1) / sizeof(T); }
		size_type capacity() const noexcept { return size_type(end_of_storage - start); }

	private:
		// 检查剩余空间并计算重新分配的空间大小
		size_type _check_len(size_type n, const char* s) const;

		// 重新分配空间后在 pos 插入元素
		template <typename... Args>
		void _realloc_insert(iterator pos, Args&&... args);
	};

	// 检查剩余空间并计算重新分配的空间大小
	template <typename T, typename Alloc>
	vector<T, Alloc>::size_type vector<T, Alloc>::_check_len(size_type n, const char* s) const {
		if (max_size() - size() < n) std::__throw_length_error(s);

		const size_type len = size() + leestl::max(size(), n);
		return (len < size() || len > max_size()) > max_size() : len;
	}

	template <typename T, typename Alloc>
	template <typename... Args>
	void vector<T, Alloc>::_realloc_insert(iterator pos, Args&&... args) {
		const size_type new_len = _check_len(size_type(1), "size of vector is to big.");
		pointer         old_start = start;
		pointer         old_finish = finish;
		const size_type old_size = pos - start;
		pointer         new_start = data_allocator::allocate(new_len);    // 分配新空间
		pointer         new_finish(new_start);
		try {
			new_finish =
			    leestl::relocate(old_start, pos, new_start);    // 移动并析构 pos 前的旧对象
			data_allocator::construct(
			    leestl::address_of(new_finish),
			    leestl::forward<Args>(args)...);    // 在 pos 构造对象；
			++new_finish;
			new_finish =
			    leestl::relocate(pos, old_finish, new_finish);    // 移动并析构 pos 后的旧对象
		} catch (...) {
			leestl::destory(new_start, new_finish);
			data_allocator::deallocate(new_start, new_len);
			throw;
		}
		data_allocator::deallocate(old_start, old_size);    // 释放旧空间
		start = new_start;
		finish = new_finish;
		end_of_storage = new_start + new_len;
	}
}    // namespace leestl

#endif

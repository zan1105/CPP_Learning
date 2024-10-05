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
	template <typename T>
	class vector {
		static_assert(!std::is_same<bool, T>::value, "leestl's vector can't support bool!");

	public:
		typedef leestl::allocator<T> allocator_type;    // 配置器类型
		typedef leestl::allocator<T> data_allocator;

		typedef typename allocator_type::value_type      value_type;
		typedef typename allocator_type::size_type       size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;

		typedef value_type*                              iterator;
		typedef const value_type*                        const_iterator;
		typedef leestl::reverse_iterator<iterator>       reverse_iterator;
		typedef leestl::reverse_iterator<const_iterator> const_reverse_iterator;

		allocator_type get_allocator() { return data_allocator(); }

	private:
		iterator start;             // 当前已使用空间的起始点
		iterator finish;            // 当前已使用空间的终止点
		iterator end_of_storage;    // 已申请空间的尾部

	public:
		/**
		 * @brief vector 默认构造函数
		 *
		 */
		vector() noexcept : start(), finish(), end_of_storage() {};

		/**
		 * @brief 给出 大小的 vector 构造函数
		 *
		 * @param n    vector 的大小
		 */
		explicit vector(size_type n) {
			_create_storage(_check_init_len(n));
			finish = uninitialized_fill_n(start, n, value_type());
		}

		/**
		 * @brief 给出大小、初始值的 vector 构造函数
		 *
		 * @param n vector 的大小
		 * @param value 初始化值
		 */
		vector(size_type n, const value_type& value) {
			_create_storage(_check_init_len(n));
			finish = uninitialized_fill_n(start, n, value);
		}

		/**
		 * @brief 复制构造函数
		 *
		 * @param x 要复制的 vector
		 */
		vector(const vector& x) {
			_create_storage(x.size());
			finish = uninitialized_copy(x.begin(), x.end(), start);
		}

		/**
		 * @brief 移动构造函数
		 */
		vector(vector&&) noexcept = default;

		/**
		 * @brief 通过初始化列表构造 vector
		 *
		 * @param il  初始化列表
		 * @param alloc 配置器
		 */
		vector(std::initializer_list<value_type> il) {
			_range_initialize(il.begin(), il.end(), leestl::random_acess_interator_tag());
		}

		/**
		 * @brief 通过迭代器区间构造 vector
		 *
		 * @tparam _II 迭代器类型
		 * @tparam
		 * @param first
		 * @param last
		 * @param alloc
		 */
		template <typename _II, typename = leestl::RequireInputIterator<_II>>
		vector(_II first, _II last) {
			_range_initialize(first, last, leestl::iterator_category_types<_II>());
		}

		/**
		 * @brief 析构函数
		 */
		~vector() noexcept {
			leestl::destory(start, finish);
			data_allocator::deallocate(start, capacity());
		}

		// 赋值操作符
		// 复制赋值
		vector& operator=(const vector& x) {
			if (this != &x) {
				const size_type len = x.size();
				if (len > capacity()) {
					pointer new_start = _alloc_and_copy(len, x.begin(), x.end());
					leestl::destory(start, finish);
					data_allocator::deallocate(start, capacity());
					start = new_start;
					end_of_storage = start + len;
				} else if (len <= size()) {
					leestl::destory(leestl::copy(x.begin(), x.end(), start), finish);
				} else {
					leestl::copy(x.begin(), x.begin() + size(), start);
					uninitialized_copy(x.begin() + size(), x.end(), finish);
				}
				finish = start + len;
			}
			return *this;
		}

		// 移动赋值
		vector& operator=(vector&& x) noexcept {
			if (this != &x) {
				leestl::destory(start, finish);
				data_allocator::deallocate(start, capacity());
				start = x.start;
				finish = x.finish;
				end_of_storage = x.end_of_storage;
				x.start = x.finish = x.end_of_storage = nullptr;
			}
			return *this;
		}

		// 初始化列表赋值
		vector& operator=(std::initializer_list<value_type> il) {
			_assign_aux(il.begin(), il.end(), leestl::random_acess_interator_tag());
			return *this;
		}

		// 迭代器相关操作
		iterator               begin() noexcept { return start; }
		const_iterator         begin() const noexcept { return start; }
		iterator               end() noexcept { return finish; }
		const_iterator         end() const noexcept { return finish; }
		reverse_iterator       rbegin() noexcept { return reverse_iterator(finish); }
		const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(finish); }
		reverse_iterator       rend() noexcept { return reverse_iterator(start); }
		const_reverse_iterator rend() const noexcept { return const_reverse_iterator(start); }
		const_iterator         cbegin() const noexcept { return start; }
		const_iterator         cend() const noexcept { return finish; }
		const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(finish); }
		const_reverse_iterator crend() const noexcept { return const_reverse_iterator(start); }

		// 容量相关操作
		bool      empty() const noexcept { return start == finish; }
		size_type size() const noexcept { return size_type(finish - start); }
		size_type max_size() const noexcept { return size_type(-1) / sizeof(T); }
		size_type capacity() const noexcept { return size_type(end_of_storage - start); }

		// 修改容器相关操作
		// 插入元素
		iterator insert(const_iterator pos, const value_type& value);    // 复制插入

		// 移动插入
		iterator insert(const_iterator pos, value_type&& value) {
			return _insert_rval(pos, leestl::move(value));
		}

		// 初始化列表插入
		iterator insert(const_iterator pos, std::initializer_list<value_type> il) {
			auto n = pos - cbegin();
			_range_insert(begin() + n, il.begin(), il.end(), leestl::random_acess_interator_tag());
			return begin() + n;
		}

		// 填充插入
		iterator insert(const_iterator pos, size_type n, const value_type& value) {
			difference_type _offset = pos - cbegin();
			_fill_insert(begin() + _offset, n, value);
			return begin() + _offset;
		}

		// 范围插入
		template <typename _II, typename = leestl::RequireInputIterator<_II>>
		iterator insert(const_iterator pos, _II first, _II last) {
			difference_type _offset = pos - cbegin();
			_range_insert(begin() + _offset, first, last, leestl::iterator_category_types<_II>());
			return begin() + _offset;
		}

		// 删除元素
		iterator erase(const_iterator pos);                           // 删除指定位置元素
		iterator erase(const_iterator first, const_iterator last);    // 删除指定范围元素

		void swap(vector& x) noexcept {
			// leestl::swap(start, x.start);
			// leestl::swap(finish, x.finish);
			// leestl::swap(end_of_storage, x.end_of_storage);
		}

		// void clear() noexcept { _erase_at_end(start); }

	private:
		// 构造函数用该方法检查初始化长度是否合法
		static size_type _check_init_len(size_type n) {
			if (n > size_type(-1) / sizeof(T))
				std::__throw_length_error("cannot create vector larger than max_size().");
			return n;
		}

		// 创建空间
		void _create_storage(size_type n) {
			start = data_allocator::allocate(n);
			finish = start;
			end_of_storage = start + n;
		}

		// 适用于输入迭代器的范围初始化
		template <typename _II>
		void _range_initialize(_II first, _II last, input_interator_tag) {
			try {
				// for (; first != last; ++first) emplace_back(*first);// todo
			} catch (...) {
				// clear();// todo
				throw;
			}
		}

		// 适用于前向迭代器的范围初始化
		template <typename _FI>
		void _range_initialize(_FI first, _FI last, forward_interator_tag) {
			const size_type n = leestl::distance(first, last);
			_create_storage(_check_init_len(n));
			finish = uninitialized_copy(first, last, start);
		}

		// 重新分配空间时检查剩余空间并计算新空间大小
		size_type _check_len(size_type n, const char* s) const {
			if (max_size() - size() < n) std::__throw_length_error(s);

			const size_type len = size() + leestl::max(size(), n);
			return (len < size() || len > max_size()) ? max_size() : len;
		}

		// 重新分配空间并复制元素
		template <typename _FI>
		pointer _alloc_and_copy(size_type n, _FI first, _FI last) {
			pointer result = data_allocator::allocate(n);
			try {
				leestl::uninitialized_copy(first, last, result);
				return result;
			} catch (...) {
				data_allocator::deallocate(result, n);
				throw;
			}
		}

		// 从 pos 处开始擦除元素
		void _erase_at_end(pointer pos) {
			if (size_type n = finish - pos) {
				leestl::destory(pos, finish);
				finish = pos;
				// shrink_to_fit();
			}
		}

		// 在 pos 处插入元素
		template <typename _Arg>
		void _insert_aux(iterator pos, _Arg&& arg) {
			if (finish != end_of_storage) {
				leestl::construct(leestl::address_of(*finish), leestl::move(*(finish - 1)));
				++finish;
				leestl::move_backward(pos, finish - 2, finish - 1);
				*pos = leestl::forward<_Arg>(arg);
			} else {
				_realloc_insert(pos, leestl::forward<_Arg>(arg));
			}
		}

		// 适用于输入迭代器的范围插入
		template <typename _II>
		void _range_insert(iterator pos, _II first, _II last, leestl::input_interator_tag) {
			if (pos == end()) {
				for (; first != last; ++first) insert(end(), *first);
			} else if (first != last) {
				vector tmp(first, last);
				insert(pos, tmp.begin(), tmp.end());
			}
		}

		// 适用于前向迭代器的范围插入
		template <typename _FI>
		void _range_insert(iterator pos, _FI first, _FI last, leestl::forward_interator_tag) {
			if (first != last) {
				const size_type n = leestl::distance(first, last);
				if (size_type(end_of_storage - finish) >= n) {     // 空间足够
					const size_type elems_after = finish - pos;    // pos 后的元素个数
					pointer         old_finish(finish);
					if (elems_after > n) {    // pos 到 finish 的空间足够容纳 n 个元素
						finish = leestl::uninitialized_move(
						    finish - n, finish,
						    finish);    // 将后 n 个元素移动到未初始化的finish后面
						leestl::move_backward(
						    pos, old_finish - n,
						    old_finish);    // 将剩余需要后移的元素移动到 old_finish 前面
						leestl::copy(first, last, pos);    // 将新的 n 个元素插入到 pos 后面
					} else {    // pos 到 finish 的空间不足容纳 n 个元素
						_FI mid = first;
						leestl::advance(mid, elems_after);
						finish = uninitialized_copy(mid, last, finish);
						finish = uninitialized_move(pos, old_finish, finish);
						leestl::copy(first, mid, pos);
					}
				} else {
					pointer old_start(start), old_finish(finish);

					const size_type len = _check_len(n, "size of vector is too big.");

					pointer new_start = data_allocator::allocate(len);
					pointer new_finish(new_start);

					try {
						new_finish = leestl::uninitialized_move(old_start, pos, new_finish);
						new_finish = leestl::uninitialized_copy(first, last, new_finish);
						new_finish = leestl::uninitialized_move(pos, old_finish, new_finish);
					} catch (...) {
						leestl::destory(new_start, new_finish);
						data_allocator::deallocate(new_start, len);
						throw;
					}

					leestl::destory(old_start, old_finish);
					data_allocator::deallocate(old_start, capacity());
					start = new_start;
					finish = new_finish;
					end_of_storage = new_start + len;
				}
			}
		}

		// 适用于输入迭代器的 vector 赋值
		template <typename _II>
		void _assign_aux(_II first, _II last, leestl::input_interator_tag) {
			pointer cur = start;
			for (; first != last && cur != finish; ++cur, (void)++first) *cur = *first;
			if (first == last) _erase_at_end(cur);
			else _range_insert(end(), first, last, leestl::iterator_category_types<_II>());
		}

		// 适用于前向迭代器的 vector 赋值
		template <typename _FI>
		void _assign_aux(_FI first, _FI last, leestl::forward_interator_tag) {
			const size_type len = leestl::distance(first, last);
			if (len > capacity()) {
				pointer new_start = _alloc_and_copy(len, first, last);
				leestl::destory(start, finish);
				data_allocator::deallocate(start, capacity());
				start = new_start;
				end_of_storage = finish = start + len;
			} else if (size() >= len) {
				_erase_at_end(leestl::copy(first, last, start));
			} else {
				_FI mid = first;
				leestl::advance(mid, size());
				leestl::copy(first, mid, start);
				finish = uninitialized_copy(mid, last, finish);
			}
		}

		// 空间不足时重新分配空间后在 pos 插入元素
		template <typename... Args>
		void _realloc_insert(iterator pos, Args&&... args);

		// 在 pos 处插入右值
		iterator _insert_rval(const_iterator pos, value_type&& value) {
			const size_type n = pos - cbegin();
			if (finish != end_of_storage) {
				if (pos == cend()) {
					data_allocator::construct(leestl::address_of(*finish), leestl::move(value));
					++finish;
				} else {
					_insert_aux(begin + n, leestl::move(value));
				}
			} else _realloc_insert(begin() + n, leestl::move(value));

			return iterator(start + n);
		}

		// 填充插入
		void _fill_insert(iterator _pos, size_type _n, const value_type& _x) {
			if (_n != 0) {
				if (size_type(end_of_storage - finish) >= _n) {    // 空间足够
					const size_type _elems_after = end() - _pos;
					value_type      _x_copy = _x;
					pointer         _old_finish(finish);
					if (_elems_after > _n) {
						finish = uninitialized_move(finish - _n, finish, finish);
						leestl::move_backward(_pos, _old_finish - _n, _old_finish);
						leestl::fill(_pos, _pos + _n, _x_copy);
					} else {
						leestl::uninitialized_fill_n(finish, _n - _elems_after, _x_copy);
						finish += _n - _elems_after;
						finish = leestl::uninitialized_move(_pos, _old_finish, finish);
						leestl::fill(_pos, _old_finish, _x_copy);
					}
				} else {
					const size_type _new_len = _check_len(_n, "size of vector is too big.");
					const size_type _elems_before = _pos - start;

					pointer _new_start = data_allocator::allocate(_new_len);
					pointer _old_start(start), _old_finish(finish), _new_finish(_new_start);
					try {
						leestl::uninitialized_fill_n(_new_start + _elems_before, _n, _x);
						_new_finish = pointer();
						_new_finish = leestl::uninitialized_move(_old_start, _pos, _new_start);
						_new_finish += _n;
						_new_finish = leestl::uninitialized_move(_pos, _old_finish, _new_finish);
					} catch (...) {
						if (!_new_finish) {
							leestl::destory(
							    _new_start + _elems_before, _new_start + _elems_before + _n);
						} else {
							leestl::destory(_new_start, _new_finish);
						}
						data_allocator::deallocate(_new_start, _new_len);
						throw;
					}
					leestl::destory(_old_start, _old_finish);
					data_allocator::deallocate(_old_start, capacity());
					start = _new_start;
					finish = _new_finish;
					end_of_storage = _new_start + _new_len;
				}
			}
		}
	};

	template <typename T>
	template <typename... Args>
	void vector<T>::_realloc_insert(iterator pos, Args&&... args) {
		const size_type new_len = _check_len(size_type(1), "size of vector is to big.");
		const size_type old_size = pos - start;

		pointer new_start = data_allocator::allocate(new_len);    // 分配新空间
		pointer old_start(start), old_finish(finish), new_finish(new_start);
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

	template <typename T>
	typename vector<T>::iterator vector<T>::insert(const_iterator pos, const value_type& value) {
		const size_type n = pos - start;
		if (finish != end_of_storage) {
			if (pos == end()) {
				data_allocator::construct(leestl::address_of(*finish), value);
				++finish;
			} else {
				const auto _pos = begin() + (pos - cbegin());
				auto       value_copy = value;
				_insert_aux(_pos, leestl::move(value_copy));
			}
		} else _realloc_insert(begin() + (pos - cbegin()), value);

		return iterator(start + n);
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::erase(const_iterator _pos) {
		if (_pos + 1 != end()) leestl::move(_pos + 1, end(), _pos);
		--finish;
		leestl::destory(leestl::address_of(*finish));
		return iterator(_pos);
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::erase(const_iterator _first, const_iterator _last) {
		if (_first != _last) {
			if (_last != end()) leestl::move(_last, end(), _first);
			_erase_at_end(start + (end() - _last));
		}
		return iterator(_first);
	}

}    // namespace leestl

#endif

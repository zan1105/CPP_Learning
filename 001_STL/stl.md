# c++ STL 学习笔记

## 1. STL 简介

STL（Standard Template Library）是 C++标准模板库，是一种基于泛型编程的软件库。STL 是由 Alexander Stepanov 和 Meng Lee 于 1994 年在 HP 实验室开发的。STL 的目的是提供一些模板类和函数，这些模板类和函数可以实现常用的数据结构和算法，如链表、栈、队列、排序、查找等。STL 的设计是基于泛型编程的，所以 STL 的很多组件都是通过模板类和函数实现的，这样就可以实现代码的重用。

STL 主要包括以下几个组件：

-   配置器（Allocators）：配置器是用来分配和释放内存的，STL 提供了很多种配置器，如 alloc、allocator 等。
-   迭代器（Iterators）：迭代器是用来遍历容器中的数据的，STL 提供了很多种迭代器，如 input iterator、output iterator、forward iterator、bidirectional iterator、random access iterator 等。
-   容器（Containers）：容器是用来存放数据的，STL 提供了很多种容器，如 vector、list、deque、set、map 等。
-   算法（Algorithms）：算法是用来操作容器中的数据的，STL 提供了很多种算法，如 sort、find、copy、for_each 等。
-   仿函数（Functors）：仿函数是一种行为类似函数的对象，STL 提供了很多种仿函数，如 plus、minus、multiplies、divides 等。
-   适配器（Adapters）：适配器是用来适配容器和算法的，STL 提供了很多种适配器，如 stack、queue、priority_queue 等。

## 2. STL 配置器

```cpp
template <typename T>
class allocator {
public:
	typedef T value_type;// 配置器管理的数据类型
	typedef T* pointer;// 配置器管理的数据类型的指针
	typedef const T* const_pointer;// 配置器管理的数据类型的常量指针
	typedef T& reference;// 配置器管理的数据类型的引用
	typedef const T& const_reference;// 配置器管理的数据类型的常量引用
	typedef size_t size_type;// 无符号整型，可以分配内存的大小
	typedef ptrdiff_t difference_type;// 整型，两元素之间的距离

	pointer address(reference val) const;// 获取指定元素的地址
	pointer allocate(size_type n);// 分配内存
	void deallocate(pointer p, size_type n);// 释放内存
	void construct(pointer p, const T& value);// 在地址 p 处构造对象
	void destroy(pointer p);// 析构对象，不释放内存
};
```

## 3. STL 迭代器

```cpp
template <typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*, typename Reference = T&>
struct iterator {
	typedef Category iterator_category;// 迭代器类型，如 input iterator、output iterator、forward iterator、bidirectional iterator、random access iterator，设置不同类型是为了触发重载
	typedef T value_type;// 迭代器服务的数据类型
	typedef Distance difference_type;// 两个迭代器之间的距离
	typedef Pointer pointer;// 迭代器服务的数据类型的指针
	typedef Reference reference;// 迭代器服务的数据类型的引用
};
```

traits 类型获取: 通过 traits 可以获取迭代器的类型（包括原始类型，例如原始指针）信息，主要解决数据类型（例如函数返回值类型）等无法直接获取的问题。

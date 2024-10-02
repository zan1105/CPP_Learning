/**
 * @file vector.cpp
 * @author zanzan lee (leezanzan@outlook.com)
 * @brief leestl::vector 测试程序
 * @version 0.1
 * @date 2024-08-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <vector>

#include "../LeeSTL/vector.h"

template <
    typename Vec,
    typename = std::enable_if_t<
        std::is_same_v<Vec, leestl::vector<typename Vec::value_type>> ||
        std::is_same_v<Vec, std::vector<typename Vec::value_type>>>>
std::ostream &operator<<(std::ostream &os, const Vec &v) {
	for (auto &i : v) { os << i << " "; }
	os << std::endl;
	return os;
}

using std::cout;
using std::endl;

template <typename T>
void rcout(leestl::vector<T> &v) {
	for (auto it = v.rbegin(); it != v.rend(); ++it) { cout << *it << " "; }
	cout << endl;
}

int main() {
	cout << "\n[===================================================================]\n";
	cout << "[---------------------- vector test start ---------------------->\n";
	cout << "[------------------- API test start------------------->\n";
	leestl::vector<int> v1, v2(10), v3(10, 5);
	leestl::vector<int> v4 = {41, 42, 43, 44, 45};
	leestl::vector<int> v5(v4.begin(), v4.end()), v6(v3);
	leestl::vector<int> v7, v8(leestl::move(v4)), v9, v10;
	v7 = v4;
	v9 = {91, 92, 93, 94, 95};
	cout << "v1: " << v1;
	cout << "v2: " << v2;
	cout << "v3: " << v3;
	cout << "v4: " << v4;
	cout << "v5: " << v5;
	cout << "v6: " << v6;
	cout << "v7: " << v7;
	cout << "v8: " << v8;
	cout << "v9: " << v9;

	v10 = leestl::move(v9);    // 移动赋值实现了对象移动
	cout << "v9: " << v9;
	cout << "v10: " << v10;

	leestl::vector<int> v11(leestl::move(v10));    // 移动构造使用默认构造函数，并未进行移动
	cout << "v10: " << v10;
	cout << "v11: " << v11;

	cout << "v4-reverse_iterator: ";
	rcout(v4);

	cout << ">------------------- API test end -------------------]\n";

	cout << ">---------------------- vector test end ----------------------]\n";
	return 0;
}
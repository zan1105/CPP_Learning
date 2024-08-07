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
	leestl::vector<int> v4 = {1, 2, 3, 4, 5};
	leestl::vector<int> v5(v4.begin(), v4.end()), v6(v3);

	cout << "v1: " << v1;
	cout << "v2: " << v2;
	cout << "v3: " << v3;
	cout << "v4: " << v4;
	cout << "v5: " << v5;
	cout << "v6: " << v6;
	cout << "v4.size(): " << v4.size() << endl;
	cout << "v4.max_size(): " << v4.max_size() << endl;
	cout << "v4.capacity(): " << v4.capacity() << endl;
	cout << "v4.empty(): " << v4.empty() << endl;
	cout << "v1.empty(): " << v1.empty() << endl;
	cout << "v4-reverse_iterator: ";
	rcout(v4);

	cout << ">------------------- API test end -------------------]\n";

	cout << ">---------------------- vector test end ----------------------]\n";
	return 0;
}
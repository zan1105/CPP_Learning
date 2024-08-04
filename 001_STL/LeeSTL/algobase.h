/** @file algobase.h
 * 	这个文件实现 stl 基础算法
 */

#ifndef _LEESTL_ALGOBASE_H_
#define _LEESTL_ALGOBASE_H_

namespace leestl {

	/**
	 * @brief 取二者中较大者，两者相等取第一个参数
	 *
	 * @tparam T 要比较的对象类型
	 * @param a 类型为 T 的第一个对象
	 * @param b 类型为 T 的第二个对象
	 * @return T& 较大对象的引用
	 */
	template <typename T>
	constexpr inline const T &max(const T &a, const T &b) {
		return b > a ? b : a;
	}

	/**
	 * @brief  取二者中较大者，两者相等取第一个参数
	 *
	 * @tparam T 要比较的对象类型
	 * @tparam Compare 比较两个 T 类型对象的仿函数
	 * @param a 类型为 T 的第一个对象
	 * @param b 类型为 T 的第二个对象
	 * @param comp
	 * @return constexpr const T& 较大对象的引用
	 */
	template <typename T, typename Compare>
	constexpr inline const T &max(const T &a, const T &b, Compare comp) {
		return comp(a, b) ? b : a;
	}

	/**
	 * @brief 取二者中较小者，两者相等取第一个参数
	 *
	 * @tparam T 要比较的对象类型
	 * @param a 类型为 T 的第一个对象
	 * @param b 类型为 T 的第二个对象
	 * @return T& 较小对象的引用
	 */
	template <typename T>
	constexpr inline const T &min(const T &a, const T &b) {
		return b < a ? b : a;
	}

	/**
	 * @brief  取二者中较小者，两者相等取第一个参数
	 *
	 * @tparam T 要比较的对象类型
	 * @tparam Compare 比较两个 T 类型对象的仿函数
	 * @param a 类型为 T 的第一个对象
	 * @param b 类型为 T 的第二个对象
	 * @param comp
	 * @return constexpr const T& 较小对象的引用
	 */
	template <typename T, typename Compare>
	constexpr inline const T &min(const T &a, const T &b, Compare comp) {
		return comp(a, b) ? b : a;
	}

}    // namespace leestl

#endif

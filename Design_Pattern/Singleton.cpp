/**
 * @file Singleton.cpp
 * @author Lee ZanZan (leezanzan@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-10-02
 *
 * 单例模式（Singleton Pattern）确保一个类只有一个实例，并提供一个全局访问点。
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Singleton {
private:
	Singleton() {}
	Singleton(const Singleton &) = delete;
	static Singleton *instance;
	// atomic<Singleton *> instance;// 解决指令重排的对象指针
	// mutex               mtx; // 解决线程安全的锁

public:
	// 线程不安全
	static Singleton *getInstance() {
		if (instance == nullptr) { instance = new Singleton(); }
		return instance;
	}

	// 线程安全，高代价锁
	// static Singleton *getInstance() {
	// 	lock_guard<mutex> lock(mtx);
	// 	if (instance == nullptr) { instance = new Singleton(); }
	// 	return instance;
	// }

	// 线程安全 - 双检查锁，但由于指令重排可能会出现问题
	// static Singleton *getInstance() {
	// 	if (instance == nullptr) {
	// 		lock_guard<mutex> lock(mtx);
	// 		if (instance == nullptr) { instance = new Singleton(); }
	// 	}

	// 线程安全 - 双检查锁，解决指令重排问题
	// static Singleton *getInstance() {
	// 	Singleton *tmp = instance.load(memory_order_relaxed);// 读取instance的值
	// 	atomic_thread_fence(memory_order_acquire);// 获取内存屏障
	// 	if (tmp == nullptr) {
	// 		lock_guard<mutex> lock(mtx);// 加锁
	// 		tmp = instance.load(memory_order_relaxed);// 读取instance的值
	// 		if (tmp == nullptr) {
	// 			tmp = new Singleton();
	// 			atomic_thread_fence(memory_order_release);// 释放内存屏障
	// 			instance.store(tmp, memory_order_relaxed);// 写入instance的值
	// 		}
	// 	}
	// 	return tmp;
	// }
};

Singleton *Singleton::instance = nullptr;
// atomic<Singleton *> Singleton::instance;
// mutex      Singleton::mtx;

int main() {
	Singleton *singleton1 = Singleton::getInstance();
	Singleton *singleton2 = Singleton::getInstance();
	cout << singleton1 << endl;
	cout << singleton2 << endl;
	return 0;
}
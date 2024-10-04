/**
 * @file Proxy.cpp
 * @author Lee ZanZan (leezanzan@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-10-02
 *
 * 代理模式（Proxy Pattern）为其他对象提供一种代理以控制对这个对象的访问。
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

// 共同接口
class Subject {
public:
	virtual void request() = 0;
};

// 真实主体
class RealSubject : public Subject {
public:
	void request() { cout << "RealSubject::request()" << endl; }
};

// 保存一个引用使得代理可以访问实体，并提供一个与Subject接口相同的接口，这样代理就可以用来替代实体
class Proxy : public Subject {
private:
	RealSubject *realSubject;

public:
	Proxy() { realSubject = new RealSubject(); }

	void request() {
		cout << "Proxy::request()" << endl;
		realSubject->request();
	}
};

int main() {
	Subject *subject = new Proxy();
	subject->request();

	return 0;
}

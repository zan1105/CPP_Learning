/**
 * @file Adapter.cpp
 * @author Lee ZanZan (leezanzan@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-10-02
 *
 * 适配器模式（Adapter Pattern）将一个类的接口转换成客户希望的另外一个接口。
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

// 目标接口
class Target {
public:
	virtual void request() = 0;
};

// 适配者接口
class Adaptee {
public:
	void specificRequest() { cout << "Adaptee::specificRequest()" << endl; }
};

// 适配器
class Adapter : public Target {
private:
	Adaptee *adaptee;

public:
	Adapter(Adaptee *adaptee) : adaptee(adaptee) {}
	void request() override { adaptee->specificRequest(); }
};

int main() {
	Target *target = new Adapter(new Adaptee());
	target->request();

	return 0;
}

/**
 * @file Flyweight.cpp
 * @author Lee ZanZan (leezanzan@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-10-02
 *
 * 享元模式（Flyweight Pattern）运用共享技术有效地支持大量细粒度的对象。
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Flyweight {
public:
	virtual void operation() = 0;
};

class ConcreteFlyweight : public Flyweight {
public:
	void operation() { cout << "ConcreteFlyweight::operation()" << endl; }
};

class FlyweightFactory {
private:
	map<string, Flyweight*> flyweights;

public:
	Flyweight* getFlyweight(string key) {
		if (flyweights.find(key) == flyweights.end()) { flyweights[key] = new ConcreteFlyweight(); }
		return flyweights[key];
	}
};

int main() {
	cout << "Flyweight Pattern" << endl;
	FlyweightFactory factory;
	Flyweight*       flyweight = factory.getFlyweight("key");
	flyweight->operation();

	return 0;
}

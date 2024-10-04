/**
 * @file Observer.cpp
 * @author Lee ZanZan (leezanzan@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-10-02
 *
 * 观察者模式（Observer Pattern）定义对象间的一种一对多的依赖关系
 * 当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并被自动更新。
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Subscriber {
public:
	virtual void update() = 0;
};

class Publisher {
protected:
	list<Subscriber*> subscribers;

public:
	virtual void addSubscriber(Subscriber* subscriber) = 0;
	virtual void removeSubscriber(Subscriber* subscriber) = 0;
	virtual void notify() = 0;
};

class ConcretePublisher : public Publisher {
public:
	void addSubscriber(Subscriber* subscriber) { subscribers.push_back(subscriber); }

	void removeSubscriber(Subscriber* subscriber) { subscribers.remove(subscriber); }

	void notify() {
		cout << "ConcretePublisher::notify()" << endl;
		for (auto subscriber : subscribers) { subscriber->update(); }
	}
};

class ConcreteSubscriber : public Subscriber {
public:
	void update() { cout << "ConcreteSubscriber::update()" << endl; }
};

int main() {
	cout << "Observer Pattern" << endl;
	ConcretePublisher  publisher;
	ConcreteSubscriber subscriber;

	publisher.addSubscriber(&subscriber);
	publisher.notify();

	return 0;
}

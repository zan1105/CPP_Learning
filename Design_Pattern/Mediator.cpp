/**
 * @file Mediator.cpp
 * @author Lee ZanZan (leezanzan@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-10-02
 *
 * 中介者模式（Mediator Pattern）定义一个中介对象来封装一系列对象之间的交互，
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Mediator;

class Colleague {
protected:
	Mediator *mediator;

public:
	Colleague(Mediator *mediator) : mediator(mediator) {}
	virtual void send(string message) = 0;
	virtual void receive(string message) = 0;
};

class ConcreteColleagueA : public Colleague {
public:
	ConcreteColleagueA(Mediator *mediator) : Colleague(mediator) {}
	void send(string message) override;
	void receive(string message) override {
		cout << "ConcreteColleagueA::receive() " << message << endl;
	}
};

class ConcreteColleagueB : public Colleague {
public:
	ConcreteColleagueB(Mediator *mediator) : Colleague(mediator) {}
	void send(string message) override;
	void receive(string message) override {
		cout << "ConcreteColleagueB::receive() " << message << endl;
	}
};

class Mediator {
protected:
	Colleague *colleagueA;
	Colleague *colleagueB;

public:
	virtual void send(string message, Colleague *colleague) = 0;
	virtual void setColleagueA(Colleague *colleague) = 0;
	virtual void setColleagueB(Colleague *colleague) = 0;
};

class ConcreteMediator : public Mediator {
public:
	void send(string message, Colleague *colleague) override {
		if (colleague == colleagueA) {
			colleagueB->receive(message);
		} else {
			colleagueA->receive(message);
		}
	}

	void setColleagueA(Colleague *colleague) override { colleagueA = colleague; }
	void setColleagueB(Colleague *colleague) override { colleagueB = colleague; }
};

void ConcreteColleagueA::send(string message) {
	mediator->send(message, this);
}
void ConcreteColleagueB::send(string message) {
	mediator->send(message, this);
}

int main() {
	cout << "Mediator Pattern" << endl;
	Mediator  *mediator = new ConcreteMediator();
	Colleague *colleagueA = new ConcreteColleagueA(mediator);
	Colleague *colleagueB = new ConcreteColleagueB(mediator);

	mediator->setColleagueA(colleagueA);
	mediator->setColleagueB(colleagueB);

	colleagueA->send("Hello, I'm A.");
	colleagueB->send("Hello, I'm B.");

	return 0;
}

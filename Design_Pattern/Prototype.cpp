/**
 * @file Prototype.cpp
 * @author Lee ZanZan (leezanzan@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-10-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Prototype {
public:
	virtual Prototype *clone() = 0;
	virtual void       show() = 0;
};

class ConcretePrototypeA : public Prototype {
public:
	Prototype *clone() { return new ConcretePrototypeA(*this); }
	void       show() { cout << "ConcretePrototypeA::show()" << endl; }
};

class ConcretePrototypeB : public Prototype {
public:
	Prototype *clone() { return new ConcretePrototypeB(*this); }
	void       show() { cout << "ConcretePrototypeB::show()" << endl; }
};

int main() {
	Prototype *prototypeA = new ConcretePrototypeA();
	Prototype *prototypeB = new ConcretePrototypeB();

	Prototype *cloneA = prototypeA->clone();
	Prototype *cloneB = prototypeB->clone();

	cloneA->show();
	cloneB->show();

	delete prototypeA;
	delete prototypeB;
	delete cloneA;
	delete cloneB;

	return 0;
}
/**
 * @file Bridge.cpp
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

class Implementor {
public:
	virtual void operation() = 0;
};

class ConcreteImplementorA : public Implementor {
public:
	void operation() { cout << "ConcreteImplementorA::operation()" << endl; }
};

class ConcreteImplementorB : public Implementor {
public:
	void operation() { cout << "ConcreteImplementorB::operation()" << endl; }
};

class Abstraction {
protected:
	Implementor *implementor;

public:
	Abstraction(Implementor *implementor) : implementor(implementor) {}
	virtual void operation() = 0;
};

class RefinedAbstraction : public Abstraction {
public:
	RefinedAbstraction(Implementor *implementor) : Abstraction(implementor) {}
	void operation() { implementor->operation(); }
};

int main() {
	Implementor *implementorA = new ConcreteImplementorA();
	Implementor *implementorB = new ConcreteImplementorB();

	Abstraction *abstractionA = new RefinedAbstraction(implementorA);
	Abstraction *abstractionB = new RefinedAbstraction(implementorB);

	abstractionA->operation();
	abstractionB->operation();

	delete implementorA;
	delete implementorB;
	delete abstractionA;
	delete abstractionB;

	return 0;
}
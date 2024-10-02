/**
 * @file Decorator.cpp
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

class Component {
public:
	virtual void operation1() = 0;
	virtual void operation2() = 0;
	virtual void operation3() = 0;
};

class ConcreteComponent : public Component {
public:
	void operation1() { cout << "ConcreteComponent::operation1()" << endl; }
	void operation2() { cout << "ConcreteComponent::operation2()" << endl; }
	void operation3() { cout << "ConcreteComponent::operation3()" << endl; }
};

class Decorator : public Component {
protected:
	Component *component;

public:
	Decorator(Component *component) : component(component) {}
	virtual void operation1() override { component->operation1(); }
	virtual void operation2() override { component->operation2(); }
	virtual void operation3() override { component->operation3(); }
};

class ConcreteDecoratorA : public Decorator {
public:
	ConcreteDecoratorA(Component *component) : Decorator(component) {}
	void operation1() override {
		Decorator::operation1();
		cout << "ConcreteDecoratorA::operation1()" << endl;
	}
	void operation2() override {
		Decorator::operation2();
		cout << "ConcreteDecoratorA::operation2()" << endl;
	}
	void operation3() override {
		Decorator::operation3();
		cout << "ConcreteDecoratorA::operation3()" << endl;
	}
};

class ConcreteDecoratorB : public Decorator {
public:
	ConcreteDecoratorB(Component *component) : Decorator(component) {}
	void operation1() override {
		Decorator::operation1();
		cout << "ConcreteDecoratorB::operation1()" << endl;
	}
	void operation2() override {
		Decorator::operation2();
		cout << "ConcreteDecoratorB::operation2()" << endl;
	}
	void operation3() override {
		Decorator::operation3();
		cout << "ConcreteDecoratorB::operation3()" << endl;
	}
};

int main() {
	Component *component = new ConcreteComponent();
	Decorator *decoratorA = new ConcreteDecoratorA(component);
	Decorator *decoratorB = new ConcreteDecoratorB(decoratorA);

	decoratorB->operation1();
	decoratorB->operation2();
	decoratorB->operation3();

	return 0;
}

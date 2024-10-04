/**
 * @file State.cpp
 * @author Lee ZanZan (leezanzan@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-10-02
 *
 * 状态模式（State Pattern）允许一个对象在其内部状态改变时改变它的行为，
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Context;

class State {
public:
	virtual void handle(Context *context) = 0;
};

class ConcreteStateA : public State {
public:
	void handle(Context *context) override;
};

class ConcreteStateB : public State {
public:
	void handle(Context *context) override;
};

class Context {
private:
	State *state;

public:
	Context(State *state) : state(state) {}
	void setState(State *state) { this->state = state; }
	void request() { state->handle(this); }
};

void ConcreteStateA::handle(Context *context) {
	cout << "ConcreteStateA::handle()" << endl;
	context->setState(new ConcreteStateB());
}

void ConcreteStateB::handle(Context *context) {
	cout << "ConcreteStateB::handle()" << endl;
	context->setState(new ConcreteStateA());
}

int main() {
	Context *context = new Context(new ConcreteStateA());
	context->request();
	context->request();
	context->request();
	context->request();

	delete context;

	return 0;
}

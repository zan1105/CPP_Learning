/**
 * @file Memento.cpp
 * @author Lee ZanZan (leezanzan@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-10-02
 *
 * 备忘录模式（Memento
 * Pattern）在不破坏封装性的前提下，捕获一个对象的内部状态，并在对象之外保存这个状态。
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Memento {
public:
	Memento() = default;
	Memento(const string& state) : state(state) {}
	string getState() const { return state; }

private:
	string state;
};

// 目标对象
class Originator {
public:
	void   setState(const string& state) { this->state = state; }
	string getState() const { return state; }
	// ...

	Memento createMemento() { return Memento(state); }
	void    restoreMemento(const Memento& memento) { state = memento.getState(); }

private:
	string state;
	// ...
};

class Caretaker {
public:
	void    setMemento(const Memento& memento) { this->memento = memento; }
	Memento getMemento() const { return memento; }

private:
	Memento memento;
};

int main() {
	Originator originator;
	Caretaker  caretaker;

	originator.setState("state1");
	cout << "Current state: " << originator.getState() << endl;

	caretaker.setMemento(originator.createMemento());    // 保存状态到备忘录

	// 修改状态
	originator.setState("state2");
	cout << "Current state: " << originator.getState() << endl;

	// 恢复状态
	originator.restoreMemento(caretaker.getMemento());
	cout << "Current state: " << originator.getState() << endl;

	return 0;
}

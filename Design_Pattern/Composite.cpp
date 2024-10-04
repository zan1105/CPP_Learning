/**
 * @file Composite.cpp
 * @author Lee ZanZan (leezanzan@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-10-02
 *
 * 组合模式（Composite Pattern）将对象组合成树形结构以表示“部分-整体”的层次结构。
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Component {
public:
	virtual void operation(int n = 0) = 0;
};

class Leaf : public Component {
	string name;

public:
	Leaf(string name) : name(name) {}
	void operation(int n = 0) override {
		for (int i = 0; i < n; i++) cout << "\t";    // 无其他作用，仅更改输出格式
		cout << name << "::operation()" << endl;
	}
};

class Composite : public Component {
private:
	list<Component *> children;
	string            name;

public:
	Composite(string name) : name(name) {}

	void add(Component *component) { children.push_back(component); }

	void remove(Component *component) { children.remove(component); }

	void operation(int n = 0) override {
		for (int i = 0; i < n; i++) cout << "\t";    // 无其他作用，仅更改输出格式
		cout << name << "::operation()" << endl;
		for (auto child : children) { child->operation(n + 1); }
	}
};

int main() {
	Composite root("root");
	Leaf      leaf1("leaf1"), leaf2("leaf2");
	Composite composite("node1");
	Leaf      leaf3("leaf3");

	root.add(&leaf1);
	root.add(&leaf2);
	root.add(&composite);
	composite.add(&leaf3);

	root.operation();

	return 0;
}

/**
 * @file Decorator.cpp
 * @author Lee ZanZan (leezanzan@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-10-02
 *
 * 装饰器模式（Decorator Pattern）动态地给一个对象添加一些额外的职责。
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

// 对象接口
class Component {
public:
	virtual void operation() = 0;
};

// 具体对象
class ConcreteComponent : public Component {
public:
	void operation() {
		cout << "\t\t具体对象操作开始" << endl;
		cout << "\t\t\t执行原有功能***执行旧功能" << endl;
		cout << "\t\t具体对象操作结束" << endl;
	}
};

// 装饰器，接口和 Component 一致，保持一个 Component 对象的引用
class Decorator : public Component {
protected:
	Component *component;

public:
	Decorator(Component *component) : component(component) {}
	virtual void operation() override { component->operation(); }
};

// 具体装饰器，给 Component 添加额外的职责
class ConcreteDecoratorA : public Decorator {
public:
	ConcreteDecoratorA(Component *component) : Decorator(component) {}
	void operation() override {
		cout << "\t装饰器 A 操作开始" << endl;
		cout << "\t\t执行 A 的新功能********扩展新功能" << endl;
		Decorator::operation();
		cout << "\t装饰器 A 操作结束" << endl;
	}
};

// 具体装饰器，给 Component 添加额外的职责
class ConcreteDecoratorB : public Decorator {
public:
	ConcreteDecoratorB(Component *component) : Decorator(component) {}
	void operation() override {
		cout << "装饰器 B 操作开始" << endl;
		Decorator::operation();
		cout << "\t执行 B 的新功能****************扩展新功能" << endl;
		cout << "装饰器 B 操作结束" << endl;
	}
};

int main() {
	cout << "--------------- Decorator Pattern ---------------" << endl;
	Component *component = new ConcreteComponent();
	Decorator *decoratorA =
	    new ConcreteDecoratorA(component);    // 在 ConcreteComponent 上添加新功能 A
	Decorator *decoratorB =
	    new ConcreteDecoratorB(decoratorA);    // 在 ConcreteDecoratorA 上添加新功能 B

	decoratorB->operation();

	delete decoratorB;
	delete decoratorA;
	delete component;

	cout << "--------------- Decorator Pattern ---------------" << endl;

	return 0;
}

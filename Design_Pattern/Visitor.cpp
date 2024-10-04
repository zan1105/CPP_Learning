/**
 * @file Visitor.cpp
 * @author Lee ZanZan (leezanzan@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-10-04
 *
 * 访问者模式（Visitor Pattern）是一种行为型设计模式，它能将算法与其所作用的对象分离开来。
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

class ConcreteElementA;

class ConcreteElementB;

class Visitor {
public:
	virtual void VisitConcreteElementA(ConcreteElementA* concreteElementA) = 0;
	virtual void VisitConcreteElementB(ConcreteElementB* concreteElementB) = 0;
};

class Element {
public:
	virtual void Accept(Visitor* visitor) = 0;
};

// 具体要操作的对象 A
class ConcreteElementA : public Element {
public:
	void Accept(Visitor* visitor) override { visitor->VisitConcreteElementA(this); }
	void OperationA() { cout << "ConcreteElementA::OperationA()" << endl; }
};

// 具体要操作的对象 B
class ConcreteElementB : public Element {
public:
	void Accept(Visitor* visitor) override { visitor->VisitConcreteElementB(this); }
	void OperationB() { cout << "ConcreteElementB::OperationB()" << endl; }
};

// 具体的访问者对所有目标对象进行操作
class ConcreteVisitor1 : public Visitor {
public:
	// 对目标对象 A 进行操作
	void VisitConcreteElementA(ConcreteElementA* concreteElementA) override {
		cout << "ConcreteVisitor1::VisitConcreteElementA()" << endl;
		concreteElementA->OperationA();
	}

	// 对目标对象 B 进行操作
	void VisitConcreteElementB(ConcreteElementB* concreteElementB) override {
		cout << "ConcreteVisitor1::VisitConcreteElementB()" << endl;
		concreteElementB->OperationB();
	}
};

// 对已有对象新增操作，通过创建新的访问者类来实现
class ConcreteVisitor2 : public Visitor {
public:
	void VisitConcreteElementA(ConcreteElementA* concreteElementA) override {
		cout << "ConcreteVisitor2::VisitConcreteElementA()" << endl;
		concreteElementA->OperationA();
	}

	void VisitConcreteElementB(ConcreteElementB* concreteElementB) override {
		cout << "ConcreteVisitor2::VisitConcreteElementB()" << endl;
		concreteElementB->OperationB();
	}
};

int main() {
	ConcreteElementA concreteElementA;
	ConcreteElementB concreteElementB;

	ConcreteVisitor1 concreteVisitor1;    // 具体的访问者
	ConcreteVisitor2 concreteVisitor2;    // 新增的访问者类

	concreteElementA.Accept(&concreteVisitor1);    // 对目标对象 A 进行原有操作
	concreteElementA.Accept(&concreteVisitor2);    // 对目标对象 A 进行新增操作

	concreteElementB.Accept(&concreteVisitor1);    // 对目标对象 B 进行原有操作
	concreteElementB.Accept(&concreteVisitor2);    // 对目标对象 B 进行新增操作

	return 0;
}
/**
 * @file Chain_of_Responsibility.cpp
 * @author Lee ZanZan (leezanzan@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-10-04
 *
 * 责任链模式（Chain of Responsibility Pattern）为请求创建一个接收者对象的链，
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Handler {
public:
	virtual void setSuccessor(Handler* successor) = 0;
	virtual void handleRequest(int request) = 0;
};

class ConcreteHandler1 : public Handler {
private:
	Handler* successor;

public:
	void setSuccessor(Handler* successor) { this->successor = successor; }

	void handleRequest(int request) {
		if (request >= 0 && request < 10) {
			cout << "Request: " << request << " is handled by ConcreteHandler1" << endl;
		} else if (successor != nullptr) {
			successor->handleRequest(request);
		}
	}
};

class ConcreteHandler2 : public Handler {
private:
	Handler* successor;

public:
	void setSuccessor(Handler* successor) { this->successor = successor; }

	void handleRequest(int request) {
		if (request >= 10 && request < 20) {
			cout << "Request: " << request << " is handled by ConcreteHandler2" << endl;
		} else if (successor != nullptr) {
			successor->handleRequest(request);
		}
	}
};

class ConcreteHandler3 : public Handler {
private:
	Handler* successor;

public:
	void setSuccessor(Handler* successor) { this->successor = successor; }

	void handleRequest(int request) {
		if (request >= 20 && request < 30) {
			cout << "Request: " << request << " is handled by ConcreteHandler3" << endl;
		} else if (successor != nullptr) {
			successor->handleRequest(request);
		}
	}
};

int main() {
	cout << "-----------Chain of Responsibility Pattern-----------" << endl;
	Handler* handler1 = new ConcreteHandler1();
	Handler* handler2 = new ConcreteHandler2();
	Handler* handler3 = new ConcreteHandler3();

	handler1->setSuccessor(handler2);
	handler2->setSuccessor(handler3);

	handler1->handleRequest(5);
	handler1->handleRequest(15);
	handler1->handleRequest(25);

	delete handler1;
	delete handler2;
	delete handler3;

	cout << "-----------Chain of Responsibility Pattern-----------" << endl;

	return 0;
}

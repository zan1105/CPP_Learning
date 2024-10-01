#include <bits/stdc++.h>
using namespace std;

class Singleton {
private:
	Singleton() {}
	static Singleton *instance;

public:
	static Singleton *getInstance() {
		if (instance == nullptr) { instance = new Singleton(); }
		return instance;
	}
};

Singleton *Singleton::instance = nullptr;

int main() {
	Singleton *singleton1 = Singleton::getInstance();
	Singleton *singleton2 = Singleton::getInstance();
	cout << singleton1 << endl;
	cout << singleton2 << endl;
	return 0;
}
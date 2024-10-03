/**
 * @file Facade.cpp
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

class CommonAPI {
public:
	virtual void operation1() = 0;
	virtual void operation2() = 0;
	virtual void operation3() = 0;
};

class WinOS : public CommonAPI {
public:
	void operation1() override { cout << "WinOS::operation1()" << endl; }
	void operation2() override { cout << "WinOS::operation2()" << endl; }
	void operation3() override { cout << "WinOS::operation3()" << endl; }
};

class MacOS : public CommonAPI {
public:
	void operation1() override { cout << "MacOS::operation1()" << endl; }
	void operation2() override { cout << "MacOS::operation2()" << endl; }
	void operation3() override { cout << "MacOS::operation3()" << endl; }
};

class AndroidOS : public CommonAPI {
public:
	void operation1() override { cout << "AndroidOS::operation1()" << endl; }
	void operation2() override { cout << "AndroidOS::operation2()" << endl; }
	void operation3() override { cout << "AndroidOS::operation3()" << endl; }
};

class Facade {
private:
	map<string, CommonAPI *> commonAPIs;
	string                   type;

public:
	Facade(string type) : type(type) {
		commonAPIs["WinOS"] = new WinOS();
		commonAPIs["MacOS"] = new MacOS();
		commonAPIs["AndroidOS"] = new AndroidOS();
	}

	void operation1() { commonAPIs[type]->operation1(); }

	void operation2() { commonAPIs[type]->operation2(); }

	void operation3() { commonAPIs[type]->operation3(); }
};

int main() {
	cout << "Facade Pattern" << endl;
	Facade facade("WinOS");
	facade.operation1();
	facade.operation2();
	facade.operation3();

	return 0;
}

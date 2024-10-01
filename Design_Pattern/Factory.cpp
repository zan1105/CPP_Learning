// 抽象工厂模式 - 智能电子产品工厂

#include <bits/stdc++.h>
using namespace std;

// 抽象产品接口
class Product {
public:
	virtual void manufacture() = 0;
};

// 具体产品类
class Phone : public Product {
public:
	void manufacture() override { std::cout << "manufacturing phone" << std::endl; };
};

class Pad : public Product {
public:
	void manufacture() override { std::cout << "manufacturing pad" << std::endl; };
};

class Laptop : public Product {
public:
	void manufacture() override { std::cout << "manufacturing laptop" << std::endl; };
};

// 抽象工厂模式的抽象工厂接口
class Factory {
public:
	virtual Phone  *createPhone() = 0;
	virtual Pad    *createPad() = 0;
	virtual Laptop *createLaptop() = 0;
};

// 抽象工厂模式的具体工厂类
class XiaomiFactory : public Factory {
public:
	Phone  *createPhone() override { return new Phone(); }
	Pad    *createPad() override { return new Pad(); }
	Laptop *createLaptop() override { return new Laptop(); }
};

class HuaweiFactory : public Factory {
public:
	Phone  *createPhone() override { return new Phone(); }
	Pad    *createPad() override { return new Pad(); }
	Laptop *createLaptop() override { return new Laptop(); }
};

// 抽象工厂模式的的客户端类
class Application {
private:
	Factory *factory;

public:
	Application(Factory *factory) : factory(factory) {}
	void    setFactory(Factory *factory) { this->factory = factory; }
	Phone  *createPhone() { return factory->createPhone(); }
	Pad    *createPad() { return factory->createPad(); }
	Laptop *createLaptop() { return factory->createLaptop(); }
};

// 工厂方法模式
class FactoryMethod {
public:
	virtual Product *createProduct() = 0;
};

class PhoneFactory : public FactoryMethod {
public:
	Product *createProduct() override { return new Phone(); }
};

class PadFactory : public FactoryMethod {
public:
	Product *createProduct() override { return new Pad(); }
};

class LaptopFactory : public FactoryMethod {
	Product *createProduct() override { return new Laptop(); }
};

int main() {
	// 抽象工厂
	Factory     *factory_mi = new XiaomiFactory(), *factory_hw = new HuaweiFactory();
	Application *app = new Application(factory_mi);
	Pad         *xiaomipad = app->createPad();
	app->setFactory(factory_hw);
	Phone *huaweiphone = app->createPhone();

	delete xiaomipad;
	delete huaweiphone;
	delete app;
	delete factory_mi;
	delete factory_hw;

	// 工厂方法
	vector<FactoryMethod *> factories;
	factories.push_back(new PhoneFactory());
	factories.push_back(new PadFactory());
	factories.push_back(new LaptopFactory());

	vector<Product *> products;
	for (auto factory : factories) {
		products.push_back(factory->createProduct());
	}

	for (auto product : products) {
		product->manufacture();
	}

	for (int i = 0; i < factories.size(); i++) {
		delete factories[i];
		delete products[i];
	}
	return 0;
}
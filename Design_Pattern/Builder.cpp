/**
 * @file Builder.cpp
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

class Product {
public:
	void AddPart(const string& part) { parts.push_back(part); }

	void Show() {
		for (auto& part : parts) { cout << part << endl; }
	}

private:
	vector<string> parts;
};

class Builder {
public:
	virtual void     BuildPartA() = 0;
	virtual void     BuildPartB() = 0;
	virtual Product* GetProduct() = 0;
};

class ConcreteBuilder1 : public Builder {
public:
	ConcreteBuilder1() { product = new Product(); }

	void BuildPartA() override { product->AddPart("PartA1"); }

	void BuildPartB() override { product->AddPart("PartB1"); }

	Product* GetProduct() override { return product; }

private:
	Product* product;
};

class ConcreteBuilder2 : public Builder {
public:
	ConcreteBuilder2() { product = new Product(); }

	void BuildPartA() override { product->AddPart("PartA2"); }

	void BuildPartB() override { product->AddPart("PartB2"); }

	Product* GetProduct() override { return product; }

private:
	Product* product;
};

class Director {
public:
	Director(Builder* builder) { this->builder = builder; }

	void Construct() {
		builder->BuildPartA();
		builder->BuildPartB();
	}

private:
	Builder* builder;
};

int main() {
	Builder* builder1 = new ConcreteBuilder1();
	Builder* builder2 = new ConcreteBuilder2();

	Director* director1 = new Director(builder1);
	Director* director2 = new Director(builder2);

	director1->Construct();
	Product* product1 = builder1->GetProduct();
	product1->Show();

	director2->Construct();
	Product* product2 = builder2->GetProduct();
	product2->Show();

	delete builder1;
	delete builder2;
	delete director1;
	delete director2;
	delete product1;
	delete product2;

	return 0;
}

/**
 * @file Iterator.cpp
 * @author Lee ZanZan (leezanzan@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-10-02
 *
 * 迭代器模式（Iterator
 * Pattern）提供一种方法顺序访问一个聚合对象中的各个元素，而又不暴露其内部的表示。
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Iterator {
public:
	virtual bool hasNext() = 0;
	virtual void next() = 0;
	virtual int  currentItem() = 0;
};

// 聚合对象
class Aggregate {
public:
	virtual Iterator *createIterator() = 0;
};

// 具体迭代器
class ConcreteIterator : public Iterator {
private:
	vector<int> *items;
	int          index;

public:
	ConcreteIterator(vector<int> *items) : items(items), index(0) {}
	bool hasNext() override { return index < items->size(); }
	void next() override { index++; }
	int  currentItem() override { return items->at(index); }
};

// 具体聚合对象
class ConcreteAggregate : public Aggregate {
private:
	vector<int> items;

public:
	Iterator *createIterator() override { return new ConcreteIterator(&items); }
	void      addItem(int item) { items.push_back(item); }
};

int main() {
	ConcreteAggregate aggregate;
	aggregate.addItem(1);
	aggregate.addItem(2);
	aggregate.addItem(3);

	Iterator *iterator = aggregate.createIterator();
	while (iterator->hasNext()) {
		cout << iterator->currentItem() << endl;
		iterator->next();
	}

	return 0;
}

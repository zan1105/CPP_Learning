/**
 * @file Interpreter.cpp
 * @author Lee ZanZan (leezanzan@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-10-04
 *
 * 解释器模式（Interpreter Pattern）提供了评估语言的语法或表达式的方式，
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Context;

// 抽象表达式
class AbstractExpression {
public:
	virtual void interpret(Context* context) = 0;
};

// 终结符表达式
class TerminalExpression : public AbstractExpression {
public:
	void interpret(Context* context) override { cout << "TerminalExpression::interpret()" << endl; }
};

// 非终结符表达式
class Nonterminal : public AbstractExpression {
public:
	void interpret(Context* context) override { cout << "Nonterminal::interpret()" << endl; }
};

class Context {
private:
	string input;
	string output;

public:
	string getInput() { return input; }
	void   setInput(string input) { this->input = input; }

	string getOutput() { return output; }
	void   setOutput(string output) { this->output = output; }
};

int main() {
	Context* context = new Context();
	context->setInput("Hello World!");

	vector<AbstractExpression*> expressions = {new Nonterminal(), new TerminalExpression()};

	for (auto expression : expressions) { expression->interpret(context); }

	return 0;
}

/**
 * @file Command.cpp
 * @author Lee ZanZan (leezanzan@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-10-04
 *
 * 命令模式（Command Pattern）将一个请求封装为一个对象，从而使你可用不同的请求对客户进行参数化；
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Command {
public:
	virtual void execute() = 0;
};

class Receiver {

public:
	void action() { cout << "Receiver::action()" << endl; }
};

// 具体命令封装成的对象
class ConcreteCommand : public Command {
private:
	Receiver *receiver;

public:
	ConcreteCommand(Receiver *receiver) : receiver(receiver) {}

	void execute() override { receiver->action(); }
};

class Invoker {
private:
	Command *command;

public:
	void setCommand(Command *command) { this->command = command; }

	void executeCommand() { command->execute(); }
};

int main() {
	Receiver        receiver;
	ConcreteCommand command(&receiver);    // 将命令和接收者绑定
	Invoker         invoker;

	invoker.setCommand(&command);    // 将命令传递给调用者
	invoker.executeCommand();

	return 0;
}
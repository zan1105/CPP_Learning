# 目录
- [目录](#目录)
- [设计原则](#设计原则)
- [设计模式](#设计模式)
	- [创建型模式](#创建型模式)
	- [结构型模式](#结构型模式)
	- [行为型模式](#行为型模式)

# 设计原则

设计原则是指在设计软件时应该遵循的一些原则，这些原则是经过大量实践总结出来的。遵循这些原则可以使得软件设计更加合理，更加易于维护和扩展。

> 1. 单一职责原则 (Single Responsibility Principle, SRP)：一个类只负责一个职责，即一个类只有一个引起它变化的原因。
> 2. 开闭原则 (Open-Closed Principle, OCP)：对扩展开放，对修改关闭。
> 3. 里氏替换原则 (Liskov Substitution Principle, LSP)：子类可以替换父类并且可以正常工作。
> 4. 依赖倒置原则 (Dependency Inversion Principle, DIP)：高层模块不应该依赖低层模块，两者都应依赖其抽象。抽象不应该依赖细节，细节应该依赖抽象。
> 5. 接口隔离原则 (Interface Segregation Principle, ISP)：对象不应依赖无关接口，类间依赖应该建立在最小的接口上。
> 6. 迪米特法则 (Law of Demeter, LoD)：一个对象应该对其他对象保持最少的了解。
> 7. 组合复用原则 (Composite Reuse Principle, CRP)：尽量使用组合/聚合的方式，而不是使用继承。

# 设计模式

设计模式是对设计原则的具体应用，使用设计模式是为了重用代码、让代码更容易被他人理解、保证代码可靠性。

## 创建型模式

创建型模式主要用于创建对象，提供了一种创建对象的最佳方式。

> 1. 工厂方法模式 (Factory Method Pattern)：定义一个创建**抽象对象**的**抽象工厂**，工厂子类实例化指定对象
> 2. 抽象工厂模式 (Abstract Factory Pattern)：提供一个创建**一系列抽象对象**的**抽象工厂**，工厂子类实例化一系列对象
> 3. 原型模式 (Prototype Pattern)：用原型实例指定创建对象的种类，并通过拷贝这些原型创建新的对象
> 4. 建造者模式 (Builder Pattern)：将一个复杂对象的构建与它的表示分离，使得同样的构建过程可以创建不同的表示
> 5. 单例模式 (Singleton Pattern)：保证一个类仅有一个实例，并提供一个访问它的全局访问点

## 结构型模式

结构型模式主要用于处理类或对象的组合。

> 1. 装饰器模式 (Decorator Pattern)：动态地给一个对象添加一些额外的职责，就扩展功能而言，装饰模式比生成子类更为灵活
> 2. 桥接模式 (Bridge Pattern)：将抽象部分与它的实现部分分离，使它们可以独立地变化
> 3. 享元模式 (Flyweight Pattern)：运用共享技术有效地支持大量细粒度的对象，使用 Map 记录创建过的对象以复用
> 4. 外观模式 (Facade Pattern)：为子系统中的一组接口提供一个一致的界面，定义一个高层接口，使子系统更易于使用
> 5. 代理模式 (Proxy Pattern)：为其他对象提供一种代理以控制对这个对象的访问，代理对象与被代理对象实现同一接口
> 6. 适配器模式 (Adapter Pattern)：将类接口转换成客户希望的接口，使得原本由于接口不兼容而不能一起工作的类可以一起工作
> 7. 组合模式 (Composite Pattern)：将对象组合成树形结构以表示"部分-整体"的层次结构，使得用户对单个对象和组合对象的使用具有一致性

## 行为型模式

行为型模式主要负责对象间的高效沟通和职责委派

> 1. 模板方法模式 (Template Method Pattern)：定义一个操作中的**算法骨架**，而将一些步骤延迟到子类中
> 2. 策略模式 (Strategy Pattern)：定义一系列算法，将每个算法封装起来，并使它们可以互相替换
> 3. 观察者模式 (Observer Pattern)：定义对象间**一对多**依赖关系，当"一"对象态变化时，"多"对象都得到通知并自动更新
> 4. 中介者模式 (Mediator Pattern)：用一个中介对象来封装一系列对象的交互，中介者使各对象不需要显式地相互引用
> 5. 状态模式 (State Pattern)：允许一个对象在其内部状态改变时改变它的行为，对象看起来似乎修改了它的类
> 6. 备忘录模式 (Memento Pattern)：在不破坏封装的前提下，捕获一个对象的内部状态，并在对象之外保存这个状态
> 7. 迭代器模式 (Iterator Pattern)：提供一种方法顺序访问一个聚合对象中的各个元素，而不暴露该对象的内部表示
> 8. 责任链模式 (Chain of Responsibility Pattern)：为解除请求的发送者和接收者之间的耦合，而使多个对象都有机会处理这个请求
> 9. 命令模式 (Command Pattern)：将一个请求封装为一个对象，从而使你可用不同的请求对客户进行参数化
> 10. 访问者模式 (Visitor Pattern)：在不改变数据结构的前提下，增加作用于一组对象元素的新功能
> 11. 解释器模式 (Interpreter Pattern)：给定一个语言，定义它的文法的一种表示，并定义一个解释器，这个解释器使用该表示来解释语言中的句子
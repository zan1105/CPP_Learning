/**
 * @file MacroVersion.cpp
 * @author @zan1105 (@lezanzan@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-11-01
 *
 * 基于宏实现C++反射
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
#include <cxxabi.h>
using namespace std;
using RReg = void (*)();    // 反射注册函数指针类型

template <typename T>
string GetTypeName() {
	int status;
	// 获取类型信息并解码
	char* demangledName = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status);
	string result = (status == 0) ? demangledName : typeid(T).name();    // 解码失败返回原始名称
	free(demangledName);                                                 // 释放内存
	return result;
}

template <>
string GetTypeName<string>() {
	return "string";
}

struct DataInfo {
	virtual ~DataInfo() = default;
	string type;      // 成员变量类型
	size_t offset;    // 成员变量偏移量
	DataInfo(string& _t, size_t _o) : type(_t), offset(_o) {}
};

struct BaseMethodInfo {
	virtual ~BaseMethodInfo() = default;
	virtual string GetParamsType() = 0;
	virtual string GetReturnType() = 0;
};

// 函数信息
template <typename ClzT, typename Ret, typename... Args>
struct MethodInfo : BaseMethodInfo {
	using FuncType = Ret (ClzT::*)(Args...);
	FuncType m_func;         // 函数指针
	size_t   paramsCount;    // 参数个数

	MethodInfo(FuncType _func, size_t _paramsCount) : m_func(_func), paramsCount(_paramsCount) {}

	string GetParamsType() {
		string paramsType = "";
		((paramsType += GetTypeName<Args>() + ", "), ...);
		paramsType = paramsType.substr(0, paramsType.size() - 2);
		return paramsType;
	}

	string GetReturnType() { return GetTypeName<Ret>(); }
};

class BaseClassInfo {
public:
	virtual ~BaseClassInfo() = default;
	virtual void   ShowDataMembers() = 0;
	virtual void   ShowMethodMembers() = 0;
	virtual void   ShowClassInfo() = 0;
	virtual size_t GetSize() const = 0;
	virtual string GetType() const = 0;
	virtual void*  Create() = 0;
};

// 类信息
template <typename ClzT>
class ClassInfo : public BaseClassInfo {
	string                                 type;           // 类型
	size_t                                 size;           // 大小
	unordered_map<string, DataInfo*>       dataInfos;      // 成员变量信息
	unordered_map<string, BaseMethodInfo*> methodInfos;    // 成员函数信息

public:
	ClassInfo() {
		type = GetTypeName<ClzT>();
		size = sizeof(ClzT);
	}

	~ClassInfo() {
		for (auto& it : dataInfos) delete it.second;
		for (auto& it : methodInfos) delete it.second;
	}

	// 添加成员变量
	void AddDataInfo(string name, string type, size_t offset) {
		cout << "AddDataInfo: " << offset << " " << type << " " << name << endl;
		dataInfos[name] = new DataInfo(type, offset);
	}

	// 添加成员函数
	template <typename Ret, typename... Args>
	void AddMethodInfo(string name, Ret (ClzT::*func)(Args...)) {
		cout << "AddMethodInfo: " << name << endl;
		methodInfos[name] = new MethodInfo<ClzT, Ret, Args...>{func, sizeof...(Args)};
	}

	// 显示数据成员
	void ShowDataMembers() {
		cout << "Data Members of " << type << ":" << endl;
		for (auto& it : dataInfos)
			cout << setw(5) << it.second->offset << setw(10) << it.second->type << setw(10)
			     << it.first << endl;
	}

	// 显示函数成员
	void ShowMethodMembers() {
		cout << "Method Members of " << type << ":" << endl;
		for (auto& it : methodInfos) {
			string tmp = it.first + "(" + it.second->GetParamsType() + ")";
			cout << left << setw(20) << tmp << " -> " << it.second->GetReturnType() << endl;
		}
	}

	// 显示类信息
	void ShowClassInfo() {
		cout << "Class Info of " << type << ":" << endl;
		ShowDataMembers();
		ShowMethodMembers();
	}

	size_t GetSize() const { return size; }    // 获取类大小
	string GetType() const { return type; }    // 获取类类型
	ClzT*  Create() { return new ClzT(); }     // 创建类对象

	// 获取成员变量值
	template <typename T>
	T& GetData(const string& name, ClzT* obj) {
		auto it = dataInfos.find(name);
		if (it != dataInfos.end()) return *(T*)((char*)obj + it->second->offset);
		else {
			cout << "GetData Error: " << name << " not found in " << type << "!" << endl;
			return T();
		}
	}

	// 设置成员变量值
	template <typename T>
	void SetData(const string& name, ClzT* obj, const T& value) {
		auto it = dataInfos.find(name);
		// 将 value 转为 name 对应的类型
		if (it != dataInfos.end()) {
			if (it->second->type == "float")
				*(float*)((char*)obj + it->second->offset) = float(value);
			else *(T*)((char*)obj + it->second->offset) = T(value);
		} else cout << "SetData Error: " << name << " not found in " << type << "!" << endl;
	}

	// 针对 string 类型的特化
	void SetData(const string& name, ClzT* obj, const char* value) {
		auto it = dataInfos.find(name);
		if (it != dataInfos.end()) {
			// 获取指向目标成员的 string 指针
			size_t offset = it->second->offset;
			*((string*)((char*)obj + offset)) = value;
		} else {
			cout << "SetData Error: " << name << " not found!" << endl;
		}
	}

	// 调用成员函数
	template <typename Ret, typename... Args>
	Ret CallFunction(const string& name, ClzT* obj, Args... args) {
		auto it = methodInfos.find(name);
		if (it != methodInfos.end()) {
			auto methodInfo = dynamic_cast<MethodInfo<ClzT, Ret, Args...>*>(it->second);
			if (methodInfo) {
				if (sizeof...(args) == methodInfo->paramsCount)
					return (obj->*(methodInfo->m_func))(args...);
				else {
					cout << "CallFunction Error: " << name << " params count not match!" << endl;
					return Ret();
				}
			} else {
				cout << "CallFunction Error: " << name << " type not match!" << endl;
				return Ret();
			}
		} else {
			cout << "CallFunction Error: " << name << " not found in " << type << "!" << endl;
			return Ret();
		}
	}
};

// 注册器单例
class Register {
	Register() = default;
	unordered_map<string, BaseClassInfo*> classInfos;

	static vector<RReg> regfuncs;    // 反射注册函数指针容器

public:
	static Register& GetInstance() {
		static Register instance;
		return instance;
	}

	static void AddRegFunc(RReg fptr) { regfuncs.push_back(fptr); }

	template <typename ClzT>
	void RegisterClass(string clz) {
		if (classInfos.find(clz) == classInfos.end()) {
			ClassInfo<ClzT>* classInfo = ClzT::GetClassInfo();
			classInfos[clz] = classInfo;
		}
	}

	void run() {
		for (auto& f : regfuncs) f();
	}

	BaseClassInfo* GetClassInfo(const string& typeName) {
		auto it = classInfos.find(typeName);
		if (it != classInfos.end()) return it->second;
		else {
			cout << "GetClassInfo Error: " << typeName << " not found!" << endl;
			return nullptr;
		}
	}
};

vector<RReg> Register::regfuncs;    // 静态成员的定义

Register& reg = Register::GetInstance();    // 获取注册器实例

// 反射宏，每个支持反射的类都要执行下列宏
// 开始生成反射代码
#define BEGIN_BODY(CLASSNAME)                                                                      \
public:                                                                                            \
	static ClassInfo<CLASSNAME>* GetClassInfo() {                                                  \
		static ClassInfo<CLASSNAME> classInfo;                                                     \
		return &classInfo;                                                                         \
	}                                                                                              \
	static void registerflection() {                                                               \
		cout << "Register Class: " << #CLASSNAME << endl;                                          \
		Register::GetInstance().RegisterClass<CLASSNAME>(#CLASSNAME);

// 数据成员注册宏
#define REGISTER_DATA_MEMBER(CLASSNAME, NAME)                                                      \
	CLASSNAME::GetClassInfo()->AddDataInfo(                                                        \
	    #NAME, GetTypeName<decltype(CLASSNAME::NAME)>(), offsetof(CLASSNAME, NAME));

// 函数成员注册宏
#define REGISTER_METHOD_MEMBER(CLASSNAME, RET, NAME, ...)                                          \
	cout << #CLASSNAME << "Register Method: " << #NAME << endl;                                    \
	CLASSNAME::GetClassInfo()->AddMethodInfo<RET, ##__VA_ARGS__>(#NAME, &CLASSNAME::NAME);

// 结束标志
#define END_BODY() }

// 调用以上宏生成的静态函数，在类外使用
#define REGISTER_REFLECTION(CLASS)                                                                 \
	static struct CLASS##_AutoReg {                                                                \
		CLASS##_AutoReg() { reg.AddRegFunc(OBJ1::registerflection); }                              \
	} CLASS##_AutoReg_Instance;

// 一个基类
class BaseObject {

public:
	virtual ~BaseObject() = default;
};

// 一个类
class OBJ1 : public BaseObject {
	int    a;
	float  b;
	string c;

public:
	OBJ1() : a(0), b(1.0), c("str") {}
	void show() { cout << setw(20) << a << setw(20) << b << setw(20) << c << endl; }
	int  getA() { return a; }
	bool SetA(int _a) {
		a = _a;
		return true;
	}
	size_t getoffsetC() { return offsetof(OBJ1, c); }

	BEGIN_BODY(OBJ1)
	REGISTER_DATA_MEMBER(OBJ1, a)
	REGISTER_DATA_MEMBER(OBJ1, b)
	REGISTER_DATA_MEMBER(OBJ1, c)
	REGISTER_METHOD_MEMBER(OBJ1, void, show)
	REGISTER_METHOD_MEMBER(OBJ1, int, getA)
	REGISTER_METHOD_MEMBER(OBJ1, bool, SetA, int)
	END_BODY()
};
REGISTER_REFLECTION(OBJ1);

int main() {
	reg.run();
	OBJ1 obj1;
	obj1.show();
	OBJ1* p = &obj1;
	// *((string*)((char*)p + 16)) = "cccccc";
	// obj1.show();
	// *((string*)((char*)p + 16)) = string("bbbbbb");
	// obj1.show();

	string str;
	while (cin >> str) {
		if (str == "q") break;
		char             op = str[0];
		BaseClassInfo*   classInfo1 = reg.GetClassInfo("OBJ1");
		ClassInfo<OBJ1>* p = dynamic_cast<ClassInfo<OBJ1>*>(classInfo1);

		switch (op) {
		case 'c': classInfo1->ShowClassInfo(); break;
		case 'd': classInfo1->ShowDataMembers(); break;
		case 'm': classInfo1->ShowMethodMembers(); break;
		case 's': p->CallFunction<void>("show", &obj1); break;
		// case 's': obj1.show(); break;
		case 'o': cout << obj1.getoffsetC() << endl; break;
		case 'r':
			if (p) {
				p->SetData("a", &obj1, 99);
				p->SetData("b", &obj1, 22.2);    // double to float
				p->SetData("c", &obj1, "CCCC");
			}
			break;
		case 'w':
			cout << "输入要设置的成员变量名: ";
			string name;
			cin >> name;
			cout << "输入要设置的成员变量值: ";
			string valuestr;
			cin >> valuestr;
			if (name == "a") {
				int value = stoi(valuestr);
				p->SetData("a", &obj1, value);
			} else if (name == "b") {
				float value = stof(valuestr);
				p->SetData("b", &obj1, value);
			} else if (name == "c") {
				p->SetData("c", &obj1, valuestr.c_str());
			}
			break;
		}
	}

	return 0;
}

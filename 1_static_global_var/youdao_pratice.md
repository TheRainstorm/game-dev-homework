## 1. 补充

**静态成员变量**：

**作用域**：

​	public：类外可以通过 class_name::static_var访问

​	private: 只能在类的函数内通过class_name::static_var访问

​	protected: 在类或子类(派生类)中通过class_name::static_var访问

**生存期**：

​	整个程序执行期间。

**语义**：

静态成员变量属于一个类而不属于任何一个对象。所有对象都可以通过类名来访问，修改。因此可以用来作为共享变量，实现一些功能如计数器等。



## 2. 

```c++
void change_variable_value_get_address(int *variable){
	*variable = xxx;
	...
}
void change_variable_value_reference(int &variable){
	variable = xxx;
	...
}
```

## 3. 
- 栈：
  - 内存地址从高地址到低地址
  -  主要用于存储函数调用时的**帧**。包含函数返回地址，实参，函数内局部变量等。
  - 编译器在编译时便可以确定。

- 堆：
  - 内存地址从低地址到高地址
  - 一般用于动态分配内存，大小编译时无法确定。
  - 分配和释放需要程序员来操作。

## 4.

变量类型      | 作用域        | 生命周期
---           | ---           | ---
局部变量      | 函数内        | 函数调用结束前
静态变量      | 函数内/单文件 | 整个程序执行期间
全局变量      | 单文件/所有   | 整个程序执行期间

## 5.

char array_str[10] = "string_char_star"；

会在编译时在静态内存区域存储一个字符串常量，array_str存储了其首地址，不可以更改。

char * str = "string_char_star"

str为一个char *类型的指针变量，因此可以赋值为不同地址(字符串常量可以用地址表示)。
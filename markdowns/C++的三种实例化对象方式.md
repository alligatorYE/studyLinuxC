# C++的三种实例化对象方式

# 一、隐式创建

```c++
int main() {
    CEmployee cEmployee1; //隐式创建并调用无参构造器
    CEmployee cEmployee2(2); //隐式创建并调用有参构造器
    return 0;
}
```

这种创建方式在进程虚拟地址空间中的栈中分配内存，它的分配和释放由系统决定，函数内局部变量的存储单元可以在栈上创建，函数执行完毕，系统会自动释放这些存储单元。

# 二、显示创建

```c++
int main() {
    CEmployee cEmployee1 = CEmployee; //显式创建并调用无参构造器
    CEmployee cEmployee2 = CEmployee(2); //显式创建并调用无参构造器
    return 0;
}
```

这种创建方式和第一种一样，在进程虚拟地址空间中的栈中分配内存，它的分配和释放由系统决定，函数内局部变量的存储单元可以在栈上创建，函数执行完毕，系统会自动释放这些存储单元。

# 三、显示new创建

```c++
int main() {
    CEmployee *cEmployee1 = new CEmployee; //显式new创建并调用无参构造器
    CEmployee *cEmployee2 = new CEmployee(2); //显式new创建并调用无参构造器
    return 0;
}
```

这种方式使用了new关键字，在堆中分配了内存，堆上的内存分配，亦称动态内存分配。程序在运行的期间用malloc申请的内存，这部分内存由程序员自己负责管理，其生存期由开发者决定:在何时分配，分配多少，并在何时用free来释放该内存。

new的注意:

- new创建类对象需要指针接收，一处初始化，多处使用
- new创建类对象使用完需delete销毁
- new创建对象直接使用堆空间，而局部不用new定义类对象则使用栈空间
- new对象指针用途广泛，比如作为函数返回值、函数参数等
- 频繁调用场合并不适合new，就像new申请和释放内存一样
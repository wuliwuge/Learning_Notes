/*
 * Data: 2023-3-09
 * 仅当自己感兴趣时，才测试
*/

#include <iostream>
#include <compare> // 用于使用三向比较运算符
// #include <format>  // 测试format模块是否可用 ，好像也不太行的样子

// import <iostream>; // 测试是否支持c++20的模组 测试了还是不支持
using namespace std;

// 定义强类型枚举，
enum class PieceType01 { King, Queen, Rook, Pawn};

// 定义弱枚举类型
enum PieceType02 { King, Queen, Rook, Pawn};

// 定义弱枚举类型
// enum PieceType03 { King, Queen, Rook, Pawn}; // 如果是弱枚举类型，它的

void test01()
{
	if (PieceType02::King == 0) cout << PieceType02::King << endl;
	if (Queen == 1) cout << Queen << endl; //
	// if (PieceType01::King == 0) cout << PieceType01::King << endl; // 对于强枚举类型，它已经不是普通的整型了

	/*
        我的理解或猜测：对于强枚举类型来说它已经是类类型的(静态)成员了。它的作用域只在这个类类型之内，
        而弱枚举，他的作用域是整个引入的文件空间，所以无法做到枚举成员可以同名，而强枚举可以做到
    */

   // 测试强枚举
   PieceType01 ob {PieceType01::King};
   if (ob == PieceType01::Queen) {
        cout << "==" << endl;
   } else {
        cout << "!=" << endl;
   }

   // 从C++20开始，可以时using enum 声明来避免枚举值得全名。
//    using enum PieceType01::King;
//    using enum PieceType01; 
    // 但是测试这两种都不行，可能当前编译器还不支持吧。

    
    /* 旧式风格的枚举 --》这是一种弱枚举
        这种枚举的值会被导出到外层的作用域，这意味着可以不通过全名来访问。
    */
   PieceType02 data {King};  // 未使用全名
   // 这意味着我们可能会和父作用域的名称产生冲突。导致编译错误
   bool ok {false};
//    enum Status {error, ok}; 

    //  ok 首先被定义为bool，然后再被定义为 enum中的成员，因此报错，所以使用旧式的枚举应当确保它独一无二，
    //  并且，这些旧式的枚举不是强类型，意味着他们不是类型安全的，总是被解释为整型 

}

// if 语句的初始化器
void test02()
{
    // C++ 允许在if语句中包括一个初始化器，eg：
    /*
        if (<initializer>; <conditonal_expression>) {
            <if_body>
        } else if (<else_if_expression>) {
            <else_if_body>
        } else {
            <else_body>
        }
    */
   int num = 10;
   if (int a {50}; a > num) {  // 尽管vscode显示错误，但是可以编译通过，且运行
        cout << a << endl;
   } else {
        cout << num << endl;
   }

   // switch 语句也有 初始化器
}

// 三向比较运算符，虽然现在还不知道它的好处是啥
void test03()
{
    /*
        strong_ordering::less   第一个操作数小于第二个
        strong_ordering::greater   第一个操作数大于第二个
        strong_ordering::equal   第一个操作数等于第二个
        还有一些其他的暂时不理解，也难得写了
    */

    int i {11};
    strong_ordering result { i <=> 0};
    if (result == strong_ordering::less) { cout << "less" << endl; }
    if (result == strong_ordering::greater) { cout << "greater" << endl; }
    if (result == strong_ordering::equal) { cout << "equal" << endl; }
}

int main()
{

	test03();
}

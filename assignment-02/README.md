# 第二节课习题

## 熟悉 Eigen 矩阵运算

设线性方程 Ax = b，在 A 为方阵的前提下，请回答以下问题:

1. 在什么条件下，x 有解且唯一?
    - 有解: 系数矩阵 A 与增广矩阵 [A b] 的秩相等，即 det(A) = det([A b])
    - 唯一: R(A) 满秩
2. 高斯消元法的原理是什么?
    - 通过初等行变换依次消除未知量，把 A 变换成上三角矩阵。
    - 从最下面一行（仅有一个未知量）开始求解，逐行回代依次求解每个未知量。
    - 参考：[高斯消元法](https://zh.wikipedia.org/wiki/%E9%AB%98%E6%96%AF%E6%B6%88%E5%8E%BB%E6%B3%95)
3. QR 分解的原理是什么?
    - A = QR，Q 为正交矩阵，R 为上三角矩阵，如果 A 是非奇异 (det(A) 不为 0)的，则限定 R 的对角线元素为正，则这个因数分解是唯一的。
    - 实际计算方法比如 Gram-Schmidt 正交化，是利用投影原理在已有正交基的基础上构造一个新的正交基。
    - 参考：[QR分解](https://zh.wikipedia.org/wiki/QR%E5%88%86%E8%A7%A3)
4. Cholesky 分解的原理是什么?
    - 指将一个正定的埃尔米特矩阵（也称自伴随矩阵，是共轭对称的方阵。埃尔米特矩阵中每一个第 i 行第 j 列的元素都与第 j 行第 i 列的元素的复共轭）分解成一个下三角矩阵（且所有对角元素均为正实数）与其共轭转置之乘积。
    - 每一个正定埃尔米特矩阵都有一个唯一的科列斯基分解。
    - 参考：[科列斯基分解](https://zh.wikipedia.org/wiki/%E7%A7%91%E5%88%97%E6%96%AF%E5%9F%BA%E5%88%86%E8%A7%A3)
5. 编程实现 A 为 100 × 100 随机矩阵时，用 QR 和 Cholesky 分解求 x 的程序。你可以参考本次课用到的 useEigen 例程。
    - 见[ex1.cpp](ex1.cpp)

## 几何运算练习

见[ex2.cpp](ex2.cpp)

## 旋转的表达

1. 见 [prove-rotation.jpg](prove-rotation.jpg)
2. 四元数实部是一维，虚部是三维
3. 见 [prove-q1.jpg](prove-q1.jpg)

## 罗德里格斯公式的证明

见 [prove-rodrigues.jpg](prove-rodrigues.jpg)

## 四元数运算性质的验证

见 [prove-q2.jpg](prove-q2.jpg)

## 熟悉 C++11

见注释：

``` cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class A {
public:
    A(const int &i) : index(i) {}

    int index = 0;
};

int main() {
    A a1(3), a2(5), a3(9);
    // 初始化列表，更加优雅的初始化方法
    vector<A> avec{a1, a2, a3};

    // 运用lambda表达式 []，用于创建并定义匿名的函数对象
    std::sort(avec.begin(), avec.end(), [](const A&a1, const A&a2) {return a1.index<a2.index;});

    // 序列 for 循环，用于遍历数组，容器，string 及由 beigin 和 end 函数定义的序列
    // auto 自动类型推导，用于在编译时从初始化表达式中推断出变量的数据类型
    for ( auto& a: avec ) cout<<a.index<<" ";
    cout<<endl;
    return 0;
}
```

//
// Created by bxh on 6/10/17.
//
/**
 * 这个文件定义方法，CppBean.cpp 具体实现方法
 * 在native_haha_lib.cpp中使用
 * */
#ifndef JNIDEMO_NATIVE_CPPBEAN_H
#define JNIDEMO_NATIVE_CPPBEAN_H


#include <string>

using namespace std;
/**
 * 似乎是 定义一个单例对象
 */
#define MCppBean  (CppBean::GetInstance())

typedef signed char Bool;
#define MPTrue          1
#define MPFalse         0

typedef unsigned char Byte;

/**
 * 定义类
 */
class CppBean {

/**
 * 声明一些方法
 */
public:
    int getcpp_int() const;

    void setcpp_int(int jb_int);

    Bool getcpp_Bool() const;

    void setcpp_Bool(Bool jb_boolean);

    Byte getcpp_byte() const;

    void setcpp_byte(Byte jb_byte);

    short getcpp_short() const;

    void setcpp_short(short jb_short);

    long getcpp_long() const;

    void setcpp_long(long jb_long);

    float getcpp_float() const;

    void setcpp_float(float jb_float);

    double getcpp_double() const;

    void setcpp_double(double jb_double);

    string getcpp_str() const;

    void setcpp_str(char *str);

    int *getcpp_intArr();

    void setcpp_intArr(int *intArr, int length);

/**
 * 似乎是单例模式？
 */
public:
    static CppBean &GetInstance() {
        static CppBean instance;
        return instance;
    }

    virtual ~CppBean();

/**
 * 似乎是构造方法
 */
private:
    CppBean();

    CppBean(const CppBean &);

    CppBean &operator=(const CppBean &);

/**
 * 声明一些变量
 * */
private:

    int cpp_int;
    Bool cpp_boolean;
    Byte cpp_byte;
    short cpp_short;
    long cpp_long;
    float cpp_float;
    double cpp_double;

    string cpp_str;
    int cpp_intArr[];

};


#endif
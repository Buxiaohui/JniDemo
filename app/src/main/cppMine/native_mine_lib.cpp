//
// Created by bxh on 6/10/17.
//

#include <jni.h>
#include "native_mine_lib.h"
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_fly_bxh_jnidemo_MainActivity_stringFromMineJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++ ,and buxiaohui ,加油！！！！";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_fly_bxh_jnidemo_MainActivity_addFromMineJNI(
        JNIEnv* env,
        jobject /* this */,
        jint x,
        jint y) {
        return  x+y;
}
extern "C"//-->extern "C"<---必须写这个,why??????? 是C++语法么？
JNIEXPORT jintArray JNICALL
Java_com_fly_bxh_jnidemo_MainActivity_intArrayFromMineJNI(
        JNIEnv* env,
        jobject /* this */,
        jintArray m_intArray) {
    jint *intArray = env->GetIntArrayElements(m_intArray,NULL);//获取数组指针
    jsize  len = env->GetArrayLength(m_intArray);//获取数组长度
    for (int i = 0; i < len; ++i) {
        *(intArray+i)+=10;//每个元素+10
    }
    env->ReleaseIntArrayElements(m_intArray,intArray,0);//释放内存
    return m_intArray;
}

/**
 * http://blog.csdn.net/heccjoel/article/details/57085351
 * C本地函数命名规则： Java_包名类名本地方法名
 * JNIEXPORT，JNICALL：是系统定义的宏，JNIEXPORT后面写函数的输出类型，JNICALL后面写函数名，实测这两个宏可写可不写。
 * JNIEnv *env： 是结构体JNINativeInterface的二级指针，重定义了大量的函数指针，这些函数指针在jni开发中很常用。
 * 可以理解为JNI的上下文环境，需要通过env调用各种接口。
 * jobject instance :调用本地函数的Java对象，在此例中就是JNIManager的实例。
 * */
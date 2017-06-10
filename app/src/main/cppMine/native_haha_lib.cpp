//
// Created by bxh on 6/10/17.
//

#include <jni.h>
#include <string>
#include "CppBean.h"
#include <android/log.h>

#define  LOG_TAG    "System.out.fromC"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern "C"
JNIEXPORT jstring JNICALL
Java_com_fly_bxh_jnidemo_jniInterface_JniInterface_stringFromMineJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++ ,and buxiaohui ,加油！！！！";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_fly_bxh_jnidemo_jniInterface_JniInterface_addFromMineJNI(
        JNIEnv *env,
        jobject /* this */,
        jint x,
        jint y) {
    return x + y;
}
extern "C"//-->extern "C"<---必须写这个,why??????? 是C++语法么？
JNIEXPORT jintArray JNICALL
Java_com_fly_bxh_jnidemo_jniInterface_JniInterface_intArrayFromMineJNI(
        JNIEnv *env,
        jobject /* this */,
        jintArray m_intArray) {
    jint *intArray = env->GetIntArrayElements(m_intArray, NULL);//获取数组指针
    jsize len = env->GetArrayLength(m_intArray);//获取数组长度
    for (int i = 0; i < len; ++i) {
        *(intArray + i) += 10;//每个元素+10
    }
    env->ReleaseIntArrayElements(m_intArray, intArray, 0);//释放内存
    return m_intArray;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_fly_bxh_jnidemo_jniInterface_JniInterface_transferData(JNIEnv *env, jobject instance, jobject bean) {

    jclass cls_bean = env->GetObjectClass(bean);//获取字节码对象

    jfieldID ids_int = env->GetStaticFieldID(cls_bean, "jb_int", "I");//获取静态字段ID对象
    jint jb_int = env->GetStaticIntField(cls_bean, ids_int);//获取相应静态字段的int值
    MCppBean.setcpp_int(jb_int);//将int值赋给CppBean中的映射值

    jfieldID id_boolean = env->GetFieldID(cls_bean, "jb_boolean", "Z");//获取非静态字段ID对象
    jboolean jb_boolean = env->GetBooleanField(bean, id_boolean);//获取相应非静态字段的boolean值
    MCppBean.setcpp_Bool(jb_boolean);//将boolean值赋给CppBean中的映射值

    jbyte jb_byte = env->GetByteField(bean, env->GetFieldID(cls_bean, "jb_byte", "B"));
    MCppBean.setcpp_byte(jb_byte);

    MCppBean.setcpp_short(env->GetShortField(bean, env->GetFieldID(cls_bean, "jb_short", "S")));

    MCppBean.setcpp_long(env->GetLongField(bean, env->GetFieldID(cls_bean, "jb_long", "J")));

    MCppBean.setcpp_float(env->GetFloatField(bean, env->GetFieldID(cls_bean, "jb_float", "F")));

    MCppBean.setcpp_double(env->GetDoubleField(bean, env->GetFieldID(cls_bean, "jb_double", "D")));

    LOGI("MCppBean中：int字段值=%d,Bool字段值=%d,Byte字段值=%d,short字段值=%hd,long字段值=%ld,float字段值=%f,double字段值=%lf",
         MCppBean.getcpp_int(), MCppBean.getcpp_Bool(), MCppBean.getcpp_byte(),
         MCppBean.getcpp_short(), MCppBean.getcpp_long(),
         MCppBean.getcpp_float(), MCppBean.getcpp_double());

    //字符串
    jfieldID ids_str = env->GetFieldID(cls_bean, "jb_str", "Ljava/lang/String;");
    jstring jb_str = (jstring) env->GetObjectField(bean, ids_str);
    char *str = (char *) env->GetStringUTFChars(jb_str, 0);
    MCppBean.setcpp_str(str);
    env->ReleaseStringUTFChars(jb_str, str);
    LOGI("MCppBean中：string字段值=%s", MCppBean.getcpp_str().c_str());

    //数组
    jfieldID ids_intArr = env->GetFieldID(cls_bean, "jb_intArr", "[I");
    jintArray jb_intArr = (jintArray) env->GetObjectField(bean, ids_intArr);
    jint *intArray = env->GetIntArrayElements(jb_intArr, NULL);
    jsize length = env->GetArrayLength(jb_intArr);
    MCppBean.setcpp_intArr(intArray, length);
    env->ReleaseIntArrayElements(jb_intArr, intArray, 0);
    for (int i = 0; i < length; i++) {
        LOGI("数组元素%d：%d", i, *(MCppBean.getcpp_intArr() + i));
    }
}
/**
 * http://blog.csdn.net/heccjoel/article/details/57085351
 * C本地函数命名规则： Java_包名类名本地方法名
 * JNIEXPORT，JNICALL：是系统定义的宏，JNIEXPORT后面写函数的输出类型，JNICALL后面写函数名，实测这两个宏可写可不写。
 * JNIEnv *env： 是结构体JNINativeInterface的二级指针，重定义了大量的函数指针，这些函数指针在jni开发中很常用。
 * 可以理解为JNI的上下文环境，需要通过env调用各种接口。
 * jobject instance :调用本地函数的Java对象，在此例中就是JNIManager的实例。
 * */
//
// Created by bxh on 6/10/17.
//

#include <jni.h>

#ifndef JNIDEMO_NATIVE_MINE_LIB_H
#define JNIDEMO_NATIVE_MINE_LIB_H

#endif //JNIDEMO_NATIVE_MINE_LIB_H
extern "C" {
JNIEXPORT void JNICALL
Java_com_fly_bxh_jnidemo_jniInterface_JniInterface_transferData(JNIEnv *env, jobject instance,
                                                             jobject bean);
}
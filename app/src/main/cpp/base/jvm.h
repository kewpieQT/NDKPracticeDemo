//
// Created by Kewpie Qin on 12/4/20.
//

#ifndef NATIVEPRACTICE_JVM_H
#define NATIVEPRACTICE_JVM_H

#include <jni.h>
#include "base.h"

void setJvm(JavaVM *jvm);

JavaVM * getJvm();


#endif //NATIVEPRACTICE_JVM_H

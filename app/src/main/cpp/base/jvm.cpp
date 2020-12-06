//
// Created by Kewpie Qin on 12/4/20.
//

#include "jvm.h"
static JavaVM *gVm= nullptr;

void setJvm(JavaVM *jvm){
    gVm = jvm;
}

JavaVM *getJvm(){
    return gVm;
}
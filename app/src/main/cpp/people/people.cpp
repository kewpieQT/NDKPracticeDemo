//
// Created by Kewpie Qin on 2020/12/2.
//

#include "people.h"

std::string people::getString() {
    return "this is from people";
}

std::string people::getStringFromCStyle(const char *str) {
    std::string s(str);
    return s;
}


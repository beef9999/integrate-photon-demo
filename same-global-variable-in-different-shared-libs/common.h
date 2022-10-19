#pragma once

#include <iostream>

class MyClass {
public:
    MyClass(int a) : a_(a) {
        printf("[%p] construct %d \n", this, a_);

    }

    ~MyClass() {
        printf("[%p] destruct %d \n", this, a_);
    }

    int a_;
};

MyClass* get_common();
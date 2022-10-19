#include "common.h"

static MyClass myClass(1);

MyClass* get_common() {
    return &myClass;
}
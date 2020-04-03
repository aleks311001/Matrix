#include <iostream>
#include "Finite.h"

int main() {
    Finite<17> x = 7;
    Finite<17> y = Finite<17>(3) / x;
    y.print();
    return 0;
}
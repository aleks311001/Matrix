#include <iostream>
#include "Rational.h"
int main() {
    /*BigInteger x;
    BigInteger y;
    x.fromString("4732785678463287564783265874627832687567824678362874675674365784365746357627846783267834657634287568734627653457623478567834265764876257864785463257864872567");
    y.fromString("2462528746567836784263578463785624783264782564237856347832678432542435432543254352435434263563478326586437867641678386473256476784637865643668746781256362784637831");

    std::cout << x + y << "\n" << x - y << "\n" << x * y << "\n" << x / y << "\n" << x % y << "\n" << x.BinaryGCD(y) << "\n";*/

    Rational x = 1;
    Rational y = 3;

    std::cout << (x/y).asDecimal(5);
    return 0;
}

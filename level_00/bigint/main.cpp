#include "bigint.hpp"

int main() 
{
    bigint a; // Default
    bigint b(123456);
    bigint c("78901234567890");
    bigint d("0000012345"); // Leading zeros
    bigint e("abc123");     // Invalid string
    bigint f(1);
    bigint xs(100);

    std::cout << "Constructors:\n";
    std::cout << "a (default): " << a << "\n";
    std::cout << "b (from int): " << b << "\n";
    std::cout << "c (from string): " << c << "\n";
    std::cout << "d (leading zeros): " << d << "\n";
    std::cout << "e (invalid string): " << e << "\n";
    std::cout << "f (from 0): " << f << "\n\n";

    // Test addition
    std::cout << "Addition:\n";
    std::cout << b << " + " << d << " = " << (b + d) << "\n";
    bigint g = c + b;
    std::cout << c << " + " << b << " = " << g << "\n";
    bigint h("999");
    std::cout << h << " + 1 = " << (h + bigint(1)) << "\n\n";

    // Test +=
    std::cout << "Operator += :\n";
    bigint x("1000");
    x += bigint("2000");
    std::cout << "1000 += 2000: " << x << "\n\n";

    // Test comparison
    std::cout << "Comparison:\n";
    std::cout << "Is " << b  << " == " << d << "? " << (b == d ? "yes" : "no") << "\n";
    std::cout << "Is " << f  << " == " << xs << "? " << (f == xs ? "yes" : "no") << "\n";
    std::cout << "Is " << b << " != " << d << "? " << (b != d ? "yes" : "no") << "\n";
    std::cout << "Is " << b << " < " << d << "? " << (b < d ? "yes" : "no") << "\n";
    std::cout << "Is " << b << " > " << d << "? " << (b > d ? "yes" : "no") << "\n";
    std::cout << "Is " << b << " <= " << d << "? " << (b <= d ? "yes" : "no") << "\n";
    std::cout << "Is " << b << " >= " << d << "? " << (b >= d ? "yes" : "no") << "\n\n";

    // Test digit left shift
    std::cout << "Digit shift left:\n";
    bigint y("12345");
    std::cout << y << " << 3 = " << (y << 3) << "\n";
    std::cout << y << " << 0 = " << (y << 0) << "\n";
    std::cout << "0 << 10 = " << (bigint(0) << 10) << "\n\n";

    // Test digit right shift
    std::cout << "Digit shift right:\n";
    std::cout << y << " >> 2 = " << (y >> 2) << "\n";
    std::cout << y << " >> 10 = " << (y >> 10) << "\n";
    std::cout << y << " >> 0 = " << (y >> 0) << "\n\n";

    // Test <<= and >>=
    std::cout << "Operator <<= and >>= :\n";
    bigint z("98765");
    z <<= 2;
    std::cout << "98765 <<= 2: " << z << "\n";
    z >>= 4;
    std::cout << "(previous result) >>= 4: " << z << "\n\n";

    // // Test <<+ and >>+
    // std::cout << "Operator <<+ and >>+ :\n";
    // bigint m("13");
    // std::cout << m << " <<+ 2: " << (m <<+ 2) << "\n";
    // std::cout << m << " >>+ 1: " << (m >>+ 1) << "\n\n";

    // Test pre-increment and post-increment
    std::cout << "Pre-increment and post-increment:\n";
    bigint w("99");
    std::cout << "Original w: " << w << "\n";
    std::cout << "w++: " << w++ << "\n";
    std::cout << "After w++: " << w << "\n";
    std::cout << "++w: " << ++w << "\n";
    std::cout << "After ++w: " << w << "\n";

    // Edge test: huge shift right
    std::cout << "\nEdge case: huge shift right\n";
    bigint edge("123456789");
    std::cout << edge << " >> 100 = " << (edge >> 100) << "\n";

    return 0;
}

#include <iostream>
#include "Rational.h"

int main() {
    std::cout << "Welcome to rational numbers class showcase" << std::endl;
    std::cout << "All denominators should be >0" << std::endl;

    Rational test1;
    Rational test2(11, 13); 
    Rational test3(1, 3);
    std::cin >> test1;
    std::cout << "\nTest1 equals " << test1;
    std::cout << "\nTest2 + Test3 equals " << test2 + test3;
    std::cout << "\nTest2 - Test3 equals " << test2 - test3;
    std::cout << "\nTest2 * Test3 equals " << test2 * test3;
    std::cout << "\nTest2 / Test3 equals " << test2 / test3;
    std::cout << "\nTest2 == Test3 equals " << (test2 == test3);
    std::cout << "\nTest2 != Test3 equals " << (test2 != test3);
    std::cout << "\nTest2 < Test3 equals " << (test2 < test3);
    std::cout << "\nTest2 > Test3 equals " << (test2 > test3);
    std::cout << "\nTest2 <= Test3 equals " << (test2 <= test3);
    std::cout << "\nTest2 >= Test3 equals " << (test2 >= test3);
    //if (test1 == test2)
    //    std::cout << "\nTest1 is equal to Test2";
    //if (test1 < test2)
    //    std::cout << "\nTest1 is less than Test2";
    return 0;
}

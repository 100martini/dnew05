#include "vect2.hpp"
#include <iostream>

int main()
{
    std::cout << "=== ORIGINAL MAIN TEST ===" << std::endl;
    
    vect2 v1;
    vect2 v2(2, 7);
    const vect2 v3(v2);
    vect2 v4 = v2;
    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v1: " << "{" << v1[0] << v1[1] << "}" << std::endl;
    std::cout << "v2: " << v2 << std::endl;
    std::cout << "v3: " << v4 << std::endl;
    std::cout << "v3: " << v4 << std::endl;
    std::cout << v4++ << std::endl;
    std::cout << ++v4 << std::endl;
    std::cout << v4-- << std::endl;
    std::cout << --v4 << std::endl;
    v2 += v3;
    v1 -= v2;
    v2 = v3 + v3 * 2;
    v2 = v3 * 2;
    v2 += v2 += v3;
    v1 *= 42;
    v1 = v1 - v1 + v1;
    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v2: " << v2 << std::endl;
    std::cout << "-v2: " << -v2 << std::endl;
    std::cout << "v1[1]: " << v1[1] << std::endl; 
    v1[1] = 12;
    std::cout << "v1[1]: " << v1[1] << std::endl; 
    std::cout << "v3[1]: " << v3[1] << std::endl; 
    std::cout << "v1 == v3 : " << (v1 == v3) << std::endl;
    std::cout << "v1 == v1 : " << (v1 == v1) << std::endl;
    std::cout << "v1 != v3 : " << (v1 != v3) << std::endl;
    std::cout << "v1 != v1 : " << (v1 != v1) << std::endl;
    
    std::cout << "\n=== CRAZY TESTS ===" << std::endl;
    
    // Test 1: Self-assignment
    std::cout << "Test 1: Self-assignment" << std::endl;
    vect2 self_test(5, 10);
    self_test = self_test;  // Should not crash
    std::cout << "self_test after self-assignment: " << self_test << std::endl;
    
    // Test 2: Chained operations
    std::cout << "\nTest 2: Chained operations" << std::endl;
    vect2 chain1(1, 2);
    vect2 chain2(3, 4);
    vect2 result = (chain1 + chain2) * 2 - vect2(1, 1);
    //(7, 11)
    std::cout << "Chained result: " << result << std::endl;
    
    // Test 3: Multiple assignments in one line
    std::cout << "\nTest 3: Multiple assignments" << std::endl;
    vect2 a, b, c;
    a = b = c = vect2(42, 24);
    std::cout << "a: " << a << " b: " << b << " c: " << c << std::endl;
    
    // Test 4: Complex compound assignments
    std::cout << "\nTest 4: Complex compound assignments" << std::endl;
    vect2 compound_test(10, 20);
    (compound_test += vect2(5, 5)) *= 2;  // Should be {30, 50}
    std::cout << "compound_test after complex compound: " << compound_test << std::endl;
    
    // Test 5: Extreme values
    std::cout << "\nTest 5: Extreme values" << std::endl;
    vect2 big(2147483647, -2147483648);  // INT_MAX, INT_MIN
    vect2 zero(0, 0);
    std::cout << "Big vector: " << big << std::endl;
    std::cout << "Zero vector: " << zero << std::endl;
    std::cout << "Big == Zero: " << (big == zero) << std::endl;
    
    // Test 6: Multiple increment/decrement
    std::cout << "\nTest 6: Multiple increment/decrement" << std::endl;
    vect2 inc_test(0, 0);
    std::cout << "Start: " << inc_test << std::endl;
    std::cout << "inc_test++: " << inc_test++ << " (inc_test now: " << inc_test << ")" << std::endl;
    std::cout << "++inc_test: " << ++inc_test << std::endl;
    std::cout << "inc_test--: " << inc_test-- << " (inc_test now: " << inc_test << ")" << std::endl;
    std::cout << "--inc_test: " << --inc_test << std::endl;
    
    // Test 7: Unary operators
    std::cout << "\nTest 7: Unary operators" << std::endl;
    vect2 unary(-5, 3);
    std::cout << "Original: " << unary << std::endl;
    std::cout << "Unary minus: " << -unary << std::endl;
    std::cout << "Unary plus: " << +unary << std::endl;
    std::cout << "Double negative: " << -(-unary) << std::endl;
    
    // Test 8: Array access edge cases
    std::cout << "\nTest 8: Array access" << std::endl;
    vect2 access_test(100, 200);
    std::cout << "access_test[0]: " << access_test[0] << " access_test[1]: " << access_test[1] << std::endl;
    access_test[0] = -999;
    access_test[1] = 999;
    std::cout << "After modification: " << access_test << std::endl;
    
    // Test 9: Const object operations
    std::cout << "\nTest 9: Const operations" << std::endl;
    const vect2 cv(7, 14);
    std::cout << "Const vector: " << cv << std::endl;
    std::cout << "cv[0]: " << cv[0] << " cv[1]: " << cv[1] << std::endl;
    vect2 result2 = cv + cv;
    std::cout << "cv + cv: " << result2 << std::endl;
    
    // Test 10: Chain of operations with temporaries
    std::cout << "\nTest 10: Temporary objects" << std::endl;
    vect2 temp_result = vect2(1, 1) + vect2(2, 2) + vect2(3, 3);
    std::cout << "Temporary chain result: " << temp_result << std::endl;
    
    // Test 11: Scalar multiplication edge cases
    std::cout << "\nTest 11: Scalar multiplication" << std::endl;
    vect2 mult_test(3, 4);
    std::cout << "mult_test * 0: " << mult_test * 0 << std::endl;
    std::cout << "mult_test * -1: " << mult_test * -1 << std::endl;
    std::cout << "0 * mult_test: " << 0 * mult_test << std::endl;
    std::cout << "-2 * mult_test: " << -2 * mult_test << std::endl;
    
    // Test 12: Complex expression
    std::cout << "\nTest 12: Complex expression" << std::endl;
    vect2 expr1(1, 2);
    vect2 expr2(3, 4);
    vect2 complex = ((expr1 * 2 + expr2) -= vect2(1, 1)) * -1;
    std::cout << "Complex expression result: " << complex << std::endl;
    
    std::cout << "\n=== ADDITIONAL EXTREME TESTS ===" << std::endl;
    
    // Test 13: Memory corruption test (array bounds)
    std::cout << "\nTest 13: Array bounds behavior" << std::endl;
    vect2 bounds_test(111, 222);
    // Note: Assignment says no bounds checking required, but let's test valid indices
    std::cout << "bounds_test[0]: " << bounds_test[0] << std::endl;
    std::cout << "bounds_test[1]: " << bounds_test[1] << std::endl;
    
    // Test 14: Overflow tests
    std::cout << "\nTest 14: Integer overflow scenarios" << std::endl;
    vect2 overflow1(2147483647, 1);  // INT_MAX
    vect2 overflow2(1, 1);
    std::cout << "Before potential overflow: " << overflow1 << std::endl;
    // This might overflow, but that's expected behavior with int
    vect2 overflow_result = overflow1 + overflow2;
    std::cout << "After potential overflow: " << overflow_result << std::endl;
    
    // Test 15: Negative multiplication stress test
    std::cout << "\nTest 15: Negative multiplication stress" << std::endl;
    vect2 neg_test(-5, 10);
    for (int i = -3; i <= 3; i++) {
        std::cout << "neg_test * " << i << " = " << neg_test * i << std::endl;
        std::cout << i << " * neg_test = " << i * neg_test << std::endl;
    }
    
    // Test 16: Rapid fire operations
    std::cout << "\nTest 16: Rapid fire operations" << std::endl;
    vect2 rapid(1, 1);
    for (int i = 0; i < 5; i++) {
        rapid += rapid;
        std::cout << "Iteration " << i << ": " << rapid << std::endl;
    }
    
    // Test 17: Assignment chain stress
    std::cout << "\nTest 17: Assignment chain stress" << std::endl;
    vect2 a1, a2, a3, a4, a5;
    a1 = a2 = a3 = a4 = a5 = vect2(99, -99);
    std::cout << "Chain result - a1:" << a1 << " a3:" << a3 << " a5:" << a5 << std::endl;
    
    // Test 18: Compound assignment chain
    std::cout << "\nTest 18: Compound assignment chain" << std::endl;
    vect2 compound(2, 3);
    std::cout << "Start: " << compound << std::endl;
    (((compound += vect2(1, 1)) *= 2) -= vect2(2, 2)) += vect2(10, 10);
    //(14, 16)
    std::cout << "After compound chain: " << compound << std::endl;
    
    // Test 19: Mixed increment/decrement chaos
    std::cout << "\nTest 19: Mixed increment/decrement" << std::endl;
    vect2 chaos(5, 5);
    std::cout << "Start: " << chaos << std::endl;
    std::cout << "chaos++: " << chaos++ << std::endl;
    std::cout << "++chaos: " << ++chaos << std::endl;
    std::cout << "chaos--: " << chaos-- << std::endl;
    std::cout << "--chaos: " << --chaos << std::endl;
    std::cout << "++(chaos++): " << ++(chaos++) << std::endl; // This should work
    
    // Test 20: Equality/inequality stress
    std::cout << "\nTest 20: Equality/inequality stress" << std::endl;
    vect2 eq1(0, 0), eq2(0, 0), eq3(0, 1), eq4(-0, 0);
    std::cout << "eq1 == eq2: " << (eq1 == eq2) << std::endl;
    std::cout << "eq1 == eq3: " << (eq1 == eq3) << std::endl;
    std::cout << "eq1 == eq4: " << (eq1 == eq4) << std::endl;  // -0 == 0
    std::cout << "eq1 != eq2: " << (eq1 != eq2) << std::endl;
    std::cout << "eq1 != eq3: " << (eq1 != eq3) << std::endl;
    
    // Test 21: Complex nested operations
    std::cout << "\nTest 21: Extremely complex nested operations" << std::endl;
    vect2 nest1(1, 2), nest2(3, 4), nest3(5, 6);
    vect2 complex_result = ((nest1 + nest2) * 2 - nest3) + (nest1 * -1) - (-nest2 + nest3);
    std::cout << "Complex nested result: " << complex_result << std::endl;
    
    // Test 22: Zero operations
    std::cout << "\nTest 22: Zero operations" << std::endl;
    vect2 zero_test(10, 20);
    std::cout << "Original: " << zero_test << std::endl;
    zero_test *= 0;
    std::cout << "After *= 0: " << zero_test << std::endl;
    zero_test += vect2(0, 0);
    std::cout << "After += {0,0}: " << zero_test << std::endl;
    zero_test -= vect2(0, 0);
    std::cout << "After -= {0,0}: " << zero_test << std::endl;
    
    // Test 23: Unary operator combinations
    std::cout << "\nTest 23: Unary operator combinations" << std::endl;
    vect2 unary_test(-3, 7);
    std::cout << "Original: " << unary_test << std::endl;
    std::cout << "-unary_test: " << -unary_test << std::endl;
    std::cout << "+unary_test: " << +unary_test << std::endl;
    std::cout << "-(+unary_test): " << -(+unary_test) << std::endl;
    std::cout << "+(-unary_test): " << +(-unary_test) << std::endl;
    std::cout << "-(-(-unary_test)): " << -(-(-unary_test)) << std::endl;
    
    // Test 24: Performance/stress test
    std::cout << "\nTest 24: Performance stress test" << std::endl;
    vect2 stress(1, 1);
    for (int i = 0; i < 1000; i++) {
        stress = stress + vect2(1, 1) - vect2(1, 1);
        if (i % 100 == 0) {
            std::cout << "Iteration " << i << ": " << stress << std::endl;
        }
    }
    
    std::cout << "\n=== ALL TESTS COMPLETED SUCCESSFULLY ===" << std::endl;
    
    return 0;
}
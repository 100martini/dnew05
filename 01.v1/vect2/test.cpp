#include "vect2.hpp"
#include <iostream>
#include <climits>
#include <cstdlib>
#include <ctime>

// Test counters
int tests_passed = 0;
int tests_failed = 0;
int total_tests = 0;

// Test macros
#define TEST(condition, test_name) \
    do { \
        total_tests++; \
        if (condition) { \
            tests_passed++; \
        } else { \
            tests_failed++; \
            std::cout << "FAILED: " << test_name << " at line " << __LINE__ << std::endl; \
        } \
    } while(0)

#define EXPECT_EQ(actual, expected, test_name) \
    TEST((actual) == (expected), test_name)

#define EXPECT_NE(actual, expected, test_name) \
    TEST((actual) != (expected), test_name)

// Helper function to create random int
int rand_int() { return rand() % 2000 - 1000; }

void test_constructors() {
    std::cout << "\n=== Testing Constructors ===" << std::endl;
    
    // Default constructor
    vect2 v1;
    TEST(v1[0] == 0 && v1[1] == 0, "Default constructor");
    
    // Parameterized constructor
    vect2 v2(5, 10);
    TEST(v2[0] == 5 && v2[1] == 10, "Parameterized constructor");
    
    // Copy constructor
    vect2 v3(v2);
    TEST(v3[0] == 5 && v3[1] == 10, "Copy constructor");
    
    // Assignment constructor
    vect2 v4 = v2;
    TEST(v4[0] == 5 && v4[1] == 10, "Assignment constructor");
    
    // Const constructor
    const vect2 v5(7, 14);
    TEST(v5[0] == 7 && v5[1] == 14, "Const constructor");
    
    for (int i = 0; i < 100; i++) {
        int x = rand_int(), y = rand_int();
        vect2 vr(x, y);
        TEST(vr[0] == x && vr[1] == y, "Random constructor test");
    }
}

void test_assignment_operator() {
    std::cout << "\n=== Testing Assignment Operator ===" << std::endl;
    
    vect2 v1(3, 4);
    vect2 v2(7, 8);
    
    // Basic assignment
    v2 = v1;
    TEST(v2[0] == 3 && v2[1] == 4, "Basic assignment");
    
    // Self assignment
    v1 = v1;
    TEST(v1[0] == 3 && v1[1] == 4, "Self assignment");
    
    // Chained assignment
    vect2 v3, v4, v5;
    v3 = v4 = v5 = vect2(10, 20);
    TEST(v3[0] == 10 && v3[1] == 20, "Chained assignment v3");
    TEST(v4[0] == 10 && v4[1] == 20, "Chained assignment v4");
    TEST(v5[0] == 10 && v5[1] == 20, "Chained assignment v5");
    
    for (int i = 0; i < 50; i++) {
        vect2 va(rand_int(), rand_int());
        vect2 vb;
        vb = va;
        TEST(vb[0] == va[0] && vb[1] == va[1], "Random assignment test");
    }
}

void test_array_access() {
    std::cout << "\n=== Testing Array Access Operator [] ===" << std::endl;
    
    vect2 v1(15, 25);
    
    // Read access
    TEST(v1[0] == 15, "Array access read [0]");
    TEST(v1[1] == 25, "Array access read [1]");
    
    // Write access
    v1[0] = 100;
    v1[1] = 200;
    TEST(v1[0] == 100, "Array access write [0]");
    TEST(v1[1] == 200, "Array access write [1]");
    
    // Const access
    const vect2 cv(30, 40);
    TEST(cv[0] == 30, "Const array access [0]");
    TEST(cv[1] == 40, "Const array access [1]");
    
    for (int i = 0; i < 50; i++) {
        int x = rand_int(), y = rand_int();
        vect2 vr(x, y);
        TEST(vr[0] == x && vr[1] == y, "Random array access test");
        
        int nx = rand_int(), ny = rand_int();
        vr[0] = nx;
        vr[1] = ny;
        TEST(vr[0] == nx && vr[1] == ny, "Random array write test");
    }
}

void test_addition() {
    std::cout << "\n=== Testing Addition Operator + ===" << std::endl;
    
    vect2 v1(2, 3);
    vect2 v2(4, 5);
    vect2 result = v1 + v2;
    
    TEST(result[0] == 6 && result[1] == 8, "Basic addition");
    
    // Addition with zero
    vect2 zero(0, 0);
    vect2 result2 = v1 + zero;
    TEST(result2[0] == 2 && result2[1] == 3, "Addition with zero");
    
    // Negative addition
    vect2 neg(-1, -2);
    vect2 result3 = v1 + neg;
    TEST(result3[0] == 1 && result3[1] == 1, "Addition with negative");
    
    // Chained addition
    vect2 result4 = v1 + v2 + vect2(1, 1);
    TEST(result4[0] == 7 && result4[1] == 9, "Chained addition");
    
    for (int i = 0; i < 100; i++) {
        int x1 = rand_int() % 1000, y1 = rand_int() % 1000;
        int x2 = rand_int() % 1000, y2 = rand_int() % 1000;
        vect2 va(x1, y1), vb(x2, y2);
        vect2 sum = va + vb;
        TEST(sum[0] == x1 + x2 && sum[1] == y1 + y2, "Random addition test");
    }
}

void test_subtraction() {
    std::cout << "\n=== Testing Subtraction Operator - ===" << std::endl;
    
    vect2 v1(10, 8);
    vect2 v2(3, 2);
    vect2 result = v1 - v2;
    
    TEST(result[0] == 7 && result[1] == 6, "Basic subtraction");
    
    // Subtraction with zero
    vect2 zero(0, 0);
    vect2 result2 = v1 - zero;
    TEST(result2[0] == 10 && result2[1] == 8, "Subtraction with zero");
    
    // Self subtraction
    vect2 result3 = v1 - v1;
    TEST(result3[0] == 0 && result3[1] == 0, "Self subtraction");
    
    for (int i = 0; i < 100; i++) {
        int x1 = rand_int() % 1000, y1 = rand_int() % 1000;
        int x2 = rand_int() % 1000, y2 = rand_int() % 1000;
        vect2 va(x1, y1), vb(x2, y2);
        vect2 diff = va - vb;
        TEST(diff[0] == x1 - x2 && diff[1] == y1 - y2, "Random subtraction test");
    }
}

void test_scalar_multiplication() {
    std::cout << "\n=== Testing Scalar Multiplication * ===" << std::endl;
    
    vect2 v1(3, 4);
    
    // Right scalar multiplication
    vect2 result1 = v1 * 2;
    TEST(result1[0] == 6 && result1[1] == 8, "Right scalar multiplication");
    
    // Left scalar multiplication
    vect2 result2 = 3 * v1;
    TEST(result2[0] == 9 && result2[1] == 12, "Left scalar multiplication");
    
    // Multiplication by zero
    vect2 result3 = v1 * 0;
    TEST(result3[0] == 0 && result3[1] == 0, "Multiplication by zero (right)");
    
    vect2 result4 = 0 * v1;
    TEST(result4[0] == 0 && result4[1] == 0, "Multiplication by zero (left)");
    
    // Multiplication by negative
    vect2 result5 = v1 * -1;
    TEST(result5[0] == -3 && result5[1] == -4, "Multiplication by -1 (right)");
    
    vect2 result6 = -2 * v1;
    TEST(result6[0] == -6 && result6[1] == -8, "Multiplication by negative (left)");
    
    for (int i = 0; i < 100; i++) {
        int x = rand_int() % 100, y = rand_int() % 100;
        int scalar = rand_int() % 10;
        vect2 v(x, y);
        
        vect2 right_mult = v * scalar;
        vect2 left_mult = scalar * v;
        
        TEST(right_mult[0] == x * scalar && right_mult[1] == y * scalar, "Random right scalar mult");
        TEST(left_mult[0] == x * scalar && left_mult[1] == y * scalar, "Random left scalar mult");
        TEST(right_mult[0] == left_mult[0] && right_mult[1] == left_mult[1], "Scalar mult commutativity");
    }
}

void test_unary_operators() {
    std::cout << "\n=== Testing Unary Operators ===" << std::endl;
    
    vect2 v1(5, -3);
    
    // Unary minus
    vect2 neg = -v1;
    TEST(neg[0] == -5 && neg[1] == 3, "Unary minus");
    
    // Unary plus
    vect2 pos = +v1;
    TEST(pos[0] == 5 && pos[1] == -3, "Unary plus");
    
    // Double negative
    vect2 double_neg = -(-v1);
    TEST(double_neg[0] == 5 && double_neg[1] == -3, "Double negative");
    
    // Mixed unary
    vect2 mixed = -(+v1);
    TEST(mixed[0] == -5 && mixed[1] == 3, "Mixed unary operators");
    
    for (int i = 0; i < 50; i++) {
        int x = rand_int(), y = rand_int();
        vect2 v(x, y);
        
        vect2 neg_v = -v;
        vect2 pos_v = +v;
        
        TEST(neg_v[0] == -x && neg_v[1] == -y, "Random unary minus");
        TEST(pos_v[0] == x && pos_v[1] == y, "Random unary plus");
    }
}

void test_equality_operators() {
    std::cout << "\n=== Testing Equality Operators == and != ===" << std::endl;
    
    vect2 v1(7, 9);
    vect2 v2(7, 9);
    vect2 v3(7, 8);
    vect2 v4(6, 9);
    
    // Equality
    TEST(v1 == v2, "Equal vectors");
    TEST(v1 == v1, "Self equality");
    TEST(!(v1 == v3), "Unequal vectors (different y)");
    TEST(!(v1 == v4), "Unequal vectors (different x)");
    
    // Inequality
    TEST(!(v1 != v2), "Equal vectors inequality");
    TEST(!(v1 != v1), "Self inequality");
    TEST(v1 != v3, "Unequal vectors inequality (different y)");
    TEST(v1 != v4, "Unequal vectors inequality (different x)");
    
    // Zero vectors
    vect2 zero1(0, 0);
    vect2 zero2(0, 0);
    TEST(zero1 == zero2, "Zero vectors equality");
    TEST(!(zero1 != zero2), "Zero vectors inequality");
    
    for (int i = 0; i < 50; i++) {
        int x = rand_int(), y = rand_int();
        vect2 v1(x, y);
        vect2 v2(x, y);
        vect2 v3(x + 1, y);
        
        TEST(v1 == v2, "Random equal vectors");
        TEST(!(v1 != v2), "Random equal vectors inequality");
        TEST(v1 != v3, "Random unequal vectors");
        TEST(!(v1 == v3), "Random unequal vectors equality");
    }
}

void test_compound_assignment() {
    std::cout << "\n=== Testing Compound Assignment Operators +=, -=, *= ===" << std::endl;
    
    // Addition assignment
    vect2 v1(2, 3);
    v1 += vect2(4, 5);
    TEST(v1[0] == 6 && v1[1] == 8, "Addition assignment");
    
    // Subtraction assignment
    vect2 v2(10, 15);
    v2 -= vect2(3, 7);
    TEST(v2[0] == 7 && v2[1] == 8, "Subtraction assignment");
    
    // Multiplication assignment
    vect2 v3(4, 6);
    v3 *= 3;
    TEST(v3[0] == 12 && v3[1] == 18, "Multiplication assignment");
    
    // Chained compound assignment
    vect2 v4(1, 1);
    (v4 += vect2(2, 2)) *= 2;
    TEST(v4[0] == 6 && v4[1] == 6, "Chained compound assignment");
    
    // Self compound assignment
    vect2 v5(5, 7);
    v5 += v5;
    TEST(v5[0] == 10 && v5[1] == 14, "Self addition assignment");
    
    for (int i = 0; i < 50; i++) {
        int x1 = rand_int() % 100, y1 = rand_int() % 100;
        int x2 = rand_int() % 100, y2 = rand_int() % 100;
        int scalar = rand_int() % 5 + 1;
        
        vect2 va(x1, y1);
        va += vect2(x2, y2);
        TEST(va[0] == x1 + x2 && va[1] == y1 + y2, "Random += test");
        
        vect2 vb(x1, y1);
        vb -= vect2(x2, y2);
        TEST(vb[0] == x1 - x2 && vb[1] == y1 - y2, "Random -= test");
        
        vect2 vc(x1, y1);
        vc *= scalar;
        TEST(vc[0] == x1 * scalar && vc[1] == y1 * scalar, "Random *= test");
    }
}

void test_increment_decrement() {
    std::cout << "\n=== Testing Increment/Decrement Operators ++, -- ===" << std::endl;
    
    // Prefix increment
    vect2 v1(5, 10);
    vect2 pre_inc = ++v1;
    TEST(v1[0] == 6 && v1[1] == 11, "Prefix increment - original");
    TEST(pre_inc[0] == 6 && pre_inc[1] == 11, "Prefix increment - returned");
    
    // Postfix increment
    vect2 v2(3, 7);
    vect2 post_inc = v2++;
    TEST(v2[0] == 4 && v2[1] == 8, "Postfix increment - original");
    TEST(post_inc[0] == 3 && post_inc[1] == 7, "Postfix increment - returned");
    
    // Prefix decrement
    vect2 v3(8, 12);
    vect2 pre_dec = --v3;
    TEST(v3[0] == 7 && v3[1] == 11, "Prefix decrement - original");
    TEST(pre_dec[0] == 7 && pre_dec[1] == 11, "Prefix decrement - returned");
    
    // Postfix decrement
    vect2 v4(15, 20);
    vect2 post_dec = v4--;
    TEST(v4[0] == 14 && v4[1] == 19, "Postfix decrement - original");
    TEST(post_dec[0] == 15 && post_dec[1] == 20, "Postfix decrement - returned");
    
    // Multiple increments
    vect2 v5(0, 0);
    ++v5;
    v5++;
    TEST(v5[0] == 2 && v5[1] == 2, "Multiple increments");
    
    for (int i = 0; i < 50; i++) {
        int x = rand_int() % 100, y = rand_int() % 100;
        
        vect2 v_pre(x, y);
        ++v_pre;
        TEST(v_pre[0] == x + 1 && v_pre[1] == y + 1, "Random prefix increment");
        
        vect2 v_post(x, y);
        vect2 old = v_post++;
        TEST(v_post[0] == x + 1 && v_post[1] == y + 1, "Random postfix increment - new");
        TEST(old[0] == x && old[1] == y, "Random postfix increment - old");
    }
}

void test_output_operator() {
    std::cout << "\n=== Testing Output Operator << ===" << std::endl;
    
    // Note: We can't easily test the actual output format without complex string capture
    // But we can test that it doesn't crash and returns the stream
    vect2 v1(42, 24);
    
    // This should not crash
    std::cout << "Output test (should show {42, 24}): " << v1 << std::endl;
    
    TEST(true, "Output operator doesn't crash");
    
    // Test with various values
    for (int i = 0; i < 10; i++) {
        vect2 vr(rand_int() % 100, rand_int() % 100);
        std::cout << "Random output " << i << ": " << vr << std::endl;
    }
    TEST(true, "Random output tests don't crash");
}

void test_complex_expressions() {
    std::cout << "\n=== Testing Complex Expressions ===" << std::endl;
    
    vect2 a(1, 2), b(3, 4), c(5, 6);
    
    // Complex arithmetic
    vect2 result1 = (a + b) * 2 - c;
    TEST(result1[0] == 3 && result1[1] == 6, "Complex expression 1");
    
    vect2 result2 = a * 2 + b * 3 - c * 1;
    TEST(result2[0] == 2 && result2[1] == 4, "Complex expression 2");
    
    // Mixed operations
    vect2 result3 = -a + b - (-c);
    TEST(result3[0] == 7 && result3[1] == 8, "Mixed unary and arithmetic");
    
    // With compound assignments
    vect2 temp = a;
    (temp += b) *= 2;
    TEST(temp[0] == 8 && temp[1] == 12, "Compound in expression");
    
    for (int i = 0; i < 50; i++) {
        vect2 x(rand_int() % 10, rand_int() % 10);
        vect2 y(rand_int() % 10, rand_int() % 10);
        
        // Test associativity
        vect2 left_assoc = (x + y) + x;
        vect2 right_assoc = x + (y + x);
        TEST(left_assoc[0] == right_assoc[0] && left_assoc[1] == right_assoc[1], 
             "Addition associativity");
        
        // Test distributivity of scalar multiplication
        int s = rand_int() % 5 + 1;
        vect2 distributed = x * s + y * s;
        vect2 factored = (x + y) * s;
        TEST(distributed[0] == factored[0] && distributed[1] == factored[1], 
             "Scalar multiplication distributivity");
    }
}

void test_edge_cases() {
    std::cout << "\n=== Testing Edge Cases ===" << std::endl;
    
    // Zero vector operations
    vect2 zero(0, 0);
    vect2 nonzero(5, 10);
    
    TEST((zero + nonzero)[0] == 5 && (zero + nonzero)[1] == 10, "Zero addition");
    TEST((nonzero - zero)[0] == 5 && (nonzero - zero)[1] == 10, "Zero subtraction");
    TEST((zero * 5)[0] == 0 && (zero * 5)[1] == 0, "Zero scalar multiplication");
    
    // Negative zero
    vect2 neg_zero = zero * -1;
    TEST(neg_zero == zero, "Negative zero equals zero");
    
    // Large values (but not overflow)
    vect2 large(10000, -10000);
    vect2 large_result = large * 2;
    TEST(large_result[0] == 20000 && large_result[1] == -20000, "Large value operations");
    
    // Single component operations
    vect2 single_x(42, 0);
    vect2 single_y(0, 42);
    vect2 sum = single_x + single_y;
    TEST(sum[0] == 42 && sum[1] == 42, "Single component vectors");
}

// === CRYZE TESTS ===
void test_cryze_custom() {
    std::cout << "\n=== CRYZE CUSTOM TESTS ===" << std::endl;

    // Test overflow behavior
    vect2 max_int(INT_MAX, INT_MAX);
    vect2 min_int(INT_MIN, INT_MIN);
    vect2 res1 = max_int + vect2(1, 1);
    vect2 res2 = min_int - vect2(1, 1);
    // Results are implementation-defined for overflow, just test no crash
    TEST(true, "Overflow addition doesn't crash");
    TEST(true, "Overflow subtraction doesn't crash");

    // Test extremely large scalar multiplication
    vect2 v1(1, -1);
    vect2 v2 = v1 * INT_MAX;
    TEST(v2[0] == INT_MAX && v2[1] == -INT_MAX, "Large scalar multiplication");

    // Test chained assignments with self-references
    vect2 a(2, 2);
    vect2 b(3, 3);
    vect2 c(4, 4);
    a = b = c;
    TEST(a[0] == 4 && a[1] == 4, "Chained assignment a");
    TEST(b[0] == 4 && b[1] == 4, "Chained assignment b");

    // Test alternating compound assignments
    vect2 z(1, 2);
    z += vect2(2, 3);
    z -= vect2(1, 1);
    z *= 2;
    TEST(z[0] == 4 && z[1] == 8, "Alternating compound assignment");

    // Test output operator with extreme values
    vect2 extreme(INT_MAX, INT_MIN);
    std::cout << "Cryze output extreme test: " << extreme << std::endl;
    TEST(true, "Cryze output operator doesn't crash");

    // Test unary minus and plus on zero
    vect2 zero(0, 0);
    vect2 minus_zero = -zero;
    vect2 plus_zero = +zero;
    TEST(minus_zero == zero, "Unary minus on zero");
    TEST(plus_zero == zero, "Unary plus on zero");

    // Test chained increment/decrement
    vect2 chain(0, 0);
    ++chain;
    chain++;
    --chain;
    chain--;
    TEST(chain[0] == 0 && chain[1] == 0, "Chained inc/dec returns to zero");

    // Test assignment after arithmetic
    vect2 assign(7, 8);
    assign = assign + vect2(1, 2);
    TEST(assign[0] == 8 && assign[1] == 10, "Assignment after addition");
    assign = assign - vect2(3, 5);
    TEST(assign[0] == 5 && assign[1] == 5, "Assignment after subtraction");
    assign = assign * 2;
    TEST(assign[0] == 10 && assign[1] == 10, "Assignment after multiplication");

    // Test compound assignment with itself
    vect2 self(2, 3);
    self += self;
    TEST(self[0] == 4 && self[1] == 6, "Compound assignment with self");

    // Test equality with different types of initialization
    vect2 eq1(9, 9);
    vect2 eq2 = vect2(9, 9);
    TEST(eq1 == eq2, "Equality with different initialization");

    // Test assignment of const vect2
    const vect2 constv(11, 12);
    vect2 copy_const;
    copy_const = constv;
    TEST(copy_const[0] == 11 && copy_const[1] == 12, "Assignment from const vect2");

    // Test multiple chained compound assignments
    vect2 mchain(1, 1);
    (mchain += vect2(2, 2)) += vect2(3, 3);
    TEST(mchain[0] == 6 && mchain[1] == 6, "Multiple chained += compound assignment");
    (mchain -= vect2(2, 2)) -= vect2(1, 1);
    TEST(mchain[0] == 3 && mchain[1] == 3, "Multiple chained -= compound assignment");
    (mchain *= 2) *= 3;
    TEST(mchain[0] == 18 && mchain[1] == 18, "Multiple chained *= compound assignment");
}

void run_stress_tests() {
    std::cout << "\n=== Running Stress Tests ===" << std::endl;
    
    // Performance stress
    for (int i = 0; i < 1000; i++) {
        vect2 stress(1, 1);
        for (int j = 0; j < 10; j++) {
            stress = stress + vect2(1, 1) - vect2(1, 1);
            stress *= (j % 2 == 0) ? 1 : -1;
        }
        // Just test that it doesn't crash and maintains some basic property
        TEST(true, "Stress test iteration");
    }
    
    // Memory stress with temporaries
    for (int i = 0; i < 100; i++) {
        vect2 temp_result = vect2(i, i) + vect2(i+1, i+1) + vect2(i+2, i+2);
        TEST(temp_result[0] == 3*i + 3 && temp_result[1] == 3*i + 3, "Temporary object stress");
    }
}

int main()
{
    srand(time(nullptr));
    
    std::cout << "=== COMPREHENSIVE VECT2 CLASS TEST SUITE ===" << std::endl;
    std::cout << "Testing ALL operators with expected results..." << std::endl;
    
    // Run all test categories
    test_constructors();
    test_assignment_operator();
    test_array_access();
    test_addition();
    test_subtraction();
    test_scalar_multiplication();
    test_unary_operators();
    test_equality_operators();
    test_compound_assignment();
    test_increment_decrement();
    test_output_operator();
    test_complex_expressions();
    test_edge_cases();
    test_cryze_custom(); // <--- CRYZE TESTS ADDED
    run_stress_tests();
    
    // Final results
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "TEST RESULTS SUMMARY:" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << "Total Tests Run:     " << total_tests << std::endl;
    std::cout << "Tests PASSED:        " << tests_passed << " (" << 
                 (100.0 * tests_passed / total_tests) << "%)" << std::endl;
    std::cout << "Tests FAILED:        " << tests_failed << " (" << 
                 (100.0 * tests_failed / total_tests) << "%)" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    if (tests_failed == 0) {
        std::cout << "🎉 PERFECT SCORE! All tests passed! 🎉" << std::endl;
        std::cout << "Your vect2 implementation is FLAWLESS!" << std::endl;
    } else if (tests_failed < total_tests * 0.05) {  // Less than 5% failed
        std::cout << "✅ EXCELLENT! Almost perfect implementation!" << std::endl;
    } else if (tests_failed < total_tests * 0.15) {  // Less than 15% failed
        std::cout << "👍 GOOD! Your implementation works well with minor issues." << std::endl;
    } else if (tests_failed < total_tests * 0.30) {  // Less than 30% failed
        std::cout << "⚠️  NEEDS WORK! Several operators have issues." << std::endl;
    } else {
        std::cout << "❌ MAJOR ISSUES! Your implementation needs significant fixes." << std::endl;
    }
    
    std::cout << std::string(60, '=') << std::endl;
    
    // Operator coverage summary
    std::cout << "\nOPERATOR COVERAGE TESTED:" << std::endl;
    std::cout << "✓ Constructors (default, parameterized, copy)" << std::endl;
    std::cout << "✓ Assignment operator (=)" << std::endl;
    std::cout << "✓ Array access operator ([])" << std::endl;
    std::cout << "✓ Addition operator (+)" << std::endl;
    std::cout << "✓ Subtraction operator (-)" << std::endl;
    std::cout << "✓ Scalar multiplication (* both ways)" << std::endl;
    std::cout << "✓ Unary operators (+, -)" << std::endl;
    std::cout << "✓ Equality operators (==, !=)" << std::endl;
    std::cout << "✓ Compound assignment (+=, -=, *=)" << std::endl;
    std::cout << "✓ Increment/Decrement (++, -- pre/post)" << std::endl;
    std::cout << "✓ Output operator (<<)" << std::endl;
    std::cout << "✓ Complex expressions and edge cases" << std::endl;
    std::cout << "✓ CRYZE custom tests" << std::endl;
    
    return (tests_failed == 0) ? 0 : 1;
}
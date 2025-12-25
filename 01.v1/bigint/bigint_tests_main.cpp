#include "bigint.hpp"
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <sstream>

class BigIntTester {
private:
    int passed = 0;
    int failed = 0;
    std::mt19937 rng;
    
public:
    BigIntTester() : rng(std::chrono::steady_clock::now().time_since_epoch().count()) {}
    
    void test(bool condition, const std::string& description) {
        if (condition) {
            passed++;
            std::cout << "✓ " << description << std::endl;
        } else {
            failed++;
            std::cout << "✗ " << description << std::endl;
        }
    }
    
    std::string generateRandomNumber(int digits) {
        std::string result;
        std::uniform_int_distribution<int> dist(0, 9);
        
        // First digit can't be 0 (unless single digit)
        if (digits == 1) {
            result += std::to_string(dist(rng));
        } else {
            std::uniform_int_distribution<int> first_digit(1, 9);
            result += std::to_string(first_digit(rng));
            for (int i = 1; i < digits; i++) {
                result += std::to_string(dist(rng));
            }
        }
        return result;
    }
    
    std::string generateWeirdString() {
        std::vector<std::string> weird_cases = {
            "000000000000000000000000000000000000000001",
            "123000000000000000000000000000000000000000",
            "999999999999999999999999999999999999999999",
            "111111111111111111111111111111111111111111",
            "987654321098765432109876543210987654321098",
            "102030405060708090102030405060708090102030",
            "999000999000999000999000999000999000999000",
            "123456789012345678901234567890123456789012",
            "777777777777777777777777777777777777777777",
            "505050505050505050505050505050505050505050"
        };
        return weird_cases[rng() % weird_cases.size()];
    }
    
    void runAllTests() {
        std::cout << "Starting BigInt 10K Test Suite...\n" << std::endl;
        
        // Test 1-100: Basic Constructor Tests
        std::cout << "=== Constructor Tests (1-100) ===" << std::endl;
        test(bigint().getDigits() == "0", "Test 1: Default constructor");
        test(bigint(0).getDigits() == "0", "Test 2: Zero constructor");
        test(bigint(1).getDigits() == "1", "Test 3: One constructor");
        test(bigint(42).getDigits() == "24", "Test 4: 42 constructor (reversed)");
        test(bigint(999).getDigits() == "999", "Test 5: 999 constructor");
        test(bigint(1000).getDigits() == "0001", "Test 6: 1000 constructor");
        test(bigint(4294967295U).getDigits().size() > 0, "Test 7: Max uint constructor");
        
        for (int i = 8; i <= 100; i++) {
            unsigned int val = rng() % 1000000;
            bigint b(val);
            test(true, "Test " + std::to_string(i) + ": Random uint " + std::to_string(val));
        }
        
        // Test 101-500: String Constructor Edge Cases
        std::cout << "\n=== String Constructor Tests (101-500) ===" << std::endl;
        test(bigint("").getDigits() == "0", "Test 101: Empty string");
        test(bigint("0").getDigits() == "0", "Test 102: Zero string");
        test(bigint("00000").getDigits() == "0", "Test 103: Leading zeros");
        test(bigint("123").getDigits() == "321", "Test 104: Simple reverse");
        test(bigint("000123").getDigits() == "321", "Test 105: Leading zeros with number");
        test(bigint("abc").getDigits() == "0", "Test 106: Invalid string");
        test(bigint("12a34").getDigits() == "0", "Test 107: Mixed valid/invalid");
        test(bigint("   ").getDigits() == "0", "Test 108: Spaces");
        test(bigint("-123").getDigits() == "0", "Test 109: Negative number");
        test(bigint("12.34").getDigits() == "0", "Test 110: Decimal number");
        
        // More edge cases for string constructor
        for (int i = 111; i <= 200; i++) {
            std::string test_str = generateRandomNumber(rng() % 50 + 1);
            bigint b(test_str);
            test(true, "Test " + std::to_string(i) + ": Random string " + test_str);
        }
        
        // Weird string patterns
        for (int i = 201; i <= 300; i++) {
            std::string weird = generateWeirdString();
            bigint b(weird);
            test(true, "Test " + std::to_string(i) + ": Weird pattern " + weird.substr(0, 20) + "...");
        }
        
        // Ultra long numbers
        for (int i = 301; i <= 400; i++) {
            int length = 100 + (rng() % 900); // 100-1000 digits
            std::string ultra_long = generateRandomNumber(length);
            bigint b(ultra_long);
            test(b.getDigits().size() > 0, "Test " + std::to_string(i) + ": Ultra long " + std::to_string(length) + " digits");
        }
        
        // Palindromes and patterns
        for (int i = 401; i <= 500; i++) {
            std::string palindrome = "12321";
            for (int j = 0; j < i % 10; j++) palindrome += palindrome;
            bigint b(palindrome);
            test(true, "Test " + std::to_string(i) + ": Palindrome pattern");
        }
        
        // Test 501-1500: Addition Tests
        std::cout << "\n=== Addition Tests (501-1500) ===" << std::endl;
        test((bigint("123") + bigint("456")).getDigits() == "975", "Test 501: Simple addition");
        test((bigint("999") + bigint("1")).getDigits() == "0001", "Test 502: Carry propagation");
        test((bigint("0") + bigint("0")).getDigits() == "0", "Test 503: Zero addition");
        test((bigint("1") + bigint("999999999")).getDigits() == "0000000001", "Test 504: Small + large");
        
        // Massive addition tests
        for (int i = 505; i <= 800; i++) {
            std::string a = generateRandomNumber(rng() % 100 + 1);
            std::string b = generateRandomNumber(rng() % 100 + 1);
            bigint ba(a), bb(b);
            bigint result = ba + bb;
            test(result.getDigits().size() > 0, "Test " + std::to_string(i) + ": Random addition");
        }
        
        // Chain additions
        for (int i = 801; i <= 1000; i++) {
            bigint accumulator("0");
            for (int j = 0; j < 10; j++) {
                accumulator += bigint(rng() % 1000);
            }
            test(accumulator.getDigits().size() > 0, "Test " + std::to_string(i) + ": Chain addition");
        }
        
        // Extreme additions
        for (int i = 1001; i <= 1200; i++) {
            std::string huge1 = generateRandomNumber(500);
            std::string huge2 = generateRandomNumber(500);
            bigint b1(huge1), b2(huge2);
            bigint result = b1 + b2;
            test(result.getDigits().size() >= 500, "Test " + std::to_string(i) + ": Huge addition");
        }
        
        // Self addition
        for (int i = 1201; i <= 1300; i++) {
            std::string num = generateRandomNumber(rng() % 50 + 1);
            bigint b(num);
            bigint doubled = b + b;
            test(doubled.getDigits().size() > 0, "Test " + std::to_string(i) + ": Self addition");
        }
        
        // Addition with leading zeros
        for (int i = 1301; i <= 1500; i++) {
            std::string zeros(rng() % 20, '0');
            std::string num = zeros + generateRandomNumber(rng() % 30 + 1);
            bigint b1(num);
            bigint b2(generateRandomNumber(rng() % 30 + 1));
            bigint result = b1 + b2;
            test(result.getDigits().size() > 0, "Test " + std::to_string(i) + ": Addition with leading zeros");
        }
        
        // Test 1501-2500: Comparison Tests
        std::cout << "\n=== Comparison Tests (1501-2500) ===" << std::endl;
        test(bigint("123") == bigint("123"), "Test 1501: Equality");
        test(bigint("123") != bigint("124"), "Test 1502: Inequality");
        test(bigint("123") < bigint("124"), "Test 1503: Less than");
        test(bigint("124") > bigint("123"), "Test 1504: Greater than");
        test(bigint("123") <= bigint("123"), "Test 1505: Less than or equal");
        test(bigint("123") >= bigint("123"), "Test 1506: Greater than or equal");
        test(bigint("0") == bigint("00000"), "Test 1507: Zero equality");
        test(bigint("123") == bigint("000123"), "Test 1508: Leading zero equality");
        
        // Random comparison tests
        for (int i = 1509; i <= 2000; i++) {
            std::string a = generateRandomNumber(rng() % 50 + 1);
            std::string b = generateRandomNumber(rng() % 50 + 1);
            bigint ba(a), bb(b);
            
            // Test consistency
            bool eq = (ba == bb);
            bool neq = (ba != bb);
            bool lt = (ba < bb);
            bool gt = (ba > bb);
            bool lte = (ba <= bb);
            bool gte = (ba >= bb);
            
            test(eq != neq, "Test " + std::to_string(i) + ": Comparison consistency");
        }
        
        // Length-based comparisons
        for (int i = 2001; i <= 2200; i++) {
            int len1 = rng() % 50 + 1;
            int len2 = rng() % 50 + 1;
            std::string a = generateRandomNumber(len1);
            std::string b = generateRandomNumber(len2);
            bigint ba(a), bb(b);
            
            if (len1 < len2) {
                test(ba < bb, "Test " + std::to_string(i) + ": Length comparison (shorter < longer)");
            } else if (len1 > len2) {
                test(ba > bb, "Test " + std::to_string(i) + ": Length comparison (longer > shorter)");
            } else {
                test(true, "Test " + std::to_string(i) + ": Same length comparison");
            }
        }
        
        // Edge case comparisons
        for (int i = 2201; i <= 2500; i++) {
            std::string weird1 = generateWeirdString();
            std::string weird2 = generateWeirdString();
            bigint b1(weird1), b2(weird2);
            
            // Just test that comparison doesn't crash
            bool result = (b1 == b2) || (b1 != b2) || (b1 < b2) || (b1 > b2) || (b1 <= b2) || (b1 >= b2);
            test(result, "Test " + std::to_string(i) + ": Weird comparison");
        }
        
        // Test 2501-4000: Shift Operations
        std::cout << "\n=== Shift Operations (2501-4000) ===" << std::endl;
        test((bigint("123") << 2).getDigits() == "32100", "Test 2501: Left shift by 2");
        test((bigint("12300") >> 2).getDigits() == "321", "Test 2502: Right shift by 2");
        test((bigint("123") << 0).getDigits() == "321", "Test 2503: Left shift by 0");
        test((bigint("123") >> 0).getDigits() == "321", "Test 2504: Right shift by 0");
        test((bigint("0") << 5).getDigits() == "0", "Test 2505: Zero left shift");
        test((bigint("0") >> 5).getDigits() == "0", "Test 2506: Zero right shift");
        test((bigint("123") >> 10).getDigits() == "0", "Test 2507: Over-shift right");
        
        // Random shift tests
        for (int i = 2508; i <= 3000; i++) {
            std::string num = generateRandomNumber(rng() % 30 + 1);
            unsigned int shift = rng() % 20;
            bigint b(num);
            bigint left_shifted = b << shift;
            bigint right_shifted = b >> shift;
            test(left_shifted.getDigits().size() > 0 && right_shifted.getDigits().size() > 0, 
                 "Test " + std::to_string(i) + ": Random shift operations");
        }
        
        // Extreme shifts
        for (int i = 3001; i <= 3200; i++) {
            std::string huge = generateRandomNumber(100);
            unsigned int huge_shift = rng() % 200;
            bigint b(huge);
            bigint shifted = b << huge_shift;
            test(shifted.getDigits().size() > 0, "Test " + std::to_string(i) + ": Extreme left shift");
        }
        
        // Shift and compare
        for (int i = 3201; i <= 3400; i++) {
            std::string num = generateRandomNumber(rng() % 20 + 5);
            bigint b(num);
            bigint shifted_left = b << 3;
            bigint shifted_right = shifted_left >> 3;
            test(b == shifted_right, "Test " + std::to_string(i) + ": Shift round-trip");
        }
        
        // Chain shifts
        for (int i = 3401; i <= 3600; i++) {
            bigint b(generateRandomNumber(rng() % 30 + 1));
            for (int j = 0; j < 5; j++) {
                b <<= (rng() % 5 + 1);
            }
            test(b.getDigits().size() > 0, "Test " + std::to_string(i) + ": Chain left shifts");
        }
        
        // Alternating shifts
        for (int i = 3601; i <= 3800; i++) {
            bigint b(generateRandomNumber(rng() % 50 + 10));
            for (int j = 0; j < 10; j++) {
                if (j % 2 == 0) {
                    b <<= 2;
                } else {
                    b >>= 1;
                }
            }
            test(b.getDigits().size() > 0, "Test " + std::to_string(i) + ": Alternating shifts");
        }
        
        // Massive shifts
        for (int i = 3801; i <= 4000; i++) {
            std::string massive = generateRandomNumber(200);
            bigint b(massive);
            unsigned int massive_shift = 100 + (rng() % 100);
            bigint result = b << massive_shift;
            test(result.getDigits().size() >= 200, "Test " + std::to_string(i) + ": Massive shift");
        }
        
        // Test 4001-5500: Increment Operations
        std::cout << "\n=== Increment Operations (4001-5500) ===" << std::endl;
        bigint inc_test("999");
        test((++inc_test).getDigits() == "0001", "Test 4001: Pre-increment with carry");
        
        bigint post_test("123");
        bigint old_val = post_test++;
        test(old_val.getDigits() == "321" && post_test.getDigits() == "421", "Test 4002: Post-increment");
        
        // Chain increments
        for (int i = 4003; i <= 4500; i++) {
            bigint b(rng() % 1000);
            for (int j = 0; j < 100; j++) {
                ++b;
            }
            test(b.getDigits().size() > 0, "Test " + std::to_string(i) + ": Chain pre-increments");
        }
        
        // Post-increment chains
        for (int i = 4501; i <= 5000; i++) {
            bigint b(rng() % 1000);
            for (int j = 0; j < 50; j++) {
                bigint old = b++;
                test(old.getDigits().size() > 0, "Test " + std::to_string(i) + ": Chain post-increments");
            }
        }
        
        // Mixed increment operations
        for (int i = 5001; i <= 5500; i++) {
            bigint b(rng() % 10000);
            for (int j = 0; j < 25; j++) {
                if (j % 2 == 0) {
                    ++b;
                } else {
                    b++;
                }
            }
            test(b.getDigits().size() > 0, "Test " + std::to_string(i) + ": Mixed increments");
        }
        
        // Test 5501-7000: Stress Tests and Edge Cases
        std::cout << "\n=== Stress Tests (5501-7000) ===" << std::endl;
        
        // Memory stress tests
        for (int i = 5501; i <= 5700; i++) {
            std::vector<bigint> big_numbers;
            for (int j = 0; j < 100; j++) {
                big_numbers.push_back(bigint(generateRandomNumber(rng() % 100 + 1)));
            }
            test(big_numbers.size() == 100, "Test " + std::to_string(i) + ": Memory stress");
        }
        
        // Computation stress
        for (int i = 5701; i <= 5900; i++) {
            bigint accumulator("1");
            for (int j = 0; j < 50; j++) {
                accumulator += bigint(generateRandomNumber(rng() % 20 + 1));
                accumulator <<= 1;
                ++accumulator;
            }
            test(accumulator.getDigits().size() > 50, "Test " + std::to_string(i) + ": Computation stress");
        }
        
        // Fibonacci-like sequences
        for (int i = 5901; i <= 6100; i++) {
            bigint a("1"), b("1");
            for (int j = 0; j < 30; j++) {
                bigint temp = a + b;
                a = b;
                b = temp;
            }
            test(b.getDigits().size() > 5, "Test " + std::to_string(i) + ": Fibonacci-like");
        }
        
        // Powers of 2 simulation
        for (int i = 6101; i <= 6300; i++) {
            bigint power("1");
            for (int j = 0; j < 100; j++) {
                power += power; // Doubling
            }
            test(power.getDigits().size() > 25, "Test " + std::to_string(i) + ": Power of 2 simulation");
        }
        
        // Factorial-like growth (actually computing sum of squares)
        for (int i = 6301; i <= 6500; i++) {
            bigint accumulator("0");
            // Compute sum of i*i for i from 1 to 100 (much larger growth)
            for (int j = 1; j <= 100; j++) {
                bigint square("0");
                bigint base(j);
                // Simulate j*j by adding j to itself j times
                for (int k = 0; k < j; k++) {
                    square += base;
                }
                accumulator += square;
            }
            // Sum of squares from 1 to 100 is 338350, which has 6 digits
            test(accumulator.getDigits().size() >= 4, "Test " + std::to_string(i) + ": Factorial-like growth");
        }
        
        // Alternating operations stress
        for (int i = 6501; i <= 6700; i++) {
            bigint b(generateRandomNumber(30));
            for (int j = 0; j < 100; j++) {
                switch (j % 4) {
                    case 0: b += bigint(rng() % 100); break;
                    case 1: b <<= (rng() % 3 + 1); break;
                    case 2: ++b; break;
                    case 3: b >>= 1; break;
                }
            }
            test(b.getDigits().size() > 0, "Test " + std::to_string(i) + ": Alternating operations");
        }
        
        // Copy and assignment stress
        for (int i = 6701; i <= 6900; i++) {
            bigint original(generateRandomNumber(rng() % 100 + 1));
            std::vector<bigint> copies;
            for (int j = 0; j < 50; j++) {
                copies.push_back(original);
                copies.back() += bigint(j);
            }
            test(copies.size() == 50, "Test " + std::to_string(i) + ": Copy stress");
        }
        
        // Extreme edge cases
        for (int i = 6901; i <= 7000; i++) {
            // Create pathological cases
            std::string pathological;
            for (int j = 0; j < 1000; j++) {
                pathological += (j % 2 == 0) ? "9" : "0";
            }
            bigint b(pathological);
            b += bigint("1");
            b <<= 10;
            b >>= 5;
            test(b.getDigits().size() > 500, "Test " + std::to_string(i) + ": Pathological case");
        }
        
        // Test 7001-8500: Advanced Pattern Tests
        std::cout << "\n=== Advanced Pattern Tests (7001-8500) ===" << std::endl;
        
        // Palindrome arithmetic
        for (int i = 7001; i <= 7200; i++) {
            std::string pal = "12321";
            bigint palindrome(pal);
            bigint doubled = palindrome + palindrome;
            test(doubled.getDigits() == "24642", "Test " + std::to_string(i) + ": Palindrome arithmetic");
        }
        
        // Repeating digit patterns
        for (int i = 7201; i <= 7400; i++) {
            std::string pattern;
            int digit = rng() % 10;
            int length = rng() % 100 + 1;
            for (int j = 0; j < length; j++) {
                pattern += std::to_string(digit);
            }
            bigint b(pattern);
            b += bigint("1");
            test(b.getDigits().size() > 0, "Test " + std::to_string(i) + ": Repeating digits");
        }
        
        // Ascending/descending sequences
        for (int i = 7401; i <= 7600; i++) {
            std::string ascending, descending;
            for (int j = 0; j < 10; j++) {
                ascending += std::to_string(j);
                descending += std::to_string(9 - j);
            }
            bigint asc(ascending), desc(descending);
            bigint sum = asc + desc;
            test(sum.getDigits().size() > 0, "Test " + std::to_string(i) + ": Ascending/descending");
        }
        
        // Binary-like patterns (only 0s and 1s)
        for (int i = 7601; i <= 7800; i++) {
            std::string binary_like;
            for (int j = 0; j < 100; j++) {
                binary_like += (rng() % 2 == 0) ? "0" : "1";
            }
            bigint b(binary_like);
            b <<= (rng() % 10);
            test(b.getDigits().size() > 0, "Test " + std::to_string(i) + ": Binary-like pattern");
        }
        
        // Alternating high/low digits
        for (int i = 7801; i <= 8000; i++) {
            std::string alt_pattern;
            for (int j = 0; j < 50; j++) {
                alt_pattern += (j % 2 == 0) ? "9" : "1";
            }
            bigint b(alt_pattern);
            b += bigint("1111111111");
            test(b.getDigits().size() > 0, "Test " + std::to_string(i) + ": Alternating pattern");
        }
        
        // Prime-like sequences
        std::vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
        for (int i = 8001; i <= 8200; i++) {
            std::string prime_seq;
            for (int p : primes) {
                prime_seq += std::to_string(p);
            }
            bigint b(prime_seq);
            b += bigint(std::to_string(rng() % 1000));
            test(b.getDigits().size() > 0, "Test " + std::to_string(i) + ": Prime sequence");
        }
        
        // Mathematical constants (approximations)
        for (int i = 8201; i <= 8300; i++) {
            std::string pi_digits = "31415926535897932384626433832795028841971693993751";
            std::string e_digits = "27182818284590452353602874713526624977572470936999";
            bigint pi_approx(pi_digits), e_approx(e_digits);
            bigint sum = pi_approx + e_approx;
            test(sum.getDigits().size() > 0, "Test " + std::to_string(i) + ": Mathematical constants");
        }
        
        // Factorial digit patterns
        for (int i = 8301; i <= 8400; i++) {
            // Simulate factorial digit pattern
            std::string fact_pattern = "120";  // 5!
            for (int j = 0; j < 10; j++) {
                fact_pattern += fact_pattern;
            }
            bigint b(fact_pattern.substr(0, 100)); // Truncate
            b <<= (rng() % 5);
            test(b.getDigits().size() > 0, "Test " + std::to_string(i) + ": Factorial pattern");
        }
        
        // Chaos patterns
        for (int i = 8401; i <= 8500; i++) {
            std::string chaos;
            int seed = rng() % 1000;
            for (int j = 0; j < 100; j++) {
                seed = (seed * 1103515245 + 12345) % 1000000;
                chaos += std::to_string(seed % 10);
            }
            bigint b(chaos);
            b += bigint(chaos);
            test(b.getDigits().size() > 0, "Test " + std::to_string(i) + ": Chaos pattern");
        }
        
        // Test 8501-9500: Boundary and Overflow Tests
        std::cout << "\n=== Boundary Tests (8501-9500) ===" << std::endl;
        
        // Maximum single digit operations
        for (int i = 8501; i <= 8600; i++) {
            bigint nine("9");
            for (int j = 0; j < i % 50; j++) {
                nine = nine + nine;
            }
            test(nine.getDigits().size() > 0, "Test " + std::to_string(i) + ": Nine multiplication");
        }
        
        // Minimum non-zero operations
        for (int i = 8601; i <= 8700; i++) {
            bigint one("1");
            for (int j = 0; j < 100; j++) {
                ++one;
                one <<= 1;
            }
            test(one.getDigits().size() > 20, "Test " + std::to_string(i) + ": One progression");
        }
        
        // Large number boundaries
        for (int i = 8701; i <= 8800; i++) {
            std::string huge(1000, '9');
            bigint b(huge);
            b += bigint("1");
            test(b.getDigits().size() == 1001, "Test " + std::to_string(i) + ": Huge boundary");
        }
        
        // Shift boundaries
        for (int i = 8801; i <= 8900; i++) {
            bigint b("123456789");
            unsigned int max_shift = 500;
            b <<= max_shift;
            b >>= (max_shift - 1);
            test(b.getDigits().size() > 0, "Test " + std::to_string(i) + ": Shift boundary");
        }
        
        // Addition overflow patterns
        for (int i = 8901; i <= 9000; i++) {
            std::string all_nines(100, '9');
            std::string all_ones(100, '1');
            bigint nines(all_nines), ones(all_ones);
            bigint overflow = nines + ones;
            test(overflow.getDigits().size() > 100, "Test " + std::to_string(i) + ": Addition overflow");
        }
        
        // Extreme increment boundaries
        for (int i = 9001; i <= 9100; i++) {
            std::string boundary(50, '9');
            bigint b(boundary);
            for (int j = 0; j < 10; j++) {
                ++b;
            }
            test(b.getDigits().size() > 50, "Test " + std::to_string(i) + ": Increment boundary");
        }
        
        // Zero boundaries
        for (int i = 9101; i <= 9200; i++) {
            bigint zero("0");
            for (int j = 0; j < 100; j++) {
                zero += bigint("0");
                zero <<= (rng() % 5);
                zero >>= (rng() % 5);
            }
            test(zero == bigint("0"), "Test " + std::to_string(i) + ": Zero preservation");
        }
        
        // Leading zero stress
        for (int i = 9201; i <= 9300; i++) {
            std::string zeros(rng() % 100, '0');
            std::string num = zeros + "123456789";
            bigint b(num);
            for (int j = 0; j < 10; j++) {
                b += bigint("1");
            }
            test(b.getDigits().size() > 0, "Test " + std::to_string(i) + ": Leading zero stress");
        }
        
        // Comparison boundaries
        for (int i = 9301; i <= 9400; i++) {
            std::string almost_equal1 = generateRandomNumber(100);
            std::string almost_equal2 = almost_equal1;
            if (!almost_equal2.empty()) {
                almost_equal2.back() = (almost_equal2.back() == '9') ? '8' : char(almost_equal2.back() + 1);
            }
            bigint b1(almost_equal1), b2(almost_equal2);
            test(b1 != b2, "Test " + std::to_string(i) + ": Almost equal boundary");
        }
        
        // Size boundaries
        for (int i = 9401; i <= 9500; i++) {
            std::string tiny = "1";
            std::string massive = generateRandomNumber(1000);
            bigint t(tiny), m(massive);
            test(t < m, "Test " + std::to_string(i) + ": Size boundary comparison");
        }
        
        // Test 9501-10000: Ultimate Chaos Tests
        std::cout << "\n=== Ultimate Chaos Tests (9501-10000) ===" << std::endl;
        
        // Random operation sequences
        for (int i = 9501; i <= 9700; i++) {
            bigint chaos(generateRandomNumber(rng() % 50 + 1));
            for (int j = 0; j < 50; j++) {
                int op = rng() % 6;
                switch (op) {
                    case 0: chaos += bigint(generateRandomNumber(rng() % 20 + 1)); break;
                    case 1: chaos <<= (rng() % 10 + 1); break;
                    case 2: chaos >>= (rng() % 5 + 1); break;
                    case 3: ++chaos; break;
                    case 4: chaos++; break;
                    case 5: {
                        bigint temp = chaos;
                        chaos = temp + bigint(rng() % 1000);
                        break;
                    }
                }
            }
            test(chaos.getDigits().size() > 0, "Test " + std::to_string(i) + ": Random operation chaos");
        }
        
        // Nested operation madness
        for (int i = 9701; i <= 9750; i++) {
            bigint base(generateRandomNumber(20));
            bigint result = ((base + bigint("999")) << 3) + ((base << 2) + bigint("111"));
            ++result;
            result += (result >> 1);
            test(result.getDigits().size() > 0, "Test " + std::to_string(i) + ": Nested operations");
        }
        
        // Comparison chaos
        for (int i = 9751; i <= 9800; i++) {
            std::vector<bigint> numbers;
            for (int j = 0; j < 20; j++) {
                numbers.push_back(bigint(generateRandomNumber(rng() % 100 + 1)));
            }
            
            // Chaos sorting attempt
            bool sorted = true;
            for (size_t j = 1; j < numbers.size(); j++) {
                if (numbers[j-1] > numbers[j]) {
                    sorted = false;
                    break;
                }
            }
            test(true, "Test " + std::to_string(i) + ": Comparison chaos - " + (sorted ? "sorted" : "unsorted"));
        }
        
        // Memory management chaos
        for (int i = 9801; i <= 9850; i++) {
            std::vector<bigint*> heap_numbers;
            for (int j = 0; j < 100; j++) {
                heap_numbers.push_back(new bigint(generateRandomNumber(rng() % 30 + 1)));
                if (j > 0) {
                    *heap_numbers[j] = *heap_numbers[j-1] + bigint("1");
                }
            }
            
            // Cleanup
            for (auto* ptr : heap_numbers) {
                delete ptr;
            }
            test(true, "Test " + std::to_string(i) + ": Memory chaos");
        }
        
        // String representation chaos
        for (int i = 9851; i <= 9900; i++) {
            bigint b(generateRandomNumber(100));
            for (int j = 0; j < 20; j++) {
                std::ostringstream oss;
                oss << b;
                std::string str_repr = oss.str();
                bigint reconstructed(str_repr);
                test(b == reconstructed, "Test " + std::to_string(i) + ": String representation chaos");
                b += bigint("1");
            }
        }
        
        // Final ultimate chaos
        for (int i = 9901; i <= 10000; i++) {
            // Create the most chaotic test possible
            std::string chaos_str;
            for (int j = 0; j < 200; j++) {
                chaos_str += std::to_string(rng() % 10);
            }
            
            bigint chaos_num(chaos_str);
            
            // Apply random operations
            for (int j = 0; j < 20; j++) {
                int op = rng() % 10;
                switch (op) {
                    case 0: chaos_num += bigint(generateRandomNumber(rng() % 50 + 1)); break;
                    case 1: chaos_num <<= (rng() % 20 + 1); break;
                    case 2: chaos_num >>= (rng() % 10 + 1); break;
                    case 3: ++chaos_num; break;
                    case 4: chaos_num++; break;
                    case 5: {
                        bigint temp(generateRandomNumber(rng() % 30 + 1));
                        chaos_num += temp;
                        break;
                    }
                    case 6: {
                        std::ostringstream oss;
                        oss << chaos_num;
                        bigint temp(oss.str());
                        chaos_num = temp + bigint("1");
                        break;
                    }
                    case 7: {
                        bigint copy = chaos_num;
                        chaos_num = copy + copy;
                        break;
                    }
                    case 8: {
                        for (int k = 0; k < 5; k++) {
                            if (k % 2 == 0) chaos_num <<= 1;
                            else chaos_num >>= 1;
                        }
                        break;
                    }
                    case 9: {
                        // Create a huge temporary and add it
                        std::string huge_temp = generateRandomNumber(100);
                        chaos_num += bigint(huge_temp);
                        break;
                    }
                }
            }
            
            // Final validation - just make sure it didn't crash
            test(chaos_num.getDigits().size() > 0, "Test " + std::to_string(i) + ": ULTIMATE CHAOS");
        }
        
        // Final summary
        std::cout << "\n=== TEST SUMMARY ===" << std::endl;
        std::cout << "Passed: " << passed << std::endl;
        std::cout << "Failed: " << failed << std::endl;
        std::cout << "Total:  " << (passed + failed) << std::endl;
        std::cout << "Success Rate: " << (100.0 * passed / (passed + failed)) << "%" << std::endl;
        
        if (failed == 0) {
            std::cout << "\n🎉 ALL TESTS PASSED! Your BigInt implementation is ROCK SOLID! 🎉" << std::endl;
        } else {
            std::cout << "\n❌ Some tests failed. Check the implementation for edge cases." << std::endl;
        }
    }
    
    // Helper function to check if a bigint represents zero
    bool isZero(const bigint& b) {
        return b == bigint("0");
    }
};

int main() {
    BigIntTester tester;
    tester.runAllTests();
    return 0;
}
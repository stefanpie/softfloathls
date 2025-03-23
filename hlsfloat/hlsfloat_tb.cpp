#include "hlsfloat.h"
#include <cstdio>
#include <iostream>
#include <limits>
#include <random>

typedef bool (*test_func)();

template <typename T>
bool check_equal(T a, T b) {
    return (a == b);
}

std::mt19937 gen(7);

float random_numeric_float32() {

    std::uniform_real_distribution<float> exponent_dist(-38.0f, 38.0f);
    std::uniform_real_distribution<float> mantissa_dist(1.0f, 10.0f);
    std::uniform_int_distribution<int> sign_dist(0, 1);

    double sign = sign_dist(gen) == 0 ? 1.0 : -1.0;
    double exponent = exponent_dist(gen);
    double mantissa = mantissa_dist(gen);

    double value = sign * mantissa * std::pow(10.0, exponent);

    // Clamp to float finite range
    if (value > std::numeric_limits<float>::max())
        value = std::numeric_limits<float>::max();
    else if (value < -std::numeric_limits<float>::max())
        value = -std::numeric_limits<float>::max();

    return static_cast<float>(value);
}

bool test_initialization() {

    float float_real_0 = 0.0f;
    float float_real_n0 = -0.0f;
    float float_real_1 = 1.0f;
    float float_real_n1 = -1.0f;

    hlsfloat_float float_hls_0 = hlsfloat_float(float_real_0);
    hlsfloat_float float_hls_n0 = hlsfloat_float(-0.0f);
    hlsfloat_float float_hls_1 = hlsfloat_float(1.0f);
    hlsfloat_float float_hls_n1 = hlsfloat_float(-1.0f);

    float float_back_0 = float_hls_0.to_float();
    float float_back_n0 = float_hls_n0.to_float();
    float float_back_1 = float_hls_1.to_float();
    float float_back_n1 = float_hls_n1.to_float();

    bool pass = true;
    pass &= check_equal(float_back_0, float_real_0);
    pass &= check_equal(float_back_n0, float_real_n0);
    pass &= check_equal(float_back_1, float_real_1);
    pass &= check_equal(float_back_n1, float_real_n1);

    return pass;
}

bool test_initialization_random() {

    // int seed = 7;
    // srand(seed);

    const int num_tests = 100;
    bool pass = true;
    for (int i = 0; i < num_tests; ++i) {
        float random_value = random_numeric_float32();
        hlsfloat_float float_hls_random = hlsfloat_float(random_value);
        float float_back_random = float_hls_random.to_float();
        bool result = check_equal(float_back_random, random_value);
        if (!result) {
            std::cout << "Test failed for value: " << random_value << std::endl;
        }
        pass &= result;
    }
    return pass;
}

enum BooleanOperationArith { ADD, SUBTRACT, MULTIPLY, DIVIDE, REMAINDER };

template <BooleanOperationArith op>
bool test_boolean_op_random() {
    const int num_tests = 100;
    int n_pass = 0;
    bool pass = true;
    for (int i = 0; i < num_tests; ++i) {
        float random_value_a = random_numeric_float32();
        float random_value_b = random_numeric_float32();
        hlsfloat_float float_hls_a = hlsfloat_float(random_value_a);
        hlsfloat_float float_hls_b = hlsfloat_float(random_value_b);
        hlsfloat_float float_hls_result;
        float real_result;

        switch (op) {
        case ADD:
            float_hls_result = float_hls_a + float_hls_b;
            real_result = random_value_a + random_value_b;
            break;
        case SUBTRACT:
            float_hls_result = float_hls_a - float_hls_b;
            real_result = random_value_a - random_value_b;
            break;
        case MULTIPLY:
            float_hls_result = float_hls_a * float_hls_b;
            real_result = random_value_a * random_value_b;
            break;
        case DIVIDE:
            float_hls_result = float_hls_a / float_hls_b;
            real_result = random_value_a / random_value_b;
            break;
        case REMAINDER:
            float_hls_result = float_hls_a % float_hls_b;
            real_result = std::remainder(random_value_a, random_value_b);
            break;
        }

        float float_back_result = float_hls_result.to_float();
        bool result = check_equal(float_back_result, real_result);
        if (!result) {
            std::cout << "Test failed for values: " << random_value_a << " and " << random_value_b << std::endl;
            std::cout << "Expected: " << real_result << ", Got: " << float_back_result << std::endl;
        }

        if (result) {
            n_pass++;
        }

        pass &= result;
    }
    if (!pass) {
        std::cout << "Passed " << n_pass << " out of " << num_tests << " tests." << std::endl;
    }
    return pass;
}

// bool operator==(const hlsfloat_float &d) {
//     return float32_eq(data, d.data);
// }
// bool operator!=(const hlsfloat_float &d) {
//     return !(*this == d);
// }
// bool operator<(const hlsfloat_float &d) {
//     return float32_lt(data, d.data);
// }
// bool operator<=(const hlsfloat_float &d) {
//     return float32_le(data, d.data);
// }
// bool operator>(const hlsfloat_float &d) {
//     return !(*this <= d);
// }
// bool operator>=(const hlsfloat_float &d) {
//     return !(*this < d);
// }

enum BooleanOperationComp { EQ, NE, LT, LE, GT, GE };
template <BooleanOperationComp op>
bool test_boolean_comp_random() {
    const int num_tests = 100;
    int n_pass = 0;
    bool pass = true;
    for (int i = 0; i < num_tests; ++i) {
        float random_value_a = random_numeric_float32();
        float random_value_b = random_numeric_float32();
        hlsfloat_float float_hls_a = hlsfloat_float(random_value_a);
        hlsfloat_float float_hls_b = hlsfloat_float(random_value_b);
        bool result;
        bool real_result;

        switch (op) {
        case EQ:
            result = (float_hls_a == float_hls_b);
            real_result = random_value_a == random_value_b;
            break;
        case NE:
            result = (float_hls_a != float_hls_b);
            real_result = random_value_a != random_value_b;
            break;
        case LT:
            result = (float_hls_a < float_hls_b);
            real_result = random_value_a < random_value_b;
            break;
        case LE:
            result = (float_hls_a <= float_hls_b);
            real_result = random_value_a <= random_value_b;
            break;
        case GT:
            result = (float_hls_a > float_hls_b);
            real_result = random_value_a > random_value_b;
            break;
        case GE:
            result = (float_hls_a >= float_hls_b);
            real_result = random_value_a >= random_value_b;
            break;
        }

        if (result != real_result) {
            std::cout << "Test failed for values: " << random_value_a << " and " << random_value_b << std::endl;
            std::cout << "Expected: " << real_result << ", Got: " << result << std::endl;
        }

        if (result == real_result) {
            n_pass++;
        }

        pass &= (result == real_result);
    }
    if (!pass) {
        std::cout << "Passed " << n_pass << " out of " << num_tests << " tests." << std::endl;
    }
    return pass;
}

enum UnaryOperation { RND_INT, NEG };

template <UnaryOperation op>
bool test_unary_op_random() {
    const int num_tests = 100;
    bool pass = true;
    for (int i = 0; i < num_tests; ++i) {
        float random_value = random_numeric_float32();
        hlsfloat_float float_hls_random = hlsfloat_float(random_value);
        hlsfloat_float float_hls_result;
        float real_result;
        switch (op) {
        case RND_INT:
            float_hls_result = float_hls_random.round_to_int();
            real_result = std::nearbyint(random_value);
            break;
        case NEG:
            float_hls_result = -float_hls_random;
            real_result = -random_value;
            break;
        }

        float float_back_result = float_hls_result.to_float();
        bool result = check_equal(float_back_result, real_result);
        if (!result) {
            std::cout << "Test failed for value: " << random_value << std::endl;
            std::cout << "Expected: " << real_result << ", Got: " << float_back_result << std::endl;
        }
        pass &= result;
    }
    return pass;
}

#define TEST_FN(test)                                                                                                  \
    std::cout << "Running test: " << #test << "..." << std::endl;                                                      \
    if (test()) {                                                                                                      \
        std::cout << "Test passed!" << std::endl;                                                                      \
    } else {                                                                                                           \
        std::cout << "Test failed!" << std::endl;                                                                      \
    }

int main() {
    printf("Running hlsfloat tests...\n");
    printf("-------------------------\n");
    TEST_FN(test_initialization);
    TEST_FN(test_initialization_random);
    TEST_FN(test_boolean_op_random<ADD>);
    TEST_FN(test_boolean_op_random<SUBTRACT>);
    TEST_FN(test_boolean_op_random<MULTIPLY>);
    TEST_FN(test_boolean_op_random<DIVIDE>);
    TEST_FN(test_boolean_op_random<REMAINDER>);
    TEST_FN(test_boolean_comp_random<EQ>);
    TEST_FN(test_boolean_comp_random<NE>);
    TEST_FN(test_boolean_comp_random<LT>);
    TEST_FN(test_boolean_comp_random<LE>);
    TEST_FN(test_boolean_comp_random<GT>);
    TEST_FN(test_boolean_comp_random<GE>);
    TEST_FN(test_unary_op_random<RND_INT>);
    TEST_FN(test_unary_op_random<NEG>);
    std::cout << "All tests completed." << std::endl;
    return 0;
}
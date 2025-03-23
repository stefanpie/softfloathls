#include "softfloat_processed.h"

inline float float32_to_float(float32 f) {
    union {
        float32 u;
        float f;
    } u;
    u.u = f;
    return u.f;
}

inline float32 float_to_float32(float f) {
    union {
        float32 u;
        float f;
    } u;
    u.f = f;
    return u.u;
}

class softfloathls_float {

  public:
    float32 data; // from SoftFloat

    softfloathls_float() : data(0) {
    }
    softfloathls_float(const float val) {
        data = float_to_float32(val);
    }
    softfloathls_float(const float32 val) : data(val) {
    } // Added constructor
    softfloathls_float(const softfloathls_float &d) {
        data = d.data;
    } // Updated constructor

    softfloathls_float operator=(const softfloathls_float &d) {
        data = d.data;
        return *this;
    }
    softfloathls_float operator=(const float &d) {
        data = float_to_float32(d);
        return *this;
    }

    softfloathls_float operator+(const softfloathls_float &d) {
        return softfloathls_float(float32_add(data, d.data));
    }
    softfloathls_float operator-(const softfloathls_float &d) {
        return softfloathls_float(float32_sub(data, d.data));
    }
    softfloathls_float operator*(const softfloathls_float &d) {
        return softfloathls_float(float32_mul(data, d.data));
    }
    softfloathls_float operator/(const softfloathls_float &d) {
        return softfloathls_float(float32_div(data, d.data));
    }

    softfloathls_float operator%(const softfloathls_float &d) {
        return softfloathls_float(float32_rem(data, d.data));
    }

    softfloathls_float sqrt() {
        return softfloathls_float(float32_sqrt(data));
    }
    softfloathls_float round_to_int() {
        return softfloathls_float(float32_round_to_int(data));
    }

    //   unary operators
    softfloathls_float operator-() {
        float32 negated = data ^ 0x80000000; // flip the sign bit
        return softfloathls_float(negated);
    }

    //   comparisons

    bool operator==(const softfloathls_float &d) {
        return float32_eq(data, d.data);
    }
    bool operator!=(const softfloathls_float &d) {
        return !(*this == d);
    }
    bool operator<(const softfloathls_float &d) {
        return float32_lt(data, d.data);
    }
    bool operator<=(const softfloathls_float &d) {
        return float32_le(data, d.data);
    }
    bool operator>(const softfloathls_float &d) {
        return !(*this <= d);
    }
    bool operator>=(const softfloathls_float &d) {
        return !(*this < d);
    }

    //   conversions
    float to_float() {
        return float32_to_float(data);
    }
    int to_int32() {
        return float32_to_int32(data);
    }
    int to_int32_round_to_zero() {
        return float32_to_int32_round_to_zero(data);
    }
    long long to_int64() {
        return float32_to_int64(data);
    }
    long long to_int64_round_to_zero() {
        return float32_to_int64_round_to_zero(data);
    }
    float64 to_float64() {
        return float32_to_float64(data);
    }
    float128 to_float128() {
        return float32_to_float128(data);
    }

    //   check for nan
    bool is_nan() {
        return float32_is_nan(data);
    }
};
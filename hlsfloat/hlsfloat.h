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

class hlsfloat_float {

  public:
    float32 data; // from SoftFloat

    hlsfloat_float() : data(0) {
    }
    hlsfloat_float(const float val) {
        data = float_to_float32(val);
    }
    hlsfloat_float(const float32 val) : data(val) {
    } // Added constructor
    hlsfloat_float(const hlsfloat_float &d) {
        data = d.data;
    } // Updated constructor

    hlsfloat_float operator=(const hlsfloat_float &d) {
        data = d.data;
        return *this;
    }
    hlsfloat_float operator=(const float &d) {
        data = float_to_float32(d);
        return *this;
    }

    hlsfloat_float operator+(const hlsfloat_float &d) {
        return hlsfloat_float(float32_add(data, d.data));
    }
    hlsfloat_float operator-(const hlsfloat_float &d) {
        return hlsfloat_float(float32_sub(data, d.data));
    }
    hlsfloat_float operator*(const hlsfloat_float &d) {
        return hlsfloat_float(float32_mul(data, d.data));
    }
    hlsfloat_float operator/(const hlsfloat_float &d) {
        return hlsfloat_float(float32_div(data, d.data));
    }

    hlsfloat_float operator%(const hlsfloat_float &d) {
        return hlsfloat_float(float32_rem(data, d.data));
    }

    hlsfloat_float sqrt() {
        return hlsfloat_float(float32_sqrt(data));
    }
    hlsfloat_float round_to_int() {
        return hlsfloat_float(float32_round_to_int(data));
    }

    //   unary operators
    hlsfloat_float operator-() {
        float32 negated = data ^ 0x80000000; // flip the sign bit
        return hlsfloat_float(negated);
    }

    //   comparisons

    bool operator==(const hlsfloat_float &d) {
        return float32_eq(data, d.data);
    }
    bool operator!=(const hlsfloat_float &d) {
        return !(*this == d);
    }
    bool operator<(const hlsfloat_float &d) {
        return float32_lt(data, d.data);
    }
    bool operator<=(const hlsfloat_float &d) {
        return float32_le(data, d.data);
    }
    bool operator>(const hlsfloat_float &d) {
        return !(*this <= d);
    }
    bool operator>=(const hlsfloat_float &d) {
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
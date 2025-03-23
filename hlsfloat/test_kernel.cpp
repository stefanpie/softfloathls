#include "hlsfloat.h"

// wirte a kernle that computes a polynomial of degree 4 with user given coeffs

hlsfloat_float top(hlsfloat_float x, hlsfloat_float coeffs[5]) {
  hlsfloat_float x2 = x * x;
  hlsfloat_float x3 = x2 * x;
  hlsfloat_float x4 = x3 * x;

  hlsfloat_float result = coeffs[0] + (coeffs[1] * x) + (coeffs[2] * x2) +
                          (coeffs[3] * x3) + (coeffs[4] * x4);

  return result;
}
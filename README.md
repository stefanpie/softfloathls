
<img src="./branding/logo_softfloathls.svg" alt="SoftFloatHLS Logo" width="100%">
<hr>

**SoftFloatHLS** is a soft floating-point C++ header library designed for use in high-level synthesis (HLS) designs.

It adapts the SoftFloat library (version 2c) and provides C++ wrapper classes for 32-bit, 64-bit, and 128-bit floating-point types. These wrappers support common C++ operators, utility functions, type conversions, and ergonomic use in HLS-compatible C++ code.

## Setup

Simply copy the `softfloathls/softfloathls.h` and `softfloathls/softfloat_processed.h` header files in your HLS C++ project.
That's it! How nice for a change.

## Usage

Here is an example kernel that evaluates a degree 4 polynomial using SoftFloatHLS types

```cpp
#include "softfloathls.h"

 // 32-bit floating-point type from SoftFloatHLS
typedef softfloathls_float data_t;

data_t top(data_t x, data_t coeffs[5]) {
    data_t x2 = x * x;
    data_t x3 = x2 * x;
    data_t x4 = x3 * x;

    data_t result = coeffs[0] + (coeffs[1] * x) + (coeffs[2] * x2) + (coeffs[3] * x3) + (coeffs[4] * x4);
    
    return result;
}
```

This kernel is now synthesizable using Vitis HLS or other HLS tools that support C++ synthesis. The datatypes in SoftFloatHLS don't depend on any vendor-specific HLS types so the library is completely standalone, we avoid having to include any vendor-specific headers or libraries in our design.

## Motivation

The goal of SoftFloatHLS is not necessarily to be a high-performance floating-point library, but rather to serve as a drop-in replacement for native C++ floating-point types in HLS environments. Many HLS tools lower native floating-point operations to custom hardware floating-point units provided by the tool vendor.

For example, Xilinx only supports mapping floating-point operations to their proprietary "Floating-Point Operator" IP core. As a result, Verilog output from tools like Vitis HLS includes encrypted vendor-specific IP instantiations, which are not portable to other synthesis or implementation tools.

In many use cases, we still want to use Vitis HLS to synthesize C++ to Verilog, but we want the resulting Verilog to be portable and vendor-agnostic. SoftFloatHLS enables this by replacing native floating-point types with "soft" or manual implementations of floating-point operations using the SoftFloat library. These implementations can be directly synthesized to Verilog without relying on vendor IP.

Additionally, SoftFloatHLS mitigates the performance overhead introduced by some vendor-provided floating-point libraries during simulation and analysis. By using lightweight wrappers around SoftFloat and keeping the float classes simple, designs can be parsed more efficiently by C++ tools, and functional C simulations become faster to compile and run.

However, portability comes at a cost. Since native floating-point operations are replaced with custom types and functions, the HLS compiler loses its ability to recognize and optimize generalized floating-point expressions. For instance, it cannot reorder SoftFloatHLS operations—even if they are mathematically equivalent—and even if we ignore IEEE associativity rules with unsafe math optimizations.

This limitation impacts HLS design strategies that rely on expression balancing and operation reordering for performance optimization (e.g., unrolled summations). In such cases, performance may degrade, and some optimizations may be outright not possible. This is the trade-off SoftFloatHLS makes in favor of portability and tool speed.

## Ongoing Work

- Port over the newer version 3 of the SoftFloat library mainly to support 16-bit floating-point types
- Provide a simple but fairly complete math library for SoftFloatHLS types, including trigonometric functions, logarithms, exponentials, and selected special functions
- Provide some latency and resource usage comparisons between SoftFloatHLS implementation and Vitis HLS / Vivado implementation of floating point operations

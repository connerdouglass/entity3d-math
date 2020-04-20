# Entity3d Math Library
This is the math library which is used in the Entity3d graphics library. The code is very general and portable, and can be used anywhere. There is an emphasis on linear algebra, specifically matrix and vector operations.

### Why use Entity3d
In two words: safety and accuracy. This library makes extensive use of C++ templates and static assertions. For instance, there is one `Mat` class for matrices, and users can specify the dimensions of the matrix using templates like so: `Mat<4, 4>` (for a 4x4 matrix). The benefit of using generics in this fashion is that some illegal matrix operations can be prevented at compile-time, instead of causing errors at runtime.

As an example, if one attempts to multiply matrices together with incompatible dimensions, the code will not compile. This prevents whole classes of runtime errors, and removes the need for runtime dimension checks / assertions.

### Goals

The following are some of the goals of this library:
 - Provide a very general set of linear algebra types (vectors, matrices, quaternions, points, etc.) and utility functions to manipulate them.
 - Make no assumptions about the vector space of the user. Everything is templated with `uint8_t` and should theoretically support [1, 256) dimensions, even though that is admittedly outrageous.
 - A single interface should exist across any number of dimensions. Vectors in 2 or 100 dimensions are both of type `Vec<S>`.
 - Where possible, a single implementation should exist across any number of dimensions, but only if the runtime cost is zero or near-zero. If this isn't possible, metaprogramming and macros may be used to optimize at compile-time.
 - Make compile-time guarantees of the legality of all operations, such as multiplying matrices (must be compatible), or creating identity matrices (must be square).

### Sample code

The code below shows how to create and print vectors:

```cpp
#include "e3dmath.h"

using namespace e3d;

// Create a unit vector along each axis
Vec3 i = utils::vec::x_axis<4>();
Vec3 j = utils::vec::y_axis<4>();
Vec3 k = utils::vec::z_axis<4>();

// Create some composite vector with operators
Vec3 composite = i * 2.0f + j * 3.0f + k * 4.0f;

// Or, just define it manually...
Vec3 composite ((float[]){ 2, 3, 4 });

// Then, we can print it out
std::cout << composite << std::endl;   // --> < 2, 3, 4 >
```

`Vec3` is a typedef shortcut which indicates a vector with three components. You can create vectors with arbitrary components with the template syntax `Vec<#>`. These are built-in: `Vec2`, `Vec3`, `Vec4`, and `Mat4` (4x4 matrix).

Even further, every vector is actually just a matrix with a single column, and a configurable `S` rows. The type definition for vector, `Vec<uint8_t S>`, is an alias for `Mat<S, 1>`. This allows all of the matrix math functions in `e3d::utils::mat` to apply both to matrices and vectors.

This is useful because it enables the following transformations to be very simple, as simple as they would be in GLSL, for instance:

```cpp
// Define our starting point
Vec4 original ((float[]){ 1, 2, 3, 0 });

// Rotate the point about the origin π radians (180 degrees) CCW
Mat4 rotation = utils::mat::mat4_create_rotation_y(M_PI);
Vec4 result = rotation * original;

// Print out the result
std::cout << "Result: " << result << std::endl;   // --> Result: <-1, 2, -3, 0>
```

Note that order matters. The 4x4 `rotation` matrix needed to come before the 4x1 `original` vector in order for the multiplication to be compatible. You can multiply `(4x4) * (4x1)` but you CANNOT multiply `(4x1) * (4x4)`, due to the rules of linear algebra (more below).

### Compile-time Safety

In linear algebra, matrices can only be multiplied if they are dimensionally compatible. The number of columns on the left matrix must match the number of rows on the right matrix.

Even though `Mat<R, C>` and `Vec<S>` are templated and allow arbitrary dimensions to be used, it's impossible to perform multiplications and divisions on matrices and vectors which are incompatible. This error is a compiler error, not a runtime error.

As an example, the following code will not compile:

```cpp
// Create a 3x4 and a 5x6 matrix
Mat<3, 4> a = ...
Mat<5, 6> b = ...

// This line will cause a compiler error!
auto result = a * b;
```

The following code, however, compiles and runs without issue:

```cpp
// Create a 3x4 and a 4x5 matrix
Mat<3, 4> a = ...
Mat<4, 5> b = ...

// Multiply them together, resulting in a 3x5 result
Mat<3, 5> = a * b;
```

Likewise, there is a special type of matrix called an "identity matrix." When a matrix is multiplied by an identity matrix, the result is a matrix exactly equal to the original. Despite their seeming uselessness, identity matrices are indeed useful as the starting point when composing a sequence of transformations.

Importantly, identity matrices must be square – the number of rows must match the number of columns. This is necessary so that the product of multiplication has the same dimensions as the original matrix.

This rule is enforced at compile-time via a static assertion. Here's an example of this:

```cpp
// This will not compile:
auto bad_identity = Mat<3, 6>::identity();

// But, this WILL compile:
auto identity = Mat<4, 4>::identity();
```

### Resizing Vectors

It's likely that you will encounter a situation in which you need to transform a 3-dimensional `Vec3` by a 4x4-dimensional `Mat4` (or something to that effect). As stated above, this is disallowed at compile-time. To perform this action, your vector needs to be resized to a `Vec4` to make it dimensionally compatible with the matrix.

Here's how you would achieve that:

```cpp
// We have a vector
Vec3 vec ((float[]){ 1, 2, 0 });

// We have a transform matrix, let's do scaling (2x on all axes)
Mat4 scale = utils::mat::mat4_create_scale(2, 2, 2);

// Perform the multiplication, but resize first
Vec4 result = utils::vec::resize<4>(vec) * scale;

// If you wish, resize back to 3-dimensions
Vec3 result_3d = utils::vec::resize<3>(result);
```

### Contribute
Contributions are welcome!

# Entity3d Math Library
This is the math library which is used in the Entity3d graphics library. The code is very general and portable, and can be used anywhere. There is an emphasis on linear algebra, specifically matrix and vector operations.

### Why use Entity3d
In two words: safety and accuracy. This library makes extensive use of C++ templates and static assertions. For instance, there is one `Mat` class for matrices, and users can specify the dimensions of the matrix using templates like so: `Mat<4, 4>` (for a 4x4 matrix). The benefit of using generics in this fashion is that some illegal matrix operations can be prevented at compile-time, instead of causing errors at runtime.

As an example, if one attempts to multiply matrices together with incompatible dimensions, the code will not compile. This prevents whole classes of runtime errors, and removes the need for runtime dimension checks / assertions.

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
Vec3 composite = x * 2.0f + y * 3.0f + z * 4.0f;

// Or, just define it manually...
Vec3 composite ((float[]){ 2.0f, 3.0f, 4.0f });

// Then, we can print it out
std::cout << composite << std::endl;   // --> <2, 3, 4>
```

`Vec3` is a typedef shortcut which indicates a vector with three components. You can create vectors with arbitrary components with the template syntax `Vec<#>`.

Even further, every vector is actually just a matrix with a single row, and a configurable number of columns. The type definition for vector, `Vec<uint8_t S>`, is an alias for `Mat<1, S>`. This allows all of the matrix math functions in `e3d::utils::mat` to apply both to matrices and vectors.

### Contribute
Contributions are welcome!

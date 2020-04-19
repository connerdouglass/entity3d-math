# Entity3d Math Library
This is the math library which is used in the Entity3d graphics library. The code is very general and portable, and can be used anywhere. There is an emphasis on linear algebra, specifically matrix and vector operations.

### Why use Entity3d
Entity3d makes extensive use of C++ templates for matrices and vectors. For instance, there is one `Mat` class for matrices, and users can specify the dimensions of the matrix using generics like so: `Mat<4, 4>` (for a 4x4 matrix). The benefit of using generics in this fashion is that some illegal matrix operations can be prevented at compile-time, instead of causing errors at runtime.

As an example, if one attempts to multiply matrices together with incompatible dimensions, the code will not compile. This prevents whole classes of runtime errors, and removes the need for runtime dimension checks / assertions.

### Contribute
Contributions are welcome!

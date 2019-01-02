# LAPACK95
Archive / mirror of Netlib LAPACK95, with added cmake support.

See also [scivision/LAPACK95](https://github.com/scivision/LAPACK95) with a different cmake implementation.

## Build and install (cmake)
(Note: This compiles the full `single_double_complex_dcomplex` version.)

The standard procedure
```sh
mkdir build && cd build
cmake .. [-DCMAKE_INSTALL_PREFIX=/your/install/path (default: /usr/local)]
make -j$(nproc)
```
gives  `liblapack95.a`, with module files placed in `include/`. Your program can then `use f95_lapack` and be compiled with e.g.
```sh
gfortran yourprogram.f90 -I/path/to/LAPACK95/build/include -L/path/to/LAPACK95/build -llapack -llapack95
```
(assuming ordinary `LAPACK` is in your path).

Install with (still in the `build` folder)
```sh
make install
```
(may require `sudo` depending on install location). Programs can then be compiled with
```sh
gfortran yourprogram.f90 -I/your/install/prefix/include -llapack -llapack95
```
(assuming `/your/install/prefix/lib` is part of `LD_LIBRARY_PATH`).

## Use in a cmake project
This library can be used inside a cmake project by adding this repository with `add_subdirectory`. One can for example use [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html):
```cmake
cmake_minimum_required(VERSION 3.11)

project(myproject Fortran)

find_package(LAPACK REQUIRED)

include(FetchContent)
FetchContent_Declare(
    lapack95
    GIT_REPOSITORY https://github.com/anjohan/LAPACK95.git
)

FetchContent_GetProperties(lapack95)
if(NOT lapack95_POPULATED)
    FetchContent_Populate(lapack95)
    add_subdirectory(${lapack95_SOURCE_DIR})
endif()

add_executable(myexe ${CMAKE_CURRENT_SOURCE_DIR}/myexe.f90)
target_link_libraries(myexe ${LAPACK_LIBRARIES} lapack95)

```

## Example program
```fortran
program ex
    ! Double precision
    use la_precision, only: wp => dp
    use f95_lapack, only: la_gesv

    real(wp) :: A(3,3), b(3)

    call random_number(A)
    b(:) = 3*A(:,1) + 2*A(:,2) - A(:,3)
    
    ! Solve Ax=b, overwrite b with solution
    call la_gesv(A,b)

    write(*,*) b
end program

! Output (exact: 3 2 -1):
! 2.9999999999999978        2.0000000000000018       -1.0000000000000004
```

## Build (makefiles)
To build
[LAPACK95](http://www.netlib.org/lapack95/)
library with any Fortran compiler simply:
```sh
cd LAPACK95/
make clean -C SRC

make double -C SRC
```
which creates `lapack95.a` in `LAPACK95/`  with "double" precision.
Use "single" or other options described in tne README files under LAPACK95 and LAPACK95/SRC if complex etc. precision is needed.

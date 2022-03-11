This package contains command line tools and input data for demonstrating two
failures of a floating-point based implementation of an algorithm for
computing the convex hull of a set of points in the plane. The algorithm is a
plane sweep variant of Graham's scan and runs in worst case optimal time
O(n log n).

The algorithm and how it's floating-point based implementation fails are
described in detail in the paper 

Marc Moerig, Another Classroom Example of Robustness Problems in
Planar Convex Hull Computation, presented at MACIS 2015

This package also contains a robust implementation of the same algorithm. The
robust implementation is based on exact predicates by J.R. Shewchuk, available
at https://www.cs.cmu.edu/~quake/robust.html and described in

Jonathan Richard Shewchuk, Adaptive Precision Floating-Point Arithmetic and Fast
Robust Geometric Predicates, Discrete & Computational Geometry 18:305-363, 1997.

The robust orientation predicate is located in predicates.cpp. The code has been
slightly adapted for modern C++ compilers. Most of the code is unnecessary for
our task and has been disabled instead of beeing adapted.

This package and further material may be obtained from
http://wwwisg.cs.uni-magdeburg.de/ag/ClassroomExample/

################################################################################
BUILDING AND RUNNING

Building is based on cmake, the central CMakeLists.txt is located in the
src subdirectory. Starting from the directory containing this README:

1. Create a build directory

mkdir build

2. Run cmake

cd build
cmake ../src

3. Run make

make

4. Check individual orientation test results

./test_failures

The test will tell you whether the orientation predicates behave as expected on
a few critical point configurations. If anything is wrong, please read A NOTE ON
REPRODUCIBILITY at the end of this file.

5. Run convex hull algorithm 

./robust_convex_hull    ../data/failure_u.points    robust_u.output
./nonrobust_convex_hull ../data/failure_u.points nonrobust_u.output

6. Compare results from robust/nonrobust implementation and inspect differences

diff robust_u.output  nonrobust_u.output

################################################################################
TOOLS

--------------------------------------------------------------------------------
test_failures

Checks whether the orientation tests behave as expected on a few critical point
configurations. Run this first.

--------------------------------------------------------------------------------
nonrobust_convex_hull  
   robust_convex_hull

A robust and a nonrobust implementation of the algorithm described in the paper.
Both take as arguments an input file, containing the input set and an output
file where the resulting convex hull is written. The nonrobust version will show
the problems described in the paper, while the robust version will always
compute the correct result. 
   
--------------------------------------------------------------------------------
test_circular_sequence

Checks methods for circular traversal of a std::list.

--------------------------------------------------------------------------------
test_read_write

Checks code for reading/writing point files. 

################################################################################
DATASETS

--------------------------------------------------------------------------------
data/failure_u.points

Input point set leading to the first failure described in the paper.

--------------------------------------------------------------------------------
failure_uprime.points 

Input point set leading to the second failure described in the paper.

--------------------------------------------------------------------------------
slides_example.points

Input point set from sildes.

################################################################################
A NOTE ON REPRODUCIBILITY

The results as described in the paper can be achieved in an environment with a
64bit and fully IEEE 754 compliant floating-point arithmetic. If results fail to
be as expected you may try and find out whether your compiler supports any
options that force full IEEE 754 compliance. 

Modern x86 CPU have both 'old' 80bit registers and newer 64bit (SSE) registers
for floating-point arithmetic. The failures may not be reproducible if the 80bit
registers are used. For GCC on 64bit systems the default is to use the 64bit
registers only, so we are fine. For MSVC unfortunately there is no option to
force the compiler to use the 64bit registers only.

There are some measures in the code that should force the compiler to write each
intermediate result back to main memory and therefore round it to the 64bit
format. In case the original result was computed in an 80bit register, this
involves two rounding steps instead of one, i.e., double rounding, so the final
result may still be different than with only one rounding step.

That beeing said, results were successfully reproduced on

Intel Core2 T5500      openSUSE 11.4       gcc 4.5.1
AMD Neo K235           Windows 7           MSVC 10
SPARC-T3               Solaris 11          Sun C++ 5.11

Shewchuk's robust predicate impementations require a fully IEEE 754 compliant
floating-point arithmetic, too.

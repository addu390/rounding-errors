# Precision Summation Algorithms (Part 1)

- Python `math.fsum()`: Returns an accurate floating point sum of values in the iterable. Avoids loss of precision by tracking multiple intermediate partial sums.
- `fsum` [Documentation](https://docs.python.org/3/library/math.html#math.fsum).

## Installation

- [Jupyter Documentation](https://jupyter.org/install)
- Install JupyterLab with pip: `pip install jupyterlab`
- Launch JupyterLab with: `jupyter-lab`

## Using Jupyter Notebook Online:

- Try it out on [Binder](https://mybinder.org/): [https://mybinder.org/v2/gh/addu390/rounding-errors/master](https://mybinder.org/v2/gh/addu390/rounding-errors/master)
- Use Timberlea: [https://timberlea.cs.dal.ca:8000/](https://timberlea.cs.dal.ca:8000/)

---

# Robustness Problems in Planar Convex Hull Computation (Part 2)

- Command line tools and input data for demonstrating two failures of a floating-point based implementation of an algorithm for computing the convex hull of a set of points in the plane. 
- The algorithm is a plane sweep variant of Graham's scan and runs in worst case optimal time O(n log n).
- The algorithm and how it's floating-point based implementation fails are described in detail in the paper [2]
- Also contains a robust implementation of the same algorithm. The robust implementation is based on exact predicates by J.R. Shewchuk, available at [https://www.cs.cmu.edu/~quake/robust.html](https://www.cs.cmu.edu/~quake/robust.html) and described in Jonathan Richard Shewchuk, Adaptive Precision Floating-Point Arithmetic and Fast Robust Geometric Predicates, Discrete & Computational Geometry 18:305-363, 1997.

## Installation

Building is based on cmake, the central CMakeLists.txt is located in the `convex-null/src` sub-directory

- Working directory: `cd convex-hull`
- Create a build directory: `mkdir build`
- Run cmake: 
    - `cd build`
    - `cmake ../src`
- Run cmake: `make`
- Check individual orientation test results: `./test_failures`

## Run and Compare Convex Hull Algorithm(s)

- Robust: `./robust_convex_hull    ../data/failure_u.points    robust_u.output`
- Non Robust: `./nonrobust_convex_hull ../data/failure_u.points nonrobust_u.output`
- Compare results from robust/non-robust implementation: `diff robust_u.output  nonrobust_u.output`

Reading output of `diff` command: [Using Diff Command to Compare Two Files in Linux Terminal](https://linuxhandbook.com/diff-command/)

Explanation: [1] and [2]

Note: The original `README.md` for Part 2 can be found inside `convex-hull` directory.

---

# The Exact Computation Paradigm

- [CGAL Documentation](https://www.cgal.org/exact.html).
- [FAQ](https://www.cgal.org/FAQ.html#inexact_NT) section on using inexact number types. 
- The problem is that double and float are inexact number types, and as such they cannot guarantee exact results in all cases. Worse than this, small roundoff errors can have large consequences, up to the point where an algorithm crashes. Algorithms in geometric computing are particularly sensitive in this respect.

## Installation

- [Using CGAL on Unix](https://doc.cgal.org/latest/Manual/usage.html) (Linux, macOS, ...)
- [Using CGAL on Windows](https://doc.cgal.org/latest/Manual/windows.html) (with Visual C++)
  
## Running the program (Example)

- Download the [CGAL examples](https://github.com/CGAL/cgal/releases/download/v5.4/CGAL-5.4-examples.tar.xz").

- 
```
cd CGAL-5.4/examples/<example-problem>
cmake -DCMAKE_BUILD_TYPE=Release .
make
./<compiled-file>
```

## Compiling your own program:

```
cd /path/to/your/program
path/to/cgal/Scripts/scripts/cgal_create_CMakeLists -s your_program
cmake -DCMAKE_BUILD_TYPE=Release .
make
```

For example, the path is `/opt/homebrew/opt/cgal/bin/cgal_create_CMakeLists` on a Mac.

# References

> [1] “Robustness Problems in Convex Hull Computation,” wwwisg.cs.uni-magdeburg.de. http://wwwisg.cs.uni-magdeburg.de/ag/ClassroomExample/#Kettner2008 (accessed Mar. 11, 2022).

> [2] L. Kettner, K. Mehlhorn, S. Pion, S. Schirra, and C. Yap, “Classroom examples of robustness problems in geometric computations,” Computational Geometry, vol. 40, no. 1, pp. 61–78, May 2008, doi: 10.1016/j.comgeo.2007.06.003.

> [3] “Floating Point Math,” 0.30000000000000004.com. https://0.30000000000000004.com/ (accessed Mar. 11, 2022).

> [4] “The Floating-Point Guide - Exact Types,” floating-point-gui.de. https://floating-point-gui.de/formats/exact/ (accessed Mar. 11, 2022).

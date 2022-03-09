# Precision Summation Algorithms

- Python `math.fsum()`: Returns an accurate floating point sum of values in the iterable. Avoids loss of precision by tracking multiple intermediate partial sums.
- `fsum` [Documentation](https://docs.python.org/3/library/math.html#math.fsum).

## Installation

- [Jupyter Documentation](https://jupyter.org/install)
- Install JupyterLab with pip: `pip install jupyterlab`
- Launch JupyterLab with: `jupyter-lab`

# The Computational Geometry Algorithms Library ([CGAL](https://www.cgal.org/))

## The Exact Computation Paradigm

- [CGAL Documentation](https://www.cgal.org/exact.html).
- [FAQ](https://www.cgal.org/FAQ.html#inexact_NT) section on using inexact number types. 
- The problem is that double and float are inexact number types, and as such they cannot guarantee exact results in all cases. Worse than this, small roundoff errors can have large consequences, up to the point where an algorithm crashes. Algorithms in geometric computing are particularly sensitive in this respect.

## Installation

- [Using CGAL on Unix](https://doc.cgal.org/latest/Manual/usage.html) (Linux, macOS, ...)
- [Using CGAL on Windows](https://doc.cgal.org/latest/Manual/windows.html) (with Visual C++)
  
## Running the program 

```
cd CGAL-5.4
cmake -DCMAKE_BUILD_TYPE=Release .
make
./mp_float
```

## Compiling your own program is similar:

```
cd /path/to/your/program
path/to/cgal/Scripts/scripts/cgal_create_CMakeLists -s your_program
cmake -DCMAKE_BUILD_TYPE=Release .
make
```

For example, the path is `/opt/homebrew/opt/cgal/bin/cgal_create_CMakeLists` on a Mac.
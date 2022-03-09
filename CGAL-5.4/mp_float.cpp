// standard includes
#include <iostream>
#include <fstream>
#include <cassert>

// the number type
#include <CGAL/MP_Float.h>


// example that uses an exact number type

typedef CGAL::MP_Float NT;

// *** WARNING ***
// The use of a kernel based on an exact number type is highly inefficient.
// It is used in this example primarily for illustration purposes.
// In an efficiency critical context, and/or for the purposes of
// benchmarking the Apollonius_graph_filtered_traits_2<> class should
// be used.

int main() {
    NT x = 0;
    for (int i = 0; i < (1 << 25); i++) {
        x += NT(1);
    }
    printf("%f\n", CGAL::to_double(x));
}

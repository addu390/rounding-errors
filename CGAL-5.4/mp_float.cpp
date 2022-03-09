#include <iostream>
#include <fstream>
#include <cassert>

#include <CGAL/MP_Float.h>

typedef CGAL::MP_Float NT;

int main() {
    NT x = 0;
    for (int i = 0; i < (1 << 25); i++) {
        x += NT(1);
    }
    printf("%f\n", CGAL::to_double(x));
}

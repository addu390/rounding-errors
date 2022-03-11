project(another_classroom_example)

add_executable ( test_read_write
  point.hpp
  test_read_write.cpp
)

add_executable ( test_circular_sequence
  circular_sequence.hpp
  test_circular_sequence.cpp
)

add_executable ( test_failures
  robust_orientation.hpp
  nonrobust_orientation.hpp
  predicates.hpp
  predicates.cpp
  test_failures.cpp
)

add_executable ( nonrobust_convex_hull
  point.hpp
  circular_sequence.hpp 
  graham_scan.hpp
  nonrobust_orientation.hpp
  nonrobust_convex_hull.cpp
)

add_executable ( robust_convex_hull
  point.hpp
  circular_sequence.hpp
  graham_scan.hpp
  robust_orientation.hpp
  robust_convex_hull.cpp
  predicates.hpp
  predicates.cpp
)

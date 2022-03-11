#ifndef ROBUST_ORIENTATION
#define ROBUST_ORIENTATION

#include "point.hpp"
#include "predicates.hpp"

//*****************************************************************************

/*! Robust (exact) orientation predicate based on Shewchuks work. */
struct RobustOrientation
{

  RobustOrientation()
  {
    exactinit();
  }

  int operator()(const point& p, const point& q, const point& r)const
  {
      double pa[2] = {p.x,p.y};
      double pb[2] = {q.x,q.y};
      double pc[2] = {r.x,r.y};
      const double d = orient2dslow(pa,pb,pc);
      if(d > 0) return  1;
      if(d < 0) return -1;
      return 0;
  }

};

//*****************************************************************************

#endif//ROBUST_ORIENTATION

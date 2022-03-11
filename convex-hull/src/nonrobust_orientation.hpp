#ifndef NONROBUST_ORIENTATION
#define NONROBUST_ORIENTATION

#include "point.hpp"

//*****************************************************************************

/*! Nonrobust orientation predicate, straightforwar floating-point
    implementation. */
struct NonrobustOrientation
{

  int operator()(const point& p, const point& q, const point& r)const
  {
    return orient(p.x,p.y,q.x,q.y,r.x,r.y);
  }

private:

  int orient(const double px, const double py,
             const double qx, const double qy,
             const double rx, const double ry)const
  {
    //make variables volatile to ensure they are written
    //back to memory and therefore rounded to 64 bit
    //to defy 80 bit registers on MSVC
    volatile double qpx = qx-px;
    volatile double rpy = ry-py;
    volatile double rpx = rx-px;
    volatile double qpy = qy-py;
    volatile double A = qpx*rpy;
    volatile double B = rpx*qpy;
    volatile double d = A-B;
    //const double d = (qx-px)*(ry-py) - (rx-px)*(qy-py);
    if(d > 0) return  1;
    if(d < 0) return -1;
    return 0;
  }

};

//*****************************************************************************

#endif//NONROBUST_ORIENTATION

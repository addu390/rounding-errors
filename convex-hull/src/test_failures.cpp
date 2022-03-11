
#include "robust_orientation.hpp"
#include "nonrobust_orientation.hpp"
#include "point.hpp"

#include <cmath>
#include <iostream>
#include <iomanip>

//*****************************************************************************

bool check(const int result, const int expected
          ,std::string call)
{
  std::cout << call << "= " << std::setw(2) << result;
  if(result == expected) std::cout << " EXPECTED";
  else
    std::cout << " UNEXPECTED (should be " << std::setw(2) << expected << ")";
  std::cout << std::endl;

  return (result == expected);
}

//*****************************************************************************

int main(int argc, char* argv[])
{
   
  const point p(-10.04094770362331879,  -7.506293383338360492 );
  const point q(  1.056089924324703055, -0.9655180522057801307);
  const point r( -5.5608992432470305545,-2.255180522057801307 );
  const point u(  1.0560899243247048318,-0.9655180522057800196);
  const point v(  1.0560899243247043877,-0.9655180522057800196);

  bool ok = true;

  NonrobustOrientation nonrobust;
  ok &= check(nonrobust(p,q,u), 1,"nonrobust(p,q,u)");
  ok &= check(nonrobust(r,q,u),-1,"nonrobust(r,q,u)");
  ok &= check(nonrobust(p,q,v), 1,"nonrobust(p,q,v)");
  ok &= check(nonrobust(r,q,v), 0,"nonrobust(r,q,v)");
  std::cout << std::endl;

  RobustOrientation robust;
  ok &= check(robust(p,q,u),-1,"robust(p,q,u)");
  ok &= check(robust(r,q,u),-1,"robust(r,q,u)");
  ok &= check(robust(p,q,v),-1,"robust(p,q,v)");
  ok &= check(robust(r,q,v),-1,"robust(r,q,v)");
  std::cout << std::endl;

  if(!ok)
  {
    std::cout << "Not all critical orientation test results are as expected. "
              << "Failures of convex hull algorithm may not be reproducible."
              << std::endl;
    return 1;
  }

  std::cout << "All results are as expected. "
               "Failures should be reproducible." << std::endl;
  return 0;
}


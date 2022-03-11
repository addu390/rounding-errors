
#include "point.hpp"
#include "robust_orientation.hpp"
#include "graham_scan.hpp"

#include <list>
#include <iostream>
#include <sstream>
#include <iterator>

//*****************************************************************************

int main(int argc, char* argv[])
{

  if(argc < 2)
  {
      std::cerr << "usage: " << argv[0] << " [input file]" << std::endl;
      std::cerr << "       " << argv[0] << " [input file] [output file]"
                << std::endl;
    return 1;
  }

  std::string infile = argv[1];
  std::string outfile;
  if(argc > 2) outfile = argv[2];

  std::list<point> points;
  
  bool ok = read_points(infile,std::back_inserter(points));
  if(!ok)
  {
    std::cerr << "Reading '" << infile << "' failed." << std::endl;
    return 1;
  }

  std::list<point> hull;
  RobustOrientation orient;
  graham_scan(points.begin(),points.end(),orient,std::back_inserter(hull));

  if(outfile == "") return 0;

  ok = write_points(hull.begin(),hull.end(),outfile);
  if(!ok)
  {
    std::cerr << "Writing '" << outfile << "' failed." << std::endl;
    return 1;
  }

  return 0;
}

//*****************************************************************************

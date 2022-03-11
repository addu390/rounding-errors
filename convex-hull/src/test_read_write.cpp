
#include "point.hpp"

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
  
  std::stringstream sstrm;
  ok = write_points(points.begin(),points.end(),sstrm);
  if(!ok)
  {
      std::cerr << "Writing stringstream failed." << std::endl;
      return 1;
  }

  std::list<point> points_copy;
  ok = read_points(sstrm,std::back_inserter(points_copy));
  if(!ok)
  {
    std::cerr << "Reading stringstream failed." << std::endl;
    return 1;
  }

  if(points != points_copy)
  {
    std::cerr << "Points unequal after write/read on stringstream."
              << std::endl
              << "Set1: " << std::endl;
    write_points(points.begin(),points.end(),std::cerr);
    std::cerr << "Set2: " << std::endl;
    write_points(points_copy.begin(),points_copy.end(),std::cerr);
    return 1;
  }

  if(outfile == "") return 0;

  ok = write_points(points.begin(),points.end(),outfile);
  if(!ok)
  {
    std::cerr << "Writing '" << outfile << "' failed." << std::endl;
    return 1;
  }


  return 0;
}

//*****************************************************************************

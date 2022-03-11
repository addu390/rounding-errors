#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//*****************************************************************************

/*! A simple struct to store 2D points. */
struct point {

  //! constructor
  point(){}

  //! constructor
  point(const double a, const double b)
  : x(a)
  , y(b)
  {}
  
  //! x-coordinate
  double x;
  
  //! y-coordnate
  double y;

  //! compare points for equality
  bool operator==(const point& o)const
  {
    return (x == o.x) && (y == o.y);
  }

  //! compare points x-y-lexicographically
  bool operator<(const point& o)const
  {
    if(x < o.x) return true;
    if(x > o.x) return false;
    return (y < o.y);
  }

  //! write coordinates to stream, separated by whitespace
  friend std::ostream& operator<<(std::ostream& strm,const point& p)
  {
    strm << p.x << " " << p.y;
    return strm;
  }

  //! read coordinates from stream
  friend std::istream& operator>>(std::istream& strm,point& p)
  {
    strm >> p.x >> p.y;
    return strm;
  }
};

//*****************************************************************************

/*! \brief Read points from a stream.

Each point must be on a separate line, coordinates are separated by whitespace.
Lines starting with a # are ignored, empty lines are skipped.

Points are added to out, returns true if reading succeeded.*/

template <class OutputIterator>
bool read_points(std::istream& strm, OutputIterator out)
{

  while(true)
  {
    std::string line;
    std::getline(strm,line);

    if(strm.fail()) break;

    if(line[0] == '#') continue;

    std::stringstream linestrm(line);

    point p;
    linestrm >> p;

    if(linestrm.fail()) return false;

    *out = p;
    ++out;

    if(strm.eof()) break;
  }

  return true;
}
//*****************************************************************************

/*! \brief Read points from a file.

Points must be in the same format as for reading from a stream.
Returns true if reading succeeded.
*/

template <class OutputIterator>
bool read_points(const std::string& filename, OutputIterator out)
{
  std::ifstream strm(filename.c_str());
  if(!strm) return false;
  return read_points(strm,out);
}

//*****************************************************************************

/*! \brief Write points to a stream.

Each point in [begin,end) is put on a separate line, coordinates a separated
by whitespace.  Returns true, if writing succeeded. */
template <class ForwardIterator>
bool write_points(ForwardIterator begin, ForwardIterator end
                 , std::ostream& strm)
{

  std::streamsize old_prec = strm.precision();
  strm.precision(18);

  while(begin != end)
  {
    strm << *begin << "\n";
    ++begin;
  }

  strm.precision(old_prec);

  return strm.good();
}
//*****************************************************************************

/*! \brief Write points to a file.

Points are written in the same format as when writing to a stream. Returns
true, if writing succeeded. */
template <class ForwardIterator>
bool write_points(ForwardIterator begin, ForwardIterator end
                 , const std::string& filename)
{
  std::ofstream strm(filename.c_str());
  if(!strm) return false;
  return write_points(begin,end,strm);
}

//*****************************************************************************

#endif//POINT_HPP

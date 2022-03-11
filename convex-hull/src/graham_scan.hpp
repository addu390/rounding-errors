#ifndef GRAHAM_SCAN
#define GRAHAM_SCAN

#include "point.hpp"
#include "circular_sequence.hpp"

#include <list>
#include <vector>
#include <algorithm>
#include <iterator>

//*****************************************************************************

template < class ReversibleContainer
         , class OrientationTest >
typename ReversibleContainer::iterator
find_upper_tangent( ReversibleContainer& hull
                  , size_t hull_size
                  , typename ReversibleContainer::iterator t
                  , const point& u
                  , const OrientationTest& orient)
{
  typedef typename ReversibleContainer::iterator iterator;

  iterator succt = circular_successor(hull,t);

  while(orient(*succt,*t,u) >= 0)
  {
    t = succt;
    succt = circular_successor(hull,t);
    if(hull_size == 2) break;
  }

  return t;
}

//*****************************************************************************

template < class ReversibleContainer
         , class OrientationTest >
typename ReversibleContainer::iterator
find_lower_tangent( ReversibleContainer& hull
                  , size_t hull_size
                  , typename ReversibleContainer::iterator t
                  , const point& u
                  , const OrientationTest& orient)
{
  typedef typename ReversibleContainer::iterator iterator;

  iterator predt = circular_predecessor(hull,t);

  while(orient(*predt,*t,u) <= 0)
  {
    t = predt;
    predt = circular_predecessor(hull,t);
    if(hull_size == 2) break;
  }

  return t;
}

//*****************************************************************************

/*! A plane sweep variant of grahams scan. */
template < class ForwardIterator
         , class OrientationTest
         , class OutputIterator >
OutputIterator
graham_scan( ForwardIterator begin, ForwardIterator end
           , const OrientationTest& orient
           , OutputIterator out)
{
  //copy input points
  std::vector<point> points;
  std::copy(begin,end,std::back_inserter(points));

  //sort points x-y-lexicographically
  std::sort(points.begin(),points.end());

  //index to point that we currently handle
  size_t i=0;

  //type for handles to points in convex hull
  typedef std::list<point>::iterator handle_t;

  //extreme points in ccw order
  std::list<point> hull;

  //number of extreme points
  size_t hull_size=0;

  //initialize convex hull from first two points
  handle_t last_inserted = hull.begin();
  while(i < 2 && i < points.size())
  {
    last_inserted = hull.insert(last_inserted,points[i]);
    ++hull_size;
    ++i;
  }

  //handle remaining points
  while(i < points.size())
  {
    //find upper and lower tangents
    handle_t upper_tangent
      = find_upper_tangent(hull,hull_size,last_inserted,points[i],orient);
    handle_t lower_tangent
      = find_lower_tangent(hull,hull_size,last_inserted,points[i],orient);

    //remove hull points strictly between lower and upper
    //tangent point
    handle_t rm = lower_tangent;
    rm = circular_successor(hull,rm);
    while(rm != upper_tangent)
    {
      handle_t tmp = circular_successor(hull,rm);
      hull.erase(rm);
      --hull_size;
      rm = tmp;
    }

    //insert new point between lower and upper tangent point
    last_inserted = hull.insert(upper_tangent,points[i]);
    ++hull_size;

    ++i;
  }

  //copy hull points to output
  return std::copy(hull.begin(),hull.end(),out);
}

//*****************************************************************************

#endif//GRAHAM_SCAN

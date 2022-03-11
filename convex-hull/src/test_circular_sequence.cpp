
#include "circular_sequence.hpp"

#include <list>
#include <iostream>
#include <cstdlib>

//*****************************************************************************

int main(int argc, char* argv[])
{
  if(argc < 2)
  {
    std::cerr << "usage: " << argv[0] << " [num elements]" << std::endl;
    return 1;
  }

  size_t n = std::atoi(argv[1]);

  typedef std::list<size_t>::iterator circulator;
  std::list<size_t> elements;

  for(size_t i=0;i<n;++i) elements.push_back(i);

  { //test forward iteration
    circulator c = elements.begin();
    for(size_t i=0;i<n/2;++i)
      c = circular_successor(elements,c);
    circulator d = c;

    if(c != elements.end())
    {
       do
       {
         std::cout << *c << " ";
         c = circular_successor(elements,c);
       }
       while (c != d);
       std::cout << std::endl;
    }
  }

  { //test backward iteration
    circulator c = elements.begin();
    for(size_t i=0;i<n/2;++i)
      c = circular_predecessor(elements,c);

    circulator d = c;

    if(c != elements.end())
    {
       do
       {
         std::cout << *c << " ";
         c = circular_predecessor(elements,c);
       }
       while (c != d);
       std::cout << std::endl;
    }
  }
}

//*****************************************************************************


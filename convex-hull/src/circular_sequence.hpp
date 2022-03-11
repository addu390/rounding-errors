#ifndef CIRCULAR_SEQUENCE_HPP
#define CIRCULAR_SEQUENCE_HPP

//*****************************************************************************

template <class ReversibleContainer>
typename ReversibleContainer::iterator
circular_successor( ReversibleContainer& container
                  , const typename ReversibleContainer::iterator& it)
{
  typedef typename ReversibleContainer::iterator iterator;

  if(it == container.end()) return it;

  iterator tmp = it;
  ++tmp;
  if(tmp != container.end()) return tmp;
  return container.begin();
}

//*****************************************************************************

template <class ReversibleContainer>
typename ReversibleContainer::iterator
circular_predecessor( ReversibleContainer& container
                    , const typename ReversibleContainer::iterator& it)
{
  typedef typename ReversibleContainer::iterator iterator;

  if(it == container.end()) return it;

  iterator tmp=it;
  if(tmp != container.begin()) return --tmp;
  return --container.end();
}

//*****************************************************************************

#endif//CIRCULAR_SEQENCE_HPP

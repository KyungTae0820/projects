#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <algorithm>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;
  void heapify_trickleUp(int loc);
  void heapify_trickleDown(int loc);

private:
  int ary;
  PComparator comp;
  std::vector<T> vecHeap;
};

// Add implementation of member functions
//heapify_trickleUp
template <typename T, typename PComparator>
void Heap<T, PComparator>::heapify_trickleUp(int loc){
  while(loc > 0){
    int parentIdx = (loc - 1)/ary;
    if(!comp(vecHeap[loc], vecHeap[parentIdx])) break;

    std::swap(vecHeap[loc], vecHeap[parentIdx]);
    loc = parentIdx;
  }
}

//heapify_trickleDown
template <typename T, typename PComparator>
void Heap<T, PComparator>::heapify_trickleDown(int loc){
  while(true){
    std::size_t lChild = ary*loc + 1;
    if(lChild >= vecHeap.size()) return;
    std::size_t smallerChild = lChild;
    for(int i = 1; i < ary; i++){
      std::size_t nextChild = lChild + i;
      if(nextChild < vecHeap.size() && comp(vecHeap[nextChild], vecHeap[smallerChild])){ //check rChild Exist
          smallerChild = nextChild;
        }
    }

    if(!comp(vecHeap[smallerChild], vecHeap[loc])) break;
    
    std::swap(vecHeap[smallerChild], vecHeap[loc]);
    loc = smallerChild;
  }
}


//Constructor
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : ary(m), comp(c){}

//Destructor
template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap(){}

//Push
template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item){
  vecHeap.push_back(item);
  //heapify need one trickle up
  heapify_trickleUp(vecHeap.size()-1);
}

//Empty
template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const{
  return vecHeap.empty();
}

//Size
template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const{
  return vecHeap.size();
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){

    throw std::underflow_error("Top From Empty Heap");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return vecHeap[0];
}


// pop() to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    throw std::underflow_error("Pop From Empty Heap");
  }
  std::swap(vecHeap[0], vecHeap.back());
  vecHeap.pop_back();
  if(!empty()){
    heapify_trickleDown(0);
  }
}



#endif


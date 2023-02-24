#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>

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
  void push(const T& item); // 

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
  void pop(); //

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

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> tree;
  PComparator comp_;
  size_t heap_max;
  void heapify(std::size_t index = 0);
  void trickleUp(std::size_t index);


};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) :comp_(c),heap_max(m){
}


template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap(){
  // while(!empty()){
  //   tree.pop_back();
  // }

}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================

    throw std::underflow_error("heap is empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return tree[0];

}

template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
    if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("heap is empty");
  }
  std::swap(tree[0], tree[tree.size()-1]);
  
  tree.pop_back();

  heapify();
}


template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item)
{
  if (tree.size() == tree.max_size()){
    throw std::overflow_error("heap is at max ");
  }

  tree.push_back(item);
  trickleUp(tree.size()-1);
}



template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return tree.size() == 0;

}


template <typename T, typename PComparator>
std::size_t Heap<T,PComparator>::size() const
{
  return tree.size();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(std::size_t index) {
    std::size_t bestChild = index * heap_max + 1;
    if (bestChild >= tree.size()) {
        return;
    }

    while (bestChild < tree.size()) {
        std::size_t i = bestChild;
        for (std::size_t j = 1; j < heap_max && i + j < tree.size(); ++j) {
            if (comp_(tree[i + j], tree[bestChild])) {
                bestChild = i + j;
            }
        }

        if (comp_(tree[bestChild], tree[index])) {
            std::swap(tree[index], tree[bestChild]);
            index = bestChild;
            bestChild = index * heap_max + 1;
        } else {
            break;
        }
    }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(std::size_t index) {
    std::size_t parentIndex = (index - 1) / heap_max;

    while (index > 0 && comp_(tree[index], tree[parentIndex])) {
        std::swap(tree[index], tree[parentIndex]);
        index = parentIndex;
        parentIndex = (index - 1) / heap_max;
    }
}

#endif
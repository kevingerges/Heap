#ifndef HEAP_H
#define HEAP_H
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
  size_t heap_size;
  int m_;



};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c)
    : tree(std::vector<T>()),
      comp_(c),
      heap_size(0),
      m_(std::max(m, 2)) {}


template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap(){}


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
  if (empty()) {
    throw std::underflow_error("Heap is empty");
  }

  std::swap(tree[0], tree[tree.size() - 1]);

  T x = tree[tree.size() - 1];
  tree.pop_back();

  if (!empty()) {
    size_t current = 0;
    size_t child = 1;

    while (child < tree.size()) {

      size_t max_child = child;
      for (size_t i = 1; i < m_; ++i) {
        if (child + i >= tree.size())
        { 
          break;
        }
        if (comp_(tree[child + i], tree[max_child])) 
        {
          max_child = child + i;
        }
      }
      if (comp_(tree[current], tree[max_child])) 
      {
        break;
      }
      std::swap(tree[current], tree[max_child]);
      current = max_child;
      child = current * m_ + 1;
    }

    tree[current] = x;
    --heap_size;
  }
}



template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item)
{
  tree.push_back(item);
  ++heap_size;

  size_t i = tree.size() - 1;
  T temp = tree[i];

  while (i > 0) {
    size_t parent = (i - 1) / m_;
    if (comp_(temp, tree[parent])) 
    {
      tree[i] = tree[parent];
      i = parent;
    } 
    else 
    {
      break;
    }
  }
  tree[i] = temp;
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

#endif


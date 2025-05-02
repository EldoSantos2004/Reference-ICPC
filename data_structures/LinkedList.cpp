/*
  Linked list
  -------------------------------------
  Time Complexity:
    -insert: O(1)
  Space Complexity: O(n)

  -Can be adapted for rectangular grids by using n, m separately
*/
// === Constructors and Destructor ===
// list()               // Default constructor, creates an empty list.
// list(n, val)          // Creates a list with 'n' elements, all initialized to 'val'.
// list(first, last)     // Creates a list from another range (e.g., another list or array).
// list(const list& other) // Copy constructor.
// list(list&& other)    // Move constructor.
// ~list()               // Destructor, destroys the list.

// === Iterators ===
// begin()               // Returns an iterator to the first element of the list.
// end()                 // Returns an iterator to the position just past the last element.
// rbegin()              // Returns a reverse iterator to the last element.
// rend()                // Returns a reverse iterator to the position just before the first element.
// insert(it, val)       // Inserts 'val' before the position of the iterator 'it'.
// erase(it)             // Removes the element at the position of the iterator 'it'.
// erase(first, last)    // Removes a range of elements from 'first' to 'last'.
// push_back(val)        // Adds 'val' to the end of the list.
// push_front(val)       // Adds 'val' to the front of the list.
// pop_back()            // Removes the last element of the list.
// pop_front()           // Removes the first element of the list.
// clear()               // Removes all elements from the list.

// === Capacity ===
// empty()               // Returns true if the list is empty, otherwise false.
// size()                // Returns the number of elements in the list.
// max_size()            // Returns the maximum number of elements the list can hold.

// === Modifiers ===
// insert(it, n, val)    // Inserts 'n' copies of 'val' before the position of 'it'.
// insert(it, first, last) // Inserts a range of elements before the position of 'it'.
// remove(val)            // Removes all occurrences of 'val' from the list.
// remove_if(pred)        // Removes all elements that satisfy the predicate 'pred'.
// unique()               // Removes consecutive duplicate elements from the list.
// merge(other)           // Merges two sorted lists into one sorted list.
// merge(other, pred)     // Merges two sorted lists into one sorted list using custom comparison 'pred'.
// splice(it, other)      // Transfers elements from another list 'other' to the list at position 'it'.
// splice(it, other, it2) // Transfers an element from another list 'other' at position 'it2' to the list at position 'it'.
// splice(it, other, first, last) // Transfers a range from another list 'other' from 'first' to 'last' to the list at position 'it'.
// reverse()              // Reverses the order of elements in the list.
// sort()                 // Sorts the elements in the list in ascending order.
// sort(comp)             // Sorts the elements in the list using custom comparison 'comp'.
// swap(other)            // Swaps the content of the list with another list 'other'.

// === Element Access ===
// front()               // Returns a reference to the first element in the list.
// back()                // Returns a reference to the last element in the list.

// === Search ===
// find(val)             // Returns an iterator to the first occurrence of 'val'.
// find_if(pred)         // Returns an iterator to the first element satisfying the predicate 'pred'.
// count(val)            // Returns the number of occurrences of 'val' in the list.
// count_if(pred)        // Returns the number of elements satisfying the predicate 'pred'.
// equal_range(val)      // Returns a pair of iterators representing the range of elements equal to 'val'.

// === Other Functions ===
// swap(other)           // Swaps the contents of the list with another list 'other'.
// emplace(it, args...)  // Constructs and inserts an element at the position 'it' using 'args...' (perfect forwarding).
// emplace_front(args...) // Constructs and inserts an element at the front using 'args...' (perfect forwarding).
// emplace_back(args...)  // Constructs and inserts an element at the back using 'args...' (perfect forwarding).

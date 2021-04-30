#ifndef __REF_MANAGER_H_
#define __REF_MANAGER_H_

#include <iostream>
#include <unordered_map>
#include <assert.h>

using namespace std;

#define MAX_PTRS 100
#define MAX_GARBAGE 100

class ReferenceManager {
public:
  // constructor
  ReferenceManager();

  // destructor
  ~ReferenceManager();

  // run the garbage collection on every pointer that is enqueued for
  // garbage collection
  void garbageCollect();

  // reassign the pointer at this index to point to the new address
  // if this causes the number of references to a string to drop to 0,
  // enqueue that pointer to be garbage collected
  void reassignPointer(unsigned int ptrIndex, const char* new_address);

  // allocate space for a string of size length (plus space for the
  // null terminator), read the string from the user and then reassign
  // the pointer at ptrIndex to the newly allocated string
  void readString(unsigned int ptrIndex, unsigned int length);

  // return the pointer held at the given pointer index
  const char* getPtr(unsigned int ptrIndex);

private:
  unordered_map<const char*, int> refCount;
  const char *pointers[MAX_PTRS];
  const char *garbage[MAX_GARBAGE];
  int numToDelete;
};

#endif

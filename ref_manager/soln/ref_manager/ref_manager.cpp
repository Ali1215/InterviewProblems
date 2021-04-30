#include "ref_manager.h"
/*
Name:  Ali Muneer
ID :   1615694
Acknowledgements: None
CMPUT 275, Winter 2021
Weekly Exercise 3
*/


ReferenceManager::ReferenceManager() {
  numToDelete = 0;
  for (int i = 0; i < MAX_PTRS; i++) {
    pointers[i] = NULL;
  }
}

ReferenceManager::~ReferenceManager() {
  /*
  Description: This destructor will set all pointers to NULL and collect garbage.
  */
  for (int i = 0; i < MAX_PTRS; i++) {
    //assign each pointer to NULL
    reassignPointer(i, NULL);
  }
  garbageCollect();
}

void ReferenceManager::garbageCollect() {
  /*

    Description: this function will set all pointers to NULL and garbage collect
    args = none
    returns = none
  */
  for( int i = 0; i < numToDelete; i++){
    //print out each element of garbage array then deallocate
    cout << garbage[i] << endl;
    delete[] garbage[i];
  }
  
  // all garbage is collected so no garbage to delete
  numToDelete = 0;
  
}

void ReferenceManager::reassignPointer(unsigned int ptrIndex, const char* newAddr) {
  /*
    Description:  Swaps elements in the pointer array at a given index for a given new pointer
                  while keeping the refCount updated

    args: ptrIndex  = positive integer showing index of pointers[] to replace
          newAddr   = pointer to const char that will be inserted
    
    returns: none
  */

  const char* currAddress = pointers[ptrIndex];
  if (currAddress!= NULL){
    // if the address being replaced is not NULL
    // decrement the reference count and check if
      refCount[currAddress]--;
      if (refCount[currAddress] == 0){
        //mark for deallocation and add 1 more to delete
        garbage[numToDelete] = pointers[ptrIndex];
        numToDelete++;
      }
     
  }
  pointers[ptrIndex] = newAddr;
  if (newAddr != NULL){
    //update reference count if new address is not NULL

    // see if new pointer exists already in map
    if (refCount.find(newAddr) != refCount.end()) {
      refCount[pointers[ptrIndex]]++;
    }
    else {
      // if non-existent, intialize it to 1
      refCount[pointers[ptrIndex]] = 1;
    }
    
  }
  return;
}

void ReferenceManager::readString(unsigned int ptrIndex, unsigned int length) {
  /*
    Description:  Stores input from standard in, into a dynamically allocated char[]

    args: ptrIndex  = positive integer showing index of pointers[] to replace
          length   = length of the string
    
    returns: none
  */
  
  //allocate space for char array plus null character
  char *str = new char[length + 1];
  cin >> str;
  
  //call reassign pointer
  reassignPointer(ptrIndex, str);

  return;
}

const char* ReferenceManager::getPtr(unsigned int ptrIndex) {
  assert(ptrIndex < MAX_PTRS);
  return pointers[ptrIndex];
}
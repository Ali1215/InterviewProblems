#include <iostream>
#include "ref_manager.h"
#include <assert.h>

using namespace std;

int main() {
  ReferenceManager memory;

  while (true) {
    char query;
    cin >> query;

    if (query == 'c') {
      int ptrIndex, strLen;
      cin >> ptrIndex >> strLen;
      memory.readString(ptrIndex, strLen);
    }
    else if (query == 's') {
      int ptrIndex1, ptrIndex2;
      cin >> ptrIndex1 >> ptrIndex2;
      const char* ptr = memory.getPtr(ptrIndex2);

      memory.reassignPointer(ptrIndex1, ptr);
    }
    else if (query == 'q') {
      int ptrIndex;
      cin >> ptrIndex;
      const char* ptr = memory.getPtr(ptrIndex);
      if (ptr == NULL) {
        cout << "NULL" << endl;
      }
      else {
        cout << ptr << endl;
      }
    }
    else if (query == 'g') {
      memory.garbageCollect();
    }
    else if (query == 'e') {
      break;
    }
    else {
      assert(false);
    }
  }

  // the destructor for the memory manager will free up all remaining strings:
  // namely those currently queued for garbage collection and those that
  // still have references
  return 0;
}

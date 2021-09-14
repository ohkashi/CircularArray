# CircularArray
Double Buffered Circular Array

[![Licence](https://img.shields.io/badge/license-MIT-blue.svg?style=flat)](LICENSE)

## Example
```cpp
#include "CircularArray.h"

using namespace std;

int main()
{
    CircularArray<int> arTest(10);
    cout << arTest.GetCount() << endl;
    for (int i = 0; i < 100; i++)
        arTest.Add(i % 10);
    cout << arTest.GetCount() << " " << arTest.GetTail() << endl;
}
```

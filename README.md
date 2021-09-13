# CircularArray
Double Buffered Circular Array

## Example
~~~cpp
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
~~~

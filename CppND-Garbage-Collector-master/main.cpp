#include "gc_pointer.h"
#include "LeakTester.h"
#include<iostream>
int main()
{
    Pointer<int> p = new int(19);
    p = new int(21);
    p = new int(28);

    Pointer<int> t(p);
    Pointer<int> c;
    c=p;
    

    return 0;
}
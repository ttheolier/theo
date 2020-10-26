#include <vector>
#include <functional>
#include <iostream>
#include <cstdlib>
#include "heap.h"

using namespace std;


int main() {
    Heap<string, greater<string> > max_heap(2);
    //cerr<<1<<endl;
   /* for(size_t i = 0; i < 20; i++) {
        //cerr<<i<<endl;
        max_heap.push(rand() % 100);
        //max_heap.print();
        //cerr<<endl;
    }
    cerr<<endl;*/
    
    max_heap.push("tv");
    max_heap.push("ps4");
    max_heap.push("laptop");
    max_heap.push("apple");
    max_heap.push("clown");
    //max_heap.print();
    cerr<<endl;
    //cerr<<2<<endl;
    //[1,2,3,4,5]
    //5 is first index
    //int i =0;
    while (!max_heap.empty()) {
        cout << max_heap.top() << " ";
        max_heap.pop();
    }
    cout << endl;
    //cerr<<"end while"<<endl;
    //5 4 3 2 1
    Heap<int> min_heap(3);

    for (size_t i = 0; i < 20; i++) {
        min_heap.push(rand() % 100);
    }
    //min_heap.print();
    cerr<<endl;
    while (!min_heap.empty()) {
        cout << min_heap.top() << " ";
        min_heap.pop();
    }
    cout << endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "quicksort.h"
#include <string>

using namespace std;


int main() {
    srand(time(NULL));
    vector<string> test;
    test.push_back("zoo");
    test.push_back("bad");
    test.push_back("mother");
    

    
    quicksort(test, std::greater<string> {});

    for (unsigned int i = 0; i < test.size(); i++) {
        cout << test[i] << " ";
    }
    cout << endl;

    /*srand(time(NULL));
    vector<double> test;
    for (int i =0; i < 100; i++) {
        test.push_back(double(rand() % 1000)*.90);
    }

    quicksort(test, std::less<double> {});
    //cout<<"a"<<endl;
    for (int i = 0; i < 100; i++) {
        cout << test[i] << " ";
    }
    cout << endl;*/

    return 0;
}

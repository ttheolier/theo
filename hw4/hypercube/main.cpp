#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "hypercube.h"

using namespace std;


int main(int argc, char* argv[]) {
    if (argc != 3) {
        return 2;
    }

    ifstream permitted(argv[1]);
    HyperCube h;
    //cerr<<100<<endl;
    h.read(permitted);
    //cerr<<"hi"<<endl;
    SearchResult result = h.search(argv[2]);

    if (result.found) {
        for (size_t i = 0; i < result.path.size(); i++){
            cout << result.path[i] << endl;
        }
        cout << result.expansions << endl;
        return 0;
    } else {
        cout << "no path" << endl << result.expansions << endl;
        return 1;
    }
}

#include <iostream>
#include <chrono>

#include "SuperVector.h"
using namespace std;
int main() {
    std::cout << "VEKTOR" << std::endl;

    vector<int> v1;
/*    auto start = std::chrono::high_resolution_clock::now(); //laiko matavimo start
    int size = v1.size();
    cout << v1.capacity() << endl;
    cout << v1.size() << endl << endl;

    if(v1.empty()) cout << "empty" << endl;*/

    for(auto i = 0; i < 10; i++)  v1.push_back(i);

    for(auto v: v1)  cout << v << " ";
    cout << endl;
    vector<int>::iterator it = v1.end();
    it = v1.begin();
    v1.insert(it+5, {10, 10, 10, 80, 40});
    v1.pop_back();
    v1.pop_back();
    v1.pop_back();
    v1.pop_back();
    v1.pop_back();
    v1.pop_back();
    for(auto v: v1)  cout << v << " ";
    cout << endl;
    v1.erase(it+2);
    for(auto v: v1)  cout << v << " ";
    v1.clear();
    cout << endl;
    cout << v1.size() << " ";
    cout << v1.capacity() << " ";


/*    auto finish = std::chrono::high_resolution_clock::now(); //laiko matavimo start
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "turbo vector finish: " << elapsed.count() << std::endl;*/

    return 0;
}
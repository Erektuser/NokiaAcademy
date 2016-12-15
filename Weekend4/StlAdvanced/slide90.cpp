#include <list>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;

#if 0
template <typename Iter>
void zeroIt(Iter first, Iter last) {
    cout << "memset-";
    memset(first, 0, std::distance(first, last) * sizeof(*first));
}
#endif

template <typename Iter>
void zeroIt(Iter first, Iter last) {
    cout << "forloop-";
    for (; first != last; ++first) *first = {};
}

int main() {
    int a[] = {1, 2, 3};
    std::string b[] = {"1", "2", "3"};
    std::list<int> c = {1, 2, 3};
    zeroIt(std::begin(a), std::end(a));
    zeroIt(std::begin(b), std::end(b));
    zeroIt(std::begin(c), std::end(c));
}

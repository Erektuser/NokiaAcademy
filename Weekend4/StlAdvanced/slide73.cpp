// TODO
#if 0

template <class ForwardIt, class T>
std::size_t removeAndCountNotRemoved(ForwardIt first, ForwardIt last, const T& value)
{
    // TODO: Implement
}

#endif

int main() {
#if 0
    std::list<int> ll{1,2,3,3,4};
    auto notRemoved = removeAndCountNotRemoved(ll.begin(), ll.end(), 3);
    std::copy(ll.begin(), ll.end(), std::ostream_iterator<int>(cout, "-"));
    cout << "\nNot removed: " << notRemoved;
#endif
}

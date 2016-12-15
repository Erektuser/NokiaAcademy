template <class Container, class T>
void clear(Container& container, const T& value) {
    // TODO: Implement
}
int main() {
#if 0
    std::list<int> ll{1,2,3,3,4};
    clear(ll, 3);
    std::copy(ll.begin(), ll.end(), std::ostream_iterator<int>(cout, "-"));

    std::string msg = "Hello World!";
    clear(msg, 'l');
    cout << msg.data();
#endif
}

#include <iostream>
#include "Stack.hpp"
int main() {
    Stack<int> s;
    s.push(1 + 3);
    int i = 3;
    s.push(i);
    std::cout << s.top() << std::endl;
}
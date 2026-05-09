#include <iostream>

int add(int a, int b) {
    return a + b;
}

int main() {
    int x = 3;
    int y = 5;

    std::cout << x << " + " << y << " = " << add(x, y) << '\n';
    return 0;
}

#include <stdio.h>

struct my_struct {
    char first;
    long second;
    char third;
    long fourth;
};

int main(void) {
    struct my_struct test;
    test.first = 'a';
    test.second = 2;
    test.third = 'b';
    test.fourth = 2;
    printf("Hello World! %c %ld %c %ld", test.first, test.second, test.third, test.fourth);
}

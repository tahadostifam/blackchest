#include <stdio.h>

void do_something(char name[]) {
    printf("Hi, %s\n", name);
}

int main()
{
    void (*my_func)(char[]);

    my_func = do_something;

    my_func("Hello");

    return 0;
}
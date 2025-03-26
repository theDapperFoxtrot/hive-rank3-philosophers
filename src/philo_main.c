#include "../include/philo.h"

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;
    char *test;

    test = "a";
    memset(test, 0, 1);
    printf("Hello, %s\n", "Steve");
    printf("Variable value: %s\n", test);

    return (0);
}

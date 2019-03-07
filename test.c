#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *test = "Hello World";
    char test2[24] = {0, };
    strcpy(test2, test);
    printf("%s\n", test2);
    return 0;
}

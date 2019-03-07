#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    const char *testString = "Hello World!";
    FILE *hFile = fopen("hiddenFile.txt", "wb");
    fwrite(testString, sizeof(char), strlen(testString), hFile);
    fclose(hFile);
    return 0;
}

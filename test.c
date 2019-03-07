#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char buffer[1024] = { 0, };
	const char *filename = "hiddenFile.txt";
	const char *filename2 = "hiddenFile2.txt";
	strcpy(buffer, "Hello World!");\
    
	umask(0);

    FILE *hFile = fopen(filename, "wb");
    fwrite(buffer, sizeof(char), strlen(buffer), hFile);
    fclose(hFile);

    rename(filename, filename2);

    hFile = fopen(filename2, "wb");
    fwrite(buffer, sizeof(char), sizeof(buffer), hFile);
    puts(buffer);
    fclose(hFile);

    remove(filename2);
    return 0;
}

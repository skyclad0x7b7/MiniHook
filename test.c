#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char buffer[1024] = { 0, };
    const char *filename = "test_output_file.txt";
    const char *filename2 = "test_output_file_2.txt";
    strcpy(buffer, "Hello World!");
    
    access("/etc/init.d", 0);
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

    pid_t childPid = fork();
    if(childPid)
    {
        // Parent Process
        const char *parent_filename = "ParentFile.txt";
        FILE *hParentFile = fopen(parent_filename, "wb");
        fwrite(buffer, sizeof(char), strlen(buffer), hParentFile);
        fclose(hParentFile);
    }
    else
    {
        // Child Process
        const char *child_filename = "ChildFile.txt";
        FILE *hChildFile = fopen(child_filename, "wb");
        fwrite(buffer, sizeof(char), strlen(buffer), hChildFile);
        fclose(hChildFile);
    }
    return 0;
}

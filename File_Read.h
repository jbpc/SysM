// #include <stdlib.h>
// #include <string.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <unistd.h>
// #include <fcntl.h>
char File_Read(char *Address, char *Content, int Content_Length){
//*************************************************************************************************************************
    int File = open(Address, O_RDWR);
    if (File == -1){
        return 'X';
    }
    if (read(File, Content, Content_Length) == -1){
        close(File);
        return 'X';
    }
    if (close(File) == -1){
        return 'X';
    }
    return 'V';
}

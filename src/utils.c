#ifdef linux
#include <unistd.h>
#endif

#include <errno.h>
#include <string.h>
#include "utils.h"

char* get_file_ext(const char* file_name, char* file_ext){
    size_t len = strlen(file_name);
    size_t i = len;
    
    while( i>0 && file_name[i-1] != '.') i--;
    if(i == 0){
        file_ext[0] = '\0';
        return file_ext;
    }
    int j = 1;
    while(i < len){
        file_ext[j] = file_name[i];
        j++;i++;
    }
    
    file_ext[0] = '.';
    file_ext[j] = '\0';
    return file_ext;
}

int file_exist(const char* file_name){
#ifdef linux
    return access(file_name, F_OK);
#endif

#ifdef WIN32
    return _access(file_name, 0);
#endif
}

int end_with(const char* str, char ch) {
    int len = strlen(str);
    return str[len - 1] == ch ? 0 : 1;
}

int start_with(const char* str, char ch) {
    if (str != NULL) {
        return str[0] == ch ? 0 : 1;
    }
    return 1;
}
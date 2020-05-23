#include <stdio.h>
#include <sys/types.h>
#ifdef linux
#include <unistd.h>
#include <dirent.h>
#elif defined WIN32
#include <direct.h>
#include <io.h>
#endif

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "tree.h"
#include "config.h"
#include "map.h"
#include "color.h"
#include "utils.h"

static RBRoot* configs = NULL;

void combine_path(char* parent_dir, const char* success_dir){
    size_t parent_len = strlen(parent_dir);
    if(parent_dir[parent_len] != '/' && success_dir[0] != '/'){
#ifdef linux
        strcat(parent_dir, "/");
#elif defined WIN32
        int len = strnlen_s(parent_dir, 1000) + strnlen_s("/", 1000) + 1;
        errno_t error = strcat_s(parent_dir, len, "/");
#endif

    }
    else if(parent_dir[parent_len] == '/' && success_dir[0] == '/'){
        parent_dir[parent_len-1] = '\0';
    }
    else{   
    }

#ifdef linux
    strcat(parent_dir, success_dir);
#elif defined WIN32
    int len = strnlen_s(parent_dir, 1000) + strnlen_s(success_dir, 1000) + 1;
    errno_t error = strcat_s(parent_dir, len, success_dir);
#endif
}

int split_colors(const char* str, char* fore, char* back){
    int len = strlen(str);
    int i = 0;
    for(int i = 0; i<len; i++){
        if(str[i] == ','){
            break;
        }
    }
    
    for(int j = 0; j<i; j++){
        fore[j] = str[j];
    }
    fore[i] = '\0';
    
    i++;
    int j = 0;
    for(; i<len; i++){
        if(str[i]== '\r' || str[i] == '\n') continue;
        back[j] = str[i];
        j++;
    }
    back[j] == '\0';

    return 0;
}

#ifdef linux
void _print_directory(const char* dir_name, const char* space){
    
    DIR* dir = opendir(dir_name);
    if (dir == NULL) {
        perror("color tree error message: ");
        return;
    }

    struct dirent* entry = NULL;

    while (NULL != (entry = readdir(dir))) {
        if (0 == strcmp(entry->d_name, "..") || 0 == strcmp(entry->d_name, ".")) {
            continue;
        }

        if (entry->d_type == DT_DIR) {      //This is a directory.
            printf("\033[32m%s%s\n\033[0m", space, (char*)entry->d_name);
            char new_dir[1024] = { 0 };
            strcpy(new_dir, dir_name);
            if (strcmp(dir_name, "/") != 0) {
                strcat(new_dir, "/");
            }
            strcat(new_dir, entry->d_name);
            char new_space[1024];
            strcpy(new_space, space);
            strcat(new_space, "  ");
            _print_directory(new_dir, new_space);
        }
        else if (entry->d_type == DT_LNK) {      //This is a symbolic link.
            printf("\033[34m%s%s\n\033[0m", space, (char*)entry->d_name);
        }
        else if (entry->d_type == DT_REG) {      //This is a regular file.
            char ext[10] = {'\0'};
            get_file_ext((char*)entry->d_name, ext);
            Pair pair;
            int result = get(configs, ext, &pair);
            
            char color_setting[30]= {'\0'};
            assemble_color_config(pair.value, color_setting);
            
            color_print(color_setting, "%s%s\n", space, (char*)entry->d_name);
        }
    }

    closedir(dir);
}
#elif defined WIN32
void _print_directory(const char* dir_name, const char* space){
    if (end_with(dir_name, '\\') != 0) {
        strcat_s(dir_name, 1000, "\\");
    }

    struct _finddata_t fa;
    char temp_path[1024] = { '\0' };
    memcpy(temp_path, dir_name, strlen(dir_name) + 1);
    strcat_s(temp_path, 1000, "*");
    long handle = _findfirst(temp_path, &fa);
    if (handle == -1L) return;

    do
    {
        if ((strcmp(fa.name, ".") == 0) || (strcmp(fa.name, "..") == 0)) continue;

        if ((fa.attrib & _A_SUBDIR) != 0) {
            char new_path[1024] = { '\0' };
            memcpy(new_path, dir_name, strlen(dir_name) + 1);
            if (end_with(new_path, '\\') != 0) {
                strcat_s(new_path, 1000, "\\");
            }
            strcat_s(new_path, 1000, fa.name);
            print_directory(new_path, space);
        }

        if ((fa.attrib & _A_ARCH) != 0
            || (fa.attrib & _A_HIDDEN) != 0
            || (fa.attrib & _A_RDONLY) != 0
            || (fa.attrib & _A_SUBDIR) != 0
            || (fa.attrib & _A_SYSTEM) != 0) {
            printf("%s\n", fa.name);
        }

    } while (_findnext(handle, &fa) == 0);
    _findclose(handle);
}
#endif


void print_directory(const char* dir_name, const char* space){
    configs = get_configs();
    create_configs();
    _print_directory(dir_name, space);
    destroy_configs();
    destroy_rbtree(configs);
}

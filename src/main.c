#include <stdio.h>
#include <stdlib.h>
#ifdef linux
#include <unistd.h>
#elif defined WIN32
#include <io.h>
#endif 

#include "tree.h"
#include "arguments.h"

int main(int argc, char** argv){
    arguments args = process_arguments(argc, argv);
    char* target_folder = args.terget_path;

    if(target_folder == NULL){
#ifdef linux
        target_folder = getenv("HOME");
#elif definded WIN32
        size_t len;
        errno_t err = _dupenv_s(&target_folder, &len, "HOME");
        if (err != 0) {
            return err;
        }
#endif
    } 

    //check if the path is valid
#ifdef linux
    int path_valid = access(target_folder, R_OK);
#elif defined WIN32
    int path_valid = _access(target_folder, 0);
#endif 

    if(path_valid != 0){
        printf("The path is not valid!");
        return -1;
    }

    int recursive = args.recursive;

    print_directory(target_folder, "  ");
  
    return 0;
}


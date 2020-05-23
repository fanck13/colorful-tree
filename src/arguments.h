#ifndef __ARGUMENTS_H__
#define __ARGUMENTS_H__

typedef struct _arguments{
    char* terget_path;
    char recursive;
} arguments;

arguments process_arguments(int argc, char** argv);

#endif
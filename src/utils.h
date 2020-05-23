#ifndef __UTILS_H__
#define __UTILS_H__

char* get_file_ext(const char* file_name, char* file_ext);

int file_exist(const char* file_name);

int end_with(const char* str, char ch);

int start_with(const char* str, char ch);

#endif
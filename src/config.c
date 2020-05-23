#include <stdio.h>
#ifdef linux
#include <unistd.h>
#endif
#include <string.h>
#include <stdlib.h>
#include "map.h"
#include "config.h"
#include "utils.h"
#include "color.h"
#include "map.h"

#define MAXBUFSIZE 128

static RBRoot* config_map = NULL;


int split_ext_color(const char* str, Pair* pair){
    int len = strlen(str);
    int i = 0;
    for(; i< len; i++){
        if(str[i] == '='){
            break;
        }
    }

    int j = 0;
    for(; j<i; j++){
        pair->key[j] = str[j];
    }
    pair->key[i] = '\0';

    i++;
    for(j = 0; i<len; i++){
        if(str[i] == '\r' || str[i] == '\n') continue;
        pair->value[j] = str[i];
        j++;
    }

    pair->value[j] = '\0';

    return 0;
}

int read_in_configs(){
    char buf[MAXBUFSIZE] = {0};
    char *current_path = getcwd(buf, MAXBUFSIZE);

#ifdef linux
    strcat(buf, "/src/.config");
#elif defined WIN32
    int len = strnlen_s(current_path, 1000) + strnlen_s("/.config", 1000) + 1;
    strcat_s(current_path, len, "/.config");
#endif


#ifdef _DEBUG
    printf("%s\n", current_path);
#endif

#ifdef linux
    FILE* config = fopen(buf, "r");
    if (config == NULL) {
        return -1;
    }
#elif defined WIN32
    FILE* config; 
    int error = fopen_s(&config, current_path, "r");
    if (error != 0) {
        return error;
    }
#endif

    char readBuf[MAXBUFSIZE];
    int n = 0;
    while(!feof(config)){
        fgets(readBuf, MAXBUFSIZE, config);
        
        if(readBuf != NULL && (start_with(readBuf, '#') == 0 || start_with(readBuf, '\r') == 0 ||start_with(readBuf, '\n') == 0)){
            memset(readBuf, '\0', MAXBUFSIZE);
            continue;
        }

        if(config_map == NULL){
           config_map = create_rbtree();
        }
      
        Pair pair;
        split_ext_color(readBuf, &pair);
        set(config_map, &pair);
        memset(readBuf, '\0', MAXBUFSIZE);
    }
    return 0;
}

#ifdef DEBUG
void print_config(){
    list_node *head = configs;
    while(head != NULL){
        list_node* temp = head->next;
        printf("%s  %s  \n", head->ext, head->color);
        head = temp;
    }
}
#endif

RBRoot* get_configs(){
    if(config_map == NULL){
        read_in_configs();
    }
    return config_map;
}


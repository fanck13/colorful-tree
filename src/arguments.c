#include <string.h>
#include "arguments.h"

#ifdef linux
#define string_cmpare_ignore_case strcasecmp
#elif defined WIN32
#define string_cmpare_ignore_case _stricmp
#endif // linux


arguments process_arguments(int argc, char** argv){
    arguments args;
    memset(&args, 0, sizeof(arguments));
    for(int i = 0; i<argc; i++){
        if(string_cmpare_ignore_case("-p", argv[i]) == 0 && (i+1 < argc)){
            args.terget_path = argv[i+1];
        }
        else if(string_cmpare_ignore_case("-r", argv[i]) == 0){
            args.recursive = 1;
        }
    }
    return args;   
}

#include "zexsh.h"


char* prev_dir = NULL ;

int update_prev_dir(void) {

    char temp[1024];

    if (getcwd(temp, sizeof(temp)) == NULL) {
        perror("getcwd");
        return 1;
    }

    free(prev_dir) ;
    prev_dir = malloc(strlen(temp) + 1);

    if (!prev_dir) {
        perror("malloc");
        return 1;
    }
    strcpy(prev_dir, temp);
    return 0;
}

const char *get_prev_dir(void) {
    return prev_dir;   
}

int command_cd(char** args, char* intial_directory) {

     if (update_prev_dir() != 0) {
        return 1;
     }
   
    if(!args[1] || my_strcmp(args[1],  "~") == 0 ) {
        char *home = getenv("HOME") ;

        if(!home) {
            fprintf(stderr, "cd: HOME not set\n");
            return 1;
        }
        if(chdir(home)) {
            perror("cd");
            return 1;
        }
    }
    else if(my_strcmp(args[1], "-") == 0 || my_strcmp(args[1], "..") == 0) {
         if (!prev_dir) {
            fprintf(stderr, "cd: no previous directory\n");
            return 1;
        }

        if (chdir(prev_dir) != 0) {
            perror("cd");
            return 1;
        }

        printf("%s\n", prev_dir);
    }
    else {
        if(chdir(args[1])) {
            perror("cd") ;
            return 1 ;
        }
        else {
            printf("%s" , "cd worked!!") ;
        }
    }
    return 0 ;
}
int command_pwd() {
    // char cwd[MAX_PATH] ;

    char* cwd = NULL ;
    cwd = getcwd(cwd, 0) ;

    if(!cwd) {
        perror("cwd") ; return 1 ;
    } ;
    printf("%s\n", cwd) ;
    free(cwd) ;

    return 0 ;
}

int command_echo(char** args, char** env) {

    int new_line = 1 ;
    size_t pos = 1 ;

    while(args[pos] && !my_strcmp(args[pos], "-n")) {
        new_line = 0 , pos++ ;
    }
    if (!args[pos]) {
        if (new_line)
            printf("\n");
        return 0;
    }
    while(args[pos]) {

        if(args[pos][0] == '$') {
            char* value = my_getenv(args[pos] + 1, env) ;

            if(value) {
                printf("%s", value) ;
            }
            else {
                printf("%s", "" ) ;
            }
        }
        else {
            printf("%s", args[pos]) ;
        }
        if(args[pos + 1]) {
            printf(" ") ;
        }
        else if(new_line) {
            printf("\n") ;
        }
        pos++ ;
    }
    return 0 ;

}
int command_env(char** env) {
    for(size_t i = 0 ; env[i] ; i++) {
        printf("%s\n", env[i]) ;
    }
    return 0 ;
}
int command_which(char** args, char** env) {

}
int command_exit(char** args, char* intial_directory) {

}
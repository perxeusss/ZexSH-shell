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
// function to search for the command in PATH
char* find_command_in_path(const char* command, char** env) {

    char* path_env = NULL ;
    char* path = NULL ;
    char* token = NULL ;
    char full_path[1024] ;

    path_env = my_getenv("PATH", env) ;

    printf("%s", path_env) ;


    if(!path_env) {
        return NULL ;
    }

    path = my_strdup(path_env) ;
    
    if(!path) {
        perror("my_strdup") ;
        return NULL ;
    }
    token = strtok(path, ":") ;
    // printf("token : %s", token ) ;
    
    while(token) {
        size_t len = my_strlen(token) ;

        if(token[len - 1] == '/') {
            snprintf(full_path, sizeof(full_path), "%s%s", token, command) ;
        }
        else {
            snprintf(full_path, sizeof(full_path), "%s%s%s", token, "/", command) ;
        }

        // if the command exists as executable
        if(!access(full_path, X_OK)) {
            free(path) ;
            return my_strdup(full_path) ;
        }
        token = strtok(NULL, ":") ; // don't start from a new string, continue from where u stopped
    }
    free(path) ;
    return NULL ;
}

int command_which(char** args, char** env) {

    if(args[1] == NULL) {
        printf("which: expected argument\n") ;
        return 1 ;
    }

    // const char* built_in_commands[] = {"cd", "pwd", "echo", "env", "setenv", "unsetenv", "which", "exit"} ;

    // for(size_t i = 0 ; i < 8 ; i++) {
    //     if(!my_strcmp(built_in_commands[i] , args[1])) {
    //         printf("%s: shell buillt-in command\n", args[1]) ;
    //         return 0 ;
    //     }
    // }
    // for external commands 
    char* full_path = find_command_in_path(args[1], env) ;
    printf("%s\n", full_path) ;
    return 1 ;
}

int cnt_env_vars(char** env) {
    int cnt = 0 ;
    while(env[cnt]) cnt++ ;
    return cnt ;
}


char** command_setenv(char** args, char** env) {
    if(!args[1]) {
        printf("Usage : setenv VAR=value\nor\tsetenv <variable> <value>\n") ;
        return env ;
    }
   int env_cnt = cnt_env_vars(env) ;
   char** new_env = malloc((env_cnt + 2) * sizeof(char*)) ;

   if(!new_env) {
    perror("malloc") ;
    return env ;
   }

   for(size_t i = 0 ; i < env_cnt ; i++) {
    new_env[i] = my_strdup(env[i]) ;
    if(!new_env[i]) {

        perror("strdup") ;
        for(size_t j = 0 ; j < i ; j++) {
            free(new_env[j]) ;
        }
        free(new_env) ;
        return env ;
    }
   }
   char* new_var = NULL ;
   if(!args[2]) {
    new_var = strdup(args[1]) ;
   }
   else {
    new_var = malloc((my_strlen(args[1]) + my_strlen(args[2]) + 2) * sizeof(char)) ;
    if(new_var) {
        sprintf(new_var, "%s=%s", args[1], args[2]) ;
    }
   }    

   if(!new_var) {
    perror("malloc") ;
    for(int i = 0 ; i < env_cnt ; i++) {
        free(new_env[i]) ;
    }
    free(new_env) ;
    return env ;
   }
   new_env[env_cnt] = new_var ;
   new_env[env_cnt + 1] = NULL ;

return new_env ;
}

char** command_unsetenv(char** args, char** env) {

    if(!args[1]) {
        printf("Usage: unsetenv <variable>\n") ;
        return env ;
    }

    int env_cnt = cnt_env_vars(env) ;
    char** new_env = malloc(env_cnt * sizeof(char*)) ;

    if(!new_env) {
        perror("malloc") ;
        return env ;
    }
    int loc = 0, found = 0, len = my_strlen(args[1]) ;

    for(int i = 0 ; i < env_cnt ; i++) {

        if(!my_strncmp(env[i], args[1], len) && !my_strncmp(env[i] + len, "=", 1)) {
            found = 1 , loc = i ;
            free(env[i]) ;
            break ;
        }
    }
    if(!found) {
        free(new_env) ;
        printf("Variable %s don't found int environment\n" , args[1]) ;
        return env ;
    }
    for(int i = 0 , j = 0 ; j < env_cnt;  j++) {
        if(j == loc) continue ;
        new_env[i++] = env[j] ;
    }
    for(int i = 0 ; i < env_cnt; i++) {
        free(env[i]) ;
    }
    free(env) ;
    return new_env ;
} 
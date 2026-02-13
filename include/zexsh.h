#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stddef.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

#define MAX 1024
#define MAX_PATH 256

char** parse_input(char* input) ;
void free_tokens(char** tokens) ;


// Built-in functions
int command_cd(char** args, char* intial_directory) ;
int command_pwd() ;
int command_echo(char** args, char** env) ;
int command_env(char** env) ;
int command_which(char** args, char** env) ;

char** command_setenv(char** args, char** env) ;
char** command_unsetenv(char** args, char** env) ;

// // Executors 
void executor(char** args, char** env) ;
// int child_process(char** args, char** env) ;

// // Path functions
// char* get_path(char** env) ;
// char** split_paths(char* paths, int* cnt) ;



// Helper functions 
int my_strcmp(const char* str1, const char* str2) ;
char* my_getenv(const char* name, char** env) ;
size_t my_strncmp(const char* str1, const char* str2, size_t n) ;
size_t my_strlen(const char* name) ;
char* my_strcpy(char* dest, const char* src) ;
char* my_strdup (const char* str) ;
char** my_strtok(const char* str, const char* delimeter ) ;
char* my_strncpy(char* dst, char* src, size_t n) ;
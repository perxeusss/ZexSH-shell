#include "zexsh.h"

int shell_builts(char** args, char** env, char* initial_directory) {

    if(!my_strcmp(args[0], "cd")) {
        return command_cd(args, initial_directory);
    }
    else if(!my_strcmp(args[0], "pwd")) {
        return command_pwd();
    }
    else if(!my_strcmp(args[0], "echo")) {
        return command_echo(args, env);
    }
    else if(!my_strcmp(args[0], "env")) {  
        return command_env(env);
    }
    else if(!my_strcmp(args[0], "which")) {
        return command_which(args, env);
    }
    else if(!my_strcmp(args[0], "exit") || !strcmp(args[0], "quit")) {
        exit(EXIT_SUCCESS);
    }
    else {
        return executor(args, env);
    }
}

void shell_loop(char** env) {
    char* input = NULL;
    size_t input_size = 0;

    char** args;
    char* initial_directory = getcwd(NULL, 0);

    while(1) {

        printf("zexsh> ");
        fflush(stdout);

        if(getline(&input, &input_size, stdin) == -1) {
            perror("getline");
            break;
        } 
        input[strcspn(input, "\n")] = '\0'; 

        args = parse_input(input);
        
        if(!args[0]) {
            free_tokens(args);
            continue;  
        }
        else if(!my_strcmp(args[0], "setenv")) {
            env = command_setenv(args, env);
        }
        else if(!my_strcmp(args[0], "unsetenv")) {
            env = command_unsetenv(args, env);
        }
        else {
            shell_builts(args, env, initial_directory);
        }

        free_tokens(args);
    } 

    free(input);
    free(initial_directory);
}

int main(int argc, char** argv, char** env) {

    (void) argc;
    (void) argv;

    shell_loop(env);
    return 0;
}
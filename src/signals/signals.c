#define _POSIX_C_SOURCE 200809L
#include <stdio.h>      
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include "signals.h"
#include "zexsh.h"


static void sigchld_handler(int sig) {
    (void)sig;
    int saved = errno;

    while (1) {
        int status;
        pid_t pid = waitpid(-1, &status, WNOHANG);

        if (pid <= 0) {
            break;
        }
    }

    errno = saved;
}

void setup_sigchld(void) {
    struct sigaction sa;

    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;

    if (sigaction(SIGCHLD, &sa, NULL) < 0)
        perror("sigaction");
}

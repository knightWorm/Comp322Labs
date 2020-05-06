
//
//  lab3.c
//  
//
//  Created by Ronal Portillo on 4/1/20.
//


// this si a user defineed catcher
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>

typedef void (*sighandler_t)(int);

// global vars
// these are needed here becasue the program needs access to the same data from multiple functions.

int sigs[27] = {SIGHUP, SIGINT, SIGQUIT, SIGILL, SIGTRAP, SIGABRT, SIGIOT, SIGBUS, SIGFPE, SIGUSR1, SIGSEGV, SIGUSR2, SIGPIPE, SIGALRM, SIGTERM, SIGSTKFLT, SIGCHLD, SIGCONT, SIGTTIN, SIGTSTP, SIGTTOU,SIGURG, SIGXCPU,SIGXFSZ,SIGVTALRM, SIGPROF,SIGWINCH};

// this extra array is needed to hand the input from STDIN which will be given in the form of: eg. INT, program needs to understand that as SIGINT
char incomingSingnal[27][10] = {"HUP","INT", "QUIT", "ILL", "TRAP", "ABRT", "IOT", "BUS","FPE", "USR1","SEGV", "USR2", "PIPE", "ALRM", "TERM", "TKFLT", "CHLD", "CONT", "TTIN", "TSTP", "TTOU", "URG", "XCPU", "FSZ","VTALRM", "PROF", "WINCH"};

int termCounter = 0; // this is to trap if the the signal term is used 3 times.

int signalCounter = 0;

// end of global

void signal_handler(int sig);
int main(int argv, char * args[]){
    int i = 1;
    
    //printf the pid to stderr
    fprintf(stderr, "Catcher: $$ = %d\n", getpid());
    void signal_handler(int);
    //1wLoop
    while(i  < argv){
        
        int j = 0;
        
        //2 wLoop
        while(j < 27){
            
            if(strcmp(args[i],incomingSingnal[j]) == 0){
                signal(sigs[j],signal_handler);
            }
            j++;
        }// end of 2wLoop
        i++;
    }//end of 1wLoop
    // wont be able to catch signal so program must pause itself continously
    while(termCounter != 3){
        printf("Waiting for signals...\n");
        pause();
    }
    fprintf(stderr, "Catcher: Total signals caught: %d\n", signalCounter);
    
    exit(EXIT_SUCCESS);
}// end of main function

void signal_handler(int sig){
    int count = 0;
    while(count < 27){
        
        if(sig == sigs[count]){
            signalCounter++;
            printf("SIG%s caught at: %ld\n", incomingSingnal[count], time(NULL));
            
            if(count == 14){
                
                termCounter++;
                
            }else{
                
                termCounter =0;
            }
            
            //signalCounter++;
            break;
            
        }
        count++;
    }// end of while loop
    
    // done to register the handler again.
    signal(sig,signal_handler);
}// end of handler
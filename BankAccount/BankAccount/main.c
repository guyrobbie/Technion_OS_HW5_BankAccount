#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "debug.h"
#include <pthread.h>
#include "list.h"

#define NUM_OF_ATMS 40

int g_Num_Of_ATMs = 0;
LIST_ELEMENT* g_List = NULL;

int countLines(FILE* fp);
void *ATM(void* input_params);

int main(int argc, char **argv)
{
    int ret;
    pthread_t* threads;
    
    if(argc == 1) {
        ERROR("Input arguments are missing, usage: ./Bank <N> <input_file1.txt> ... <input_fileN.txt> \r\n \
        N = num of ATMs");
        exit(EXIT_FAILURE);
    }
    
    g_Num_Of_ATMs = atoi(argv[1]);
    
    if(argc != (g_Num_Of_ATMs + 2)) {
        printf("Error: Input arguments are missing, N doesn't match the number of input files!!\r\n \
        N = %d, number of input files = %d", g_Num_Of_ATMs, argc - 2);
        exit(EXIT_FAILURE);
    }
        
    threads = (pthread_t*)malloc(sizeof(pthread_t)*g_Num_Of_ATMs);
    for(int i = 0; i < g_Num_Of_ATMs; i++)
    {
        ret = pthread_create(&threads[i], NULL, ATM, argv[2+i]);
        
        if(ret){
            ERROR("pthread_create failed to create threads[%d]!!!", i);
            exit(EXIT_FAILURE);
        }else{
            TRACE("Create Thread[%d] sucessfuly",i);
        }
    }
    
    pthread_exit(NULL);
	return 0;
}

void *ATM(void* input_params)
{
    FILE* pFile = NULL;
    char* filename = (char*)input_params;
    size_t len = 0;
    ssize_t read;
    char* line = NULL;
    LIST_ELEMENT* pCurr = g_List;
    char* cmd = NULL;
    char* delimiters = " \t\n";
    char* args[TRANSFER_CMD_NUM_OF_ARG] = {0};
   
   if(input_params == NULL){
       TRACE("ATM failed, not a valid imput params!!");
       exit(EXIT_FAILURE);
       }
   
    TRACE("Open input file");
    pFile = fopen(filename, "r");
    
    if(pFile == NULL)
    {
        ERROR("file %s doesn't exist!", filename);
        exit(EXIT_FAILURE);
    }
    
    for(int j = 0; (read = getline(&line, &len, pFile)) != -1; j++)
    {
        TRACE("Retrieved line of length %zu :", read);
        if(line ==  NULL){
            continue;
        }
        TRACE("%s", line);
        
        cmd = strtok(line, delimiters);
        if (cmd == NULL)
        {
            ERROR("Empty input line!!"); 
            pthread_exit(NULL);
        }
        TRACE("cmd = %s", cmd);
        if(*cmd == 'O')
        {
            TRACE("Open account");
            for (int i=0; i<OPEN_CMD_NUM_OF_ARG; i++)
            {
                args[i] = strtok(NULL, delimiters); 
                if (args[i] == NULL) 
                {
                    ERROR("Wrong number of input arguments");
                    free(line);
                    line = NULL;
                    pthread_exit(NULL);
                }
            }
            for (int i=0; i<OPEN_CMD_NUM_OF_ARG; i++)
            {
                TRACE("args[%d] = %s", i,args[i]);
            }
        }
        else if(*cmd == 'T')
        {
            TRACE("Transfer money"); 
            for (int i=0; i<TRANSFER_CMD_NUM_OF_ARG; i++)
            {
                args[i] = strtok(NULL, delimiters); 
                if (args[i] == NULL) 
                {
                    ERROR("Wrong number of input arguments");
                    free(line);
                    line = NULL;
                    pthread_exit(NULL);
                }
            }
            for (int i=0; i<TRANSFER_CMD_NUM_OF_ARG; i++)
            {
                TRACE("args[%d] = %s", i,args[i]);
            }
        }
        else if(*cmd == 'W')
        {
            TRACE("Wid");
            for (int i=0; i<WITHDRAW_CMD_NUM_OF_ARG; i++)
            {
                args[i] = strtok(NULL, delimiters); 
                if (args[i] == NULL) 
                {
                    ERROR("Wrong number of input arguments");
                    free(line);
                    line = NULL;
                    pthread_exit(NULL);
                }
            }
            for (int i=0; i<WITHDRAW_CMD_NUM_OF_ARG; i++)
            {
                TRACE("args[%d] = %s", i,args[i]);
            }           
        }
        else if(*cmd == 'B')
        {
            TRACE("Balance"); 
            for (int i=0; i<BALANCE_CMD_NUM_OF_ARG; i++)
            {
                args[i] = strtok(NULL, delimiters); 
                if (args[i] == NULL) 
                {
                    ERROR("Wrong number of input arguments");
                    free(line);
                    line = NULL;
                    pthread_exit(NULL);
                }
            }
            for (int i=0; i<BALANCE_CMD_NUM_OF_ARG; i++)
            {
                TRACE("args[%d] = %s", i,args[i]);
            }
        }
        else if(*cmd == 'D')
        {
            TRACE("Deposite"); 
            for (int i=0; i<DEPOSIT_CMD_NUM_OF_ARG; i++)
            {
                args[i] = strtok(NULL, delimiters); 
                if (args[i] == NULL) 
                {
                    ERROR("Wrong number of input arguments");
                    free(line);
                    line = NULL;
                    pthread_exit(NULL);
                }
            }
            for (int i=0; i<DEPOSIT_CMD_NUM_OF_ARG; i++)
            {
                TRACE("args[%d] = %s", i,args[i]);
            }           
        }
        else
        {
            ERROR("Unknown command!!");
        }
        free(line);
        line = NULL;
    }
    
    pthread_exit(NULL);
}

int countLines(FILE* fp)
{
    int lines = 0;
    char ch;
    
    if(fp == NULL)
        return 0;

    while(!feof(fp))
    {
        ch = fgetc(fp);
        if(ch == '\n')
        {
            lines++;
        }
    }
    return lines;
}
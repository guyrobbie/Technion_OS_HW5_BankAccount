#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "debug.h"


#define NUM_OF_ATMS 40

int g_Num_Of_ATMs = 0;
char** ATMs_commands[NUM_OF_ATMS];

int countLines(FILE* fp);
int getCommands(char*** commandsArray, char** fileList, int fileListLen);

int main(int argc, char **argv)
{
    if(argc > 0)
    {
        g_Num_Of_ATMs = atoi(argv[1]);
            TRACE("argc: %d", argc);
        if(argc != (g_Num_Of_ATMs + 2))
        {
            ERROR("not enought input arguments!");
            exit(1);
        }
        else
        {
            if(getCommands(ATMs_commands, &argv[2], g_Num_Of_ATMs) == -1)
            {
                ERROR("failed to run: getCommands");
                exit(2);
            }
            else
            {
                for(int i = 0; i < g_Num_Of_ATMs; i++)
                {
                    for(int j = 0; ATMs_commands[i][j] != NULL; j++)
                    {
                        TRACE("ATMs_commands[%d][%d]: %s",i ,j ,ATMs_commands[i][j]);
                    }
                }
            }
            
        }
    }


//       fp = fopen("/etc/motd", "r");
//       if (fp == NULL)
//           exit(EXIT_FAILURE);
//
//       while ((read = getline(&line, &len, fp)) != -1) {
//           printf("Retrieved line of length %zu :\n", read);
//           printf("%s", line);
//       }
//
//       fclose(fp);
//       if (line)
//           free(line);
//       exit(EXIT_SUCCESS);

    getchar();
    
	return 0;
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

int getCommands(char*** commandsArray, char** fileList, int fileListLen)
{
    FILE * pFile = NULL;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int numOfLines = 0;
    
    if(commandsArray == NULL)
    {
        ERROR("commandsArray is NULL!");
        return -1;
    }
    
    if(fileList == NULL)
    {
        ERROR("fileList is NULL!");
        return -1;
    }
    
    if(fileListLen == 0)
    {
        ERROR("fileListLen is 0!");
        return -1;
    }
    
    for(int i = 0; i < fileListLen; i++)
    {
            TRACE("enter the for loop with i: %d", i);
        pFile = fopen(fileList[i], "r");
        
        if(pFile == NULL)
        {
            ERROR("file %s doesn't exist!", (char*)fileList[i]);
            return -1;
        }
        
        numOfLines = countLines(pFile); //counting the lines in the file to allocate the correct space in the commands array
            TRACE("numOfLines: %d", numOfLines);
        commandsArray[i] = (char**)malloc(sizeof(char*) * numOfLines );
            TRACE("allocated %lu bytes (to holds %d line pointers), in commandsArray[%d]", sizeof(char*) * numOfLines , numOfLines, i);
        rewind(pFile); //setting the file pointer to points to the begining of the file.
        
        for(int j = 0; (read = getline(&line, &len, pFile)) != -1; j++)
        {
                TRACE("Retrieved line of length %zu :", read);
                TRACE("%s", line);
            commandsArray[i][j] = (char*)malloc(sizeof(char) * read + 1);
                TRACE("allocated %lu bytes, in commandsArray[%d][%d]", sizeof(char) * read + 1 , i, j);
            strcpy(commandsArray[i][j], line);
                TRACE("commandsArray[%d][%d]: %s",i ,j ,commandsArray[i][j]);
            free(line);
            line = NULL;
        }
    }
    return 0;
}


/*
 *     for(int i = 0; i < g_Num_Of_ATMs; i++)
            {
                    TRACE("enter the for loop with i: %d\r\n", i);
                pFile = fopen(argv[i + 2], "r");
                
                if(pFile == NULL)
                {
                    ERROR("file %s doesn't exist!\r\n", (char*)argv[2+i]);
                    exit(2);
                }
                
                numOfLines = countLines(pFile); //counting the lines in the file to allocate the correct space in the commands array
                    TRACE("numOfLines: %d\r\n", numOfLines);
                ATMs_commands[i] = (char**)malloc(sizeof(char*) * numOfLines );
                    TRACE("allocated %lu bytes (to holds %d line pointers), in ATMs_commands[%d]\r\n", sizeof(char*) * numOfLines , numOfLines, i);
                rewind(pFile); //setting the file pointer to points to the begining of the file.
                
                for(int j = 0; (read = getline(&line, &len, pFile)) != -1; j++)
                {
                        TRACE("Retrieved line of length %zu :\n", read);
                        TRACE("%s", line);
                    ATMs_commands[i][j] = (char*)malloc(sizeof(char) * read + 1);
                        TRACE("allocated %lu bytes, in ATMs_commands[%d][%d]\r\n", sizeof(char) * read + 1 , i, j);
                    strcpy(ATMs_commands[i][j], line);
                        TRACE("ATMs_commands[%d][%d]: %s",i ,j ,ATMs_commands[i][j]);
                    free(line);
                    line = NULL;
                }
            }
 * 
 * 
 * */
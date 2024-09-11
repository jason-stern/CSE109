#include <stdio.h>
#include <stdlib.h>
#include "globalDefs.h"
#include "syscalls.h"
#include "string.h"

void   parseArgsAndOpenFiles(int argc, char *argv[], FILE **rFile, FILE **cFile) {
    if (argc != 3) { // checker for invalid arg count
        fprintf(stderr, "error - invalid # of args (must be 3)\n");
        exit(10);
    }

    *rFile = Fopen(argv[1], "r"); // open remote file (tinyFile)
    *cFile = Fopen(argv[2], "r"); // open cmdsFile
}

long   copyFile(char *rFileName, FILE *rFile, char *envp[], FILE **lFile) {
    // Getting username from envp[6]
    char *userid = NULL;
    for (int i = 0; envp[i] != NULL; i++) {
        if (strncmp(envp[i], "USER=", 5) == 0) {
            userid = envp[i] + 5;
            break;
        }
    }
    char username[128];
    username[0] = '.';
    strcpy(username + 1, userid);
    *lFile = Fopen(strcat(rFileName, username), "w+");


    char *buffer = (char *)(Malloc(NUM_BYTES_TO_COPY_AT_A_TIME));
    long totalCount = 0;
    size_t numBytes = 0;

    /*
        reads NUM_BYTES_TO_COPY_AT_A_TIME bytes from remote file into buffer
        writes contents of buffer into local file
        increments total count
    */
    while ((numBytes = Fread(buffer, sizeof(char), NUM_BYTES_TO_COPY_AT_A_TIME, rFile)) > 0) { // read remote file and store in buffer
        Fwrite(buffer, sizeof(int), (numBytes / 4), *lFile); // write from buffer into local file
        totalCount += numBytes;
    }
    Fseek(*lFile, 0, SEEK_SET);


    free(buffer);
    Fclose(rFile); // close remote file
    return totalCount;
}

void   runCmds(FILE *lFile, FILE *cFile, long totalCount, qbu_t msg[]) {
    // getline variables
    char *buffer = NULL; // each line of cmdsFile
    size_t length = 0;
    /*
    
        reads each line of commands file and stores them into buffer
        interpret buffer and run Fseek, Fwrite, or Fread functions if command is valid

    */
    while ((getline(&buffer, &length, cFile)) != -1) {
        char action; // s, w, r
        long arg1; // number of bytes to seek, write, or read
        int arg2; // location to start action
        int whence = 0; // whence for Fseek
        if ((buffer[0] != 's') && (buffer[0] != 'w') && (buffer[0] != 'r')) { // ignores invalid actions and comments
            continue;
        }
        sscanf(buffer, "%c %ld %d", &action, &arg1, &arg2);

        /*
            switch case for action (first character of buffer). Only runs if checker above doesn't continue
                case 'w': Fwrite()
                case 'r': Fread()
                case 's': Fseek()
        */
        switch (buffer[0]) {
            case 'w': // write command
                if ((Ftell(lFile) + 4) <= totalCount) {
                    Fwrite(&arg1, sizeof(int), 1, lFile);
                }
                break;
            case 'r': // read command
                    if (((0 <= arg1) && (arg1 < 16))) {
                        qbu_t input;
                        int var = 0;
                        Fread(&var, sizeof(int), 1, lFile);
                        input.i = var;
                        msg[arg1] = input;
                    }
                break;
            case 's': // seek command
                switch (arg2) {
                    case 0: // SEEK_SET
                        if ((arg1 >= 0) && (arg1 < (totalCount + 1))) {
                            //fprintf(stdout, " %d\n", Ftell(lFile)); // testing
                            whence = SEEK_SET;
                            Fseek(lFile, arg1, whence);
                        }
                        break;
                    case 1: // SEEK_CUR
                        if (((arg1 + Ftell(lFile)) >= 0) && ((arg1 + Ftell(lFile)) <= totalCount)) { // not working
                            whence = SEEK_CUR;
                            Fseek(lFile, arg1, whence);
                        }
                        break;
                    case 2: // SEEK_END
                        if ((-totalCount <= arg1) && (arg1 < 0L)) { // not working
                            whence = SEEK_END;
                            Fseek(lFile, arg1, whence);
                        }
                        break;
                    default: // invalid whence
                        break;
                    
                }
                break;
        }
    }
    free(buffer);
    // close lFile and cFile
    Fclose(lFile);
    Fclose(cFile);
}
    
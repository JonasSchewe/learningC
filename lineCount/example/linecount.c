#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct lines{
    size_t ccpp;

};

struct lines countLines = {0};


int main(int argc, char** argv){
    if(2 < argc){
        fprintf(stderr, "Error: Not enough arguments. Usage \"linecount <FOLDER>\"\n");
        exit(EXIT_FAILURE);
    }

}
/************************************************************************/
/* File Name : assembler.c 												*/
/* Purpose   : This program will assemble a .ASM file into a .OBJ file  */
/*             This program will use the "asm_parser" library to achieve*/
/*			   its functionality.										*/ 
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"

int main(int argc, char** argv) {

	if(argc<=1 || argv[1]==NULL){
		perror("error1: usage: ./assembler <assembly_file.asm>\n");
		return 1;
	}
	char* filename = argv[1] ;					// name of ASM file
	char program [ROWS][COLS];	// ASM file line-by-line

	if(read_asm_file(filename, program)==0){
		for(int i=0;i<ROWS;i++){
			if(program[i][0]=='\0'){
				break;
			}
			printf("%s\n",program[i]);
		
		}

	}			
	else{
		printf("Failed, exiting 2.");
	}
	

	char  program_bin_str [ROWS][17] ; 		// instructions converted to a binary string
	for(int i=0;i<ROWS;i++){
		if(program[i][0]=='\0'){
				break;
			}
		if(parse_instruction(&(program[i][0]),&(program_bin_str[i][0]))==0){
			printf("%s\n", program_bin_str[i]);
		}

		else{
			printf("Failed, exiting 3.");
		}
	}


	unsigned short int program_bin [ROWS] ; // instructions in binary (HEX)
	for(int i=0;i<ROWS;i++){
		if(program_bin_str[i][0]=='\0'){
				break;
			}
		program_bin[i]=str_to_bin(&program_bin_str[i][0]);
		printf("0x%X\n", program_bin[i]);
	}


	return write_obj_file (filename, &program_bin); 
}

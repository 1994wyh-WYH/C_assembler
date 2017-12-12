/************************************************************************/
/* File Name : asm_parser.h 											*/
/* Purpose   : this header file declares the functions for those		*/
/*             in the "asm_parser.c" library 							*/
/*             standard "string.h" C-library.							*/
/************************************************************************/

#define ROWS 100
#define COLS 255

int read_asm_file 		(char* filename, char program [ROWS][COLS] ) ;
int parse_instruction 	(char* instr, char* instr_bin_str) ;
int parse_reg 			(char reg_num, char* instr_bin_str) ;
int parse_add 			(char* instr, char* instr_bin_str ) ;
int parse_mul 			(char* instr, char* instr_bin_str ) ;
/* add additional helper functions to support other instructions */
int parse_sub (char* instr, char* instr_bin_str);
int parse_div (char* instr, char* instr_bin_str);
int parse_and (char* instr, char* instr_bin_str);
int parse_or (char* instr, char* instr_bin_str);
int parse_xor (char* instr, char* instr_bin_str);

unsigned short int str_to_bin (char* instr_bin_str) ;
int write_obj_file 			  (char* filename, unsigned short int program_bin[ROWS] ) ;

//helper functions for ec
int parse_im (char* im_num, char* instr_bin_str, int len) ;
int parse_not (char* instr, char* instr_bin_str);
int parse_rti (char* instr, char* instr_bin_str);
char* convert_2c(char* binary, int SIZE);
int parse_nop(char* instr, char* instr_bin_str);
int parse_ldr(char* instr, char* instr_bin_str);
int parse_str(char* instr, char* instr_bin_str);
int parse_const(char* instr, char* instr_bin_str);
int parse_cmpi(char* instr, char* instr_bin_str);
int parse_cmpiu(char* instr, char* instr_bin_str);
int parse_cmp(char* instr, char* instr_bin_str);
int parse_cmpu(char* instr, char* instr_bin_str);

int parse_jsrr(char* instr, char* instr_bin_str);
int parse_sll(char* instr, char* instr_bin_str);
int parse_sra(char* instr, char* instr_bin_str);
int parse_srl(char* instr, char* instr_bin_str);
int parse_mod(char* instr, char* instr_bin_str);
int parse_jmpr(char* instr, char* instr_bin_str);
int parse_hiconst(char* instr, char* instr_bin_str);
int parse_trap(char* instr, char* instr_bin_str);

/************************************************************************/
/* File Name : asm_parser.c 											*/
/* Purpose   : the functions are declared in asm_parser.h 				*/
/*             The intention of this library is to parse a .ASM file 	*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"

/* to do - implement all the functions in asm_parser.h */
int read_asm_file (char* filename, char program [ROWS][COLS] ){
	FILE *theFile = fopen (filename, "r");
	if (theFile == NULL) {
		perror ("error2: read_asm_file() failed.\n");
		return 2;
	}
	//int row=7;
	for(int i=0;i<ROWS;i++){

		for(int j=0;j<=14;j++){
			char c=fgetc (theFile);
			
			if(c==EOF||c=='\0'){
				return 0;
			}
			if(c==';'){
				while(c!='\n'){
					c=fgetc(theFile);
				}
				if(j==0){
					i--;
				}
				break;
			}
			if(c=='\n' || c=='\t'){
				break;
			}
			program[i][j]=c;

		}
	}
	return 0;
}

int parse_instruction 	(char* instr, char* instr_bin_str){
	char instr_cp[15];
	strcpy(instr_cp,instr);
	char *token;
	const char s[2]=" ";
	token=strtok(instr_cp, s);

	if(strcmp(token,"ADD")==0){
		return parse_add(instr,instr_bin_str);
	}
	else if(strcmp(token,"MUL")==0){
		return parse_mul(instr,instr_bin_str);
	}
	else if(strcmp(token,"SUB")==0){
		return parse_sub(instr,instr_bin_str);
	}
	else if(strcmp(token,"DIV")==0){
		return parse_div(instr,instr_bin_str);
	}
	else if(strcmp(token,"AND")==0){
		return parse_and(instr,instr_bin_str);
	}
	else if(strcmp(token,"OR")==0){
		return parse_or(instr,instr_bin_str);
	}
	else if(strcmp(token,"XOR")==0){
		return parse_xor(instr,instr_bin_str);
	}
	else if(strcmp(token,"NOT")==0){
		return parse_not(instr,instr_bin_str);
	}
	else if(strcmp(token,"RTI")==0){
		return parse_rti(instr,instr_bin_str);
	}
	else if(strcmp(token,"NOP")==0){
		return parse_nop(instr,instr_bin_str);
	}
	else if(strcmp(token,"LDR")==0){
		return parse_ldr(instr,instr_bin_str);
	}
	else if(strcmp(token,"STR")==0){
		return parse_str(instr,instr_bin_str);
	}
	else if(strcmp(token,"CONST")==0){
		return parse_const(instr, instr_bin_str);
	}
	else if(strcmp(token,"CMPI")==0){
		return parse_cmpi(instr, instr_bin_str);
	}
	else if(strcmp(token,"CMPIU")==0){
		return parse_cmpiu(instr, instr_bin_str);
	}
	else if(strcmp(token,"CMP")==0){
		return parse_cmp(instr, instr_bin_str);
	}
	else if(strcmp(token,"CMPU")==0){
		return parse_cmpu(instr, instr_bin_str);
	}
	else if(strcmp(token,"JSRR")==0){
		return parse_jsrr(instr, instr_bin_str);
	}
	else if(strcmp(token,"JMPR")==0){
		return parse_jmpr(instr, instr_bin_str);
	}
	else if(strcmp(token,"HICONST")==0){
		return parse_hiconst(instr, instr_bin_str);
	}
	else if(strcmp(token,"TRAP")==0){
		return parse_trap(instr, instr_bin_str);
	}
	else if(strcmp(token,"SLL")==0){
		return parse_sll(instr, instr_bin_str);
	}
	else if(strcmp(token,"SRA")==0){
		return parse_sra(instr, instr_bin_str);
	}
	else if(strcmp(token,"SRL")==0){
		return parse_srl(instr, instr_bin_str);
	}
	else if(strcmp(token,"MOD")==0){
		return parse_mod(instr, instr_bin_str);
	}
	else{
		perror("error3: parse_instruction() failed.");
		return 3;
	}
	return 0;
}

int parse_add (char* instr, char* instr_bin_str){
	instr_bin_str[0]='0';
	instr_bin_str[1]='0';
	instr_bin_str[2]='0';
	instr_bin_str[3]='1';
	instr_bin_str+=4;
	//printf("instr is: %s\n", instr);

	char instr_cp1[15];
	strcpy(instr_cp1,instr);
	//printf("instr copy is: %s\n", instr_cp1);
	char* token;
	const char s[2]=" ";
	token=strtok(instr_cp1, s);
	token = strtok(NULL, s);
	//printf("token is: %s\n",token);
	//printf("token[1] is: %c\n",token[1]);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;
	if(instr_bin_str==NULL){
		perror("error4: parse_add() failed.");
		return 4;
	}

	token = strtok(NULL, s);
	//printf("token is: %s\n",token);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;
	if(instr_bin_str==NULL){
		perror("error4: parse_add() failed.");
		return 4;
	}

	token = strtok(NULL, s);
	if(token[0]!='R'){
		//printf("%c\n", token[0]);
		instr_bin_str[0]='1';
		instr_bin_str++;
		parse_im(token, instr_bin_str, 5);
		//printf("%c\n", token[0]);
		instr_bin_str+=5;
	}
	else{
		for(int i=0;i<3;i++){
			instr_bin_str[i]='0';
			}
		instr_bin_str+=3;
		parse_reg(token[1], instr_bin_str);
		instr_bin_str+=3;
	}
	if(instr_bin_str==NULL){
		perror("error4: parse_add() failed.");
		return 4;
	}

	instr_bin_str[0]='\0';

	return 0;
}

int parse_reg (char reg_num, char* instr_bin_str){
	if(reg_num=='\0'){
		perror("error5: parse_reg() failed.");
		return 5;
	}
	//printf("reg_num is :%c\n", reg_num);
	switch(reg_num){
		case '0':
			instr_bin_str[0]='0';
			instr_bin_str[1]='0';
			instr_bin_str[2]='0';
			break;
		case '1':
			instr_bin_str[0]='0';
			instr_bin_str[1]='0';
			instr_bin_str[2]='1';
			break;
		case '2':
			instr_bin_str[0]='0';
			instr_bin_str[1]='1';
			instr_bin_str[2]='0';
			break;
		case '3':
			instr_bin_str[0]='0';
			instr_bin_str[1]='1';
			instr_bin_str[2]='1';
			break;
		case '4':
			instr_bin_str[0]='1';
			instr_bin_str[1]='0';
			instr_bin_str[2]='0';
			break;
		case '5':
			instr_bin_str[0]='1';
			instr_bin_str[1]='0';
			instr_bin_str[2]='1';
			break;
		case '6':
			instr_bin_str[0]='1';
			instr_bin_str[1]='1';
			instr_bin_str[2]='0';
			break;
		case '7':
			instr_bin_str[0]='1';
			instr_bin_str[1]='1';
			instr_bin_str[2]='1';
			break;
	}
	//printf("instr_bin_str[0] is: %c\n", instr_bin_str[0]);
	return 0;
}

int parse_mul (char* instr, char* instr_bin_str){
	instr_bin_str[0]='0';
	instr_bin_str[1]='0';
	instr_bin_str[2]='0';
	instr_bin_str[3]='1';
	instr_bin_str+=4;

	char instr_cp[15];
	strcpy(instr_cp,instr);
	char* token;
	char s[2]=" ";
	token=strtok(instr_cp, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;
	

	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;
	
	for(int i=0;i<2;i++){
		instr_bin_str[i]='0';
	}
	instr_bin_str[2]='1';
	instr_bin_str+=3;

	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	instr_bin_str[0]='\0';

	return 0;
}

int parse_sub (char* instr, char* instr_bin_str){
	instr_bin_str[0]='0';
	instr_bin_str[1]='0';
	instr_bin_str[2]='0';
	instr_bin_str[3]='1';
	instr_bin_str+=4;

	char instr_cp[15];
	strcpy(instr_cp,instr);
	char* token;
	char s[2]=" ";
	token=strtok(instr_cp, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;
	

	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	
	instr_bin_str[0]='0';
	instr_bin_str[1]='1';
	instr_bin_str[2]='0';
	instr_bin_str+=3;

	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	instr_bin_str[0]='\0';

	return 0;
}

int parse_div (char* instr, char* instr_bin_str){
	instr_bin_str[0]='0';
	instr_bin_str[1]='0';
	instr_bin_str[2]='0';
	instr_bin_str[3]='1';
	instr_bin_str+=4;

	char instr_cp[15];
	strcpy(instr_cp,instr);
	char* token;
	char s[2]=" ";
	token=strtok(instr_cp, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;
	
	instr_bin_str[0]='0';
	instr_bin_str[1]='1';
	instr_bin_str[2]='1';
	instr_bin_str+=3;

	token = strtok(NULL, s);

	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;
	

	instr_bin_str[0]='\0';

	return 0;
}

int parse_and (char* instr, char* instr_bin_str){
	instr_bin_str[0]='0';
	instr_bin_str[1]='1';
	instr_bin_str[2]='0';
	instr_bin_str[3]='1';
	instr_bin_str+=4;

	char instr_cp[15];
	strcpy(instr_cp,instr);
	char* token;
	char s[2]=" ";
	token=strtok(instr_cp, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	token = strtok(NULL, s);
	//printf("%s\n", token);
	if(token[0]!='R'){
		instr_bin_str[0]='1';
		instr_bin_str++;
		parse_im(token, instr_bin_str, 5);
		instr_bin_str+=5;
	}
	else{
		instr_bin_str[0]='0';
		instr_bin_str[1]='0';
		instr_bin_str[2]='0';
		instr_bin_str+=3;
		parse_reg(token[1], instr_bin_str);
		instr_bin_str+=3;
	}

	instr_bin_str[0]='\0';

	return 0;
}

int parse_or (char* instr, char* instr_bin_str){
	instr_bin_str[0]='0';
	instr_bin_str[1]='1';
	instr_bin_str[2]='0';
	instr_bin_str[3]='1';
	instr_bin_str+=4;

	char instr_cp[15];
	strcpy(instr_cp,instr);
	char* token;
	char s[2]=" ";
	token=strtok(instr_cp, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	
	instr_bin_str[0]='0';
	instr_bin_str[1]='1';
	instr_bin_str[2]='0';
	instr_bin_str+=3;

	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;
	

	instr_bin_str[0]='\0';

	return 0;
}

int parse_xor (char* instr, char* instr_bin_str){
	instr_bin_str[0]='0';
	instr_bin_str[1]='1';
	instr_bin_str[2]='0';
	instr_bin_str[3]='1';
	instr_bin_str+=4;

	char instr_cp[15];
	strcpy(instr_cp,instr);
	char* token;
	char s[2]=" ";
	token=strtok(instr_cp, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;
	
	instr_bin_str[0]='0';
	instr_bin_str[1]='1';
	instr_bin_str[2]='1';
	instr_bin_str+=3;

	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	instr_bin_str[0]='\0';

	return 0;
}

unsigned short int str_to_bin(char* instr_bin_str){
	char instr_bin_str_cp[18];
	strcpy(instr_bin_str_cp,instr_bin_str);
	long binaryval;
	binaryval=strtol(instr_bin_str_cp, NULL, 2);
	if(binaryval=='\0'&& strlen(instr_bin_str_cp)!=7){
		perror("error6: str_to_bin() failed.");
		return 6;
	}

    return binaryval;

}

int write_obj_file(char* filename, unsigned short int program_bin[ROWS]){
	size_t len=strlen(filename);
	filename[len-3]='o';
	filename[len-2]='b';
	filename[len-1]='j';
	FILE *theFile = fopen (filename, "wb");

	unsigned short int num1=0xCADE;
	if(fwrite (&num1, sizeof(unsigned short int), 1, theFile)==0){
		perror("error7:  write_obj_file() failed.");
		return 7;
	}
	
	unsigned short int num2=0x0000;
	if(fwrite (&num2, sizeof(unsigned short int), 1, theFile)==0){
		perror("error7:  write_obj_file() failed.");
		return 7;
	}
	
	unsigned short int num3=0;
	while(program_bin[num3]!='\0'){
		num3++;
	}
	//printf("%u\n", num3);
	
	if(fwrite (&num3, sizeof(unsigned short int), 1, theFile)==0){
		perror("error7:  write_obj_file() failed.");
		return 7;
	}

	//printf("%u\n", program_bin[0]);
	if(fwrite(program_bin, sizeof(unsigned short int), num3, theFile)==0){
		perror("error7:  write_obj_file() failed.");
		return 7;
	}
	fclose(theFile);
	return 0;

}

int parse_im (char* im_num, char* instr_bin_str, int len){
	int l=strlen(im_num);
	char cp[100];
	if(im_num[0]=='-'){
		for(int i=1;i<l;i++){
			cp[i-1]=im_num[i];
		}
	}
	else{
		for(int i=0;i<l;i++){
			cp[i]=im_num[i];
		}
	}

	long binaryval;
	binaryval=strtol(cp, NULL, 10);
	//printf("b is %lu\n", binaryval);

	/*int signedValue = binaryval;
   	if (binaryval >> (len - 1))
        signedValue |= -1 << len;
    binaryval=signedValue;*/
    
    char temp[len];
	if(im_num[0]=='-'){
		for(int i=len-1;i>0;i--){
    		temp[i]=binaryval%2+48;
    		binaryval=binaryval/2;
    	}
    	temp[0]='0';
    	char* bin=convert_2c(temp,len);
    	//printf("bin is: %s\n", bin);
    	for(int i=len-1;i>=0;i--){
    		instr_bin_str[i]=bin[i];
    		//printf("%c\n", instr_bin_str[i]);
    	}
	}
	else{
   	 for(int i=len-1;i>0;i--){
   	 	//printf("binaryval is: %lu\n", binaryval);
    	instr_bin_str[i]=binaryval%2+48;
    	binaryval=binaryval/2;
    	}
    	instr_bin_str[0]='0';
	}
	
	return 0;
}

int parse_not (char* instr, char* instr_bin_str){
	instr_bin_str[0]='0';
	instr_bin_str[1]='1';
	instr_bin_str[2]='0';
	instr_bin_str[3]='1';
	instr_bin_str+=4;

	char instr_cp[15];
	strcpy(instr_cp,instr);
	char* token;
	char s[2]=" ";
	token=strtok(instr_cp, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	
	instr_bin_str[0]='0';
	instr_bin_str[1]='0';
	instr_bin_str[2]='1';
	instr_bin_str+=3;
	
	for(int i=0;i<3;i++){
		instr_bin_str[i]='0';
	}
	instr_bin_str+=3;
	instr_bin_str[0]='\0';

	return 0;
}

int parse_rti (char* instr, char* instr_bin_str){
	instr_bin_str[0]='1';
	instr_bin_str[1]='0';
	instr_bin_str[2]='0';
	instr_bin_str[3]='0';
	instr_bin_str+=4;
	instr_bin_str[0]='\0';

	return 0;
}

char* convert_2c(char* binary, int size){
    char onesComp[size + 1];
    char* twosComp=malloc(sizeof(char)*(size + 1));
    int i, carry=1;

    for(i=0; i<size; i++){
        if(binary[i] == '1')
        {
            onesComp[i] = '0';
        }
        else if(binary[i] == '0')
        {
            onesComp[i] = '1';
        }
    }
    onesComp[size] = '\0';

    for(i=size-1; i>=0; i--){
        if(onesComp[i] == '1' && carry == 1)
        {
            twosComp[i] = '0';
        }
        else if(onesComp[i] == '0' && carry == 1)
        {
            twosComp[i] = '1';
            carry = 0;
        }
        else
        {
            twosComp[i] = onesComp[i];
        }
    }
    twosComp[size] = '\0';
    /*printf("Original binary = %s\n", binary);
    printf("Ones complement = %s\n", onesComp);
    printf("Twos complement = %s\n", twosComp);*/
    char* ret=&twosComp[0];
    return ret;
}


int parse_nop (char* instr, char* instr_bin_str){
	for(int i=0;i<7;i++){
		instr_bin_str[i]='0';
	}
	instr_bin_str+=7;
	instr_bin_str[0]='\0';

	return 0;
}

int parse_ldr (char* instr, char* instr_bin_str){
	instr_bin_str[0]='0';
	instr_bin_str[1]='1';
	instr_bin_str[2]='1';
	instr_bin_str[3]='0';
	instr_bin_str+=4;

	char instr_cp[15];
	strcpy(instr_cp,instr);
	char* token;
	char s[2]=" ";
	token=strtok(instr_cp, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	token = strtok(NULL, s);
	
	parse_im(token, instr_bin_str, 6);
	instr_bin_str+=6;

	instr_bin_str[0]='\0';

	return 0;
}

int parse_str (char* instr, char* instr_bin_str){
	instr_bin_str[0]='0';
	instr_bin_str[1]='1';
	instr_bin_str[2]='1';
	instr_bin_str[3]='1';
	instr_bin_str+=4;

	char instr_cp[15];
	strcpy(instr_cp,instr);
	char* token;
	char s[2]=" ";
	token=strtok(instr_cp, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	token = strtok(NULL, s);
	
	parse_im(token, instr_bin_str, 6);
	instr_bin_str+=6;

	instr_bin_str[0]='\0';

	return 0;
}

int parse_cmpi (char* instr, char* instr_bin_str){
	instr_bin_str[0]='0';
	instr_bin_str[1]='0';
	instr_bin_str[2]='1';
	instr_bin_str[3]='0';
	instr_bin_str+=4;

	char instr_cp[15];
	strcpy(instr_cp,instr);
	char* token;
	char s[2]=" ";
	token=strtok(instr_cp, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	instr_bin_str[0]='1';
	instr_bin_str[1]='0';
	instr_bin_str+=2;

	token = strtok(NULL, s);
	
	parse_im(token, instr_bin_str, 7);
	instr_bin_str+=7;

	instr_bin_str[0]='\0';

	return 0;
}

int parse_cmpiu (char* instr, char* instr_bin_str){
	instr_bin_str[0]='0';
	instr_bin_str[1]='0';
	instr_bin_str[2]='1';
	instr_bin_str[3]='0';
	instr_bin_str+=4;

	char instr_cp[15];
	strcpy(instr_cp,instr);
	char* token;
	char s[2]=" ";
	token=strtok(instr_cp, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	instr_bin_str[0]='1';
	instr_bin_str[1]='1';
	instr_bin_str+=2;

	token = strtok(NULL, s);
	if(token[0]=='-'){
		perror("input invalid for CMPIU.\n");
		return -1;
	}
	parse_im(token, instr_bin_str, 7);
	instr_bin_str+=7;

	instr_bin_str[0]='\0';

	return 0;
}

int parse_const (char* instr, char* instr_bin_str){
	instr_bin_str[0]='1';
	instr_bin_str[1]='0';
	instr_bin_str[2]='0';
	instr_bin_str[3]='1';
	instr_bin_str+=4;

	char instr_cp[15];
	strcpy(instr_cp,instr);
	char* token;
	char s[2]=" ";
	token=strtok(instr_cp, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	token = strtok(NULL, s);
	
	parse_im(token, instr_bin_str, 9);
	instr_bin_str+=9;

	instr_bin_str[0]='\0';

	return 0;
}


int parse_cmp (char* instr, char* instr_bin_str){
	instr_bin_str[0]='0';
	instr_bin_str[1]='0';
	instr_bin_str[2]='1';
	instr_bin_str[3]='0';
	instr_bin_str+=4;

	char instr_cp[15];
	strcpy(instr_cp,instr);
	char* token;
	char s[2]=" ";
	token=strtok(instr_cp, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	instr_bin_str[0]='0';
	instr_bin_str[1]='0';
	instr_bin_str+=2;

	for(int i=0; i<4; i++){
		instr_bin_str[i]='0';
	}
	instr_bin_str+=4;

	token = strtok(NULL, s);
	
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	instr_bin_str[0]='\0';

	return 0;
}

int parse_cmpu (char* instr, char* instr_bin_str){
	instr_bin_str[0]='0';
	instr_bin_str[1]='0';
	instr_bin_str[2]='1';
	instr_bin_str[3]='0';
	instr_bin_str+=4;

	char instr_cp[15];
	strcpy(instr_cp,instr);
	char* token;
	char s[2]=" ";
	token=strtok(instr_cp, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	instr_bin_str[0]='0';
	instr_bin_str[1]='1';
	instr_bin_str+=2;
	for(int i=0; i<4; i++){
		instr_bin_str[i]='0';
	}
	instr_bin_str+=4;

	token = strtok(NULL, s);
	
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	instr_bin_str[0]='\0';

	return 0;
}

int parse_jsrr(char* instr, char* instr_bin_str){
	instr_bin_str[0]='0';
	instr_bin_str[1]='1';
	instr_bin_str[2]='0';
	instr_bin_str[3]='0';
	instr_bin_str[4]='0';
	instr_bin_str+=5;

	for(int i=0;i<2;i++){
		instr_bin_str[i]='0';
	}
	instr_bin_str+=2;

	char instr_cp[15];
	strcpy(instr_cp,instr);
	char* token;
	char s[2]=" ";
	token=strtok(instr_cp, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	for(int i=0;i<6;i++){
		instr_bin_str[i]='0';
	}
	instr_bin_str+=6;

	instr_bin_str[0]='\0';

	return 0;

}

int parse_jmpr(char* instr, char* instr_bin_str){
	instr_bin_str[0]='1';
	instr_bin_str[1]='1';
	instr_bin_str[2]='0';
	instr_bin_str[3]='0';
	instr_bin_str[4]='0';
	instr_bin_str+=5;

	for(int i=0;i<2;i++){
		instr_bin_str[i]='0';
	}
	instr_bin_str+=2;

	char instr_cp[15];
	strcpy(instr_cp,instr);
	char* token;
	char s[2]=" ";
	token=strtok(instr_cp, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	for(int i=0;i<6;i++){
		instr_bin_str[i]='0';
	}
	instr_bin_str+=6;

	instr_bin_str[0]='\0';

	return 0;

}


int parse_hiconst(char* instr, char* instr_bin_str){
	instr_bin_str[0]='1';
	instr_bin_str[1]='1';
	instr_bin_str[2]='0';
	instr_bin_str[3]='1';

	instr_bin_str+=4;

	char instr_cp[15];
	strcpy(instr_cp,instr);
	char* token;
	char s[2]=" ";
	token=strtok(instr_cp, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	instr_bin_str[0]='1';
	instr_bin_str++;

	token = strtok(NULL, s);
	if(token[0]=='-'){
		perror("input invalid for HICONST.");
		return -1;
	}
	parse_im(token, instr_bin_str, 8);
	instr_bin_str+=8;

	instr_bin_str[0]='\0';

	return 0;

}

int parse_trap(char* instr, char* instr_bin_str){
	instr_bin_str[0]='1';
	instr_bin_str[1]='1';
	instr_bin_str[2]='1';
	instr_bin_str[3]='1';

	instr_bin_str+=4;

	for(int i=0;i<4;i++){
		instr_bin_str[i]='0';
	}
	instr_bin_str+=4;

	char instr_cp[15];
	strcpy(instr_cp,instr);
	char* token;
	char s[2]=" ";
	token=strtok(instr_cp, s);
	token = strtok(NULL, s);
	if(token[0]=='-'){
		perror("input invalid for TRAP.");
		return -1;
	}
	parse_im(token, instr_bin_str, 8);
	instr_bin_str+=8;

	instr_bin_str[0]='\0';

	return 0;

}

int parse_sll(char* instr, char* instr_bin_str){
	instr_bin_str[0]='1';
	instr_bin_str[1]='0';
	instr_bin_str[2]='1';
	instr_bin_str[3]='0';
	instr_bin_str+=4;

	char instr_cp1[15];
	strcpy(instr_cp1,instr);
	char* token;
	const char s[2]=" ";
	token=strtok(instr_cp1, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;
	
	for(int i=0;i<2;i++){
		instr_bin_str[i]='0';
	}
	instr_bin_str+=2;

	token = strtok(NULL, s);
	parse_im(token, instr_bin_str,4);
	instr_bin_str+=4;

	instr_bin_str[0]='\0';

	return 0;
}
int parse_sra(char* instr, char* instr_bin_str){
	instr_bin_str[0]='1';
	instr_bin_str[1]='0';
	instr_bin_str[2]='1';
	instr_bin_str[3]='0';
	instr_bin_str+=4;

	char instr_cp1[15];
	strcpy(instr_cp1,instr);
	char* token;
	const char s[2]=" ";
	token=strtok(instr_cp1, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;
	
	
	instr_bin_str[0]='0';
	instr_bin_str[1]='1';
	instr_bin_str+=2;

	token = strtok(NULL, s);
	parse_im(token, instr_bin_str,4);
	instr_bin_str+=4;

	instr_bin_str[0]='\0';

	return 0;
}
int parse_srl(char* instr, char* instr_bin_str){
	instr_bin_str[0]='1';
	instr_bin_str[1]='0';
	instr_bin_str[2]='1';
	instr_bin_str[3]='0';
	instr_bin_str+=4;

	char instr_cp1[15];
	strcpy(instr_cp1,instr);
	char* token;
	const char s[2]=" ";
	token=strtok(instr_cp1, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;
	
	
	instr_bin_str[0]='1';
	instr_bin_str[1]='0';
	instr_bin_str+=2;

	token = strtok(NULL, s);
	parse_im(token, instr_bin_str,4);
	instr_bin_str+=4;

	instr_bin_str[0]='\0';

	return 0;
}
int parse_mod(char* instr, char* instr_bin_str){
	instr_bin_str[0]='1';
	instr_bin_str[1]='0';
	instr_bin_str[2]='1';
	instr_bin_str[3]='0';
	instr_bin_str+=4;

	char instr_cp1[15];
	strcpy(instr_cp1,instr);
	char* token;
	const char s[2]=" ";
	token=strtok(instr_cp1, s);
	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;
	
	
	instr_bin_str[0]='1';
	instr_bin_str[1]='1';
	instr_bin_str+=2;

	instr_bin_str[0]='0';
	instr_bin_str++;

	token = strtok(NULL, s);
	parse_reg(token[1], instr_bin_str);
	instr_bin_str+=3;

	instr_bin_str[0]='\0';

	return 0;
}
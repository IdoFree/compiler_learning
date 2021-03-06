#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "token.h"

static char * st_line;
static int st_line_pos;

typedef enum {
	INITIAL_STATUS,
	IN_INI_PART_STATUS,
	DOT_STATUS,
	IN_FRAC_PART_STATUS
}LexerStatus;

/*this function will return the token when every time called */
void 
get_token(Token * token)
{
	int out_pos = 0;
	LexerStatus status = INITIAL_STATUS;
	char current_char;
	
	token->kind = BAD_TOKEN;
	while(st_line[st_line_pos]!= '\0'){
		current_char = st_line[st_line_pos];
		if((status == IN_INI_PART_STATUS || status == IN_FRAC_PART_STATUS) 
			 && !isdigit(current_char)&& current_char != '.'){
				 token->kind = NUMBER_TOKEN;
				 sscanf(token->str,"%lf",&token->value);
			 }
		
		if(isspace(current_char)){
			if(current_char == '\n'){
				token->kind = END_OF_LINE_TOKEN;
				return ;
			}
			st_line_pos++;
			continue;
		}
		
		if(out_pos >= MAX_TOKEN_SIZE -1 ){
			fprintf(stderr,"token too long\n");
			exit(1);
		}
		token->str[out_pos] = st_line[st_line_pos];
		st_line_pos++;
		out_pos++;
		token->str[out_pos] = '\0';
		
		if(current_char == '+'){
			token->kind = ADD_OPPERATOR_TOKEN;
			return;
		}else if(current_char == '-'){
			token->kind = SUB_OPPERATOR_TOKEN;
			return;
		}else if(current_char == '*'){
			token->kind = MUL_OPPERATOR_TOKEN;
			return;
		}else if(current_char == '/'){
			token->kind = DIV_OPPERATOR_TOKEN;
			return;
		}else if(isdigit(current_char)){
			if(status == INITIAL_STATUS){
				status = IN_INI_PART_STATUS;
			}else if(status == DOT_STATUS){
				status = IN_FRAC_PART_STATUS;
			}
		}else if(current_char == '.'){
			if(status == IN_INI_PART_STATUS){
				status = DOT_STATUS;
			}else{
				fprintf(stderr,"syntax error\n");
			}
		}else{
			fprintf(stderr,"bad character(%c)\n",current_char);
		}
		
	}
}


void 
set_line(char * line)
{
	st_line = line;
	st_line_pos = 0;
}


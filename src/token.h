#ifndef TOKEN_H_INCLUEDED
#define TOKEN_H_INCLUEDED


typedef enum {
	BAD_TOKEN,
	NUMBER_TOKEN,
	ADD_OPPERATOR_TOKEN,
	SUB_OPPERATOR_TOKEN,
	MUL_OPPERATOR_TOKEN,
	DIV_OPPERATOR_TOKEN,
	END_OF_LINE_TOKEN,
} TokenKind;

#define MAX_TOKEN_SIZE (100)

typedef struct {
	TokenKind kind;
	double	value;
	char	str(MAX_TOKEN_SIZE);
}Token;

void set_line(char * line);
void get_token(Token* token)




#endif
%{
/*
Date: 2019.5.6
Author: Aman
ALL RIGHTS DESERVED
 */
#include <string.h>
#include <stdlib.h>
#include "Syntax.tab.h"

typedef struct node{
	char* data;
	struct node* left;
	struct node* right;
}Node;

#define maxsize 50
typedef Node* elem;

typedef struct{
	Node* root;
}Tree;

typedef struct{
	int top;
	elem index[maxsize];
}Stack;

Stack stack;
Tree tree;

int row_num = 1, col_num = 1;  //行数和列数
FILE *fp;	//指向输出文件的指针 Constant [-]?([0-9])|([1-9][0-9]+[\.]?[0-9]*)
FILE *fh;	//指向输出层次结构的指针
char *key;

void Process(char* temp);
%}


KeyWord [iI][fF]|[tT][hH][eE][nN]|[eE][lL][sS][eE]|[wW][hH][iI][lL][eE]|[dD][oO]|[rR][eE][aA][dD]|[wW][rR][iI][tT][eE]|[cC][aA][lL][lL]|[bB][eE][gG][iI][nN]|[eE][nN][dD]|[cC][oO][nN][sS][tT]|[vV][aA][rR]|[pP][rR][oO][cC][eE][dD][uU][rR][eE]|[oO][dD][dD]|[cC][aA][sS][eE]|[eE][nN][dD][cC][aA][sS][eE]
Identifier [A-Za-z][A-Za-z0-9]*
Zero [0]
PossiInt ([+]?[1-9][0-9]*)
NegatiInt ([-]?[0-9]+)
Float {Zero}|{PossiInt}|{NegatiInt}(.[0-9]+)
Constant {PossiInt}|{NegatiInt}|{Zero}
Operator [\[\]\^\-\*\+\?\{\}\"\\\(\)\|\/\$\<\>\#\=]|:=
Delimiter  [\,\;\.\:]
Space (\ )
Tab (\t)
Other [^{KeyWord}{Identifier}{Constant}{Operator}{Delimiter}]

%%

	//这部分注释要有前导空格，否则lex编译出错

{KeyWord} {
	// fprintf(fp, "%s : K, (%d, %d)\n", yytext, row_num, col_num);
	if(!strcmpi(yytext, "CONST")){
		key = "CONST";
		// Process(key);
		return CONST;
	}
	if(!strcmpi(yytext, "VAR")){
		key = "VAR";
		// Process(key);
		return VAR;
	}
	if(!strcmpi(yytext, "PROCEDURE")){
		key = "PROCEDURE";
		// Process(key);
		return PROCEDURE;
	}
	if(!strcmpi(yytext, "BEGIN")){
		key = "BEGIN";
		// Process(key);
		return _BEGIN_;
	}
	if(!strcmpi(yytext, "END")){
		key = "END";
		// Process(key);
		return END;
	}
	if(!strcmpi(yytext, "IF")){
		key = "IF";
		// Process(key);
		return IF;
	}
	if(!strcmpi(yytext, "THEN")){
		key = "THEN";
		// Process(key);
		return THEN;
	}
	if(!strcmpi(yytext, "ELSE")){
		key = "ELSE";
		// Process(key);
		return ELSE;
	}
	if(!strcmpi(yytext, "ODD")){
		key = "ODD";
		// Process(key);
		return ODD;
	}
	if(!strcmpi(yytext, "WHILE")){
		key = "WHILE";
		// Process(key);
		return WHILE;
	}
	if(!strcmpi(yytext, "DO")){
		key = "DO";
		// Process(key);
		return DO;
	}
	if(!strcmpi(yytext, "CALL")){
		key = "CALL";
		// Process(key);
		return CALL;
	}
	if(!strcmpi(yytext, "READ")){
		key = "CONST";
		// Process(key);
		return READ;
	}
	if(!strcmpi(yytext, "WRITE")){
		key = "WRITE";
		// Process(key);
		return WRITE;
	}
	if(!strcmpi(yytext, "CASE")){
		key = "CASE";
		// Process(key);
		return CASE;
	}
	if(!strcmpi(yytext, "ENDCASE")){
		key = "ENDCASE";
		// Process(key);
		return ENDCASE;
	}
	col_num += yyleng;
	// return KeyWord;
}
{Identifier} {
	if(yyleng > 10){
		// fprintf(fp, "Error!Expected a shorter IDENTIFIER!(%d, %d)\n", row_num, col_num);
		col_num += yyleng;
	}
	else{
		// fprintf(fp, "%s : I, (%d, %d)\n", yytext, row_num, col_num); col_num += yyleng;
	}
	// printf("--%s--\n", yytext);
	key = "IDENTIFIER";
	// Process(key);
	return IDENTIFIER;
}  
{Constant} {
	if(yyleng > 14){
		// fprintf(fp, "Error!Expected a shorter CONSTANT!(%d, %d)\n", row_num, col_num);
		col_num += yyleng;
	}
	else{
		// fprintf(fp, "%s : C, (%d, %d)\n", yytext, row_num, col_num);
		col_num += yyleng;
	}
	key = "CONSTANT";
	// Process(key);
	return CONSTANT;
}
{Operator} {
	// fprintf(fp, "%s : O, (%d, %d)\n", yytext, row_num, col_num);
	if(!strcmpi(yytext, "=")||!strcmpi(yytext, "#")||!strcmpi(yytext, "<")||!strcmpi(yytext, "<=")||!strcmpi(yytext, ">")||!strcmpi(yytext, ">=")){
		key = "RELOP";
		// Process(key);
		return RELOP;
	}
	if(!strcmpi(yytext, "(")){
		key = "LPAREN";
		// Process(key);
		return LPAREN;
	}
	if(!strcmpi(yytext, ")")){
		key = "RPAREN";
		// Process(key);
		return RPAREN;
	}
	if(!strcmpi(yytext, ":=")){
		key = "CONST";
		// Process(key);
		return ASSIGN;
	}
	if(!strcmpi(yytext, "-")){
		key = "MINUS";
		// Process(key);
		return MINUS;
	}
	if(!strcmpi(yytext, "+")){
		key = "PLUS";
		// Process(key);
		return PLUS;
	}
	if(!strcmpi(yytext, "*")){
		key = "TIMES";
		// Process(key);
		return TIMES;
	}
	if(!strcmpi(yytext, "/")){
		key = "DIVIDE";
		// Process(key);
		return DIVIDE;
	}
	col_num += yyleng;
	// return Operator;
}
{Delimiter} {
	// fprintf(fp, "%s : D, (%d, %d)\n", yytext, row_num, col_num);
	++col_num;
	if(!strcmpi(yytext, ",")){
		key = "COMMA";
		// Process(key);
		return COMMA;
	}
	if(!strcmpi(yytext, ";")){
		key = "SEMI";
		// Process(key);
		return SEMI;
	}
	if(!strcmpi(yytext, ".")){
		key = "DOT";
		// Process(key);
		return DOT;
	}
	if(!strcmpi(yytext, ":")){
		key = "COLON";
		// Process(key);
		return COLON;
	}
}
\n {++row_num; col_num = 1;}  //换行符计数
{Space} {;}
{Tab} {;}
{Other} {
	// fprintf(fp, "%s : T, (%d, %d)\n", yytext, row_num, col_num);
	col_num += yyleng;
}

%%
// int main(){
// 	// fp = fopen("E:/.../.../Compiling Principle/Lab2/WordOutput.txt", "w+");
// 	yylex();
// }
int yywrap(){
	return 1;
}




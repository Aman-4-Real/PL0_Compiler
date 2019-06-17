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
FILE *fw;	//指向词法输出文件的指针
// FILE *fh;	//指向输出层次结构的指针
char key[14];	//用于保存识别到的word名, 便于入栈
// char idname[20];

// Constant [-]?([0-9])|([1-9][0-9]+[\.]?[0-9]*)

void Process(char* temp);
%}


KeyWord [iI][fF]|[tT][hH][eE][nN]|[eE][lL][sS][eE]|[wW][hH][iI][lL][eE]|[dD][oO]|[rR][eE][aA][dD]|[wW][rR][iI][tT][eE]|[cC][aA][lL][lL]|[bB][eE][gG][iI][nN]|[eE][nN][dD]|[cC][oO][nN][sS][tT]|[vV][aA][rR]|[pP][rR][oO][cC][eE][dD][uU][rR][eE]|[oO][dD][dD]|[cC][aA][sS][eE]|[eE][nN][dD][cC][aA][sS][eE]
Identifier [A-Za-z][A-Za-z0-9]*
Zero [0]
PossiInt ([+]?[1-9][0-9]*)
NegatiInt ([-]?[0-9]+)
Float {Zero}|{PossiInt}|{NegatiInt}(.[0-9]+)
Constant {PossiInt}|{NegatiInt}|{Zero}
Operator [\[\]\^\-\*\+\?\{\}\"\\\(\)\|\/\$\<\>\#\=]|:=|<=|>=
Delimiter  [\,\;\.\:]
Space (\ )
Tab (\t)
Other [^{KeyWord}{Identifier}{Constant}{Operator}{Delimiter}]

%%

	//这部分注释要有前导空格，否则lex编译出错

{KeyWord} {
	fprintf(fw, "%s : K, (%d, %d)\n", yytext, row_num, col_num);
	if(!strcmpi(yytext, "CONST")){
		strcpy(key, "CONST");
		// Process(key);
		return CONST;
	}
	if(!strcmpi(yytext, "VAR")){
		strcpy(key, "VAR");
		// Process(key);
		return VAR;
	}
	if(!strcmpi(yytext, "PROCEDURE")){
		strcpy(key, "PROCEDURE");
		// Process(key);
		return PROCEDURE;
	}
	if(!strcmpi(yytext, "BEGIN")){
		strcpy(key, "BEGIN");
		// Process(key);
		return _BEGIN_;
	}
	if(!strcmpi(yytext, "END")){
		strcpy(key, "END");
		// Process(key);
		return END;
	}
	if(!strcmpi(yytext, "IF")){
		strcpy(key, "IF");
		// Process(key);
		return IF;
	}
	if(!strcmpi(yytext, "THEN")){
		strcpy(key, "THEN");
		// Process(key);
		return THEN;
	}
	if(!strcmpi(yytext, "ELSE")){
		strcpy(key, "ELSE");
		// Process(key);
		return ELSE;
	}
	if(!strcmpi(yytext, "ODD")){
		strcpy(key, "ODD");
		// Process(key);
		return ODD;
	}
	if(!strcmpi(yytext, "WHILE")){
		strcpy(key, "WHILE");
		// Process(key);
		return WHILE;
	}
	if(!strcmpi(yytext, "DO")){
		strcpy(key, "DO");
		// Process(key);
		return DO;
	}
	if(!strcmpi(yytext, "CALL")){
		strcpy(key, "CALL");
		// Process(key);
		return CALL;
	}
	if(!strcmpi(yytext, "READ")){
		strcpy(key, "READ");
		// Process(key);
		return READ;
	}
	if(!strcmpi(yytext, "WRITE")){
		strcpy(key, "WRITE");
		// Process(key);
		return WRITE;
	}
	if(!strcmpi(yytext, "CASE")){
		strcpy(key, "CASE");
		// Process(key);
		return CASE;
	}
	if(!strcmpi(yytext, "ENDCASE")){
		strcpy(key, "ENDCASE");
		// Process(key);
		return ENDCASE;
	}
	col_num += yyleng;
	// return KeyWord;
}
{Identifier} {
	if(yyleng > 10){
		fprintf(fw, "Error!Expected a shorter IDENTIFIER!(%d, %d)\n", row_num, col_num);
		col_num += yyleng;
	}
	else{
		fprintf(fw, "%s : I, (%d, %d)\n", yytext, row_num, col_num); col_num += yyleng;
	}
	// printf("--%s--\n", yytext);
	strcpy(key, yytext);
	// strcpy(idname, yytext);
	yylval.var.str = strdup(yytext);
	// Process(key);
	return IDENTIFIER;
}  
{Constant} {
	if(yyleng > 14){
		fprintf(fw, "Error!Expected a shorter CONSTANT!(%d, %d)\n", row_num, col_num);
		col_num += yyleng;
	}
	else{
		fprintf(fw, "%s : C, (%d, %d)\n", yytext, row_num, col_num);
		col_num += yyleng;
	}
	strcpy(key, yytext);
	yylval.val = atoi(yytext);
	// Process(key);
	return CONSTANT;
}
{Operator} {
	fprintf(fw, "%s : O, (%d, %d)\n", yytext, row_num, col_num);
	if(!strcmpi(yytext, "=")||!strcmpi(yytext, "#")||!strcmpi(yytext, "<")||!strcmpi(yytext, "<=")||!strcmpi(yytext, ">")||!strcmpi(yytext, ">=")){
		strcpy(key, "RELOP");
		yylval.var.str = strdup(yytext);
		// Process(key);
		return RELOP;
	}
	if(!strcmpi(yytext, "(")){
		strcpy(key, "LPAREN");
		// Process(key);
		return LPAREN;
	}
	if(!strcmpi(yytext, ")")){
		strcpy(key, "RPAREN");
		// Process(key);
		return RPAREN;
	}
	if(!strcmpi(yytext, ":=")){
		strcpy(key, "ASSIGN");
		// Process(key);
		return ASSIGN;
	}
	if(!strcmpi(yytext, "-")){
		strcpy(key, "MINUS");
		// Process(key);
		return MINUS;
	}
	if(!strcmpi(yytext, "+")){
		strcpy(key, "PLUS");
		// Process(key);
		return PLUS;
	}
	if(!strcmpi(yytext, "*")){
		strcpy(key, "TIMES");
		// Process(key);
		return TIMES;
	}
	if(!strcmpi(yytext, "/")){
		strcpy(key, "DIVIDE");
		// Process(key);
		return DIVIDE;
	}
	col_num += yyleng;
	// return Operator;
}
{Delimiter} {
	fprintf(fw, "%s : D, (%d, %d)\n", yytext, row_num, col_num);
	++col_num;
	if(!strcmpi(yytext, ",")){
		strcpy(key, "COMMA");
		// Process(key);
		return COMMA;
	}
	if(!strcmpi(yytext, ";")){
		strcpy(key, "SEMI");
		// Process(key);
		return SEMI;
	}
	if(!strcmpi(yytext, ".")){
		strcpy(key, "DOT");
		// Process(key);
		return DOT;
	}
	if(!strcmpi(yytext, ":")){
		strcpy(key, "COLON");
		// Process(key);
		return COLON;
	}
}
\n {++row_num; col_num = 1;}  //换行符计数
{Space} {;}
{Tab} {;}
{Other} {
	fprintf(fw, "%s : T, (%d, %d)\n", yytext, row_num, col_num);
	col_num += yyleng;
}

%%
// int main(){
// 	// fw = fopen("E:/.../.../Compiling Principle/Lab2/WordOutput.txt", "w+");
// 	yylex();
// }
int yywrap(){
	return 1;
}




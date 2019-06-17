%{
/*
Date: 2019.5.6
Author: Aman
ALL RIGHTS DESERVED
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


FILE *fi;  //指向输出文件的指针
extern int row_num, col_num;  //行数和列数
extern FILE *fh;  //指向输出层次结构的指针
extern char *key;
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

extern Stack stack;
extern Tree tree;

int yylex();
int yyerror(char *s);
extern void Process(char* temp);
void left_insert(Node* parent, Node* son);
void right_insert(Node* node, Node* bro);
void stack_init();
elem stack_pop();
void stack_push(elem p);
void PreOrderTravel(Node* T, int k);
int stack_empty();
int stack_size();
elem stack_top();
void Reduce(char* name, int num);

%}

%start Program
%token IDENTIFIER CONSTANT RELOP
%token COMMA SEMI DOT LPAREN RPAREN ASSIGN MINUS COLON
%token CONST VAR PROCEDURE _BEGIN_ END IF THEN ELSE ODD WHILE DO CALL READ WRITE CASE ENDCASE
%left PLUS MINUS
%left TIMES DIVIDE
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


%%
Program     :subProg DOT {
                  fprintf(fi, "Program -> subProg.\n");
                  Reduce("Program", 2);
                  tree.root = stack_pop();
                        // printf("---%s---\n", tree.root->left->data);

                  PreOrderTravel(tree.root, 0);
            }
            ;
subProg     :DeclarePart Statement {
                  fprintf(fi, "subProg -> DeclarePart Statement\n");
                  Reduce("subProg", 2);
            }
            |Statement {
                  fprintf(fi, "subProg -> Statement\n");
                  Reduce("subProg", 1);
            }
            ;
DeclarePart :ConstDec {
                  fprintf(fi, "DeclarePart -> ConstDec\n");
                  Reduce("DeclarePart", 1);
            }
            |ConstDec VarDec {
                  fprintf(fi, "DeclarePart -> ConstDec VarDec\n");
                  Reduce("DeclarePart", 2);
            }
            |ConstDec ProceDec {
                  fprintf(fi, "DeclarePart -> ConstDec ProceDec\n");
                  Reduce("DeclarePart", 2);
            }
            |ConstDec VarDec ProceDec {
                  fprintf(fi, "DeclarePart -> ConstDec VarDec ProceDec\n");
                  Reduce("DeclarePart", 3);
            }
            |VarDec ProceDec {
                  fprintf(fi, "DeclarePart -> VarDec ProceDec\n");
                  Reduce("DeclarePart", 2);
            } 
            |VarDec {
                  fprintf(fi, "DeclarePart -> VarDec\n");
                  Reduce("DeclarePart", 1);
            }
            |ProceDec {
                  fprintf(fi, "DeclarePart -> ProceDec\n");
                  Reduce("DeclarePart", 1);
            }
            // | {fprintf(fi, "DeclarePart -> ε\n");}
            ;
ConstDec    :CONST ConstDef SEMI {
                  fprintf(fi, "ConstDec -> CONST ConstDef;\n");
                  Reduce("ConstDec", 3);
            }
            ; 
ConstDef    :ConstDef COMMA CDefine {
                  fprintf(fi, "ConstDef -> ConstDef, CDefine\n");
                  Reduce("ConstDef", 3);
            }
            |CDefine {
                  fprintf(fi, "ConstDef -> CDefine\n");
                  Reduce("ConstDef", 1);
            }
            ;
CDefine     :IDENTIFIER RELOP CONSTANT {
                  $1 = $3; fprintf(fi, "CDefine -> IDENTIFIER = CONSTANT\n");
                  Reduce("CDefine", 3);
            }
            ;
VarDec      :VAR IdentiObj SEMI {
                  fprintf(fi, "VarDec -> VAR IdentiObj;\n");
                  Reduce("VarDec", 3);
            }
            ;
IdentiObj   :IdentiObj COMMA IDENTIFIER {
                  fprintf(fi, "IdentiObj -> IdentiObj, IDENTIFIER\n");
                  Reduce("IdentiObj", 3);
            }
            |IDENTIFIER {
                  fprintf(fi, "IdentiObj -> IDENTIFIER\n");
                  Reduce("IdentiObj", 1);
            }
            ;
ProceDec    :ProceHead subProg SEMI {
                  fprintf(fi, "ProceDec -> ProceHead subProg ProceDec;\n");
                  Reduce("ProceDec", 3);
            }
            |ProceDec ProceHead subProg SEMI {
                  fprintf(fi, "ProceDec -> ProceDec ProceHead subProg;\n");
                  Reduce("ProceDec", 4);
            }
            // | {fprintf(fp, "ProceDec -> ε\n");}
            ;
ProceHead   :PROCEDURE IDENTIFIER SEMI  {
                  fprintf(fi, "ProceHead -> PROCEDURE IDENTIFIER;\n");
                  Reduce("ProceHead", 3);
            }
            ;
Statement   :AssignStm {
                  fprintf(fi, "Statement -> AssignStm\n");
                  Reduce("Statement", 1);
            }
            |ComplexStm {
                  fprintf(fi, "Statement -> ComplexStm\n");
                  Reduce("Statement", 1);
            }
            |CondStm {
                  fprintf(fi, "Statement -> CondStm\n");
                  Reduce("Statement", 1);
            }
            |WhilelpStm {
                  fprintf(fi, "Statement -> WhilelpStm\n");
                  Reduce("Statement", 1);
            }
            |CaseStm {
                  fprintf(fi, "Statement -> CaseStm\n");
                  Reduce("Statement", 1);
            }
            |CallStm {
                  fprintf(fi, "Statement -> CallStm\n");
                  Reduce("Statement", 1);
            }
            |ReadStm {
                  fprintf(fi, "Statement -> ReadStm\n");
                  Reduce("Statement", 1);
            }
            |WriteStm {
                  fprintf(fi, "Statement -> WriteStm\n");
                  Reduce("Statement", 1);
            }
            // | {fprintf(fp, "Statement -> ε\n");}
            ;
AssignStm   :IDENTIFIER ASSIGN Expr {
                  $1 = $3; fprintf(fi, "AssignStm -> IDENTIFIER := Expr\n");
                  Reduce("AssignStm", 3);
            }
            ;
ComplexStm  :_BEGIN_ Statemt END {
                  fprintf(fi, "ComplexStm -> _BEGIN_ Statemt Statement END\n");
                  Reduce("ComplexStm", 3);
            }
            ;
Statemt     :Statement SEMI {
                  fprintf(fi, "Statemt -> Statement;\n");
                  Reduce("Statemt", 2);
            }
            |Statemt Statement SEMI {
                  fprintf(fi, "Statemt -> Statemt Statement;\n");
                  Reduce("Statemt", 3);
            }
            // | {fprintf(fp, "Statemt -> ε\n");}
            ;
CondStm     :IF Condition THEN Statement %prec LOWER_THAN_ELSE {
                  fprintf(fi, "CondStm -> IF Condition THEN Statement\n");
                  Reduce("CondStm", 4);
            }
            |IF Condition THEN Statement ELSE Statement {
                  fprintf(fi, "Statement -> IF Condition THEN Statement ELSE Statement\n");
                  Reduce("CondStm", 6);
            }
            ;
Condition   :Expr RELOP Expr {
                  fprintf(fi, "Condition -> Expr RELOP Expr\n");
                  Reduce("Condition", 3);
            }
            |ODD Expr {
                  fprintf(fi, "Condition -> ODD Expr\n");
                  Reduce("Condition", 2);
            }
            ;
Expr        :Expr PLUS Term {
                  $$ = $1 + $3; fprintf(fi, "Expr -> Expr + Term\n");
                  Reduce("Expr", 3);
            }
            |Expr MINUS Term {
                  $$ = $1 - $3; fprintf(fi, "Expr -> Expr - Term\n");
                  Reduce("Expr", 3);
            }
            |PLUS Term {
                  $$ = $2; fprintf(fi, "Expr -> +Term\n");
                  Reduce("Expr", 2);
            }
            |MINUS Term {
                  $$ = -$2; fprintf(fi, "Expr -> -Term\n");
                  Reduce("Expr", 2);
            }
            |Term {
                  $$ = $1; fprintf(fi, "Expr -> Term\n");
                  Reduce("Expr", 1);
            }
            ;
Term        :Term TIMES Factor {
                  $$ = $1 * $3; fprintf(fi, "Term -> Term * Factor\n");
                  Reduce("Term", 3);
            }
            |Term DIVIDE Factor {
                  $$ = $1 / $3; fprintf(fi, "Term -> Term / Factor\n");
                  Reduce("Term", 3);
            }
            |Factor {
                  $$ = $1; fprintf(fi, "Term -> Factor\n");
                  Reduce("Term", 1);
            }
            ;
Factor      :IDENTIFIER {
                  $$ = $1; fprintf(fi, "Factor -> IDENTIFIER\n");
                  Reduce("Factor", 1);
            }
            |CONSTANT {
                  $$ = $1; fprintf(fi, "Factor -> CONSTANT\n");
                  Reduce("Factor", 1);
            }
            |LPAREN Expr RPAREN {
                  $$ = $2; fprintf(fi, "Factor -> (Expr)\n");
                  Reduce("Factor", 3);
            }
            ;
WhilelpStm  :WHILE Condition DO Statement {
                  fprintf(fi, "WhilelpStm -> WHILE Condition DO Statement\n");
                  Reduce("WhilelpStm", 4);
            }
            ;
CaseStm     :CaseHead CaseBody ENDCASE {
                  fprintf(fi, "CaseStm -> CaseHead CaseBody ENDCASE\n");
                  Reduce("CaseStm", 3);
            }
            ;
CaseHead    :CASE IDENTIFIER COLON {
                  fprintf(fi, "CaseHead -> CASE IDENTIFIER COLON\n");
                  Reduce("CaseHead", 3);
            }
            ;
CaseBody    :CaseBody CONSTANT COLON Statemt {
                  fprintf(fi, "CaseBody -> CaseBody CONSTANT COLON Statemt\n");
                  Reduce("CaseBody", 4);
            }
            |CONSTANT COLON Statemt {
                  fprintf(fi, "CaseBody -> CONSTANT COLON Statemt\n");
                  Reduce("CaseBody", 3);
            }
            ;
CallStm     :CALL IDENTIFIER {
                  fprintf(fi, "CallStm -> CALL IDENTIFIER\n");
                  Reduce("CallStm", 2);
            }
            ;
ReadStm     :READ LPAREN IdentiObj RPAREN {
                  fprintf(fi, "ReadStm -> READ(IdentiObj)\n");
                  Reduce("ReadStm", 4);
            }
            ;
WriteStm    :WRITE LPAREN ExprObj RPAREN {
                  fprintf(fi, "WriteStm -> WRITE(ExprObj)\n");
                  Reduce("WriteStm", 4);
            }
            ;
ExprObj     :ExprObj COMMA Expr {
                  fprintf(fi, "ExprObj -> ExprObj, Expr\n");
                  Reduce("ExprObj", 3);
            }
            |Expr {
                  fprintf(fi, "ExprObj -> Expr\n");
                  Reduce("ExprObj", 1);
            }
            ;

%%
int main(){
    fi = fopen("E:/.../.../Compiling Principle/Lab2/SynOutput.txt", "w+");
    fh = fopen("E:/.../.../Compiling Principle/Lab2/hierarchy.txt", "w+");
    stack_init();

    yyparse();

    
    return 1;
}

int yyerror(char *s){
    printf("%s, (%d,%d)\n", s, row_num, col_num);
    // fprintf(stderr,"%s\n",s);
    return 1;
}


void left_insert(Node* parent, Node* son){
      parent -> left = son;
}

void right_insert(Node* node, Node* bro){
      node -> right = bro;
}

void stack_init(){
      stack.top = -1;
}

elem stack_pop(){
      int i;
      if(stack.top == -1){
            printf("Overflow stack pop size.\n");
            return 0;
      }
      return stack.index[stack.top --];
}

void stack_push(elem p){
      stack.index[++stack.top] = p;
}

int stack_empty(){
      return stack.top == -1;
}

int stack_size(){
      return stack.top + 1;
}

elem stack_top(){
      return stack.index[stack.top];
}

void PreOrderTravel(Node* T, int k){
      if(T==NULL) return;
      fprintf(fh, "%d:|\t", k);
      for(int i=0; i<k-1; i++) fprintf(fh, "|\t");
      fprintf(fh, "%s\n ",T->data);
      PreOrderTravel(T->left, k+1);
      PreOrderTravel(T->right, k);
}


void Process(char* temp){
      Node* tnode = (Node*)malloc(sizeof(Node));
      tnode -> data = temp;
      tnode -> left = NULL;
      tnode -> right = NULL;
      // printf("---%s---\n", tnode->data);
      stack_push(tnode);
}


void Reduce(char* name, int num){
      elem t[num];
      for (int i = 0; i < num; i++){
            t[i] = stack_pop();
      }
      Node* n = (Node*)malloc(sizeof(Node));
      n -> data = name;
      n -> left = NULL;
      n -> right = NULL;
      left_insert(n, t[num-1]);
      for (int i = num-1; i > 0; i--){
            right_insert(t[i], t[i-1]);
      }
      stack_push(n);
}

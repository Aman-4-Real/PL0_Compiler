%{
/*
Date: 2019.6.7
Author: Aman
ALL RIGHTS DESERVED
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


FILE *fi;  //指向输出文件的指针
FILE *fp;  //指向输出类pcode文件的指针
FILE *fh;  //指向输出层次结构的指针
extern int row_num, col_num;  //行数和列数
extern char key[14];
// extern char idname[20];

typedef struct node{
      char data[14];
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


/**********Lab3 Part**********/
typedef struct{ 
      int kind;         //const = 1, var = 2, proc = 3
      char* name;
      int val;          //如果为-2则为过程名, -1为未赋值的变量
      int level;        //所在层次
      int addr;         //变量的偏移地址
      int previous;     //指向的下一个地址
}symbol; 

#define MAX_SYMBOL_TABLE_SIZE 50
typedef symbol* sym;

typedef struct{
      int top;
      symbol index[MAX_SYMBOL_TABLE_SIZE];
}symbol_table;


symbol_table symtable;  //符号栈
int display_stack[20];  //display栈
int display_top = 0;   //display的栈顶
int now_Level = 0;    //当前的层数
int addr = 3;     //记录每个变量在运行栈中相对本过程基地址的偏移量

typedef struct{
    enum f{LIT, LOD, STO, CAL, INT, JMP, JPC, OPR} f;
    int l;
    int a;
}instruction; 

#define STACKSIZE 200
instruction code[STACKSIZE];
int code_line = 0;
char *fname[]={"LIT","LOD","STO","CAL","INT","JMP","JPC","OPR"};

int bkpchpos[50];  //记录回填的位置
int bkpchpos_top = -1;  //回填栈顶

#define MAXPRONUM 20
typedef struct{
    char *proname;
    int l;  //层差
    int pos;
}prostk; 
prostk prostack[MAXPRONUM];
int prostktop = -1;  //过程栈栈顶

int whilepos[10];  //记录循环的code_line
int whiletop = -1;

char *caseid;
/**********Lab3 Part**********/



//函数声明部分
int yylex();
int yyerror(char *s);
extern void Process(char* temp);
void left_insert(Node* parent, Node* son);
void right_insert(Node* node, Node* bro);
void init();
void stack_init();
elem stack_pop();
void stack_push(elem p);
void PreOrderTravel(Node* T, int k);
int stack_empty();
int stack_size();
elem stack_top();
void Reduce(char* name, int num);

void symtable_init();
void symtable_push();
void symtable_pop();
int if_declared();
int symtable_size();
symbol symtable_top();
int find_sign(char *sign_name);
int findpro(char *pname);
void Backpatch(int p, int l);
void gen(enum f f, int l, int a);
void OutputCode();
%}


%union{
      struct{
            int val;
            char *str;
      }var;
      int val;
}

%start Program
%token <var> IDENTIFIER
%token <val> CONSTANT
%token <var> RELOP
%token COMMA SEMI DOT LPAREN RPAREN ASSIGN MINUS COLON
%token CONST VAR PROCEDURE _BEGIN_ END IF THEN ELSE ODD WHILE DO CALL READ WRITE CASE ENDCASE
%type <val> Factor Term Expr
%left PLUS MINUS
%left TIMES DIVIDE
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


%%
Program     :subProg DOT {
                  fprintf(fi, "Program -> subProg.\n");
                  // symtable_pop();
                  gen(OPR, 0, 0);
                  Reduce("Program", 2);
                  tree.root = stack_pop();
                  // printf("---%s---\n", tree.root->left->data);
                  PreOrderTravel(tree.root, 0);
            }
            ;
subProg     :BeforeDec DeclarePart BeforeSTM Statement {
                  fprintf(fi, "subProg -> DeclarePart Statement\n");
                  Reduce("subProg", 2);
            }
            |BeforeDec BeforeSTM Statement {
                  fprintf(fi, "subProg -> Statement\n");
                  Reduce("subProg", 1);
            }
            ;
BeforeDec   :{
                  if(symtable_size() == 0) display_stack[++display_top] = 1;
                  else display_stack[++display_top] = symtable_size();  //写display表
                  bkpchpos[++bkpchpos_top] = code_line;  //填入回填栈等待回填
                  gen(JMP, 0, 0);
            }
            ;
BeforeSTM   :{
                  if(bkpchpos_top > -1){
                        Backpatch(bkpchpos[bkpchpos_top--], code_line);
                  }
                  if(display_stack[display_top] == 1){
                        gen(INT, 0, symtable.top + 3);
                  }
                  else{
                        gen(INT, 0, symtable.top - display_stack[display_top] + 3);
                  }
                  
                  // printf(">>>>>>>>>>> int 0 %d <<<<<<<<<<\n", symtable.top - display_stack[display_top] + 3);
            }
            ;
 /*常量、变量、过程声明部分*/
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
                  $1.val = $3; 
                  fprintf(fi, "CDefine -> IDENTIFIER = CONSTANT\n");
                  if(if_declared($1.str) == 0){ //常量没有被定义,则可以入栈
                        // printf("push: %s (const val: %d)\n", $1.str, $1.val);
                        symtable_push($1.str, 1, $1.val);
                  }
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
                  if(if_declared($3.str) == 0){ //变量没有被定义,则可以入栈
                        // printf("push: %s (var val: %d)\n", $3.str, -1);
                        symtable_push($3.str, 2, -1);
                  }
                  Reduce("IdentiObj", 3);
            }
            |IDENTIFIER {
                  fprintf(fi, "IdentiObj -> IDENTIFIER\n");
                  if(if_declared($1.str) == 0){ //变量没有被定义,则可以入栈
                        // printf("push: %s (var val: %d)\n", $1.str, -1);
                        symtable_push($1.str, 2, -1);
                  }
                  Reduce("IdentiObj", 1);
            }
            ;
ProceDec    :ProceHead subProg SEMI {
                  fprintf(fi, "ProceDec -> ProceHead subProg;\n");
                  gen(OPR, 0, 0);
                  now_Level --;  //当前层数-1
                  symtable_pop();
                  addr = 2 + symtable_size();  //addr置为过程定义前的位置
                  Reduce("ProceDec", 3);
            }
            |ProceDec ProceHead subProg SEMI {
                  fprintf(fi, "ProceDec -> ProceDec ProceHead subProg;\n");
                  gen(OPR, 0, 0);
                  now_Level --;  //当前层数-1
                  symtable_pop();
                  addr = 2 + symtable_size();  //addr置为过程定义前的位置
                  Reduce("ProceDec", 4);
            }
            // | {fprintf(fp, "ProceDec -> ε\n");}
            ;
ProceHead   :PROCEDURE IDENTIFIER SEMI  {
                  fprintf(fi, "ProceHead -> PROCEDURE IDENTIFIER;\n");
                  addr = 3;
                  if(if_declared($2.str) == 0){ //过程名没有被定义,则可以入栈
                        if(findpro($2.str) == -1){
                              // printf("push: %s (procedure)\n", $2.str);
                              symtable_push($2.str, 3, -2);  //入符号表栈
                        }
                        else{
                              printf("ProceHead error! Procedure '%s' has been declared!\n", $2.str);
                              exit(1);
                        }
                  }
                  now_Level ++;  //当前层数+1
                  // printf("display_top: %d, symtable_size: %d\n", display_stack[display_top], symtable_size());
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
                  if(find_sign($1.str) == -1){ //变量没有被定义
                        printf("AssignStm error: '%s' has not been declared!\n", $1.str);
                        exit(1);
                  }
                  int temp = find_sign($1.str);
                  if(temp == -1){
                        printf("AssignStm: Cannot find the IDENTIFIER '%s'!\n", $1.str);
                  }
                  else{
                        symtable.index[temp].val = $3;
                  }
                  gen(STO, now_Level - symtable.index[temp].level, symtable.index[temp].addr);
                  fprintf(fi, "AssignStm -> IDENTIFIER := Expr\n");
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
CondStm     :IF Condition BeforeThen THEN Statement %prec LOWER_THAN_ELSE {
                  Backpatch(bkpchpos[bkpchpos_top--], code_line);
                  fprintf(fi, "CondStm -> IF Condition THEN Statement\n");
                  Reduce("CondStm", 4);
            }
            |IF Condition BeforeThen THEN Statement ELSE BeforeElseDo Statement{
                  Backpatch(bkpchpos[bkpchpos_top--], code_line);
                  fprintf(fi, "Statement -> IF Condition THEN Statement ELSE Statement\n");
                  Reduce("CondStm", 6);
            }
            ;
BeforeThen  :{
                  bkpchpos[++bkpchpos_top] = code_line;  //填入回填栈等待回填
                  gen(JPC, 0, 0);
            }
            ;
BeforeElseDo:{
                  Backpatch(bkpchpos[bkpchpos_top--], code_line+1);  //回填条件错误跳转的地址
                  bkpchpos[++bkpchpos_top] = code_line;  //填入回填栈等待回填
                  gen(JMP, 0, 0);
            }
            ;
Condition   :Expr RELOP Expr {
                  if(strcmp($2.str, "=") == 0) gen(OPR, 0, 8);
                  if(strcmp($2.str, "#") == 0) gen(OPR, 0, 9);
                  if(strcmp($2.str, "<") == 0) gen(OPR, 0, 10);
                  if(strcmp($2.str, ">=") == 0) gen(OPR, 0, 11);
                  if(strcmp($2.str, ">") == 0) gen(OPR, 0, 12);
                  if(strcmp($2.str, "<=") == 0) gen(OPR, 0, 13);

                  fprintf(fi, "Condition -> Expr RELOP Expr\n");
                  Reduce("Condition", 3);
            }
            |ODD Expr {
                  gen(OPR, 0, 6);
                  fprintf(fi, "Condition -> ODD Expr\n");
                  Reduce("Condition", 2);
            }
            ;
Expr        :Expr PLUS Term {
                  $$ = $1 + $3;
                  gen(OPR, 0, 2);
                  fprintf(fi, "Expr -> Expr + Term\n");
                  Reduce("Expr", 3);
            }
            |Expr MINUS Term {
                  $$ = $1 - $3;
                  gen(OPR, 0, 3);
                  fprintf(fi, "Expr -> Expr - Term\n");
                  Reduce("Expr", 3);
            }
            |PLUS Term {
                  $$ = $2;
                  fprintf(fi, "Expr -> +Term\n");
                  Reduce("Expr", 2);
            }
            |MINUS Term {
                  $$ = -$2;
                  gen(OPR, 0, 1);
                  fprintf(fi, "Expr -> -Term\n");
                  Reduce("Expr", 2);
            }
            |Term {
                  $$ = $1;
                  fprintf(fi, "Expr -> Term\n");
                  Reduce("Expr", 1);
            }
            ;
Term        :Term TIMES Factor {
                  $$ = $1 * $3;
                  gen(OPR, 0, 4);
                  fprintf(fi, "Term -> Term * Factor\n");
                  Reduce("Term", 3);
            }
            |Term DIVIDE Factor {
                  $$ = $1 / $3;
                  gen(OPR, 0, 5);
                  fprintf(fi, "Term -> Term / Factor\n");
                  Reduce("Term", 3);
            }
            |Factor {
                  $$ = $1;
                  fprintf(fi, "Term -> Factor\n");
                  Reduce("Term", 1);
            }
            ;
Factor      :IDENTIFIER {
                  if(find_sign($1.str) == -1){ //变量没有被定义
                        printf("Factor error: '%s' has not been declared!\n", $1.str);
                        exit(1);
                  }
                  if(symtable.index[find_sign($1.str)].kind == 1){  //如果是常量
                        $$ = symtable.index[find_sign($1.str)].val;
                        gen(LIT, 0, symtable.index[find_sign($1.str)].val);
                  }
                  if(symtable.index[find_sign($1.str)].kind == 2){  //如果是变量
                        $$ = symtable.index[find_sign($1.str)].val;
                        gen(LOD, now_Level - symtable.index[find_sign($1.str)].level, symtable.index[find_sign($1.str)].addr);
                  }
                  fprintf(fi, "Factor -> IDENTIFIER\n");
                  Reduce("Factor", 1);
            }
            |CONSTANT {
                  $$ = $1;
                  gen(LIT, 0, $1);
                  fprintf(fi, "Factor -> CONSTANT\n");                
                  Reduce("Factor", 1);
            }
            |LPAREN Expr RPAREN {
                  $$ = $2; fprintf(fi, "Factor -> (Expr)\n");
                  Reduce("Factor", 3);
            }
            ;
WhilelpStm  :WHILE BeforeCond Condition DO BeforeCondDo Statement {
                  gen(JMP, 0, whilepos[whiletop--]);
                  Backpatch(bkpchpos[bkpchpos_top--], code_line);
                  fprintf(fi, "WhilelpStm -> WHILE Condition DO Statement\n");
                  Reduce("WhilelpStm", 4);
            }
            ;
BeforeCond  :{
                  whilepos[++whiletop] = code_line;
            }
            ;
BeforeCondDo:{
                  bkpchpos[++bkpchpos_top] = code_line;  //填入回填栈等待回填
                  gen(JPC, 0, 0);                 
            }
            ;
CaseStm     :CaseHead CaseBody ENDCASE {
                  // Backpatch(bkpchpos[bkpchpos_top--], code_line);
                  code_line --;  //回撤最后一次LOD指令
                  fprintf(fi, "CaseStm -> CaseHead CaseBody ENDCASE\n");
                  Reduce("CaseStm", 3);
            }
            ;
CaseHead    :CASE IDENTIFIER COLON {
                  if(find_sign($2.str) == -1){ //变量没有被定义
                        printf("CaseHead error: '%s' has not been declared!\n", $2.str);
                        exit(1);
                  }
                  caseid = strdup($2.str);
                  gen(LOD, now_Level - symtable.index[find_sign($2.str)].level, symtable.index[find_sign($2.str)].addr);
                  fprintf(fi, "CaseHead -> CASE IDENTIFIER COLON\n");
                  Reduce("CaseHead", 3);
            }
            ;
CaseBody    :CaseBody AfterConst COLON Statemt {
                  Backpatch(bkpchpos[bkpchpos_top--], code_line);
                  gen(LOD, now_Level - symtable.index[find_sign(caseid)].level, symtable.index[find_sign(caseid)].addr);
                  fprintf(fi, "CaseBody -> CaseBody CONSTANT COLON Statemt\n");
                  Reduce("CaseBody", 4);
            }
            |AfterConst COLON Statemt {
                  Backpatch(bkpchpos[bkpchpos_top--], code_line);
                  gen(LOD, now_Level - symtable.index[find_sign(caseid)].level, symtable.index[find_sign(caseid)].addr);
                  fprintf(fi, "CaseBody -> CONSTANT COLON Statemt\n");
                  Reduce("CaseBody", 3);
            }
            ;
AfterConst  :CONSTANT {
                  gen(LIT, 0, $1);
                  gen(OPR, 0, 8);
                  bkpchpos[++bkpchpos_top] = code_line;  //填入回填栈等待回填
                  gen(JPC, 0, 0);
            }
            ;
CallStm     :CALL IDENTIFIER {
                  if(findpro($2.str) == -1){
                        printf("Procedure '%s' not found!\n", $2.str);
                        exit(1);
                  }
                  else{
                        gen(CAL, now_Level - prostack[findpro($2.str)].l, prostack[findpro($2.str)].pos - 1);
                  }
                  fprintf(fi, "CallStm -> CALL IDENTIFIER\n");
                  Reduce("CallStm", 2);
            }
            ;
ReadStm     :READ LPAREN IDENTIFIER RPAREN {
                  if(find_sign($3.str) == -1){ //变量没有被定义
                        printf("ReadStm error: '%s' has not been declared!\n", $3.str);
                        exit(1);
                  }
                  gen(OPR, 0, 16);
                  gen(STO, now_Level - symtable.index[find_sign($3.str)].level, symtable.index[find_sign($3.str)].addr);
                  fprintf(fi, "ReadStm -> READ(IdentiObj)\n");
                  Reduce("ReadStm", 4);
            }
            ;
WriteStm    :WRITE LPAREN ExprObj RPAREN {
                  gen(OPR, 0, 14);
                  gen(OPR, 0, 15);
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
      fi = fopen("E:/.../.../Compiling Principle/Lab3/SynOutput.txt", "w+");
      fh = fopen("E:/.../.../Compiling Principle/Lab3/hierarchy.txt", "w+");
      fp = fopen("E:/.../.../Compiling Principle/Lab3/pcode.txt", "w+");
      stack_init();
      symtable_init();
      init();

      yyparse();

      // printf("top: name: %s, kind: %d, val: %d, level: %d, previous: %d, now_Level: %d\n", symtable_top().name, symtable_top().kind, symtable_top().val, symtable_top().level, symtable_top().previous, now_Level);
      
      OutputCode();

      return 1;
}

void init(){
      display_top ++;
      display_stack[display_top] = 1;
      
      // bkpchpos[++bkpchpos_top] = code_line;  //填入回填栈等待回填
      // gen(JMP, 0, 0);
      
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
      // printf("**%s**\n", temp);
      Node* tnode = (Node*)malloc(sizeof(Node));
      // tnode -> data = temp;
      strcpy(tnode -> data, temp);
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
      // n -> data = name;
      strcpy(n -> data, name);
      n -> left = NULL;
      n -> right = NULL;
      left_insert(n, t[num-1]);
      for (int i = num-1; i > 0; i--){
            right_insert(t[i], t[i-1]);
      }
      stack_push(n);
}


/**********Lab3 Part**********/

void symtable_init(){
    symtable.top = 0;
}

void symtable_pop(){    //当前层所有符号出栈, display栈顶出栈
    int offset = display_stack[display_top] - 1;
    if(symtable.top == -1){
        printf("Overflow symtable pop size.\n");
        exit(1);
    }
    int i, j;
    for(i = symtable.top; i > offset; i--){
      symtable.index[symtable.top].name = NULL;
      symtable.index[symtable.top].kind = -1;
      symtable.index[symtable.top].level = -1;
      symtable.index[symtable.top].previous = -1;     
    }
    symtable.top = offset;
    symtable.index[symtable.top].previous = 0;
      //symtable.index[symtable.top].kind = 0;
      display_stack[display_top] = 0;  //display栈顶出栈
      display_top--;
    // return symtable.index[symtable.top --];
}


void symtable_push(char *id_name, int k, int v){ //标识符名字、类型、值
      int preoffset = symtable.top; //前一个符号在符号表中的位置
      symtable.top ++;
      symtable.index[symtable.top].name = id_name;
      symtable.index[symtable.top].kind = k;
      symtable.index[symtable.top].val = v;
      symtable.index[symtable.top].level = now_Level;
      symtable.index[symtable.top].previous = 0;
      if(k < 3){  //当前为变量或常量
            if(symtable.top > 0){
                  symtable.index[preoffset].previous = symtable.top;
            }
            if(k == 2){
                  symtable.index[symtable.top].addr = addr ++;
            }
      }
      if(k == 3){  //当前为过程, 写入过程栈, 记录该过程开始的code_line
            prostktop ++;
            prostack[prostktop].proname = strdup(id_name);
            prostack[prostktop].pos = code_line + 1;
            prostack[prostktop].l = now_Level;
      }
      // printf("------in push: %s, now_Level: %d, last previous: %d, addr: %d\n", symtable.index[symtable.top].name, now_Level, symtable.index[preoffset].previous, symtable.index[symtable.top].addr);
      // symtable.index[++symtable.top] = s;
}


int if_declared(char *sign_name){   //标识符是否被定义过
      int nowtable = display_stack[display_top];
      // printf("nowtable: %d  symtable.top: %d\n", nowtable, symtable.top);
      while(nowtable <= symtable.top){
            //变量名和过程名不能重名
            if(strcmp(symtable.index[nowtable].name, sign_name) == 0){
                  printf("Error! '%s' has been declared!\n", sign_name);
                  exit(1);
            }
            if(symtable.index[nowtable].previous == 0){
                  break;
            }
            nowtable ++;
      }
      return 0;
}


int find_sign(char *sign_name){  //查找标识符在符号栈中的位置
      int nowdistop = display_top;  //当前寻找的display顶
      int symbolpos;  //去符号栈中找的位置
      while(nowdistop > 0){  //display没有找完
            symbolpos = display_stack[nowdistop];
            while(symbolpos <= symtable.top){
                  if(strcmp(sign_name, symtable.index[symbolpos].name) == 0 && symtable.index[symbolpos].kind < 3){  //符号栈中此位置的变量和查找变量相同
                        return symbolpos;  //返回该符号位置
                  }
                  if(symtable.index[symbolpos].previous == 0){  //查找到当前过程底部
                        break;
                  }
                  symbolpos ++;
            }
            nowdistop --;  //查找上一层
      }
      return -1;  //没找到该符号
}

int findpro(char *pname){
      int i;
      for(i = 0; i <= prostktop; i++){
            if(strcmp(pname, prostack[i].proname) == 0){
                  return i;
            }
      }
      return -1;
}

// int symtable_empty(){
//    return symtable.top == -1;
// }

int symtable_size(){
    return symtable.top;
}

symbol symtable_top(){
      return symtable.index[symtable.top];
}


void gen(enum f f, int l, int a){  //生成类pcode代码放到code结构体数组中
    code[code_line].f = f;
    code[code_line].l = l;
    code[code_line].a = a;
    code_line ++;
}

void Backpatch(int p, int l){  //回填函数, 参数为回填位置和回填内容
      // printf("//////////// backpatch: %d %d\n", p, l);
      code[p].a = l;  //将第p条code的a域改为l
}


void OutputCode(){
      int i;
      for(i = 0; i < code_line; i++){
            fprintf(fp, "%s %d %d\n", fname[code[i].f], code[i].l, code[i].a);
      }
}

/**********Lab3 Part**********/

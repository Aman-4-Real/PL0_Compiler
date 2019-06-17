# PL0_Compiler
编译原理实验  C语言实现的pl0编译器  flex&amp;bison

## 实验构成及说明
### 1.词法部分 2.语法部分 3.语义部分
每个部分分别对应文件夹Lab1,2,3

每个部分的实验依赖于上一个部分，层层递进，各个实验需求的输入输出不太一样，详情可以参照各实验报告。如果需要了解整个过程建议先看看最下面的参考资料，或者先看看Lab3里面的实验报告。

整个pl0编译器支持If, then, else, while, do, read, write, call, begin, end, const, var, procedure, odd以及拓展的case和endcase共16个关键字，支持最多14位变量和常量，暂时仅限正整数（负数和浮点数在词法.l文件中有定义但语法语义部分未使用），过程和变量不能同名，过程和循环均支持嵌套，case不支持嵌套。

#### 实验环境: WINDOWS & cmd + gcc
#### 实现语言: C
#### 实验工具: flex & bison

### 1.词法部分
说明一下各个文件: 

.pl0文件(测试pl0代码，用于最后实现后测试，下同)

test.l文件(词法部分主要文件，包含各识别规则，后更名为Word.l，下同)

steps.txt(最初用来记录实验步骤的，实验报告里面也有)

Output.txt(词法输出文件，输出识别的符号，类型和所在行列数，后更名为WordOutput.txt，下同)

flex.exe(flex工具文件，下同)

lex.yy.c&lex.yy.exe(不做解释。。不知道的话去看相关资料和博客，下同)

词法分析器实验报告(←看字！)


### 2.语法部分
说明一下各个文件: 

Syntax.y(语法部分主要文件，包含各文法即产生式，EBNF范式见Lab3实验报告，下同)

SynOutput.txt&hierarchy.txt(按规约顺序输出的产生式和语法层次结构，下同)

Syntax.tab.c&Syntax.tab.exe(bison Syntax.y生成的c代码及其编译后的exe，下同)

Syntax.tab.h(bison -d Syntax.y生成的头文件，Word.l中有引用)

Syntax.output(bison -v Syntax.y生成的output文件，用来debug解决移进规约冲突)

test.y系列文件(.y样例文件，小型计算器的语法实现)

bison.exe&其他文件或文件夹(bison工具文件，下同)

语法分析器实验报告(←看字！)


### 3.语义部分
说明一下各个文件: 

out.exe(联合编译Syntax.tab.c和lex.yy.c后生成的可执行文件)

pcode.txt(存放.y程序输出类pcode代码的文本文件)

pcode_test.txt(test.pl0的类pcode代码)

interprete.c(解释程序，读取pcode.txt中的类pcode代码并运行，用于测试功能是否正常)

PL0编译器实验报告(←看字！三个部分的实验报告汇总)


### Attention !!!
1. 在cmd中运行方式参考Lab3实验报告，如'out.exe < max.pl0'。

2. 在.l、.y和interprete.c中修改输出路径方可正常运行。

3. 再次提醒语法和语义部分需要在编译Syntax.tab.c前在其中/* Shift the lookahead token. */的注释下面添加一行 'Process(key);'。

4. 都看到这了，点个star再走呗。


## 参考资料：
1. pl0语言简介 https://wenku.baidu.com/view/5c16572a4b73f242336c5f68.html
2. lex(flex)&yacc(bison) https://blog.csdn.net/banana_baba/article/details/51526608
3. YACC（BISON）使用指南 https://blog.csdn.net/wp1603710463/article/details/50365640
4. pl0编译程序的实现 https://wenku.baidu.com/view/6a5ea41d2f3f5727a5e9856a561252d380eb20eb.html


<-----实验纯手写，如有错误烦请指正，欢迎建议和疑问，联系cq350073050@163.com----->

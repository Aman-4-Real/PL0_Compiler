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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct{
    enum f{LIT, LOD, STO, CAL, INT, JMP, JPC, OPR} f;
    int l;
    int a;
}instruction; 

#define STACKSIZE 5000
instruction code[STACKSIZE];
char *fname[]={"LIT","LOD","STO","CAL","INT","JMP","JPC","OPR"};


int base(int level, int *s, int b){
    int tempb = b;
    while(level > 0){
        tempb = s[tempb];
        level --;
    }
    return tempb;
}
void interpret() 
{
    int p, b, t;
    instruction i;  //instruction （指令）的类型定义（包括三个域f,l,a），请自行加入到头文件中，供其他文件共享
    int s[STACKSIZE];//stacksize：数据栈大小，需自己定义

    printf("start pl0\n");
    t=0; b=1;  //t：数据栈顶指针；b：基地址；
    p=0;	// 指令指针
    s[1]=0; s[2]=0; s[3]=0;
    do {
	
        i=code[p++];//code为指令存放数组，其定义请自行加入到头文件中，供其他文件共享
        switch (i.f) 
        {
        case LIT: 
            t=t+1;
            s[t]=i.a;
            break;
        case OPR: 
            switch(i.a) 
            {
                case 0:
                    t=b-1;
                    p=s[t+3];
                    b=s[t+2];
                    break;
                case 1: 
                    s[t]=-s[t];
                    break;
                case 2: 
                    t=t-1;
                    s[t]=s[t] + s[t+1];
                    break;
                case 3:
                    t=t-1;
                    s[t]=s[t] - s[t+1];
                    break;
                case 4: 
                    t=t-1;
                    s[t]=s[t] * s[t+1];
                    break;
                case 5: 
                    t=t-1;
                    s[t]=s[t] / s[t+1];
                    break;
                case 6: 
                    s[t]=(s[t] % 2 == 1);
                    break;
                case 8: 
                    t=t-1;
					
                    s[t]=(s[t] == s[t+1]);
                    break;
                case 9:
                    t=t-1;
                    s[t]=(s[t] != s[t+1]);
                    break;
                case 10:
                    t=t-1;
                    s[t]=(s[t]<s[t+1]);
                    break;
                case 11: 
                    t=t-1;
                    s[t]=(s[t]>=s[t+1]);
                    break;
                case 12: 
                    t=t-1;
                    s[t]=(s[t]>s[t+1]);
                    break;
                case 13: 
                    t=t-1;
                    s[t]=(s[t]<=s[t+1]);
                    break;
                case 14: 
                    printf(" %d", s[t]);
                    t=t-1;
                    break;
                case 15: 
                    printf("\n");
                    break;
                case 16: 
                    t=t+1;
                    printf(" ? ");
                    scanf("%d", &s[t]);
                    break;
            }
		    break;
        case LOD: 
            t=t+1;
            s[t]=s[base(i.l, s, b)+i.a];
            break;
        case STO: 
            s[base(i.l, s, b)+i.a]=s[t];
            t=t-1;
            break;
        case CAL:
            s[t+1]=base(i.l, s, b);
            s[t+2]=b;
            s[t+3]=p;
            b=t+1;
            p=i.a;
            break;
        case INT: 
            t=t+i.a;
            break;
        case JMP: 
            p=i.a;
            break;
        case JPC: 
            if (s[t]==0) 
            {
                p=i.a;
            }
            t=t-1;
            break;
        }
    }while (p!=0);
}


int main(){
    char readtemp[1000][50];
    int i=0, j=0;
    FILE* fp;
    if((fp=fopen("pcode.txt","r"))==0){
        printf("无文件!!\n");
        return -1;
    }
    while(!feof(fp)){
        fscanf(fp, "%s", readtemp[j]); 
//        printf("%d----------%s--------\n", i, a[i]);
		j++;
    }
//    printf("%d", j); 
    int p = 0;
    for(i=0;i<j;i++){
    	p = i / 3;
    	if(i%3 == 0){
    		if(!stricmp(readtemp[i], "lit")){
				code[p].f = LIT;
			}
			if(!stricmp(readtemp[i], "lod")){
				code[p].f = LOD;
			}
			if(!stricmp(readtemp[i], "sto")){
				code[p].f = STO;
			}
			if(!stricmp(readtemp[i], "cal")){
				code[p].f = CAL;
			}
			if(!stricmp(readtemp[i], "int")){
				code[p].f = INT;
			}
			if(!stricmp(readtemp[i], "jmp")){
				code[p].f = JMP;
			}
			if(!stricmp(readtemp[i], "jpc")){
				code[p].f = JPC;
			}
			if(!stricmp(readtemp[i], "opr")){
				code[p].f = OPR;
			}
		}
    	else if(i%3 == 1){
    		code[p].l = atoi(readtemp[i]);
		}
		else if(i%3 == 2){
    		code[p].a = atoi(readtemp[i]);
		}
	}
//    printf("////%s////\n", a[2]);
//	int j = 0;
//	for(j = 0; j < 25;j++){
//		printf("%s %d %d\n", fname[code[j].f], code[j].l, code[j].a);
//	}
    fclose(fp);
//    int k;
//    for(k = 0; k < j/3; k++){
//    	printf("%s %d %d\n", fname[code[k].f], code[k].l, code[k].a);
//	}
    interpret();
    
    return 0;
}

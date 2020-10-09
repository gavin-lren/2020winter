#include<stdio.h>
#include<string.h>
#include<ctype.h>

int outnum=0;//输出数组下标 
int tokennum=0;//token数组下标 
int num=0;//数字大小 
char token[1000];//单词字符串 
char now;//当前字符 
char out[16][20]={
	"Begin", "End", "For", "If", "Then",//0-4 
	"Else", "Ident", "Int", "Colon", "Plus",//5-9
	"Star", "Comma", "LParenthesis", "RParenthesis", "Assign",//10-14
	"Unknown",//15
};//输出内容数组 

void output(){
	if(outnum == -1){
		return;
	}
	printf("%s", out[outnum]);
	if(outnum == 6){
		printf("(%s)", token);
	}
	if(outnum == 7){
		printf("(%d)", num);
	}
	printf("\n");
}

void process(FILE *fp){
	num=0;
	tokennum=0;
	token[tokennum]='\0';
	while((now == ' ')||(now == '\n')||(now == '\t')){
		now = fgetc(fp);
	}
	if(isalpha(now)){
		while(isalpha(now) || isdigit(now)){
			token[tokennum++] = now;
			token[tokennum] = '\0';
			now = fgetc(fp);
		}
		fseek(fp, -1, SEEK_CUR);
		if(strcmp("BEGIN", token) == 0){
			outnum = 0;
		}
		else if(strcmp("END", token) == 0){
			outnum = 1;	
		}
		else if(strcmp("FOR", token) == 0){
			outnum = 2;
		}
		else if(strcmp("IF", token) == 0){
			outnum = 3;
		}
		else if(strcmp("THEN", token) == 0){
			outnum = 4;
		}
		else if(strcmp("ELSE", token) == 0){
			outnum = 5;
		}
		else outnum = 6;
	}
	else if(isdigit(now)){
		while(isdigit(now)){
			token[tokennum++] = now;
			token[tokennum] = '\0';
			now = fgetc(fp);
		}
		fseek(fp, -1, SEEK_CUR);
		int i;
		for(i = 0;i < tokennum; i++){
			num = num * 10 + (token[i] - '0');
		}
		outnum = 7;
	}
	else if(now == ':'){ 
		now = fgetc(fp);
		if(now == '='){
			outnum = 14;	
		}
		else{
			fseek(fp, -1, SEEK_CUR);
			outnum = 8;
		}
	}
	else if(now == '+'){
		outnum = 9;
	}
	else if(now == '*'){
		outnum = 10;
	}
	else if(now == ','){
		outnum = 11;
	}
	else if(now == '('){
		outnum = 12;
	}
	else if(now == ')'){
		outnum = 13;
	}
	else if(now == EOF){
		outnum = -1;
	}
	else outnum = 15;
}
int main(int argc,char *argv[]){
	FILE *fp = NULL;
	fp = fopen(argv[1] , "r");//读入文件 
	if(fp == NULL){
		return 0;
	}
	while(outnum !=15 && outnum !=-1){
		now = fgetc(fp);
		process(fp);
		output();
	}
	fclose(fp);
	return 0;
} 

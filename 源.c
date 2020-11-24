#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

char key[] = {'@', '+','*','(',')','$','E','T','F' };
char* table[][9] = {
	"s5","","","s4","","","1","2","3",
	"","s6","","","","acc","","","",
	"","r2","s7","","r2","r2","","","",
	"","r4","r4","","r4","r4","","","",
	"s5","","","s4","","","8","2","3",
	"","r6","r6","","r6","r6","","","",
	"s5","","","s4","","","","9","3",
	"s5","","","s4","","","","","10",
	"","s6","","","s11","","","","",
	"","r1","s7","","r1","r1","","","",
	"","r3","r3","","r3","r3","","","",
	"","r5","r5","","r5","r5","","",""
};
char stack[20] = "0";
int top = 1;
int is_id = 0;
int flag = 1;

int look(char c) {
	int i = 0;
	for (i = 0; i < 9; i++)
		if (key[i]==c)
			return i;
}

int main() {
	FILE* fp = NULL;
	char ch;
	int len = 0;
	char temp[20] = "";
	fp=fopen("F:\\Visual Studio 练习\\CC++\\练习\\编译原理实验\\code.txt", "r");
	if (!fp) {
		printf_s("文件打开失败。");
		return 0;
	}
	while (fread(&ch, sizeof(char), 1, fp)) {
		if (ch != '+' && ch != '*' && ch != '(' && ch != ')' && ch != '$') {
			temp[len++] = ch;
			is_id = 1;
		}
		else {
			//char c = stack[top - 1];
			//int row = c - '0';
			//char* express = table[row][0];//0 @
			//stack[top++] = '@';
			//stack[top++] = express[1];
			char c;
			int row;
			char* express;
			if (is_id) {
				c = stack[top - 1];
				row = c - '0';
				express = table[row][0];
				stack[top++] = '@';
				stack[top++] = express[1];
				is_id = 0;
			}
			while (1) {
				int col = look(ch);
				c = stack[top-1];
				row = c - '0';
				if (stack[top - 2] >= '0' && stack[top - 2] <= '9')
					row += (stack[top - 2] - '0') * 10;
				express = table[row][col];
				if (express == "") {
					printf("失败。");
					return 0;
				}
				if (express[0] == 'r') {
					if (express[1] == '1') {
						top -= 6;
						stack[top++] = 'E';
						stack[top++] = table[stack[top - 2] - '0'][look('E')][0];
					}
					else if (express[1] == '2') {
						top -= 2;
						stack[top++] = 'E';
						stack[top++] = table[stack[top - 2] - '0'][look('E')][0];
					}
					else if (express[1] =='3') {
						top -= 6;
						if (row >= 10)
							top--;
						stack[top++] = 'T';
						stack[top++] = table[stack[top - 2] - '0'][look('T')][0];
					}
					else if (express[1] == '4') {
						top -= 2;
						stack[top++] = 'T';
						stack[top++] = table[stack[top - 2] - '0'][look('T')][0];
					}
					else if (express[1] == '5') {
						top -= 6;
						if (row >= 10)
							top--;
						stack[top++] = 'F';
						stack[top++] = table[stack[top - 2] - '0'][look('F')][0];
					}
					else if (express[1] == '6') {
						top -= 2;
						stack[top++] = 'F';
						stack[top++] = table[stack[top - 2] - '0'][look('F')][0];
						if (stack[top - 3] - '0' == 7)
							stack[top++] = table[7][look('F')][1];
					}
				}
				else if (express[0] == 'a') {
					printf("接受\n");
					flag = 0;
					break;
				}
				else if (express[0] == 's') {
					stack[top++] = ch;
					stack[top++] = express[1];
					if (strlen(express) == 3)
						stack[top++] = express[2];
					break;
				}
			}
		}
		//printf("%c", ch);
	}
	if(flag==1) printf("失败。");
	return 0;
}
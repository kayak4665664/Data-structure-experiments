#include<stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Charlist
{
	char c;
	int w;
} Charlist;

typedef struct HTNode
{
	char character;
	int weiget;
	int parent, lchild, rchild;
	int flag;
} HTNode, * HuffmanTree;

int m, n, i, j, k = 0, mark, start, select[2];
char letter, character, file_name[20], cd[128], HC[256][128];
int print_tree[2000][2000];
FILE* fp, * fp1;
Charlist LIST[256];
HuffmanTree HT;

void Initial();
void Initial_Huffmantree();
void Select_Huffmantree(int range);
void Store_Huffmantree();
void Code();
int Search_Character(char character);
void Decode();
void Print_Codefile();
void Print_Huffmantree();
void Print_menu();
void Source_Code();

int main()
{
	printf("Please initialize!\n\n");
	Initial();
	Print_menu();
	while ((letter = getchar()) != 'E')
	{
		getchar();
		printf("\n\n");
		if (letter == 'I')
		{
			Initial();
			Print_menu();
		}
		else if (letter == 'C')
		{
			Code();
			Print_menu();
		}
		else if (letter == 'D')
		{
			Decode();
			Print_menu();
		}
		else if (letter == 'P')
		{
			Print_Codefile();
			Print_menu();
		}
		else if (letter == 'T')
		{
			Print_Huffmantree();
			Print_menu();
		}
		else if (letter == 'S')
		{
			Source_Code();
			Print_menu();
		}
		else
		{
			printf("Error! Please re-enter the correct instructions!\n\n");
			Print_menu();
		}
	}
	printf("\n\nGoodbye!\n");
	return 0;
}

void Initial()
{
	printf("Please enter the character set size:\n");
	scanf("%d", &n);
	printf("\nPlease enter characters and weights:\n");
	for (i = 1; i <= n; i++)
	{
		scanf("%*c%c%d", &LIST[i].c, &LIST[i].w);
	}
	getchar();
	Initial_Huffmantree();
	Store_Huffmantree();
}

void Initial_Huffmantree()
{
	if (n <= 1)
		return;
	m = 2 * n - 1;
	HT = (HuffmanTree*)malloc((m + 1) * sizeof(HTNode));
	for (i = 1; i <= m; i++)
	{
		HT[i].character = LIST[i].c;
		HT[i].weiget = LIST[i].w;
		HT[i].flag = HT[i].parent = HT[i].lchild = HT[i].rchild = 0;
	}
	for (i = n + 1; i <= m; i++)
	{
		HT[i].flag = 0;
		Select_Huffmantree(i - 1);
		HT[select[0]].parent = i;
		HT[select[1]].parent = i;
		HT[i].lchild = select[0];
		HT[i].rchild = select[1];
		HT[i].weiget = HT[select[0]].weiget + HT[select[1]].weiget;
	}
	cd[127] = '\0';
	for (i = 1; i <= n; i++)
	{
		start = 127;
		for (j = i, k = HT[i].parent; k != 0; j = k, k = HT[k].parent)
		{
			if (HT[k].lchild == j)
			{
				cd[--start] = '0';
			}
			else
			{
				cd[--start] = '1';
			}
		}
		strcpy(HC[i], &cd[start]);
	}
}

void Select_Huffmantree(int range)
{
	int min;
	for (j = 0; j < 2; j++)
	{
		for (i = 1; i <= range; i++)
		{
			if (HT[i].flag == 0)
			{
				mark = i;
				min = HT[mark].weiget;
				break;
			}
		}
		for (i = 1; i <= range; i++)
		{
			if (HT[i].flag == 0 && HT[i].weiget < min)
			{
				mark = i;
				min = HT[mark].weiget;
			}
		}
		HT[mark].flag = 1;
		select[j] = mark;
	}
}

void Store_Huffmantree()
{
	printf("\nWhich file would you like to store the Huffman tree?\n");
	scanf("%s", file_name);
	getchar();
	fp = fopen(file_name, "w");
	for (i = 1; i <= m; i++)
	{
		fprintf(fp, "%c %d %d %d %d %d", HT[i].character, HT[i].weiget, HT[i].parent, HT[i].lchild, HT[i].rchild,
			HT[i].flag);
	}
	fclose(fp);
	printf("\nComplete! The Huffman tree has been stored in %s!\n\n", file_name);
}

void Code()
{
	if (HT == NULL)
	{
		printf("Which file would you like to read into the Huffman tree?\n");
		scanf("%s", file_name);
		getchar();
		if ((fp = fopen(file_name, "r")) == NULL)
		{
			printf("Cannot open %s!\n\n", file_name);
			return;
		}
		HT = (HuffmanTree*)malloc((m + 1) * sizeof(HTNode));
		for (i = 1; i <= m; i++)
		{
			fscanf(fp, "%c%d%d%d%d%d", &HT[i].character, &HT[i].weiget, &HT[i].parent, &HT[i].lchild, &HT[i].rchild,
				&HT[i].flag);
		}
		fclose(fp);
		Initial_Huffmantree();
	}
	printf("Which file would you like to code?\n");
	scanf("%s", file_name);
	getchar();
	if ((fp = fopen(file_name, "r")) == NULL)
	{
		printf("Cannot open %s!\n\n", file_name);
		return;
	}
	printf("\nWhich file would you like to store the codes?\n");
	scanf("%s", file_name);
	getchar();
	fp1 = fopen(file_name, "w");
	while ((character = fgetc(fp)) != EOF)
	{
		mark = Search_Character(character);
		fprintf(fp1, "%s", HC[mark]);
	}
	fclose(fp);
	fclose(fp1);
	printf("\nComplete! The result has been stored in %s!\n\n", file_name);
}

int Search_Character(char character)
{
	for (i = 1; i <= n; i++)
	{
		if (HT[i].character == character)
			return i;
	}
}

void Decode()
{
	printf("Which file would you like to decode?\n");
	scanf("%s", file_name);
	getchar();
	if ((fp = fopen(file_name, "r")) == NULL)
	{
		printf("Cannot open %s!\n\n", file_name);
		return;
	}
	printf("\nWhich file would you like to store the result?\n");
	scanf("%s", file_name);
	getchar();
	fp1 = fopen(file_name, "w");
	while ((character = fgetc(fp)) != EOF)
	{
		j = m;
		while (HT[j].lchild != 0)
		{
			if (character == '0')
			{
				j = HT[j].lchild;
			}
			else
			{
				j = HT[j].rchild;
			}
			if (HT[j].lchild == 0)
			{
				break;
			}
			character = fgetc(fp);
		}
		fprintf(fp1, "%c", HT[j].character);
	}
	fclose(fp);
	fclose(fp1);
	printf("\nComplete! The result has been stored in %s!\n\n", file_name);
}

void Print_Codefile()
{
	printf("Which file of codes would you like to print?\n");
	scanf("%s", file_name);
	getchar();
	if ((fp = fopen(file_name, "r")) == NULL)
	{
		printf("\nCannot open %s!\n\n", file_name);
		return;
	}
	printf("\nWhich file would you like to store the codes?\n");
	scanf("%s", file_name);
	getchar();
	printf("\n");
	fp1 = fopen(file_name, "w");
	j = 0;
	while ((character = fgetc(fp)) != EOF)
	{
		fprintf(fp1, "%c", character);
		if (j < 50)
		{
			putchar(character);
			++j;
		}
		else
		{
			putchar('\n');
			putchar(character);
			j = 1;
		}
	}
	fclose(fp);
	fclose(fp1);
	printf("\n\nComplete! The codes have been displayed on the terminal and stored in %s!\n\n", file_name);
}

void Print_Huffmantree()
{
	printf("Which file would you like to store the Huffman tree?\n");
	scanf("%s", file_name);
	getchar();
	fp = fopen(file_name, "w");
	memset(print_tree, 0, sizeof(print_tree));
	for (i = 0, print_tree[0][0] = m; i < m / 2; i++)
	{
		for (j = 0, k = 0, mark = 0; print_tree[i][j] != 0; j++)
		{
			if (print_tree[i][j] <= m && HT[print_tree[i][j]].lchild)
			{
				print_tree[i + 1][k++] = HT[print_tree[i][j]].lchild;
				print_tree[i + 1][k++] = HT[print_tree[i][j]].rchild;
				++mark;
			}
			else
			{
				print_tree[i + 1][k++] = m + 1;
			}
		}
		if (!mark)
		{
			mark = i;
			break;
		}
	}
	for (i = 0; i <= mark; i++)
	{
		printf("\n");
		fprintf(fp, "\n");
		for (j = 0; print_tree[i][j] != 0; j++)
		{
			if (print_tree[i][j] <= m)
			{
				if (print_tree[i][j] <= n)
				{
					printf("\"%c\"  ", HT[print_tree[i][j]].character);
					fprintf(fp, "\"%c\"  ", HT[print_tree[i][j]].character);
				}
				else
				{
					printf("N    ");
					fprintf(fp, "N    ");
				}
			}
			else
			{
				printf("O   ");
				fprintf(fp, "O    ");
			}
		}
	}
	fclose(fp);
	printf("\n\nO: The degree of it's parent is 0.\nN: It's NULL.");
	printf("\n\nComplete! The Huffman tree has been displayed on the terminal and stored in %s!\n\n", file_name);
}

void Print_menu()
{
	printf("Please enter a letter, for example:\n");
	printf("E: Exit     ");
	printf("I: Initialize     ");
	printf("C: Code     ");
	printf("D: Decode     ");
	printf("P: Print code file     ");
	printf("T: Print Huffman Tree     ");
	printf("S: Code source code&Decode source code\n\n");
}

void Source_Code()
{
	n = 128;
	for(i=1;i<=n;i++)
	{
		LIST[i].c = (char)(i-1);
		LIST[i].w = i;
	}
	Initial_Huffmantree();
	fp = fopen(file_name, "w");
	for (i = 1; i <= m; i++)
	{
		fprintf(fp, "%c %d %d %d %d %d", HT[i].character, HT[i].weiget, HT[i].parent, HT[i].lchild, HT[i].rchild,
			HT[i].flag);
	}
	fclose(fp);
	Code();
	Decode();
}

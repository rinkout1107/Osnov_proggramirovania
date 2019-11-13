#pragma warning (disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NO 0
#define YES 1
#define N 100

char *types[] = { "int\0", "char\0", "float\0", "double\0", "long\0", "unsigned\0", "signed\0"};

int main(void)
{
	FILE *f1 = NULL, *f2 = NULL;		
	char **table = NULL, *str = NULL, c;					
	int tabcnt = 0,	bktcnt = 0, len = 0, i = 0;				

	if ((f1 = fopen("file1.c", "r")) == NULL || (f2 = fopen("file2.txt", "w")) == NULL)
	{
		printf("file can`t open\n");
		system("pause");
		return 0;
	}

	do {
		c = fgetc(f1);

		if (bktcnt == 0)
		{
			if (c == '{')
				bktcnt++;
		}
		else
		{
			if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
			{
				while (c != ' ' && c != '\t' && c != '\n')
				{
					str = (char*)realloc(str, (len + 1) * sizeof(char));
					str[len++] = c;
					c = fgetc(f1);
				}
				str = (char*)realloc(str, (len + 1) * sizeof(char));
				str[len] = '\0';

				if (strcmp(types[0], str) == 0 ||
					strcmp(types[1], str) == 0 ||
					strcmp(types[2], str) == 0 ||
					strcmp(types[3], str) == 0 ||
					strcmp(types[4], str) == 0 ||
					strcmp(types[5], str) == 0 ||
					strcmp(types[6], str) == 0)
				{
					str[len++] = ' ';
					do {
						c = fgetc(f1);
						if (c != '\n' && c != EOF)
						{
							str = (char*)realloc(str, (len + 1) * sizeof(char));
							str[len++] = c;
						}
						else
						{
							str = (char*)realloc(str, (len + 2) * sizeof(char));
							str[len++] = '\n';
							str[len++] = '\0';
						}
					} while (c != '\n' && c != EOF);

					table = (char**)realloc(table, (tabcnt + 1) * sizeof(char*));
					table[tabcnt++] = str;
				}
				else
				{
					free(str);
				}
				str = NULL;
				len = 0;
			}
			else if (c == '}')
				bktcnt--;
		}
	} while (c != EOF);
	fclose(f1);

	for (i = 0; i < tabcnt; i++)
	{
		fputs(table[i], f2);
		free(table[i]);
	}
	free(table);
	fclose(f2);

	printf("Program successfully complete\n");
	system("pause");
	return 0;
}

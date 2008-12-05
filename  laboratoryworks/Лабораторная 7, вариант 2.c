#include <stdio.h>
//#include <conio.h>

#define STRCOUNT 2
#define MAXCHARS 513

struct
{
	char name[MAXCHARS];
	int count[STRCOUNT];
} words[256];

int wordcount=0;


/* Запрос строк */
int inputstr(char *str, int n)
{
	int i;
	
	printf("Введите строку %d:\n", n);
	for (i=0; i<MAXCHARS; i++)
	{
		str[i] = getchar();
		
		if (str[i] == '\n')
		{
			break;
		}
		
		if ( !(((int)str[i] >= (int)'a' && (int)str[i] <= (int)'z') || ((int)str[i] >= (int)'A' && (int)str[i] <= (int)'Z') || str[i] == ' ') )
		{
			printf("Недопустимый формат строки\n");
			return 0;
		}
	}
	str[i] = '\0';
	
	printf("\n");
	
	return 1;
}


/* Создание словаря */
void decomp(char *str, int n)
{
	int i, j, k, lastchar=0, notuni;
	char tempstr[MAXCHARS];
	
	words[wordcount].count[n] = 0;
	
	for (i=0; ; i++)
	{
		if (str[i] == ' ' || str[i] == '\0')
		{
			if (lastchar != i)
			{
				j = 0;
				for (; lastchar<i; lastchar++)
				{
					/* Заносим во временную строку */
					tempstr[j] = str[lastchar];
					j++;
				}
				tempstr[j] = '\0';
				
				/* Проверяем на уникальность */
				notuni = 0;
				if (wordcount != 0)
					for (k=0; k<wordcount; k++)
					{
						if (words[k].name[0] == tempstr[0])
						{
							for (j=0; words[k].name[j] != '\0' || tempstr[j] != '\0'; j++)
								if (words[k].name[j] != tempstr[j])
									break;
								if (words[k].name[j] == '\0' && tempstr[j] == '\0')
								{
									words[k].count[n]++;
									notuni = 1;
									break;
								}
						}
					}
				
				/* Если уникально - записываем */
				if (notuni == 0)
				{
					for (j=0; tempstr[j] != '\0'; j++)
						words[wordcount].name[j] = tempstr[j];
					
					words[wordcount].name[j] = '\0';
					words[wordcount].count[n]++;
					wordcount++;
					words[wordcount].count[n] = 0;
				}
			}
			lastchar = i+1;
		}
		
		if (str[i] == '\0') break;
	}
}


/* Проверка на наличие в строке 1 всех слов строки 2 */
int test1()
{
	int i;
	
	for (i=0; i<wordcount; i++)
		if (words[i].count[1] != 0 && words[i].count[0] == 0)
		{
			printf("В строке 1 содержатся не все слова из строки 2\n");
			return 0;
		}
	
	return 1;
}


/* Вывод слов строки 2, встречающихся в строке 1 2-5 раз */
void test2()
{
	int i;
	
	printf("Cлова строки 2, встречающихся в строке 1 2-5 раз:\n");
	
	for (i=0; i<wordcount; i++)
		if (words[i].count[1] != 0 && words[i].count[0] >= 2 && words[i].count[0] <= 5)
			printf("%s, ", words[i].name);
	printf("\nНажмите любую клавишу...\n");
	//getch();
}


/* Основной код */
int main()
{
	char str[MAXCHARS];
	int i, ret;

	/* Получение и обработка строк */
	for (i=0; i<STRCOUNT; i++)
	{
		ret = inputstr (str, i+1);
		if (ret == 0) return 0;
		
		decomp (str, i);
	}
	
	ret = test1();
	if (ret == 0) return 0;
	
	test2();
	
	return 0;
}

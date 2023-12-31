#include <stdio.h>
#include <stdlib.h>
void FIFO(char[], char[], int, int);
void lru(char[], char[], int, int);
void opt(char[], char[], int, int);
int main()
{
  int ch, YN = 1, i, l, f;
  char F[10], s[25];
  system("clear");
  printf("\n\n\tEnter the no of empty frames: ");
  scanf("%d", &f);
  printf("\n\n\tEnter the length of the string: ");
  scanf("%d", &l);
  printf("\n\n\tEnter the string: ");
  scanf("%s", s);
  for (i = 0; i < f; i++)
    F[i] = -1;
  do
  {
    system("clear");
    printf("\n\n\t*********** MENU ***********");
    printf("\n\n\t1:FIFO\n\n\t2:LRU\n\n\t3:OPT\n\n\t4:EXIT");
    printf("\n\n\tEnter your choice: ");
    scanf("%d", &ch);
    system("clear");
    switch (ch)
    {
    case 1:
      for (i = 0; i < f; i++)
      {
        F[i] = -1;
      }

      FIFO(s, F, l, f);
      break;
    case 2:
      for (i = 0; i < f; i++)
      {
        F[i] = -1;
      }
      lru(s, F, l, f);
      break;
    case 3:
      for (i = 0; i < f; i++)
      {
        F[i] = -1;
      }

      opt(s, F, l, f);
      break;
    case 4:
      exit(0);
    }
    printf("\n\n\tDo u want to continue IF YES PRESS 1\n\n\tIF NO PRESS 0 : ");
    scanf("%d", &YN);
  } while (YN == 1);
  return (0);
}

//FIFO
void FIFO(char s[], char F[], int l, int f)
{
  int i, j = 0, k, flag = 0, cnt = 0;
  printf("\n\tPAGE\t    FRAMES\t  FAULTS");
  for (i = 0; i < l; i++)
  {
    for (k = 0; k < f; k++)
    {
      if (F[k] == s[i])
        flag = 1;
    }

    if (flag == 0)
    {
      printf("\n\t%c\t", s[i]);
      F[j] = s[i];
      j++;

      for (k = 0; k < f; k++)
      {
        printf("   %c", F[k]);
      }
      printf("\tPage-fault%d", cnt);
      cnt++;
    }

    else
    {
      flag = 0;
      printf("\n\t%c\t", s[i]);
      for (k = 0; k < f; k++)
      {
        printf("   %c", F[k]);
      }

      printf("\tNo page-fault");
    }
    if (j == f)
      j = 0;
  }
}

//LRU
void lru(char s[], char F[], int l, int f)
{
  int i, j = 0, k, m, flag = 0, cnt = 0, top = 0;
  printf("\n\tPAGE\t    FRAMES\t  FAULTS");
  for (i = 0; i < l; i++)
  {
    for (k = 0; k < f; k++)
    {
      if (F[k] == s[i])
      {
        flag = 1;
        break;
      }
    }

    printf("\n\t%c\t", s[i]);
    if (j != f && flag != 1)
    {
      F[top] = s[i];
      j++;

      if (j != f)
        top++;
    }
    else
    {
      if (flag != 1)
      {
        for (k = 0; k < top; k++)
        {
          F[k] = F[k + 1];
        }

        F[top] = s[i];
      }
      if (flag == 1)
      {
        for (m = k; m < top; m++)
        {
          F[m] = F[m + 1];
        }

        F[top] = s[i];
      }
    }
    for (k = 0; k < f; k++)
    {
      printf("   %c", F[k]);
    }

    if (flag == 0)
    {
      printf("\tPage-fault%d", cnt);
      cnt++;
    }
    else
      printf("\tNo page fault");
    flag = 0;
  }
}

//optimal
void opt(char s[], char F[], int l, int f)
{
  int i, j = 0, k, m, flag = 0, cnt = 0, temp[10];

  printf("\n\tPAGE\t    FRAMES\t  FAULTS");
  for (i = 0; i < 10; i++)
    temp[i] = 0;

  for (i = 0; i < f; i++)
    F[i] = -1;

  for (i = 0; i < l; i++)
  {
    for (k = 0; k < f; k++)
    {
      if (F[k] == s[i])
        flag = 1;
    }

    if (j != f && flag == 0)
    {
      F[j] = s[i];
      j++;
    }

    else if (flag == 0)
    {
      for (m = 0; m < f; m++)
      {
        for (k = i + 1; k < l; k++)
        {
          if (F[m] != s[k])
          {
            temp[m] = temp[m] + 1;
          }
          else
            break;
        }
      }
      m = 0;
      for (k = 0; k < f; k++)
      {
        if (temp[k] > temp[m])
        {
          m = k;
        }
      }

      F[m] = s[i];
    }

    printf("\n\t%c\t", s[i]);
    for (k = 0; k < f; k++)
    {
      printf("  %c", F[k]);
    }
    if (flag == 0)
    {
      printf("\tPage-fault %d", cnt);
      cnt++;
    }
    else
      printf("\tNo Page-fault");
    flag = 0;

    for (k = 0; k < 10; k++)
      temp[k] = 0;
  }
}
/* Output

pranav-27@pranav:~/te$ ./ass6

Enter the no of empty frames: 3


	Enter the length of the string: 6


	Enter the string: 130356


	*********** MENU ***********

	1:FIFO

	2:LRU

	3:OPT

	4:EXIT

	Enter your choice: 1
  PAGE	    FRAMES	  FAULTS
	1	   1   �   �	Page-fault0
	3	   1   3   �	Page-fault1
	0	   1   3   0	Page-fault2
	3	   1   3   0	No page-fault
	5	   5   3   0	Page-fault3
	6	   5   6   0	Page-fault4
Do u want to continue IF YES PRESS 1

	IF NO PRESS 0 : 1


	*********** MENU ***********

	1:FIFO

	2:LRU

	3:OPT

	4:EXIT

	Enter your choice: 2

	PAGE	    FRAMES	  FAULTS
	1	   1   �   �	Page-fault0
	3	   1   3   �	Page-fault1
	0	   1   3   0	Page-fault2
	3	   1   0   3	No page fault
	5	   0   3   5	Page-fault3
	6	   3   5   6	Page-fault4

	Do u want to continue IF YES PRESS 1

	IF NO PRESS 0 : 1

	*********** MENU ***********

	1:FIFO

	2:LRU

	3:OPT

	4:EXIT

	Enter your choice: 3


	PAGE	    FRAMES	  FAULTS
	1	  1  �  �	Page-fault 0
	3	  1  3  �	Page-fault 1
	0	  1  3  0	Page-fault 2
	3	  1  3  0	No Page-fault
	5	  5  3  0	Page-fault 3
	6	  6  3  0	Page-fault 4

	Do u want to continue IF YES PRESS 1

	IF NO PRESS 0 : 0
pranav-27@pranav:~/te$ 
*/

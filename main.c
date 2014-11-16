#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE fnCreateDB(char []);
void fnAddRecord();
void fnDispAllDB();
void fnDispDB();
void fnOpenDB(FILE *, char []);
void fnSearch();
void fnChooseDType();

int main()
{
    int iChoice,iVal;
    char DbName[25];
	FILE *fp;
	for(;;)
	{
        printf("\nApplication Operations\n");
        printf("\n1.Create new Database\n2.Display all databases\n3.Exit\n");
        scanf("%d",&iChoice);
        switch(iChoice)
        {
            case 1: printf("Enter the Database name\n");
                    scanf("%s",DbName);
                    fp=fnCreateDB(DbName);
                    fnOpenDB(fp,DbName);
                    break;
            case 2: fnDispAllDB();
                    break;
            case 3: exit(0);
            default:printf("\nInvalid Operation\n");

        }
	}

}

void fnAddRecord()
{

}

FILE fnCreateDB(char DbName[])
{
    FILE *fp;
    fp=(DbName,"w");

}


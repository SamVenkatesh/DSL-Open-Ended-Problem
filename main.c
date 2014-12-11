/**
TITLE: Application which functions as a simple database management system.
DESCRIPTION: Within the program the data is stored within a linked list and the user has the option to save the database
to a file.
BY:
Tanya-1SI13CS125
Shyam Venkatesh-1SI13CS115
Shwetabh Shekhar-1SI13CS114
**/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef union{
    int i;
    char c;
    float f;
    char str[40];
}dtype;

struct NODE{
    dtype info;
    int dt;
    struct NODE *rlink,*dlink;
};

typedef struct NODE* NODEPTR;
NODEPTR createDB(NODEPTR,char[]);
NODEPTR addField(NODEPTR,char[],int);
NODEPTR addRec(NODEPTR);
NODEPTR saveDB(NODEPTR,char[]);
NODEPTR allocNode();
void display(NODEPTR);
void releaseNode(NODEPTR);

int main()
{
    int iChoice;
    NODEPTR root;
    root=allocNode();
    root->info.i=0;
    root->rlink=NULL;
    root->dlink=NULL;
    char dbName[30],cChoice;
    for(;;)
    {
        printf("\nApplication Operations\n");
        printf("1.Create Database\n2.View Existing Databases\n3.Exit\n");
        scanf("%d",&iChoice);
        switch(iChoice)
        {
            case 1:  if(root->info.i==-1)
                     {
                        printf("\nWould you like to save this database? Any unsaved changes will be lost Y/N? ");
                        scanf("%c",&cChoice); getchar();
                        switch(cChoice)
                        {
                            case 'Y':
                            case 'y': root->info.i=0;
				      root->rlink=NULL;
			              root->dlink=NULL;
				      root=saveDB(root,dbName);
                                      break;
                            case 'N':
                            case 'n': break;
                        }
                     }
                    printf("\nEnter Database name\n");
                    scanf("%s",dbName);
                    root=createDB(root,dbName);
                    break;
            case 2: system("ls *.dat");
                    break;
            case 3: exit(0);
            default: printf("\nInvalid Operation, please try again\n");
                     break;
        }
    }
}



NODEPTR createDB(NODEPTR root,char name[])
{
    int iChoice,dt;
    char fName[20];
    root->info.i=-1;
    for(;;)
    {
        printf("\nWhat would you like to do?\n");
        printf("\n1.Add Field\n2.Add Record\n3.Display Database\n4.Save this Database\n5.Back to Main Menu\n");
        scanf("%d",&iChoice);
        switch(iChoice)
        {
            case 1: printf("Enter field name\n");
                    scanf("%s",fName);
                    printf("\nEnter datatype for elements in this field\n");
                    printf("1.Integer\n2.Floating point value\n3.Character\n4.String\n");
                    scanf("%d",&dt);
                    root=addField(root,fName,dt);
                    break;
            case 2: if(root->rlink==NULL)
                    {
                        printf("\nYou cannot add records without fields being present\n");
                        break;
                    }
                    root=addRec(root);
                    break;
            case 3: if(root->dlink==NULL)
                    {
                        printf("\nDatabase currently has no records\n");
                        break;
                    }
                    display(root);
                    break;
            case 4: if(root->rlink==NULL||root->dlink==NULL)
                    {
                        printf("\nDatabase is empty");
                        break;
                    }
                    root=saveDB(root,name);
                    break;
            case 5: return root;
        }

    }
}


NODEPTR addField(NODEPTR root,char fName[],int dt)
{
    NODEPTR cur,temp=NULL;
    temp=allocNode();
    temp->rlink=NULL;
    temp->dlink=NULL;
    strcpy(temp->info.str,fName);
    temp->dt=dt;
    if(root->rlink==NULL)
    {
        root->rlink=temp;
        return root;
    }
    for(cur=root->rlink;cur->rlink!=NULL;cur=cur->rlink);
    cur->rlink=temp;
    return root;
}

NODEPTR addRec(NODEPTR root)
{
    NODEPTR rowptr,colptr,cur,temp,prev=NULL;

    colptr=root->rlink;
    int nRows=1;
    rowptr=allocNode();
    if(root->dlink==NULL)
    {
        root->dlink=rowptr;
        rowptr->info.i=1;
    }
    else
    {
        for(cur=root->dlink;cur!=NULL;prev=cur,cur=cur->dlink,nRows++);
        rowptr->info.i=nRows;
        prev->dlink=rowptr;
    }
    rowptr->dt=1;

    for( ;colptr!=NULL;colptr=colptr->rlink)
    {
        temp=allocNode();
        temp->rlink=NULL;
        temp->dlink=NULL;
        rowptr->rlink=temp;
        colptr->dlink=temp;
        printf("\nEnter data for field %s\n",colptr->info.str);
        switch(colptr->dt)
        {
            case 1: scanf("%d",&temp->info.i);
                    break;
            case 2: scanf("%f",&temp->info.f);
                    break;
            case 3: scanf("%c",&temp->info.c);
                    break;
            case 4: scanf("%s",temp->info.str);
                    break;
        }
        temp->dt=colptr->dt;
        rowptr=temp;
    }
    return root;
}

void display(NODEPTR root)
{
    NODEPTR rowptr,colptr;

    for(colptr=root;colptr!=NULL;colptr=colptr->rlink)
    {
        if(colptr->dt==2)
             printf("%s\t\t",colptr->info.str);
        else
        printf("%s\t",colptr->info.str);
    }
    printf("\n");

    for(rowptr=root->dlink;rowptr!=NULL;rowptr=rowptr->dlink)
    {
        for(colptr=rowptr;colptr!=NULL;colptr=colptr->rlink)
        {
            switch(colptr->dt)
            {
                case 1: printf("%d\t",colptr->info.i);
                        break;
                case 2: printf("%f\t",colptr->info.f);
                        break;
                case 3: printf("%c\t",colptr->info.c);
                        break;
                case 4: {
                            printf("%s\t",colptr->info.str);
                            break;
                        }
                default: printf("\nInvalid\n");
            }
        }
        printf("\n");
    }
}

NODEPTR saveDB(NODEPTR root,char name[])
{
    root->info.i=0;
    FILE *fp;
    NODEPTR rowptr,colptr;
    strcat(name,".dat");
    fp=fopen(name,"w+");
    for(colptr=root;colptr!=NULL;colptr=colptr->rlink)
    {
        if(colptr->dt==2)
             fprintf(fp,"%s\t\t",colptr->info.str);
        else
        fprintf(fp,"%s\t",colptr->info.str);
    }
    fprintf(fp,"\n");

    for(rowptr=root->dlink;rowptr!=NULL;rowptr=rowptr->dlink)
    {
        for(colptr=rowptr;colptr!=NULL;colptr=colptr->rlink)
        {
            switch(colptr->dt)
            {
                case 1: fprintf(fp,"%d\t",colptr->info.i);
                        break;
                case 2: fprintf(fp,"%f\t",colptr->info.f);
                        break;
                case 3: fprintf(fp,"%c\t",colptr->info.c);
                        break;
                case 4: {
                            fprintf(fp,"%s\t",colptr->info.str);
                            break;
                        }
                default: printf("\nInvalid\n");
            }
        }
        fprintf(fp,"\n");
    }
    printf("\nDatabase %s has been saved\n",name);
    return root;
}

NODEPTR allocNode()
{
    NODEPTR newborn;
    newborn=(NODEPTR)malloc(sizeof(struct NODE));
    if(newborn==NULL)
    {
        printf("\nInsufficient Heap Memory\n");
        return NULL;
    }
    return newborn;
}

void releaseNode(NODEPTR x)
{
    free(x);
}


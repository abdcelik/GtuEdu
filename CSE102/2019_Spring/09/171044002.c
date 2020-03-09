#include <stdio.h>
#include <stdlib.h>

#define clear() printf("\033[H\033[J")	// clear the screen

struct person
{
	char name[15];
	char surname[15];
	char musical_work[30];
	int age;
	struct person *next;
} *top = NULL;

void menu();
void addNode(char name[], char surname[], char creation[], int age);
void deleteNode();
void Sort_Alphabetically();
void Sort_Increasingly();
void print_stack();
void free_top();
void str_cpy(char*,char*);
int str_cmp(char*,char*);
void push(struct person **head,struct person *new);
struct person *pop(struct person **head);

int main()
{
	menu();
	free_top();
	return 0;
}
void menu()
{
	char name[15],surname[15],creation[15];
	int choice=0,age;
	clear();
	while(choice != 5)
	{
		printf("**** MENU ****\n");
		printf("1 - Add a Person to the Stack\n");
		printf("2 - Pop a Person from the Stack\n");
		printf("3 - Sort Alphabetical Order\n");
		printf("4 - Sort Age in Increasing Order\n");
		printf("5 - Exit menu\n");
		printf("**************\n");
		printf("Select your choice : ");
		scanf("%d",&choice);
		clear();
		switch(choice)
		{
			case 1:
				printf("** Add a person **\n");
				printf("Name : ");
				scanf(" %[^\n]s",name);
				printf("Surname : ");
				scanf(" %[^\n]s",surname);
				printf("Creation : ");
				scanf(" %[^\n]s",creation);
				printf("Age : ");
				scanf(" %d",&age);
				addNode(name,surname,creation,age);
				print_stack();
				break;
			case 2:
				deleteNode();
				print_stack();
				break;
			case 3:
				Sort_Alphabetically();
				print_stack();
				break;
			case 4:
				Sort_Increasingly();
				print_stack();
				break;
		}
	}
}
void addNode(char name[],char surname[],char creation[],int age)
{
	struct person *temp=(struct person*)malloc(sizeof(struct person));
	struct person *iter;
	str_cpy(temp->name,name);
	str_cpy(temp->surname,surname);
	str_cpy(temp->musical_work,creation);
	temp->age=age;
	temp->next=NULL;
	if(top == NULL)
	{
		top=(struct person*)malloc(sizeof(struct person));
		top=temp;
	}
	else
	{
		iter=top;
		top=temp;
		temp->next=iter;
	}
}
void deleteNode()
{
	struct person *iter;
	if(top != NULL)
	{
		iter=top;
		top=top->next;
		free(iter);
	}
	else
		printf("There is nothing in the stack...\n");
}
void Sort_Alphabetically()
{
	struct person *temp_stack=NULL,*current,*temp,*iter;
	if(top != NULL)
	{
		while(top != NULL)
		{
			current=top;
			top=top->next;
			current->next=NULL;
			if(temp_stack == NULL || str_cmp(current->name,temp_stack->name)<0)
				push(&temp_stack,current);
			else
			{
				while(temp_stack != NULL && str_cmp(current->name,temp_stack->name)>0)
				{
					temp=pop(&temp_stack);
					iter=top;
					top=temp;
					temp->next=iter;
				}
				push(&temp_stack,current);
			}
		}
		top=temp_stack;
	}
	else
		printf("There isn't anyone to sort alphabetically...\n");
}
void Sort_Increasingly()
{
	struct person *temp_stack=NULL,*current,*temp,*iter;
	if(top != NULL)
	{
		while(top != NULL)
		{
			current=top;
			top=top->next;
			current->next=NULL;
			if(temp_stack == NULL || current->age < temp_stack->age)
				push(&temp_stack,current);
			else
			{
				while(temp_stack != NULL && current->age > temp_stack->age)
				{
					temp=pop(&temp_stack);
					iter=top;
					top=temp;
					temp->next=iter;
				}
				push(&temp_stack,current);
			}
		}
		free_top();
		top=temp_stack;
	}
	else
		printf("There isn't anyone to sort increasingly...\n");
}
void print_stack()
{
	int i;
	struct person *iter;
	iter=top;
	for(i=1;iter!=NULL;i++)
	{
		printf("--------------\n");
		printf("%d)\n%s\n",i,iter->name);
		printf("%s\n",iter->surname);
		printf("%s\n",iter->musical_work);
		printf("%d\n",iter->age);
		iter=iter->next;
	}
	printf("\n");
}
void free_top()
{
	struct person *iter;
	while(top!=NULL)
	{
		iter=top;
		top=top->next;
		free(iter);
	}
}
void push(struct person **head,struct person *new)
{
	struct person *iter;
	if(*head==NULL)
	{
		*head=(struct person*)malloc(sizeof(struct person));
		*head=new;
	}
	else
	{
		iter=*head;
		*head=new;
		new->next=iter;
	}
}
struct person *pop(struct person **head)
{
	struct person *temp;
	temp=*head;
	*head=(*head)->next;
	temp->next=NULL;
	return temp;
}
void str_cpy(char *s1,char *s2)
{
	while(*s1++=*s2++);
}
int str_cmp(char *s1,char *s2)
{
	while(*s1&&*s2&&*s1==*s2)
		s1++,s2++;
	return *s1-*s2;
}
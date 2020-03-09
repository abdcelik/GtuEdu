#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATA_NUM 20 // If you change data, you must change DATA_NUM

typedef struct stack_node
{
	int num;
	struct stack_node *next;
}stack;

typedef struct queue_node
{
	int num;
	struct queue_node *next;
}queue;

typedef struct bst_node
{
	int num;
	struct bst_node *left;
	struct bst_node *right;
}bst;

void fill_structures(stack **stack_,queue **queue_,bst **bst_,int data[]);
void ordered_print(stack **stack_,queue **queue_,bst **bst_);
void search(stack *stack_,queue *queue_,bst *bst_,int val_to_search);
void special_traverse(stack *stack_,queue *queue_,bst *bst_);

void ordered_stack(stack **stack_);
void ordered_queue(queue **queue_);
int findMaxStack(stack **stack_);
int findMinStack(stack **stack_);
int findMaxQueue(queue **queue_);
int findMinQueue(queue **queue_);
int findMaxBst(bst **bst_);
int findMinBst(bst **bst_);
void print_stack(stack *stack_);
void print_queue(queue *queue_);
void print_bst(bst *bst_);

void push(stack **stack_,int data);
int pop(stack **stack);
void enqueue(queue **queue_,int data);
int dequeue(queue **queue_);
void insert_bst(bst **bst_,int data);
bst *detele_bst(bst *bst_,int data);
bst *min_bst(bst* bst_);

int main()
{
	int data[20]={5,2,7,8,11,3,21,7,6,15,19,35,24,1,8,12,17,8,23,4};
	bst *bst_ = NULL;
	queue *queue_ = NULL;
	stack *stack_ = NULL;
	fill_structures(&stack_,&queue_,&bst_,data);
	ordered_print(&stack_,&queue_,&bst_);
	search(stack_,queue_,bst_,23);
	special_traverse(stack_,queue_,bst_);
	return 0;
}
void fill_structures(stack **stack_,queue **queue_,bst **bst_,int data[])
{
	int i;
	double time_s,time_q,time_bst;
	clock_t tick_s,tock_s,tick_q,tock_q,tick_bst,tock_bst;

	printf("**************  FILL STRUCTURES  ***************\n\n");

	tick_s = clock();
	for(i=0;i<DATA_NUM;i++)
		push(stack_,data[i]);
	tock_s = clock();
	time_s = (double)(tock_s - tick_s)/CLOCKS_PER_SEC;

	tick_q = clock();
	for(i=0;i<DATA_NUM;i++)
		enqueue(queue_,data[i]);
	tock_q = clock();
	time_q = (double)(tock_q - tick_q)/CLOCKS_PER_SEC;

	tick_bst = clock();
	for(i=0;i<DATA_NUM;i++)
		insert_bst(bst_,data[i]);
	tock_bst = clock();
	time_bst = (double)(tock_bst - tick_bst)/CLOCKS_PER_SEC;
	printf("%-15s%-12s%-12s%-12s\n","Structures","Stack","Queue","BST");
	printf("%-15s%-12lf%-12lf%-12lf\n","Exec. time",time_s,time_q,time_bst);
}
void ordered_print(stack **stack_,queue **queue_,bst **bst_)
{
	double time_s,time_q,time_bst;
	clock_t tick_s,tock_s,tick_q,tock_q,tick_bst,tock_bst;

	printf("\n\n**************  ORDER STRUCTURES  **************\n\n");

	printf("Stack :\n");
	tick_s = clock();
	ordered_stack(stack_);
	print_stack(*stack_);
	tock_s = clock();
	time_s = (double)(tock_s - tick_s)/CLOCKS_PER_SEC;

	printf("\nQueue :\n");
	tick_q = clock();
	ordered_queue(queue_);
	print_queue(*queue_);
	tock_q = clock();
	time_q = (double)(tock_q - tick_q)/CLOCKS_PER_SEC;
	
	printf("\nBST :\n");
	tick_bst = clock();
	print_bst(*bst_);
	tock_bst = clock();
	time_bst = (double)(tock_bst - tick_bst)/CLOCKS_PER_SEC;
	printf("\n\n%-15s%-12s%-12s%-12s\n","Structures","Stack","Queue","BST");
	printf("%-15s%-12lf%-12lf%-12lf\n","Exec. time",time_s,time_q,time_bst);
}
void search(stack *stack_,queue *queue_,bst *bst_,int val_to_search)
{
	stack *iter_s;
	queue *iter_q;
	bst *iter_bst;
	int count_stack = 0, count_queue = 0, count_bst = 0;
	int step_stack = 1, step_queue = 1, step_bst = 1;
	double time_s,time_q,time_bst;
	clock_t tick_s,tock_s,tick_q,tock_q,tick_bst,tock_bst;

	printf("\n\n*************  SEARCH STRUCTURES  **************\n\n");

	tick_s = clock();
	for(iter_s = stack_; iter_s != NULL; iter_s = iter_s->next)
		if(iter_s->num == val_to_search)
			count_stack++;
	printf("Stack : %d result founded on ",count_stack);
	for(iter_s = stack_; iter_s != NULL; iter_s = iter_s->next, step_stack++)
		if(iter_s->num == val_to_search)
			printf("%d.step ",step_stack);
	printf("\n");
	tock_s = clock();
	time_s = (double)(tock_s - tick_s)/CLOCKS_PER_SEC;


	tick_q = clock();
	for(iter_q = queue_; iter_q != NULL; iter_q = iter_q->next)
		if(iter_q->num == val_to_search)
			count_queue++;
	printf("Queue : %d result founded on ",count_queue);
	for(iter_q = queue_; iter_q != NULL; iter_q = iter_q->next, step_queue++)
		if(iter_q->num == val_to_search)
			printf("%d.step ",step_queue);
	printf("\n");
	tock_q = clock();
	time_q = (double)(tock_q - tick_q)/CLOCKS_PER_SEC;


	tick_bst = clock();
	for(iter_bst = bst_; iter_bst != NULL;)
	{
		if(iter_bst->num == val_to_search)
			count_bst++;
		if(val_to_search <= iter_bst->num)
			iter_bst = iter_bst->left;
		else
			iter_bst = iter_bst->right;
	}
	printf("Bst   : %d result founded on ",count_bst);
	for(iter_bst = bst_; iter_bst != NULL;step_bst++)
	{
		if(iter_bst->num == val_to_search)
			printf("%d.layer ",step_bst);
		if(val_to_search <= iter_bst->num)
			iter_bst = iter_bst->left;
		else
			iter_bst = iter_bst->right;
	}
	tock_bst = clock();
	time_bst = (double)(tock_bst - tick_bst)/CLOCKS_PER_SEC;
	printf("\n\n%-15s%-12s%-12s%-12s\n","Structures","Stack","Queue","BST");
	printf("%-15s%-12lf%-12lf%-12lf\n","Exec. time",time_s,time_q,time_bst);
}
void special_traverse(stack *stack_,queue *queue_,bst *bst_)
{
	int i,data;
	double time_s,time_q,time_bst;
	clock_t tick_s,tock_s,tick_q,tock_q,tick_bst,tock_bst;

	printf("\n\n**************  SPECIAL TRAVERSE  **************\n\n");

	tick_s = clock();
	for(i=0;stack_ != NULL;i++)
	{
		if(i%2 == 0)
			data = findMaxStack(&stack_);
		else
			data = findMinStack(&stack_);
		printf("%d ",data);
	}
	printf("\n\n");
	tock_s = clock();
	time_s = (double)(tock_s - tick_s)/CLOCKS_PER_SEC;


	tick_q = clock();
	for(i=0;queue_ != NULL;i++)
	{
		if(i%2 == 0)
			data = findMaxQueue(&queue_);
		else
			data = findMinQueue(&queue_);
		printf("%d ",data);
	}
	printf("\n\n");
	tock_q = clock();
	time_q = (double)(tock_q - tick_q)/CLOCKS_PER_SEC;


	tick_bst = clock();
	for(i=0;bst_ != NULL;i++)
	{
		if(i%2 == 0)
			data = findMaxBst(&bst_);
		else
			data = findMinBst(&bst_);
		printf("%d ",data);
	}
	tock_bst = clock();
	time_bst = (double)(tock_bst - tick_bst)/CLOCKS_PER_SEC;
	printf("\n\n%-15s%-12s%-12s%-12s\n","Structures","Stack","Queue","BST");
	printf("%-15s%-12lf%-12lf%-12lf\n","Exec. time",time_s,time_q,time_bst);
}
void ordered_stack(stack **stack_)
{
	stack *temp_stack = NULL;
	int current;

	while(*stack_ != NULL)
	{
		current = pop(stack_);
		if(temp_stack == NULL || current > temp_stack->num)
			push(&temp_stack,current);
		else
		{
			while(temp_stack != NULL && current < temp_stack->num)
				push(stack_,pop(&temp_stack));
			push(&temp_stack,current);
		}
	}
	*stack_ = temp_stack;
}
void ordered_queue(queue **queue_)
{
	queue *temp_queue = NULL, *helper = NULL, *tail = NULL;
	int current;

	while(*queue_ != NULL)
	{
		current = dequeue(queue_);
		if(temp_queue == NULL)
			enqueue(&temp_queue,current);
		else
		{
			if(current > temp_queue->num)
			{
				while(temp_queue != NULL && current > temp_queue->num)
					enqueue(&helper,dequeue(&temp_queue));
				enqueue(&temp_queue,current);
				while(helper != NULL)
					enqueue(&temp_queue,dequeue(&helper));
			}
			else
			{
				tail = temp_queue;
				while(tail->next != NULL)
					tail = tail->next;
				if(current < tail->num)
					enqueue(&temp_queue,current);
				else
				{
					while(temp_queue != NULL && current < temp_queue->num)
						enqueue(queue_,dequeue(&temp_queue));
					while(temp_queue != NULL)
						enqueue(&helper,dequeue(&temp_queue));
					enqueue(&temp_queue,current);
					while(helper != NULL)
						enqueue(&temp_queue,dequeue(&helper));
				}
			}
		}
	}
	*queue_ = temp_queue;
}
int findMaxStack(stack **stack_)
{
	stack *temp_stack = NULL, *iter = *stack_;
	int max = iter->num;

	for(;iter != NULL; iter = iter->next)
		if(iter->num > max)
			max = iter->num;

	for(;(*stack_)->num != max;)
		push(&temp_stack,pop(stack_));
	
	max = pop(stack_);

	for(; *stack_ != NULL;)
		push(&temp_stack,pop(stack_));
	*stack_ = temp_stack;

	return max;
}
int findMinStack(stack **stack_)
{
	stack *temp_stack = NULL, *iter = *stack_;
	int min = iter->num;

	for(;iter != NULL; iter = iter->next)
		if(iter->num < min)
			min = iter->num;

	for(;(*stack_)->num != min;)
		push(&temp_stack,pop(stack_));

	min = pop(stack_);

	for(; *stack_ != NULL;)
		push(&temp_stack,pop(stack_));
	*stack_ = temp_stack;

	return min;
}
int findMaxQueue(queue **queue_)
{
	queue *temp_queue = NULL, *iter = *queue_;
	int max = iter->num;

	for(;iter != NULL; iter = iter->next)
		if(iter->num > max)
			max = iter->num;

	for(;(*queue_)->num != max;)
		enqueue(&temp_queue,dequeue(queue_));
	
	max = dequeue(queue_);

	for(; *queue_ != NULL;)
		enqueue(&temp_queue,dequeue(queue_));
	*queue_ = temp_queue;

	return max;
}
int findMinQueue(queue **queue_)
{
	queue *temp_queue = NULL, *iter = *queue_;
	int min = iter->num;

	for(;iter != NULL; iter = iter->next)
		if(iter->num < min)
			min = iter->num;

	for(;(*queue_)->num != min;)
		enqueue(&temp_queue,dequeue(queue_));
	
	min = dequeue(queue_);

	for(; *queue_ != NULL;)
		enqueue(&temp_queue,dequeue(queue_));
	*queue_ = temp_queue;

	return min;
}
int findMaxBst(bst **bst_)
{
	bst *iter = *bst_, *temp;
	int max;

	for(;iter->right != NULL; iter = iter->right);

	max = iter->num;
	*bst_ = detele_bst(*bst_,iter->num);
	
	return max;
}

int findMinBst(bst **bst_)
{
	bst *iter = *bst_, *temp;
	int min;

	for(;iter->left != NULL; iter = iter->left);

	min = iter->num;
	*bst_ = detele_bst(*bst_,iter->num);
	
	return min;
}
void print_stack(stack *stack_)
{
	for(;stack_ != NULL;stack_ = stack_->next)
		printf("%d ",stack_->num);
	printf("\n");
}
void print_queue(queue *queue_)
{
	for(;queue_ != NULL;queue_ = queue_->next)
		printf("%d ",queue_->num);
	printf("\n");
}
void print_bst(bst *bst_)
{
	if(bst_ != NULL)
	{
		print_bst(bst_->right);
		printf("%d ",bst_->num);
		print_bst(bst_->left);	
	}
}
void push(stack **stack_,int data)
{
	stack *temp = (stack*)malloc(sizeof(stack)) ,*iter;
	temp->num = data;
	temp->next = NULL;
	if(*stack_ == NULL)
		*stack_ = temp; 
	else
	{
		iter = *stack_;
		*stack_ = temp;
		temp->next = iter;
	}
}
int pop(stack **stack_)
{
	stack *iter;
	int data;
	if(*stack_ != NULL)
	{
		iter = *stack_;
		data = iter->num;
		*stack_ = (*stack_)->next;
		free(iter);
		return data;
	}
	else
		printf("Stack is already empty...\n");
	return -1;
}
void enqueue(queue **queue_,int data)
{
	queue *temp = (queue*)malloc(sizeof(queue)) ,*iter;
	temp->num = data;
	temp->next = NULL;
	if(*queue_ == NULL)
		*queue_ = temp;
	else
	{
		iter = *queue_;
		while(iter->next != NULL)
			iter = iter->next;
		iter->next = temp;
	}
}
int dequeue(queue **queue_)
{
	queue *iter;
	int data;
	if(*queue_ != NULL)
	{
		iter = *queue_;
		data = iter->num;
		*queue_ = (*queue_)->next;
		free(iter);
		return data;
	}
	else
		printf("Queue is already empty...\n");
	return -1;
}
void insert_bst(bst **bst_,int data)
{
	if(*bst_ == NULL)
	{
		*bst_ = (bst*)malloc(sizeof(bst));
		(*bst_)->num = data;
		(*bst_)->left = NULL;
		(*bst_)->right = NULL;
	}
	else if((*bst_)->num < data)
		insert_bst(&(*bst_)->right,data);
	else
		insert_bst(&(*bst_)->left,data);
}
bst *detele_bst(bst *bst_,int data)
{
	bst *temp;
	if(bst_ == NULL)
		return bst_;
	if(bst_->num > data)
		bst_->left = detele_bst(bst_->left,data);
	else if(bst_->num < data)
		bst_->right = detele_bst(bst_->right,data);
	else
	{
		if(bst_->left == NULL)
		{
			temp = bst_->right;
			free(bst_);
			return temp;
		}
		else if(bst_->right == NULL)
		{
			temp = bst_->left;
			free(bst_);
			return temp;
		}
		bst *temp = min_bst(bst_->right);
		bst_->num = temp->num;
		bst_->right = detele_bst(bst_->right,temp->num);
	}
	return bst_;
}
bst *min_bst(bst* bst_)
{
	bst *iter = bst_;
	while (iter != NULL && iter->left != NULL)
		iter = iter->left;
	return iter;
}
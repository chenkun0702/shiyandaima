#include <stdio.h>
#include <stdlib.h>

typedef int data_t;

typedef struct btree{
	data_t data;
	data_t num;
	struct btree *lchild;
	struct btree *rchild;
}btree_t;



btree_t *creat_btree(int num,int max)
{
	btree_t *root;
	if(num > max)
		return NULL;
	root = malloc(sizeof(btree_t));

	root->data = num;
	root->num = num;
	root->lchild = creat_btree(2 *num,max);
	root->rchild = creat_btree(2 * num + 1,max);
	return root;
}

btree_t *creat_tree(int num,int max,int *flag)
{
	btree_t *root;
	if(num > max || 0 == flag[num])
		return NULL;
	root = malloc(sizeof(btree_t));

	root->data = num;
	root->num = num;
	root->lchild = creat_tree(2 *num,max,flag);
	root->rchild = creat_tree(2 * num + 1,max,flag);
	return root;
}


void pre_visit(btree_t *root)
{
	if(NULL == root)
		return ;
	printf(" %d ",root->data);
	pre_visit(root->lchild);
	pre_visit(root->rchild);

	return ;
}

void post_visit(btree_t *root)
{
	if(NULL == root)
		return ;
	post_visit(root->lchild);
	post_visit(root->rchild);
	printf(" %d ",root->data);

a4:	return ;
}

void mid_visit(btree_t *root)
{
	if(NULL == root)
		return ;
	mid_visit(root->lchild);
	printf(" %d ",root->data);
	mid_visit(root->rchild);

	return ;
}


void leve_visit(btree_t *root)
{
	btree_t * *queue;
	int rear = 0;
	int front = 0;

	queue = malloc(sizeof(data_t) * 100);

	//1.入队根节点
	queue[rear ++] = root;
	while(rear != front){
		if(/*有左孩子*/queue[front]->lchild != NULL)
			queue[rear ++] = queue[front]->lchild;
		if(/*有右孩子*/NULL != queue[front]->rchild)
			queue[rear ++] = queue[front]->rchild;
		//出队打印自己
		printf(" %d ",queue[front++]->data);
	}

	printf("\n");

	free(queue);

	return ;
}

void pre_stack_visit(btree_t *root)
{
	btree_t *stack[20];
	int top = -1;

	printf("pre_stack_visit");	
	while(NULL != root || -1 != top){
		while(NULL != root){
			//打印自己
			printf(" %d ",root->data);
			//入栈自己
			stack[++top] = root;
			//获取左孩子
			root = root->lchild;
		}

		//出栈栈顶元素
		root = stack[top --];
		//获取右孩子
		root = root->rchild;
	}
	printf("\n");

	return ;
}
void mid_stack_visit(btree_t *root)
{
	btree_t *stack[20];
	int top = -1;

	printf("mid_stack_visit");	
	while(NULL != root || -1 != top){
		while(NULL != root){
			//入栈自己
			stack[++top] = root;
			//获取左孩子
			root = root->lchild;
		}

		//出栈栈顶元素
		root = stack[top --];
		//打印自己
		printf(" %d ",root->data);
		//获取右孩子
		root = root->rchild;
	}
	printf("\n");

	return ;
}
#if 0
void post_visit(btree_t *root)
{
	if(NULL == root)
		return ;
a1: post_visit(root->lchild);
	// 数据出栈，获取右孩子
	// 数据入栈
a2:	post_visit(root->rchild);
	//数据出栈，打印自己
a3:	printf(" %d ",root->data);

a4:	return ;
}

#endif


void post_stack_visit(btree_t *root)
{
	struct st{
		btree_t *root;
		int flag;
	}*stack;
	int top = -1;
	stack = malloc(sizeof(struct st) * 20);
	
	printf("post_stack_visit:");

	while(NULL != root || -1 != top){
		while(NULL != root){
			stack[++top].root = root;
			stack[top].flag = 1;
			root = root->lchild;
		}

		if(1 == stack[top].flag){
			root = stack[top].root->rchild;
			stack[top].flag = 2;
		}
		else if(2 == stack[top].flag){
			printf(" %d ",stack[top --].root->data);
		}
	}
	
	printf("\n");
	free(stack);
	return ;
}

int main(int argc, const char *argv[])
{
	int flag[13] = {0,1,1,1,0,1,1,0,0,0,1,1,0};

	btree_t *root = creat_tree(1,11,flag);
	

	pre_visit(root);
	printf("\n");
	mid_visit(root);
	printf("\n");
	post_visit(root);
	printf("\n");

	leve_visit(root);
	
	pre_stack_visit(root);
	mid_stack_visit(root);
	post_stack_visit(root);

	return 0;
}

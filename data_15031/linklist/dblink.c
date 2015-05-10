#include <stdio.h>
#include <stdlib.h>

typedef int data_t;

typedef struct dblinknode{
	data_t data;
	struct dblinknode *front;
	struct dblinknode *next;
}dblink_t;

dblink_t *creat_dblink(void)
{
#if 0
	dblink_t *head,*tail;

	head = malloc(sizeof(dblink_t));
	tail = malloc(sizeof(dblink_t));

	head->next = tail;
	head->front = NULL;
	tail->next = NULL;
	tail->front = head;
#else
	dblink_t *head;

	head = malloc(sizeof(dblink_t));
	head->next = malloc(sizeof(dblink_t));
	
	head->front = NULL;

	head->next->front = head;
	head->next->next = NULL;

#endif

	return head;

}


int ins_head_dblink(dblink_t *head,const data_t *data)
{
	dblink_t * newnode;
	newnode = malloc(sizeof(dblink_t));

	newnode->data = *data;
	newnode->next = head->next;
	newnode->front = head;
	
#if 0
	head->next->front = newnode;
	head->next = newnode;
#else
	newnode->next->front = newnode;
	newnode->front->next = newnode;
#endif

	return 0;
}

int del_head_dblink(dblink_t *head,data_t *databuf)
{
	//1.拷贝数据
	//2.保存即将删除的节点地址
	//3.更改表结构
	//4.free
	//
	dblink_t *temp;

	if(NULL == head->next->next)
		return -1;

	if(NULL != databuf)
		*databuf = head->next->data;

	temp = head->next;

	head->next = head->next->next;
	head->next->front = head;

	free(temp);

	return 0;
}

void print_dblink(const dblink_t *head)
{
	dblink_t *tail;
	while(NULL != head->next->next){
		head = head->next;
		printf(" %d ",head->data);
	}
	printf("\n");
	tail = head->next;

	while(NULL != tail->front->front){
		tail = tail->front;
		printf(" %d ",tail->data);
	}
	printf("\n");
	
	return ;
}

int main(int argc, const char *argv[])
{
	
	int i;
	dblink_t *head;
	head = creat_dblink();
	
	for(i = 9 ; i >= 0;i --){
		ins_head_dblink(head,&i);
	}

	print_dblink(head);

	del_head_dblink(head,NULL);
	del_head_dblink(head,NULL);
	del_head_dblink(head,NULL);
	del_head_dblink(head,NULL);
	
	print_dblink(head);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>

typedef int data_t;
typedef struct linknode {
	data_t data;
	struct linknode *next;
}link_t;

link_t *creat_link()
{
	link_t *head;
	head = malloc(sizeof(link_t));
	if(NULL == head)
		return NULL;

	head->next = NULL;

	return head;
}

int ins_head_link(link_t *head,const data_t *data)
{
	//1.开辟保存新数据的空间
	// 	1.2 初始化数据
	//2.将这块空间插入到链表中
	//  2.1 改变指针指向
	//  	1）新创建的空间的next 指向 插入位置的后一个元素
	//  	2）插入位置的全一个元素的 next 指向新节点
	
	link_t *newnode;
	newnode = malloc(sizeof(link_t));
	if(NULL == newnode)
		return -1;

	newnode->data = *data;

	newnode->next = head->next; 
	head->next = newnode;

	return 0;


}
int ins_index_link(link_t *head,int index,const data_t *data)
{
	//1.定位
	//2.假设指向的节点为头，执行头部插入
	
	while(index --){
		head = head->next;
		if(NULL == head)
			return -1;
	}

	ins_head_link(head,data);

	return 0;
}

int del_head_link(link_t *head,data_t *databuf)
{
	link_t *temp;
	if(NULL == head->next)
		return -1;

	if(NULL != databuf)
		*databuf = head->next->data;

	temp = head->next;

	head->next = temp->next;// head->next = head->next->next;

	free(temp);
	
	return 0;
}

int del_index_link(link_t *head,int index,data_t *databuf)
{
	//1.定位
	//2.拷贝
	//3.头部删除
	//
	
	while(index --){
		head = head->next;
		if(NULL == head->next)
			return -1;
	}

	del_head_link(head,databuf);

	return 0;
}


int clean_link(link_t *head)
{
#if 0
	while(NULL != head->next){
		del_head_link(head,NULL);
	}
#endif
	while( ! del_head_link(head,NULL))
		;

	return 0;
}

/*
 * 返回找的的元素的前一个节点的地址
 * */

link_t *locate_link(link_t *head,const data_t *data)
{
	
	while(NULL != head->next){
		if(*data == head->next->data)
			return head;
		head = head->next;
	}

	return NULL;
}

int get_head_link(link_t *head,data_t *databuf)
{
	if(NULL == head->next)
		return -1;
	*databuf = head->next->data;
	
	return 0;
}

int get_index_link(link_t *head,int index,data_t *databuf)
{
	while(index --){
		head = head->next;
		if(NULL == head->next)
			return -1;
	}
	get_head_link(head,databuf);
	
	return 0;
}

int length_link(const link_t *head)
{
	int sum = 0;
	while(NULL != head->next){
		sum ++;
		head = head->next;
	}

	return sum;
}

int empty_link(link_t *head)
{
	return NULL == head->next; // head->next  == (*head).next;
}

int dis_link(link_t **headp)
{
	clean_link(*headp);
	free(*headp);
	*headp = NULL;
	
	return 0;
}

void print_link(const link_t *head)
{
	head = head->next;
	while(NULL != head){
		printf(" %d ",head->data);
		head = head->next;
	}

	printf("\n");
}

int main(int argc, const char *argv[])
{
	
	link_t *head;
	int i;
	head = creat_link();

	for(i = 9;i >= 0;i --){
		ins_head_link(head,&i);
	}


	print_link(head);

	i = 90;
	ins_index_link(head,11,&i);
	ins_index_link(head,15,&i);
	print_link(head);


	//del_head_link(head,&i);
	del_index_link(head,10,&i);
	printf("del:%d\n",i);

	print_link(head);
	
	dis_link(&head);
	return 0;
}

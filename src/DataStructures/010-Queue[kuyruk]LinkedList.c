/**	
 * 	Title: Linked list implementation of Queue[Bağlı liste ile kuyruk]
 * 	FIFO
 *	Author:	Fatih Ertuğral.
 *	Created on July 19, 2018, 7:30 PM
 **/
#include <stdio.h>
#include <stdlib.h>

typedef struct _LIST{
	int data;
	struct _LIST *next;
} LIST;

LIST *root = NULL;
LIST *son;

void enqueue(int veri){
	if(root == NULL){
		root = (LIST *)malloc(sizeof(LIST));
		root->next = NULL;
		root->data = veri;
		son = root;
		return ;
	}
	son->next = (LIST *)malloc(sizeof(LIST));
	son = son->next;
	son->data = veri;
	son->next = NULL;
}
int dequeue(){
	if(root == NULL){
		printf("list bos\n");
		return -1;
	}
	if(root->next == NULL){
		
		int rvalue = root->data;
		root = NULL;
		return rvalue;
	}

	LIST *temp = root;
	root = root->next;
	int rvalue = temp->data;
	free(temp);
	return rvalue;
}


int main(int argc, char *argv[]) {
	
	enqueue(10);
	enqueue(30);
	enqueue(40);
	enqueue(50);
	enqueue(60);
	enqueue(70);
	enqueue(80);
	enqueue(90);
	enqueue(100);
	printf("%d\n",dequeue());
	printf("%d\n",dequeue());
	printf("%d\n",dequeue());
	printf("%d\n",dequeue());
	printf("%d\n",dequeue());
	printf("%d\n",dequeue());
	printf("%d\n",dequeue());
	printf("%d\n",dequeue());
	printf("%d\n",dequeue());
	printf("%d\n",dequeue());

	return 0;
}

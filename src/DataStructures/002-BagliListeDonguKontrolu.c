#include <stdio.h>
#include <stdlib.h>

struct LIST{
	int data;
	struct LIST *next;
};
typedef struct LIST node;

void bastir(node *y){
	while(y != NULL){
		printf("%d \n", y->data);
		y = y->next;
	}
}
void ekle(node *r, int x){
	while(r->next != NULL){
		r = r->next;
	}
	r->next = (node *)malloc(sizeof(node));
	r->next->data = x;
	r->next->next = NULL;
}

int main(int argc, char *argv[]) {
	node *root;
	root = (node *)malloc(sizeof(node));
	root -> next = NULL;
	root -> data = 500;

	int i = 0;
	
	for(; i < 5; i++)
	{
		ekle(root, i*10);
	}
	bastir(root);
	getchar();
}
/*
 * Bağli listeye giriş çalışma mantığı
 */

#include <stdio.h>
#include <stdlib.h>

struct LIST{
	int data;
	struct LIST *next;
};
typedef struct LIST node;

int main(int argc, char *argv[]) {
	node *root;
	root = (node *)malloc(sizeof(node));
	root -> data = 10;
	root -> next = (node *)malloc(sizeof(node));
	root -> next -> data = 20;
	root -> next -> next = (node *)malloc(sizeof(node));
	root -> next -> next -> data = 30;

	node *iter;
	iter = root;
	printf("%d", iter -> data);
	iter = iter -> next;
	printf("%d", iter -> data);
	iter = iter -> next;
	printf("%d", iter -> data);
	
	getchar();
}
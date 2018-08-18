/**	
 * 	Title:	Making a stack using linked list.[Bağlı listelerle yığın oluşturma]
 * 			LIFO [Son giren ilk çıkar yöntemi.]
 *	Author:	Fatih Ertuğral.
 *	Created on July 12, 2018, 10:35 PM
 **/
#include <stdio.h>
#include <stdlib.h>

typedef struct LIST{
	int data;
	struct LIST *next;
} STACK;

STACK *pop(STACK *_stack);
STACK *push(STACK *_stack, int value);
void fonksiyon(int value);
void printAllStack(STACK *root);

int main(int argc, char *argv[]) { //---	Test
	STACK *root = NULL;
	root = pop(root);
	root = push(root, 10);
	root = push(root, 20);
	root = push(root, 30);
	root = push(root, 40);
	root = push(root, 50);
	root = push(root, 60);
	root = pop(root);
	root = pop(root);
	root = pop(root);
	root = pop(root);
	printAllStack(root);
	root = pop(root);
	root = pop(root);
	root = pop(root);
	root = pop(root);
	root = pop(root);
	root = pop(root);
	root = push(root, 10);
	root = push(root, 20);
	root = push(root, 30);
	root = push(root, 40);
	root = push(root, 50);
	root = push(root, 60);
	printAllStack(root);
	return 0;
}
STACK *push(STACK *_stack, int value){
	if(_stack == NULL){
		_stack = (STACK *)malloc(sizeof(STACK));
		_stack->next = NULL;
		_stack->data = value;
		return _stack;
	}
	STACK *new = (STACK *)malloc(sizeof(STACK));
	new->data = value;
	new->next = _stack;
	
	_stack = new;
	return _stack;
}
STACK *pop(STACK *_stack){
	if(_stack == NULL){
		printf("Stack bos..\n");
		return NULL;
	}
	STACK *temp =malloc(sizeof(STACK));
	temp = _stack;
	int rvalue= temp->data;
	if(_stack->next == NULL){
		free(temp);
		free(_stack);
		printf("Son stack: %d\n", rvalue);
		return NULL;
	}
	_stack = _stack->next;
	free(temp);
	fonksiyon(rvalue);
	return _stack;
}
void fonksiyon(int value){
	printf("Cikarilan stack: %d\n", value);
}
void printAllStack(STACK *root){
	
	for(int i=1;root != NULL; i++){
		printf("%d.Mevcut Stack: %d\n", i, root->data);
		root = root->next;
	}
}
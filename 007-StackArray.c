/**	
 * 	Title:	Stack [yığın] kodlaması ve Diziler
 *  LIFO [son giren ilk çıkar]
 *	Author:	Fatih Ertuğral.
 *	Created on July 12, 2018, 4:54 PM
 **/
#include <stdio.h>
#include <stdlib.h>
typedef struct _STACK{
	int *dizi;
	int boyut;
	int tepe;
} STACK;
STACK *constructor(STACK *_stack){
	_stack = (STACK *)malloc(sizeof(STACK));
	_stack->tepe = 0;
	_stack->boyut = 2;
	_stack->dizi = (int *)malloc(sizeof(int)*_stack->boyut);
	return _stack;
}
void push(STACK *_stack, int sayi){
	if(_stack->tepe >= _stack->boyut){
		int *dizi2 = (int *)malloc(sizeof(int)*(_stack->boyut)*2);
		for(int i=0 ; i < _stack->tepe ; i++){
			dizi2[i] = _stack->dizi[i];
		}
		free(_stack->dizi);
		_stack->dizi = dizi2;
		_stack->boyut *= 2;
	}
	_stack->dizi[(_stack->tepe)++] = sayi;
}

int pop(STACK *_stack){
	if(_stack->tepe == 0){
		printf("Dizi Bos Cikarilcak Veri Yok.\n");
		return -1;
	}
	if(_stack->tepe <= (_stack->boyut/4)){
		int *dizi2 = (int *)malloc(sizeof(int)*(_stack->boyut)/2);
		for(int i=0 ; i < _stack->tepe ; i++){
			dizi2[i] = _stack->dizi[i];
		}
		free(_stack->dizi);
		_stack->dizi = dizi2;
		_stack->boyut /= 2;
	}
	return _stack->dizi[--(_stack->tepe)];
}
void printStack(STACK *_stack){
		printf("Boyut: %d\n", _stack->boyut);
		for(int i=0 ; i < _stack->tepe ; ++i)
			printf("dizi[%d]: %d\n", i, _stack->dizi[i]);
		if(_stack->tepe == 0)
			printf("Stack bos gosterilcek deger yok\n");
}
int main(int argc, char *argv[]) {
	// Test
	STACK *b;
	STACK *c;
	b = NULL;
	b = constructor(b);
	c = constructor(b);
	pop(b);
	printStack(b); 
	printf("Test 1.bolum\n");

	for(int i=0; i < 10; i++)
		push(b, i*10);
	for(int i=0; i < 10; i++)
		push(b, i*10);
	printStack(b); 
	printf("Test 2.bolum\n");

	for(int i=0; i<10; i++)
		push(c, pop(b));
	printStack(b); 
	printf("Test 3.bolum\n");
	printStack(c); 
	printf("Test 4.bolum\n");
	for(int i=0; i<20; i++)
		push(c, pop(b));
	printStack(c);
	return 0;
}
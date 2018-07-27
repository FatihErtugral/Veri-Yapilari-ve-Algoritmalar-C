/**	
 * 	Title:	Sequential linked list. [Sıralı Bağlı Liste]
 *	Author:	Fatih Ertuğral.
 *	Created on July 10, 2018, 9:55 PM
 **/
#include <stdio.h>
#include <stdlib.h>

typedef struct LIST{
	int data;
	struct LIST *next;
} NODE;

NODE *siraliEkle(NODE *list, int veri){
	//
	//	Linklist boşsa, ilk değeri ekle.
	//
	if(list == NULL){	
		list = (NODE*)malloc(sizeof(NODE));
		list->next = NULL;
		list->data = veri;
		return list;
	}
	//
	//	Veri küçükse, listenin başına ekle.
	//
	else if(list->data > veri){
		NODE *temp = (NODE *)malloc(sizeof(NODE));
		temp->data = veri;
		temp->next = list;
		return temp;
	}
	//
	//	Veri büyükse, araya veya sona ekle.
	//
	else{
		NODE *iter = list;
		while(iter->next != NULL && iter->next->data < veri)
			iter = iter->next;
		NODE *temp = (NODE *)malloc(sizeof(NODE));
		temp->next = iter->next;
		iter->next = temp;
		temp->data = veri;
		return list;
	}
}

int main(int argc, char const *argv[])
{
	NODE *root;
	root = NULL;
	root = siraliEkle(root, 20);
	root = siraliEkle(root, 10);
	root = siraliEkle(root, 430);
	root = siraliEkle(root, 530);
	root = siraliEkle(root, 230);
	root = siraliEkle(root, 130);
	root = siraliEkle(root, 35);
	root = siraliEkle(root, 45);

	NODE *gezici = root;
	for(int i = 0; gezici != NULL; i++){
		
	(i == 0) ? printf("root: %d\n", gezici->data) : printf("next: %d\n", gezici->data);
	gezici = gezici->next;
	}
	return 0;
}

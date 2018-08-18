/**	
 * 	Title: Doubly linked list. [Çift yönlü bağlı liste]
 * 	Sıralı (sequential) Ekleme/Silme işlemleri.
 *	Author:	Fatih Ertuğral.
 *	Created on July 11, 2018, 10:26 PM
 **/
#include <stdio.h>
#include <stdlib.h>

typedef struct _DLIST{
	int data;
	struct _DLIST *prev;
	struct _DLIST *next;
} DLIST;

DLIST *dListSequentialAdd(DLIST *list, int veri){
	if(list == NULL){ //--------------------------------	İlk değer atanıyor.
		list = (DLIST *)malloc(sizeof(DLIST));
		list->data = veri;
		list->next = NULL;
		list->prev = NULL;
		return list;
	}
	if(list->data > veri){ //---------------------------	Root değiştiriliyor.
		DLIST *temp = (DLIST *)malloc(sizeof(DLIST));
		list->prev = temp;
		temp->next = list;
		temp->prev = NULL;
		temp->data = veri;
		return temp;
	}
	DLIST *iter = list;
	while(iter->next != NULL && iter->next->data <= veri){//Gezici ilerliyor.
		iter = iter->next;
	}
	DLIST *temp = (DLIST *)malloc(sizeof(DLIST)); //----	Araya ve sona ekleme yapılıyor.
	if(iter->next != NULL)
		iter->next->prev = temp;
	temp->next = iter->next;
	iter->next = temp;
	temp->prev = iter;
	temp->data = veri;
	return list;
}

DLIST *dListDel(DLIST *list, int veri){
	DLIST *iter = list;
	DLIST *temp;
	if(list->data == veri){
		if(list->next == NULL & list->prev == NULL){ //-	Listede tek kalan veriyi sil.
			free(list);
			return NULL;
		}
		else{ //----------------------------------------	İlk veriyi sil rootu kaydır.
		temp = list->next;
		temp->prev = NULL;
		free(list);
		return temp;
		}
	}
	while(iter->next !=NULL && iter->next->data != veri){//	Gezici ilerliyor.
		iter = iter->next;
	}
	if(iter->next == NULL && iter->data != veri){ //----	Tanımsız veriyi bildir.
		printf("veri bulunamadi\n");
		return list;
	}
	temp = iter->next;
	if(iter->next->next == NULL){ //--------------------	Listenin sonundaki veriyi sil.
		iter->next = NULL;
		free(temp);
		return list;
	}
	iter->next->next->prev = iter; //-------------------	Aradaki veriyi sil.
	iter->next = iter->next->next;
	free(temp);
	return list;
}

int main(int argc, char *argv[]) {
	//test
	DLIST *root;
	root = NULL;
	root = dListSequentialAdd(root, 10);
	root = dListSequentialAdd(root, 5);
	root = dListSequentialAdd(root, 8);
	root = dListSequentialAdd(root, 40);
	root = dListSequentialAdd(root, 10);
	root = dListSequentialAdd(root, 20);
	root = dListSequentialAdd(root, 30);
	root = dListSequentialAdd(root, 0);
	root = dListSequentialAdd(root, 55);
	root = dListDel(root, 10);
	root = dListDel(root, 5);
	root = dListDel(root, 8);
	root = dListDel(root, 40);
	root = dListDel(root, 10);
	root = dListDel(root, 20);
	root = dListDel(root, 30);
	root = dListSequentialAdd(root, 140);
	root = dListSequentialAdd(root, 110);
	root = dListSequentialAdd(root, 120);
	root = dListSequentialAdd(root, 130);
	root = dListSequentialAdd(root, 80);
	root = dListSequentialAdd(root, 55);
	root = dListDel(root, 55);
	root = dListDel(root, 55);
	root = dListDel(root, 55);
	root = dListDel(root, 55);
	root = dListSequentialAdd(root, 140);
	root = dListSequentialAdd(root, 110);
	root = dListSequentialAdd(root, 120);
	root = dListSequentialAdd(root, 130);
	root = dListSequentialAdd(root, 80);
	root = dListSequentialAdd(root, 55);
	root = dListDel(root, 55);
	root = dListDel(root, 55);
	root = dListDel(root, 10);
	root = dListDel(root, 5);
	root = dListDel(root, 8);
	root = dListDel(root, 40);
	root = dListDel(root, 10);
	root = dListDel(root, 20);
	root = dListDel(root, 30);
	return 0;
}
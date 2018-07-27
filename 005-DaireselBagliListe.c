/**	
 * 	Title:	Cycles in a Linked List.[Dairesel Bağlı Liste]
 *	Author:	Fatih Ertuğral.
 *	Created on July 11, 2018, 7:48 AM
 *	Sıralı ekleme/silme.
 **/
#include <stdio.h>
#include <stdlib.h>

typedef struct _CLIST{
	int data;
	struct _CLIST *next;
} CLIST;

CLIST *cSil(CLIST *list, int delX){
	CLIST *temp;
	CLIST *iter = list;
	if(list->next == list && list->data == delX){ // Son değer silinirse hafızayı boşaltır.
		free(list);
		return NULL;
	}	
	while((iter->next->data != delX) && (iter->next != list)){ 
		iter = iter->next;
	}
	
	if(iter->next == list){ 
			if(list->data == delX){ // while yardımıyla rootaki veriyi(baştaki) siler.
				temp = (CLIST *)malloc(sizeof(CLIST));
				temp = list->next;
				temp->next = temp;
				free(list);
				return temp;
			}
			else{
				printf("Sonuc bulunamadi.");
				return list;
			}
	}
	else{ // root dışındakileri siler.
		temp = (CLIST *)malloc(sizeof(CLIST));
		temp = iter->next;
		iter->next = iter->next->next;
		free(temp);
		return list;
	}
}

CLIST *cSiraliEkle(CLIST *list, int veri){
	if(list == NULL){
		list = (CLIST *)malloc(sizeof(CLIST));
		list->data = veri;
		list->next = list;
		return list;
	}
	CLIST *iter = list;
	CLIST *temp;
	if(iter->data > veri){
		temp = (CLIST *)malloc(sizeof(CLIST));
		temp->data = veri;
		temp->next = iter;
		iter->next = temp;
		return temp;
	}
	
		while(iter->next != list && iter->next->data <= veri){
			iter = iter->next;
		}
		temp = (CLIST *)malloc(sizeof(CLIST));
		temp->next = iter->next;
		iter->next = temp;
		temp->data = veri;
		return list;

	
}

int main(int argc, char *argv[]) {
	//test
	CLIST *root;
	root = NULL;
	root = cSiraliEkle(root, 10);
	root = cSiraliEkle(root, 5);
	root = cSiraliEkle(root, 20);
	root = cSiraliEkle(root, 15);
	root = cSiraliEkle(root, 5);
	root = cSiraliEkle(root, 10);
	root = cSil(root, 5);
	root = cSil(root, 10);
	root = cSil(root, 20);
	root = cSil(root, 0);
	root = cSil(root, 15);
	root = cSil(root, 10);
	root = cSil(root, 6);
	root = cSil(root, 5);
	getchar();
}
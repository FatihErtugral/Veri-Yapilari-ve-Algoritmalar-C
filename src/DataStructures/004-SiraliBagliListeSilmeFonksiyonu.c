/*	
 *	
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct LIST{
	int data;
	struct LIST *next;
} NODE;

NODE *siraliEkle(NODE *list, int veri){
	if(list == NULL){
		list = (NODE *)malloc(sizeof(NODE));
		list->data = veri;
		list->next = NULL;
		return list;
	}
	else if(list->data > veri){
		NODE *temp = (NODE *)malloc(sizeof(NODE));
		temp->data = veri;
		temp->next = list;
		return temp;
	}else{
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
NODE *sil(NODE *list, int DeleteData){
	NODE *iter = list;
	NODE *temp;
	if(list->data == DeleteData){
		temp = list;
		list = list->next;
		free(temp);
		return list;
	}
	while(iter->next != NULL && iter->next->data != DeleteData){
		iter = iter->next;
	}
	if(iter->next == NULL){
		printf("sayi mevcut degil \n");
		return list;
	}
	else{
		temp = iter->next;
		iter->next = iter->next->next;
		free(temp);
		return list;
	}
}

int main(int argc, char *argv[]) {
	NODE *root;
	root = NULL;
	root = siraliEkle(root, 20);
	root = siraliEkle(root, 10);
	root = siraliEkle(root, 720);
	root = siraliEkle(root, 50);
	root = siraliEkle(root, 0);
	root = siraliEkle(root, 450);
	root = sil(root, 50);
	root = sil(root, 51);
	root = siraliEkle(root, 210);
	root = siraliEkle(root, 320);
	root = siraliEkle(root, 120);
	root = sil(root, 720);
	root = sil(root, 721);
	
	NODE *gezici = root;
	while(gezici != NULL){
		printf("%d\n", gezici->data);
		gezici = gezici->next;
	}
	getchar();
}
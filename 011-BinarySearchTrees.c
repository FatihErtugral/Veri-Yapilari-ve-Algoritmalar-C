/**	
 * 	Title: Binary Search Trees - [İkili Arama Ağacı]
 *	Author:	Fatih Ertuğral.
 *	Created on July 20, 2018, 3:55 AM  
 *	.:Ağaçtaki temel operasyonlar:.
 *  	+ Ekleme(Insetion)
 *  	+ Dolaşma(Traversal)
 * 			- Infix = LeftNodeRight, RightNodeLeft
 * 			- Prefix = NodeLeftRight, NodeRightLeft
 * 			- Postfix = LeftRightNode, RightLeftNode
 *  	+ Arama(Search)
 *  	+ Max ve Min bulma
 *  	+ Silme(Deletion)
 *
 **/
#include <stdio.h>
#include <stdlib.h>

typedef struct BinarySearchTrees{
	int data;
	struct BinarySearchTrees *left;
	struct BinarySearchTrees *right;
} NODE;

NODE * ekle(NODE *agac, int veri){
	if(agac == NULL){
		NODE *root = (NODE *)malloc(sizeof(NODE));
		root->right = NULL;
		root->left = NULL;
		root->data = veri;
		return root;
	}
	
	if(agac->data < veri){
		agac->right = ekle(agac->right, veri);
		return agac;
	}
	else{
		agac->left = ekle(agac->left, veri);
		return agac;
	}
}
void dolas(NODE *agac){
	if(agac == NULL)
		return ;
	dolas(agac->left);
	printf("%d\n", agac->data);
	dolas(agac->right);
}
int bul (NODE *agac, int ara){
	if(agac ==  NULL)
		return -1;
	if(agac->data == ara)
		return 1;
	if(bul(agac->right, ara) == 1)
		return 1;
	if(bul(agac->left, ara) == 1)
		return 1;
	return-1;
}
int min(NODE *agac){
	while(agac->left != NULL)
		agac = agac->left;
	return agac->data;
}
int max(NODE *agac){
	while(agac->right != NULL)
		agac = agac->right;
	return agac->data;
}
int main(int argc, char *argv[]) {
	NODE *agac = NULL;
	agac = ekle(agac, 12);
	agac = ekle(agac, 200);
	agac = ekle(agac, 190);
	agac = ekle(agac, 213);
	agac = ekle(agac, 56);
	agac = ekle(agac, 24);
	agac = ekle(agac, 18);
	agac = ekle(agac, 27);
	agac = ekle(agac, 28);
	dolas(agac);
	printf("min: %d max: %d", min(agac), max(agac));
	return 0;
}
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

NODE *ekle(NODE *agac, int veri){
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
NODE *sil(NODE *agac, int veri){
	/*	case 1: NULL	
	 *	case 2: No child
	 *	case 3: One child
	 *	case 4: Two children
	 */
	if(agac == NULL)
		return NULL; //----------------------------------	case 1: NULL
	if(agac->data < veri){
		agac->right = sil(agac->right, veri);
		return agac;
	}
	if(agac->data > veri){
		agac->left = sil(agac->left, veri);
		return agac;
	}
	if(agac->data == veri){
		if(agac->right == NULL && agac->left == NULL){ //-	case 2: No child
			free(agac);
			return NULL;
		}
		if(agac->left != NULL){ //------------------------	case 3 and case 4
			int temp = max(agac->left);
			agac->data = temp;
			agac->left = sil(agac->left, temp);
			return agac;
		}
		if(agac->right !=NULL){ //------------------------	case 3 and case 4
			int temp = min(agac->right);
			agac->data = temp;
			agac->right = sil(agac->right, temp);
			return agac;
		}
	}
	/*	Silme işlemi performans bakımından daha iyi yapılabilir.
	 *	Mevcut silme fonksiyonu, özyineli olduğu için,
	 *	ortalarda çok çocuklu bir bağı silme işleminde, 
	 *	sürekli diğer bağlar arasında, yer değiştirme işlemi yapmaktadır.
	 *	Ayrıca her silme işleminde ağacın yapısı değişmektedir.
	 */
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
	printf("min: %d max: %d\n", min(agac), max(agac));
	agac = sil(agac, 200);
	agac = sil(agac, 28);
	agac = sil(agac, 56);
	agac = sil(agac, 57);
	dolas(agac);
	printf("min: %d max: %d\n", min(agac), max(agac));
	agac = ekle(agac, 80);
	agac = ekle(agac, 90);
	agac = ekle(agac, 100);
	agac = ekle(agac, 110);
	agac = ekle(agac, 120);
	agac = ekle(agac, 105);
	agac = ekle(agac, 95);
	agac = ekle(agac, 85);
	agac = ekle(agac, 75);
	dolas(agac);
	printf("min: %d max: %d\n", min(agac), max(agac));
	agac = sil(agac, 12);
	agac = sil(agac, 200);
	agac = sil(agac, 190);
	agac = sil(agac, 213);
	agac = sil(agac, 56);
	agac = sil(agac, 24);
	agac = sil(agac, 18);
	agac = sil(agac, 27);
	agac = sil(agac, 28);
	dolas(agac);
	printf("min: %d max: %d\n", min(agac), max(agac));
	return 0;
}
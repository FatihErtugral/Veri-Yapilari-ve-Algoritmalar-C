/**	
 * 	Title:	AVL TREE[Adelson-Velsky ve E.M. Landis]
 *	Author:	Fatih Ertuğral.
 *	Created on Aug 7, 2018, 1:15 AM
 *	
 *	■ AVL AĞAÇ ÖZELLİKLERİ ■
 *	• Arama maliyetini nlogn seviyesine düşürmek için kullanılır.
 *	• Bir ikili ağaçtır
 *	• AVL ağaçlarında düğüm yüsekliği farkı 1 olmalıdır.	
 *
 *	Açıklama: AVL ağaçlarını anlamak için BST[Binary Search Tree] ağaçlarını bilmek gereklidir.
 *	BST'de veriler eklenirken denge sorunu meydana gelmektedir. AVL ağaçları tam da bu noktada
 *	devreye girer. BST'de dengeyi düzelterek, işlem karmaşıklığını "N log N" indirgemektir.
 *	Aşağıda bu sorun görsel olarak anlatılmak istenmiştir.
 * 	
 *	(Şekil tabl boşluğu 4 olduğunda düzgün gözükür)
 * 	x[] = {10,20,15,30,25,5,40,50,60}
 * 	
 * 			BST:															AVL:
 * 
 * 			[10]														  [20]
 * 			/  \														/		\
 * 		[5]		[20]											[10]				[30]
 * 				/  \											/	\				/	\
 * 			[15]	[30]									[5]		[15]		[25]	[50]
 * 					/  \																/	\
 * 				[25]	[40]														[40]	[60]
 * 							\	
 * 							[50]
 * 								\
 * 								[60]
 *	Algoritma basitçe, bir düğümün kolları arasındaki derinlik farkı 2 ise bu durumda dengeleme işlemi yapılır. 
 *	Şayet fark 2’den az ise (yani 1 veya 0) ise bu durumda bir dengeleme işlemine gerek yoktur.
 *
 *	Algoritmanın ağacı dolaşma (traverse) algoritması ikili arama ağaçları ile aynıdır. 
 *	Ancak ağaca ekleme ve silme işlemleri sırasında ağacın dengesinin bozulması söz konusu olduğu için 
 *	bu fonksiyonlara ilave olarak derinlik kontrolü eklenmiştir.
 *
 *	Ekleme ve silme işlemlerinde ikili arama ağacının ekleme ve silme işleminin aynısını yaptıktan sonra aşağıdaki dengeleme işlemi yapılır.
 *		■ AĞAÇTA EKLEME VEYA SİLME YAPILAN HER DÜĞÜM İÇİN ■
 *		• sol <- Düğümün sol kolunun derinliğini ölç
 *		• sağ <- Düğümün sağ kolunun derinliğini ölç
 *		
 *		• Şayet (sol - sağ > 2) ise sol taraf daha uzundur, dengesizlik tespit edildi.
 *	  	• Şimdi "sol-sol" dengesizliğimi yoksa "sol-sağ" dengesiliğimiz konrtol edilir.
 *		• Şayet (sol->sol - sol->sağ < 0) sol-sol dengesizliğidir, aksi halde sol-sağdır. {LLC || LRC}
 *		 
 *		• Şayet (sol - sağ < -1) ise sağ taraf daha uzundur, dengesizlik tespit edildi.
 *	  	• Şimdi "sağ-sağ" dengesizliğimi yoksa "sağ-sol" dengesiliğimiz konrtol edilir.
 *		• Şayet (sağ->sol - sağ->sağ > 0) sağ-sağ dengesizliğidir, aksi halde sağ-soldur. {RRC || RLC}
 *
 * 	■ DENGESİZLİK SONUCU OLUŞAN DURUMLAR ve DÜZELT ■
 * 		• Sol - Sol Durumu{Left-Left Case}		Sağa döndür					{R-Rotation}
 * 		• Sağ - Sağ Durumu{Right-Right Case}	Sola döndür					{L-Rotation}
 * 		• Sol - Sağ Durumu{Left-Right Case}		Sola döndür, Sağa döndür	{L-Rotation | R-Rotation}
 * 		• Sağ - Sol Durumu{Right-Left Case}		Sağa döndür, Sola döndür	{R-Rotation | L-Rotation}
 * 
 *	■ DENGESİZ DURUMLARI DÜZELTME İŞLEMLERİ ■
 *		• Sola Döndürme{Left Rotations}	
 *		• Sağa Döndürme{Right Rotations}
 *
 * 	Bu bilgiler, kaynak belirtmeden paylaşılması yasaktır.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define AvlMax(a, b) (((a) > (b)) ? (a) : (b))

typedef struct _AVL{
	int data;
	int height;
	struct _AVL *left;
	struct _AVL *right;
} AVL;

int height(AVL *a)
{
	return a == NULL ? 0: a->height;
}
AVL *AvlRotLeft(AVL *root)
{
	AVL *A	= root;
	AVL *B	= root->right;
	AVL *T1	= B->left;
	
	root		= B;
	B->left		= A;
	A->right	= T1;

	A->height		= 1 + max(height(A->left), height(A->right));
	root->height	= 1 + max(height(root->left), height(root->right));
	return root;
}
AVL *AvlRotRight(AVL *root)
{
	AVL *A	= root;
	AVL *B	= root->left;
	AVL *T1	= B->right;
	
	root		= B;
	B->right	= A;
	A->left		= T1;

	A->height		= 1 + max(height(A->left), height(A->right));
	root->height	= 1 + max(height(root->left), height(root->right));
	return root;
}
int getBalance(AVL *a){ 
	return a == NULL ? 0: height(a->left) - height(a->right);
}
AVL *AvlInsert(AVL *a, int data)
{
	if(a == NULL)
	{
		a 			= (AVL *)malloc(sizeof(AVL));
		a->data		= data;
		a->height	= 1;
		a->left		= NULL;
		a->right	= NULL;
		return a;
	}
	else if(data < a->data)
		a->left		= AvlInsert(a->left, data);
	else if(data > a->data)
		a->right	= AvlInsert(a->right, data);
	else
		return a;

	a->height = 1 + max(height(a->left), height(a->right));

	int balance = getBalance(a);
	// Left Left Case	{R-Rotation}
	if(balance > 1)
	{
		if(getBalance(a->left) > 0)
			return AvlRotRight(a);
		a->left = AvlRotLeft(a->left);
		return AvlRotRight(a);
	}
	else if(balance < -1 )
	{
		if(getBalance(a->right) < 0)
			return AvlRotLeft(a);
		a->right = AvlRotRight(a->right);
		return AvlRotLeft(a);
	}

	return a;
}
AVL *AvlDelete(AVL *a, int data)
{
	
	if (a == NULL)
		return NULL;
	if (data > a->data)
		a->right 	= AvlDelete(a->right, data);
	else if (data < a->data)
		a->left		= AvlDelete(a->left, data);

	if (data == a->data)
	{
		AVL *temp = a;
		if (a->left == NULL && a->right == NULL)
		{
			free(a);
			return NULL;
		}
		if (a->left != NULL)
		{
			AVL *iter = a->left;
			if (a->right != NULL)
			{
				a = a->right;
				AVL *iter2 = a;
				while (iter2->left != NULL)
					iter2 = iter2->left;
				iter2->left = iter;
			}
			else 
				a = iter;
		}
		else
		{
			a = a->right;
		}
		free(temp);
	}
	if(a == NULL)
		return NULL;
	a->height = 1 + max(height(a->left), height(a->right));

	int balance = getBalance(a);
	// Left Left Case	{R-Rotation}
	if (balance > 1)
	{
		if (getBalance(a->left) > 0)
			return AvlRotRight(a);
		a->left = AvlRotLeft(a->left);
		return AvlRotRight(a);
	}
	else if (balance < -1)
	{
		if (getBalance(a->right) < 0)
			return AvlRotRight(a);
		a->right = AvlRotRight(a->right);
		return AvlRotLeft(a);
	}

	return a;
}
void preOrder(AVL *root)
{
    if(root != NULL)
    {
        preOrder(root->left);
        preOrder(root->right);
        printf("%d ", root->data);
    }
	printf("\n");
}


void avlDisplayTree(AVL *root)
{
	int sayi	= root->height;
	int kare 	= 2;
	int *x = NULL, *z =NULL;
		while(--sayi > 0)
			kare *= 2;
	z = malloc(sizeof(int) * kare);
	x = malloc(sizeof(int) * kare);
	for(int i=0; i != kare; i++)
		x[i] = z[i] = 0;
	AVL *a1, *a2, *b1, *b2, *b3, *b4, *c1, *c2, *c3, *c4, *c5, *c6, *c7, *c8;
	int iter = kare;
	x[iter /2] = root->data; // {4}
	if (root->left)
	{
		a1 = root->left;
		x[iter/4] = a1->data; //8 {2}
		if (a1)
		{
			if(b1 = a1->left)
			x[iter/8] = b1->data; //4 {1}
			if(b2 = a1->right)
			x[iter/8+iter/4] = b2->data; //12 {3}
			if (b1)
			{
				if(c1 = b1->left)
				x[iter/16] = c1->data; //2 {1}
				if(c2 = b1->right)
				x[iter/16+iter/8] = c2->data; //6 {3}
			}
			if (b2)
			{
				if(c3 = b2->left)
				x[iter/16+iter/4] = c3->data; // 10
				if(c4 = b2->right)
				x[iter/2-iter/16] = c4->data; //14
			}
		}
		
	}
<<<<<<< HEAD
	if (root->right)
	{
		a2 = root->right;
		x[iter/4+iter/2] = a2->data; //24
		if (a2)
		{
			if(b3 = a2->left)
			x[iter/4+iter/2-iter/8] = b3->data;//20 {5}
			if(b4 = a2->right)
			x[iter/4+iter/2+iter/8] = b4->data;//28 {7}
			if (b3)
			{
				if(c5 = b3->left)
				x[iter/4+iter/2-iter/] = c5->data; //18 {9}
				if(c6 = b3->right)
				x[iter/16+iter/8+iter/2] = c6->data; //22 {11}
			}
			if (b4)
			{
				if(c7 = b4->left)
				x[iter/16+iter/4+iter/2] = c7->data; // 26 {13}
				if(c8 = b4->right)
				x[iter/2-iter/16+iter/2] = c8->data; // 30 {15}
			}
		}
=======
	
	for(int i=0; i < 20; i++){
		printf("%3d", x[i]);
		for(int x=0; x < 17; x++)
			printf("%5d", y[x]);
		printf("\n ");
>>>>>>> 2ec3a3b563aefa40e6317cb2e0e05bfba07fbb5e
	}


/* 
 *	32/2 = 16*1
 *	32/4 = 8*3	8+16
 *	32/8 = 4*3	 4*5	4*7	4+8
 *	32/16= 2	2+4;
 */

	int formul = kare;
	int temp = kare;
	int bol = 2;
	int renk = 1;
	do
	{
		formul /= bol;

		while (formul < kare)
		{
			z[formul] = x[formul];
			formul += temp;
		}
		formul = kare;
		temp /= 2;
		bol *= 2;
		
		if (renk != 2)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 237);
			renk = 2;
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 97);
			renk = 1;
		}

		for (int j = 0; j < kare; ++j)
		{
			z[j] == 0 ? printf("%3s", " ") : printf("%2s[%d]", "", z[j]);
			z[j] = 0;
		}
		
		printf("\n");
	} while (formul / bol >= 1);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("__________________________________________________________________________________________________________________\n");

}


int main()
{	
	
	AVL *root = NULL;
	// TEST Right-Left Case
	root = AvlInsert(root, 3);
	avlDisplayTree(root);
    root = AvlInsert(root, 2);
 	avlDisplayTree(root);
    root = AvlInsert(root, 10);
    avlDisplayTree(root);
	root = AvlInsert(root, 11);
	avlDisplayTree(root);
    root = AvlInsert(root, 7);
	avlDisplayTree(root);
    root = AvlInsert(root, 8);
	avlDisplayTree(root);
    root = AvlInsert(root, 5);
	avlDisplayTree(root);
	//preOrder(root);
	// TEST Right-Left Case

	free(root); root = NULL;
	root = AvlInsert(root, 10);
	root = AvlInsert(root, 20);
	root = AvlInsert(root, 30);
	root = AvlInsert(root, 40);
	root = AvlInsert(root, 50);
	root = AvlInsert(root, 25);

	avlDisplayTree(root);
	free(root); root = NULL;
	// TEST Left-Right Case
	root = AvlInsert(root, 10);
    root = AvlInsert(root, 15);
    root = AvlInsert(root, 6);
    root = AvlInsert(root, 5);
    root = AvlInsert(root, 8);
    root = AvlInsert(root, 9);
    root = AvlInsert(root, 7);
	//preOrder(root);
	avlDisplayTree(root);
	free(root); root = NULL;
	// TEST Left-Right Case
    root = AvlInsert(root, 9);
    root = AvlInsert(root, 5);
    root = AvlInsert(root, 10);
    root = AvlInsert(root, -1);
    root = AvlInsert(root, 6);
    root = AvlInsert(root, 11);
    root = AvlInsert(root, -2);
    root = AvlInsert(root, 1);
    root = AvlInsert(root, 2);
	avlDisplayTree(root);
	printf("\n");
	root = AvlDelete(root, 9);
	avlDisplayTree(root);
	return 0;
}
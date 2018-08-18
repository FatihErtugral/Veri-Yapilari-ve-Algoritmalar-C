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
 *	devreye girer. BST'de dengeyi düzelterek, amacı işlem karmaşıklığını "N log N" indirgemektir.
 *	Aşağıda bu sorun görsel olarak anlatılmak istenmiştir.
 * 
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
 * 	Bu bilgilerin, kaynak belirtilmeden paylaşılması yasaktır.
 **/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define Avlmax(a, b) (((a) > (b)) ? (a) : (b))

typedef struct _AVL{
	int data;
	int height;
	struct _AVL *left;
	struct _AVL *right;
} AVL;

int height(AVL * a)
{
	return a == NULL ? 0 : a->height;
}
//	--------------------------------------------------------------------------------------------------------------------
int getBalance(AVL * root)
{
	return root == NULL ? 0 : height(root->left) - height(root->right);
}
//	--------------------------------------------------------------------------------------------------------------------
AVL *AvlRotLeft(AVL *root)
{
	AVL *A = root;
	AVL *B = root->right;
	AVL *T1 = B->left;

	root = B;
	B->left = A;
	A->right = T1;

	A->height = 1 + Avlmax(height(A->left), height(A->right));
	root->height = 1 + Avlmax(height(root->left), height(root->right));
	return root;
}
//	--------------------------------------------------------------------------------------------------------------------
AVL *AvlRotRight(AVL *root)
{
	AVL *A = root;
	AVL *B = root->left;
	AVL *T1 = B->right;

	root = B;
	B->right = A;
	A->left = T1;

	A->height = 1 + Avlmax(height(A->left), height(A->right));
	root->height = 1 + Avlmax(height(root->left), height(root->right));
	return root;
}
//	--------------------------------------------------------------------------------------------------------------------
AVL *AvlInsert(AVL *root, int data)
{
	if (root == NULL)
	{
		root = (AVL *)malloc(sizeof(AVL));
		if(!root)
			return EXIT_SUCCESS;
		root->data = data;
		root->height = 1;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else if (data < root->data)
		root->left = AvlInsert(root->left, data);
	else if (data > root->data)
		root->right = AvlInsert(root->right, data);
	else
		return root;

	root->height = 1 + Avlmax(height(root->left), height(root->right));

	int balance = getBalance(root);

	if (balance > 1)
	{
		if (getBalance(root->left) > 0)
			return AvlRotRight(root);
		root->left = AvlRotLeft(root->left);
		return AvlRotRight(root);
	}
	else if (balance < -1)
	{
		if (getBalance(root->right) < 0)
			return AvlRotLeft(root);
		root->right = AvlRotRight(root->right);
		return AvlRotLeft(root);
	}

	return root;
}
//	--------------------------------------------------------------------------------------------------------------------
AVL *AvlDelete(AVL *root, int data)
{
	if (root == NULL)
		return NULL;
	if (data > root->data)
		root->right = AvlDelete(root->right, data);
	else if (data < root->data)
		root->left = AvlDelete(root->left, data);

	if (data == root->data)
	{
		AVL *temp = root;								// > Silinecek öğeyi geçici göstericiye al, işlem sonunda free()
		if (root->left == NULL && root->right == NULL)
		{
			free(root);
			return NULL;
		}
		if (root->left != NULL)						// > Root'un SOL kolu NULL değilse,
		{
			AVL *iter = root->left;					// > iter oluştur.
			if (root->right != NULL)				// > Root'un SAĞ koluda NULL değilse,
			{
				root = root->right;					// > Root'u SAĞ kolu yap.
				AVL *iter2 = root;					// > iter2 oluştur.
				while (iter2->left != NULL)			// > Şimdi iter2'nin en soluna inmeye çalışıyoruz.
					iter2 = iter2->left;
				iter2->left = iter;					// > iter2'nin en SOLUNA iter'i koy.
				iter2->height = 1 + Avlmax(height(iter2->left), height(iter2->right));	// Yükseklik ayarını tazele.
			}
			else									// > Root'un SAĞ kolu NULL ise, SOL kolunu Root yap.
				root = iter;
		}
		else										// > Root'un SOL kolu NULL ise, SAĞ kolunu Root yap.
			root = root->right;
		free(temp);									// > Hafızada çöp bırakma.
	}
	if (root == NULL)	//	Veri bulunmadıysa NULL dön.
		return NULL;
	//	YÜKSEKLİK AYARINI TAZELE
	//	--------------------------------------------------------------------------------------------------------------------
	root->height = 1 + Avlmax(height(root->left), height(root->right));
	//	DENGESİZLİK KONTROL
	//	--------------------------------------------------------------------------------------------------------------------
	int balance = getBalance(root);
	//	DURUM KONTROL
	//	--------------------------------------------------------------------------------------------------------------------
	if (balance > 1)
	{
		/*	--------------------------------------------------------------------------------------------------------------------
		 *	• Sol - Sol Durumu{Left-Left Case}	->	Sağa döndür			->		{R-Rotation}
		 *	--------------------------------------------------------------------------------------------------------------------
		 *	(Sol - Sağ) pozitifse SOL->SOL durumu, SAĞA bir tur döndürülür.
		 *	--------------------------------------------------------------------------------------------------------------------*/
		if (getBalance(root->left) > 0)
			return AvlRotRight(root);
		/*	--------------------------------------------------------------------------------------------------------------------
		 *	• Sol - Sağ Durumu{Left-Right Case}	->	Sola döndür, Sağa döndür ->	{L-Rotation | R-Rotation}
		 *	--------------------------------------------------------------------------------------------------------------------
		 *	Yukardaki kontrol olumsuzsa, SOL->SAĞ durumu, rootun SOL kolunu: SOLA bir tur döndürülür, ardından root SAĞA döndürülür.
		 *	--------------------------------------------------------------------------------------------------------------------*/
		root->left = AvlRotLeft(root->left);
		return AvlRotRight(root);
	}
	else if (balance < -1)
	{
		/*	--------------------------------------------------------------------------------------------------------------------
		 *	• Sağ - Sağ Durumu{Right-Right Case} ->	Sola döndür			->		{L-Rotation}
		 *	--------------------------------------------------------------------------------------------------------------------
		 *	(Sol - Sağ) negatifse SAĞ->SAĞ durumu, SOLA bir tur döndürülür.
		 *	--------------------------------------------------------------------------------------------------------------------*/
		if (getBalance(root->right) < 0)
			return AvlRotLeft(root);
		/*	--------------------------------------------------------------------------------------------------------------------
		 *	• Sağ - Sol Durumu{Right-Left Case}	->	Sağa döndür, Sola döndür ->	{R-Rotation | L-Rotation}
		 *	--------------------------------------------------------------------------------------------------------------------
		 *	Yukardaki kontrol olumsuzsa, SAĞ->SOL durumu, rootun SAĞ kolunu: SOLA bir tur döndürülür, ardından root SOLA döndürülür.
		 *	--------------------------------------------------------------------------------------------------------------------*/		
		root->right = AvlRotRight(root->right);
		return AvlRotLeft(root);
	}

	return root;
}
//	--------------------------------------------------------------------------------------------------------------------
void preOrder(AVL *root)
{
	if (root != NULL)
	{
		preOrder(root->left);
		preOrder(root->right);
		printf("%d ", root->data);
	}
}
int main()
{	
	
	AVL *root = NULL;
	// TEST Right-Left Case
	root = AvlInsert(root, 3);
    root = AvlInsert(root, 2);
    root = AvlInsert(root, 10);
	root = AvlInsert(root, 11);
    root = AvlInsert(root, 7);
    root = AvlInsert(root, 8);
    root = AvlInsert(root, 5);
	preOrder(root);
	printf("\n");
	// TEST Right-Left Case end

	free(root); root = NULL;
	root = AvlInsert(root, 10);
	root = AvlInsert(root, 20);
	root = AvlInsert(root, 30);
	root = AvlInsert(root, 40);
	root = AvlInsert(root, 50);
	root = AvlInsert(root, 25);
	preOrder(root);
	printf("\n");

	// TEST Left-Right Case
	free(root); root = NULL;
	root = AvlInsert(root, 10);
    root = AvlInsert(root, 15);
    root = AvlInsert(root, 6);
    root = AvlInsert(root, 5);
    root = AvlInsert(root, 8);
    root = AvlInsert(root, 9);
    root = AvlInsert(root, 7);
	preOrder(root);
	printf("\n");
	// TEST Left-Right Case end

	free(root); root = NULL;
    root = AvlInsert(root, 9);
    root = AvlInsert(root, 5);
    root = AvlInsert(root, 10);
    root = AvlInsert(root, -1);
    root = AvlInsert(root, 6);
    root = AvlInsert(root, 11);
    root = AvlInsert(root, -2);
    root = AvlInsert(root, 1);
    root = AvlInsert(root, 2);
	root = AvlDelete(root, 9);
	printf("\n");
	preOrder(root);
	return 0;
}

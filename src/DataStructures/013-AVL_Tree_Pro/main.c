/**	
 * 	Title:	AVL TREE[Adelson-Velsky ve E.M. Landis]
 *	Author:	Fatih Ertuğral.
 *	Created on Aug 11, 2018, 5:41 PM
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
#include <stdlib.h>		// Dinamik hafıza için kullanıldı
#include <windows.h>	// Konsol renklendirmek için kullanıldı
#include <math.h> 		// Kare almak için kullanıldı

#define Avlmax(a, b) (((a) > (b)) ? (a) : (b))

typedef struct _AVL
{
	int key;
	int height;
	struct _AVL *left;
	struct _AVL *right;
} AVL;

AVL 		*AvlInsert(AVL *root, int key); 		// Ağaca key ekler.
AVL 		*AvlDelete(AVL *root, int key); 		// Ağaçtan key siler.	
void 		AvlTreeDisplay(AVL *root);				// Agacı ekrana basar.
long long 	NumaratikGiris(int size, char *mesaj);	// Rakamlar dışında girişleri engeller.

//--------------------------------------------------------------------------------------------------------------------
int main()
{
	
	// Screen size
	HWND hWnd;
  	SetConsoleTitle("AVL Tree | author: Fatih Ertgural");
   	hWnd 			= FindWindow(NULL, "AVL Tree | author: Fatih Ertgural");
    HANDLE hOut 	= GetStdHandle(STD_OUTPUT_HANDLE);
    COORD NewSBSize = GetLargestConsoleWindowSize(hOut);
    SMALL_RECT DisplayArea = {0, 0, 0, 0};

    //SetConsoleScreenBufferSize(hOut, NewSBSize); // scrooll set

    DisplayArea.Right 	= NewSBSize.X - 1;
    DisplayArea.Bottom 	= NewSBSize.Y - 1;

    SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);

    ShowWindow(hWnd, SW_MAXIMIZE);
	// Screen size end
	
	// Dialog
	
	AVL *root = NULL;
	int number, secim;
	SECTIR:
	secim = 0;
	printf("Ekle: 1 | Sil: 2 | HafizayiBosalt: 3 | Cikis: 4   ..? : ");
	scanf("%d", &secim);
	fflush(stdin);
	if(secim == 1 || secim == 2 || secim == 3 || secim == 4)
	{
		
	switch (secim)
	{
		case 1: 
			number = NumaratikGiris(4, "Eklenecek sayiyi giriniz : ");
			root = AvlInsert(root, number);
			AvlTreeDisplay(root);	
			break;
		case 2:
			number = NumaratikGiris(4, "Silinecek sayiyi giriniz : ");
			root = AvlDelete(root, number);
			AvlTreeDisplay(root);
			break;
		case 3:
			free(root);
			printf("Hafizayi bosalttiniz..\n");
			root = NULL;
			break;
		case 4:
			free(root);
			return 0;
			break;
	
		default:
			printf("Yanlis secim yaptiniz!Tekrar Deneyiniz\n"); 
			Sleep(1000);
			break;
	}
	}
	else
		{
		printf("Yanlis secim yaptiniz!Tekrar Deneyiniz\n"); Sleep(1000);
		}
	goto SECTIR;
	// Dialog end
	return 0;
}
//--------------------------------------------------------------------------------------------------------------------
int height(AVL * a)
{
	return a == NULL ? 0 : a->height;
}
//--------------------------------------------------------------------------------------------------------------------
int getBalance(AVL * root)
{
	return root == NULL ? 0 : height(root->left) - height(root->right);
}
// Sola döndür
//--------------------------------------------------------------------------------------------------------------------
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
// Sağa döndür
//--------------------------------------------------------------------------------------------------------------------
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
//--------------------------------------------------------------------------------------------------------------------
AVL *AvlInsert(AVL *root, int key)
{
	if (root == NULL)
	{
		root = (AVL *)malloc(sizeof(AVL));
		if(!root)
			return EXIT_SUCCESS;
		root->key = key;
		root->height = 1;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else if (key < root->key)
		root->left = AvlInsert(root->left, key);
	else if (key > root->key)
		root->right = AvlInsert(root->right, key);
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
//--------------------------------------------------------------------------------------------------------------------
AVL *AvlDelete(AVL *root, int key)
{
	if (root == NULL)
		return NULL;
	if (key > root->key)
		root->right = AvlDelete(root->right, key);
	else if (key < root->key)
		root->left = AvlDelete(root->left, key);

	if (key == root->key)
	{
		AVL *temp = root;							// > Silinecek öğeyi geçici göstericiye al, işlem sonunda free()
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
//--------------------------------------------------------------------------------------------------------------------
void AgaciDiziyeYerlestir(AVL *root, int *x)
{
	AVL *iter 			= root;												// Gezici
	int AgacYuksekligi	= root->height;										// Agacin yuksekligi
	int AgacDiziBoyu	= pow(2, AgacYuksekligi);							// Dizi kordinati icin hesaplaniyor
	int islemBool		= AgacYuksekligi-3; 								// [1] [0]	ikilik sistemde kaç bit okunacak
	int *boolean		= (int *)malloc(sizeof(int) * (AgacYuksekligi));	// Onluk sayiyi Ikili sayiya cevrilmis halini tut
	int DerinlikBolucu	= pow(2, AgacYuksekligi);							// Dizi kordinati icin hesaplaniyor
	int y				= -1;						// Asagidaki aciklamada 1,3,5,7... diye carpan sayisi
	int bonus 			= 0;						// Yukseklik 2 den buyukse girilen derinligi gore kordinat ayari
	int DerinlikteIslem;							// Derinlik isleminde donguleri optimize etmek icin gecici degisken
	int tempIslemBool;								// 
	int hata;										// iter gezerken NULL görürse hata olarak kayit edilip dizi içince -1454 özel rakam yazılır
	int binaryTemp;									// ikili sayiya cevirici icin gecici degisken
	////////////////////////////////////////////
	/*	FORMUL ACIKLAMASI:	
	 *	
	 *	Agac uzerine biraz dusundukten sonra, asagidaki formuller yakalndi.
	 *	Isin zor kismi dizi kordinatlarini yerlestirmekti.
	 *	Adimlar ikili sayi olarak kodlandi:
	 *	2^4 = 2 * 2 * 2* 2;
	 *	1 1 | *3 | L-L	Array[2^4 / 2^4	* 1]	Array[1]	Array[2²/2² * 3]	Array[3]	
	 *	1 0 | *2 | L-R	Array[2^4 / 2^4 * 5]	Array[5]	Array[2²/2² * 7]	Array[7]
	 * 	0 1 | *1 | R-L	Array[2^4 / 2^4 * 9]	Array[9]	Array[2²/2² * 11]	Array[11]
	 *  0 0 | *0 | R-R	Array[2^4 / 2^4 * 13]	Array[13]	Array[2²/2² * 15]	Array[15]
	 * 	
	 * 	1 | | L			Array[2^4 / 2³ * 1]		Array[2]	Array[2² / 2 * 3]	Array[6]
	 *	0 | | R 		Array[2^4 / 2³ * 5]		Array[10]	Array[2² / 2 * 7]	Array[14]
	 *   
	 * 
	 *                                                                 	Height
	 *                             [8]                                   	4		2¹
	 *             [4]                               [12]                	3		2²
	 *     [2]             [6]             [10]                [14]      	2		2³
	 * [1]     [3]     [5]     [7]     [9]      [11]      [13]      [15]	1		2^4
	 * 
	 * [1] [2] [3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15]  -> Array Dizilis
	 */
	////////////////////////////////////////////
	// agac yuksekligi 2 ise, iter'i gezdirmeye gerek yok, sağ ve sola bakıp, veriler diziye yerleştirilir.
	if(AgacYuksekligi > 2) 
	{
		DerinlikBolucu = pow(2, AgacYuksekligi)/2;
		do{
			DerinlikteIslem = DerinlikBolucu / 2 -1;
			hata 			= 0;
			tempIslemBool 	= islemBool;
			y = -1; //çarpan sayisi
			do
			{
				binaryTemp = DerinlikteIslem;
				
				for(int i = 0; i < AgacYuksekligi; i++)	// ikili taban hafizasini 0 ile doldur. Bir nevi reset.
				{
					boolean[i] = 0;
				}
				for (int i = 0; binaryTemp >= 1; i++)	//	ikili tabana çevir
				{
					boolean[i] = (binaryTemp % 2) ? 1 : 0;
					binaryTemp /= 2;
				}
				
				while(tempIslemBool > -1) // tempislemBool değeri, okunacak bit sayisini belirliyor.
					{
						//Agac uzerindeki gezinme yukaridan alinan bit degerleriyle saglanir.
						if(boolean[tempIslemBool] == 0)	// ikili sistemde bit 0 ise, iter bir saga kaydirilir.
							if(iter->right != NULL)
								iter = iter->right;
							else
								hata = 1;
						if(boolean[tempIslemBool] == 1)	// ikili sistemde bit 1 ise, iter bir sola kaydirilir.
							if(iter->left != NULL)
								iter = iter->left;
							else
								hata = 1;
						tempIslemBool--;
					}

				y+=2;
				// Dizinin indis kordinatları hesaplanıyor, iter'in içinde değer yoksa "-1454" sayisi yerleştiriliyor. 
				// AvlTreeDisplay fonksiyonunda -1454 saiyisi "[--]" karakterini ekrana basmamızı sağlıyor.
				// iter'in içinde değer varsa kordinattaki dizi adresine yerleştiriliyor.
				x[((AgacDiziBoyu / (DerinlikBolucu *2)) * y)] = (hata == 1)? -1454 : (iter->left != NULL)?	iter->left->key : -1454;
				y+=2;
				x[((AgacDiziBoyu / (DerinlikBolucu *2)) * y)] = (hata == 1)? -1454 : (iter->right != NULL)?	iter->right->key : -1454;
				
				tempIslemBool 	= islemBool;
				hata 			= 0;
				iter 			= root;		// Gezici sifirlanir.
				DerinlikteIslem--;			// ikili sistemde kodlanicak sayiyi 0 olana kadar azaltir, iter bu sayinin ikili koduna gore left right yapar
			}while(DerinlikteIslem > -1 );
				islemBool--; 				// iterin gezdirilme katı, yüksekliği, kontrol edilecek bit sayısı..
				DerinlikBolucu /=2;			// dizi çarpanını ayarla
				bonus++;					// en derinden yukarı doğru çıkınca dizi katmanını, dizi indisi için optimize edecek sayi.
		}while(DerinlikBolucu > 2);
			y = -1;
		DerinlikBolucu = pow(2,AgacYuksekligi-bonus); // Dizi indisi için optimize ediliyor.
	}
	// Agacın atadan sonraki çocuklarına, iteri gezdirmeden müdahele ediliyor
	y+=2;
	x[AgacDiziBoyu / DerinlikBolucu * y] = (iter->left == NULL)? -1454	: (iter->left->key);
	y+=2;
	x[AgacDiziBoyu / DerinlikBolucu * y] = (iter->right == NULL)? -1454 : (iter->right->key);
	free(boolean);
	return ;
}
//--------------------------------------------------------------------------------------------------------------------
void AvlTreeDisplay(AVL *root)
{
	if(root == NULL)
	{
		printf("Agac Bos..\n");
		return ;
	}

    int *ekran, *dizgiliAgac;
	int iter;
	int sayi = root->height;
	int kare = 2;

	while (--sayi > 0)	// 2^n
		kare *= 2;

	dizgiliAgac	= (int *)malloc(sizeof(int) * kare);
	ekran 		= (int *)malloc(sizeof(int) * kare);

	for (int i = 0; i != kare; i++)
		ekran[i] = dizgiliAgac[i] = -1453;	// Bu deger, ekrana basilan agacin arkaplanini olusruyor
	
	iter = kare;

    dizgiliAgac[iter / 2] = root->key; 	// Kok deger burada yerlestiriliyor.
    if(root->height > 1)
		AgaciDiziyeYerlestir(root, dizgiliAgac);
//--------------------------------------------------------------------------------------------------------------------
	// Array print..
	int formul	= kare;
	int temp	= kare;
	int bol		= 2;
	int space	= 1;
	do
	{
		formul /= bol;	// 2^n -> 2³ -> 2² -> 2¹

		while (formul < kare) // 2^n -> 2³ -> 2² -> 2¹
		{
			ekran[formul] = dizgiliAgac[formul];
			formul 		+= temp;
		}
		formul	= kare;
		temp 	/= 2;
		bol 	*= 2;

		for (int j = 0; j < kare; ++j)
		{
			if(ekran[j] == -1453) // Backgraound
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 231);	// tree background color
				(space == 0) ? printf("%4s","") : printf("%c%c%c%c", 223, 223 ,223,223); 
			}
			else if(ekran[j] == -1454) // NULL
			{
				printf("[--]");
				(space == 0) ? (space = 1) : (space = 0);
			}
			else	// TEXT
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 64); // tree text color
				printf("[%d]", ekran[j]);
				(space == 0) ? (space = 1) : (space = 0);
			}
			ekran[j] = -1453;	
		}
		printf("\n");
	} while (formul / bol >= 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // windows console color
	
	for(int u=kare; u > 0; u--)
		printf("----");
	printf("\n");
	free(ekran);
	free(dizgiliAgac);
	return ;
}
//--------------------------------------------------------------------------------------------------------------------
long long NumaratikGiris(int size, char *mesaj){
    long long rvalue;
    char *giris;
    int flag;
    
    do
    {
        flag = 0;
        giris = (char *)malloc(sizeof(char) * (size+1));
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // windows console text color
        printf("%s", mesaj);
        fgets(giris, (size+1), stdin);	// stdin klavyeden girilen karakterlerin kayıt edildiği dosyadir
										// fgets ile belirtilen boyut kadar stdin'den karakter okunur, diziye yerleştirilir.
        fflush(stdin);					// fflus bu stdin dosyasını temizler 
        for(int i=0; size > i && giris[0] != '\0' && giris[i] != '\n'; i++)
        {
			// 48 - 57 arası ASCII taplosunda rakamları, 45 ise - işaretini temsil eder
            if(!(giris[i] >= 48 && giris[i] <= 57 || giris[i] == 45))	
            {
                flag = 1; 
                break;
            }
        }
        if(flag == 1)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); // windows console text color
            printf("UYARI: Lutfen 0 ile 9 arasinda rakamlar kullaniniz!\n");
            printf("UYARI: Giridiniz sayi en fazla %d basamakli olabilir!\n\n", size);
            free(giris); fflush(stdin);
        }
    }while(flag == 1);
    rvalue = atoll(giris);
	free(giris);
    return rvalue;
}
//--------------------------------------------------------------------------------------------------------------------

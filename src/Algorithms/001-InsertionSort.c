/**	
 *	Author:	Fatih Ertuğral.
 *	Created on Aug 26, 2018, 2:13 AM
 *	Algoritma	: Sokarak Sıralama
 *	İngilizcesi	: Insertion Sort
 *	Kararlılık	: Evet
 *	Yöntem		: Sokma 
 *	Açıklama	: 
 *	{55,| 45, 98, 4, 12, -1, 0, 4, 28, 22}  //  | 'çizginin' sağındaki rakamla solundakini karşılaştırıp
 *	{45, 55,| 98, 4, 12, -1, 0, 4, 28, 22}	// küçükse yer değiştirip çizgiyi bir adım ilerletir.
 *	{45, 55, 98,| 4, 12, -1, 0, 4, 28, 22}	//  | 'çizginin' sağındaki rakamla solundakini karşılaştırıp
 *	{4, 45, 55, 98,| 12, -1, 0, 4, 28, 22}	// küçük değilse işlem yapmadan çizgiyi bir adım ilerletir.
 *	{4, 12, 45, 55, 98,| -1, 0, 4, 28, 22}	//  | 'çizginin' sağındaki rakam solundakinden küçük
 *                                         	// sağdaki rakamı geçici değişkene (temp) alarak, soldaki rakamı sağa yerleştirir.
 *                                         	// bir sonraki rakamla, tempi karşılaştırır küçükse kaydırma işlemi devam eder
 *                                         	// küçük değilse rakamı karşılaştırdığı rakamın soluna yerleştirir.
 *                                         	// Dikkat edilmesi gereken nokta, elindeki rakamla soldaki rakamları kaşılaştırırken,
 *                                         	// temp'teki rakamı araya sokmak için soldaki rakamları sağa bir adım kaydırır.
 *                                         	// Aşağıda bu durum açıklanmaya çalışılmıştır.
 *                                         	// {4, 12, 45, 55, 98,| -1, 0, 4, 28, 22}  temp = -1;
 *                                         	// {[ ], 4, 12, 45, 55,| 98, 0, 4, 28, 22}  
 *                                         	//   ↑->araya sokmak için açılan boşluk.
 *                                         	//
 *                                         	// {-1, 4, 12, 45, 55, 98,| 0, 4, 28, 22}
 *	{-1, 4, 12, 45, 55, 98,| 0, 4, 28, 22}
 *	{-1, 0, 4, 12, 45, 55, 98,| 4, 28, 22}
 *	{-1, 0, 4, 4, 12, 45, 55, 98,| 28, 22}
 *	{-1, 0, 4, 4, 12, 28, 45, 55, 98,| 22}
 *	{-1, 0, 4, 4, 12, 22, 28, 45, 55, 98|}
 * 
 *
 *	■ Algoritma Hızı ■
 *	  • Ω En iyi 	: n
 *	  • Θ Ortalama	: d+n
 *	  • O En Kötü	: n²
 *	  • Açıklama	: d yer değiştirme sayısıdır ve n² cinsindendir.
 *	■ Hafıza Karmaşıklığı ■
 *
 **/
#include <stdio.h>

#define A_SIZE 10

void InsertionSort(int arr[], int size);

int main(int argc, char *argv[]) 
{
	int arr[A_SIZE] = {55, 45, 98, 4, 12, -1, 0, 4, 28, 22};
	
	InsertionSort(arr, A_SIZE);
	for(int i=0; i<A_SIZE; i++)
		printf("%d, ", arr[i]);
	getchar();
	
	return 0;
}

void InsertionSort(int arr[], int size)
{
	int temp, swap, iter;
	for(iter = 0; ++iter < size; )
	{
		temp = arr[iter];
		swap = iter;
		while(temp < arr[swap -1])
		{
			arr[swap] = arr[swap-1];
			if(--swap <= 0)	break;
		}
		arr[swap] = temp;
	}
}
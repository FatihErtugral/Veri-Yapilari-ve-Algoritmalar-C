/**	
 *	Author:	Fatih Ertuğral.
 *	Created on Aug 26, 2018, 2:13 AM
 *	Algoritma	: Kabarcık Sıralaması (Boloncuk Sıralamsı)
 *	İngilizcesi	: Bubble Sort
 *	Kararlılığı	: Evet
 *	Yöntem		: Yer değiştirme
 *
 *
 *	■ Algoritma Hızı ■
 *	  • Ω En iyi 	: n
 *	  • Θ Ortalama	: n²
 *	  • O En Kötü	: n²
 *	  • Açıklama	: Dizi içersindeki rakamlar üzerinde her seferinde yan yana iki rakamı
 *		karşılaştırarak ilerleyen bir gözlemci varmış gibi düşünülebilir. Karşılaştırma 
 *		sırasında sağdaki soldakinden büyükse yer değiştirilir değilse işlem yapılmaz ve
 *		gözlemci bir adım ilerleyerek yeniden karşılaştırma yapar.
 *		En büyük rakam baloncuk gibi rakamlar arasından en üste çıkmış olur,  
 *		sonrasında bir adım geriden karşılaştırma yaparak diziyi sıralamış oluruz.		
 *	■ Yapılan iyileştirmeler ■
 *	  {98, 55, 45, 28, 22, 4, 4, 0, -1, 12}
 *	  12 rakamının gireceği indis numarası [5] ' tir, 5. indisten sola doğru olan kısım
 *	  senaryomuzda sıralıdır ve o kısımı kontrol etmekle vakit kaybetmemek adına, 
 * 	  "kontrol ettiğimiz rakam sıralı kısıma girmediği sürece" yani küçük olmadığı sürece, 
 * 	  yeni kontrollere sıralı kısımın son indisinden başlanarak iki yönlü daraltabiliriz. 
 * 	  Not: Algoritma en küçüğü sağa yerleştiriyor.(dizi sonu) 
 *         iyileştirme sonucu değerler hesaplanmamıştır.Standart bubble sort değerleridir.
 *
 *	■ Hafıza Karmaşıklığı ■
 *
 **/
#include <stdio.h>
#include <stdlib.h>

#define A_SIZE 10

void BubbleSort(int arr[], int size);

int main(int argc, char *argv[]) 
{
	//int arr[A_SIZE] = {55, 45, 98, 4, 12, -1, 0, 4, 28, 22};
	int arr[A_SIZE] = {98, 55, 45, 28, 22, 4, 4, 0, 11, 12};
	//int arr[A_SIZE] = {1, 2, 3, 4, 99, 20, 10, 11, 13, 12, 15};
	
	BubbleSort(arr, A_SIZE);
	for(int i=0; i<A_SIZE; i++)
		printf("%d, ", arr[i]);
	getchar();
	
	return 0;
}
void BubbleSort(int arr[], int size)
{
	int temp, flag, siraliKisim, i;
	
	flag = siraliKisim = 1;
	while(--size > 0)
	{
		(siraliKisim <= 0) ? i=0 : (i = --siraliKisim);
		while(i < size)
		{
			if(arr[i] < arr[i+1])
			{
				temp 	= arr[i+1];
				arr[i+1]= arr[i];
				arr[i]	= temp;
				flag	= 0;
			}
			i++;
			if(flag && i > 0)
				siraliKisim = i; // iyileştirme 1
		}
		if(flag) // iyileştirme 2
			break;
		flag = 1;
	}
}
/**	
 * 	Title:	[]
 *	Author:	Fatih Ertuğral.
 *	Created on July 11, 2018, 9:55 PM
 *	Algoritma	: Seçerek Sıralama
 *	İngilizcesi	: Selection Sort
 *	Kararlılı	: Kararsız
 *	Yöntem		: Seçerek
 *	Açıklama	: Listedeki en küçüğü bulup baştaki sayıyla yer değiştiriyor,
 *				  birinci elemanı sabitliyor. İkinci en küçük sayıyı buluyor,
 *				  ikinci eleamnı da sabitliyor. Bu şekilde çalışıyor.
 *
 *	■ Algoritma Hızı ■
 *	  • Ω En iyi 	: n²
 *	  • Θ Ortalama	: n²
 *	  • O En Kötü	: n²
 *
 *	■ Hafıza Karmaşıklığı ■
 *
 **/
#include <stdio.h>
#include <stdlib.h>

#define A_SIZE 10

void SelectionSort(int arr[], int size);

int main(int argc, char *argv[]) 
{
	int arr[A_SIZE] = {55, 45, 98, 4, 12, -1, 0, 4, 28, 22};
	
	SelectionSort(arr, A_SIZE);
	for(int i=0; i<A_SIZE; i++)
		printf("%d ,", arr[i]);
	getchar();
	
	return 0;
}
void SelectionSort(int arr[], int size)
{
	int temp, min;
	int n = size;

	for(int i = 0; i<n; i++)
	{
		min = i;
		for(int k = i+1; k<n; k++)
			if(arr[min] > arr[k])
				min = k;
		// swap		
		temp	= arr[i];
		arr[i]	= arr[min];
		arr[min]= temp;
	}
	return ;
}
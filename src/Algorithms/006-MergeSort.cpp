/**	
 *	Author:	Fatih Ertuğral.
 *	Created on Aug 26, 2018, 2:13 AM
 *	Algoritma	: Birleştirme Sıralaması
 *	İngilizcesi	: Merge Sort
 *	Kararlılığı	: Kararlı
 *	Yöntem		: Parçala Fethet
 *
 *
 *	■ Algoritma Hızı ■
 *	  • Ω En iyi 	: n²
 *	  • Θ Ortalama	: 
 *	  • O En Kötü	: 
 *	  • Açıklama	: -
 *	■ Hafıza Karmaşıklığı ■
 *
 **/

// GELENEKSEL ÇOĞU SİTEDE PAYLAŞILAN MERGE SORT ALGORİTMASI (Yorum Satırında olan)
// BİR GRUP SAYININ TOPLAMI TEK İSE CİDDİ PERFORMANS KAYIPRLARI YAŞANIYOR
// BİR ALTTA YAZILI OLAN MERGE SORT ALGORİTMASI KAT KAT DAHA HIZLI
// visual studio ile test edebilirsiniz.

////////////////////////////////////////////////////////////
//void merge(int arr[], int left, int mid, int right)
//{
//	int i, j, k;
//	int n1 = mid - left + 1;
//	int n2 = right - mid;
//
//	/* create temp arrays */
//	int *L, *R;
//	L = (int *)malloc(sizeof(int)*n1);
//	R = (int *)malloc(sizeof(int)*n2);
//
//
//
//	/* Copy data to temp arrays L[] and R[] */
//	for (i = 0; i < n1; i++)
//		L[i] = arr[left + i];
//	for (j = 0; j < n2; j++)
//		R[j] = arr[mid + 1 + j];
//
//	/* Merge the temp arrays back into arr[l..r]*/
//	i = 0; // Initial index of first subarray 
//	j = 0; // Initial index of second subarray 
//	k = left; // Initial index of merged subarray 
//	while (i < n1 && j < n2)
//	{
//		if (L[i] <= R[j])
//		{
//			arr[k] = L[i];
//			i++;
//		}
//		else
//		{
//			arr[k] = R[j];
//			j++;
//		}
//		k++;
//	}
//
//	/* Copy the remaining elements of L[], if there
//	   are any */
//	while (i < n1)
//	{
//		arr[k] = L[i];
//		i++;
//		k++;
//	}
//
//	/* Copy the remaining elements of R[], if there
//	   are any */
//	while (j < n2)
//	{
//		arr[k] = R[j];
//		j++;
//		k++;
//	}
//	free(L);
//	free(R);
//}
//
///* l is for left index and r is right index of the
//   sub-array of arr to be sorted */
//void mergeSort(int arr[], int left, int right)
//{
//	if (left < right)
//	{
//		// Same as (l+r)/2, but avoids overflow for 
//		// large l and h 
//		int mid = left + (right - left) / 2;
//
//		// Sort first and second halves 
//		mergeSort(arr, left, mid);
//		mergeSort(arr, mid + 1, right);
//
//		merge(arr, left, mid, right);
//	}
//}
//




#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int A[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", A[i]);

	printf("\n");
}


void MergeSort(int *arr, int size)
{
	if (size <= 1)
		return;
	int *tampon, *temp;
	int kat, son, sayacAna, sayacSol, sayacSag, gozSol, gozSag;

	tampon = (int *)malloc(size * sizeof(int));
	if (tampon == NULL)
	{
		printf("Ram'de yeterli hafiza ayrilamadi.");
		exit(EXIT_SUCCESS);
	}
	kat = 1;

	do
	{
		son = size;
		sayacAna = gozSol = 0;
		gozSag = kat;
		do
		{
			son -= sayacSol = (son >= kat) ? kat : son;
			son -= sayacSag = (son >= kat) ? kat : son;
			while (sayacSag > 0 && sayacSol > 0)
			{
				if (arr[gozSol] < arr[gozSag])
				{
					tampon[sayacAna++] = arr[gozSol++];
					sayacSol--;
				}
				else
				{
					tampon[sayacAna++] = arr[gozSag++];
					sayacSag--;
				}
			}
			while (--sayacSol >= 0)
				tampon[sayacAna++] = arr[gozSol++];
			while (--sayacSag >= 0)
				tampon[sayacAna++] = arr[gozSag++];
			gozSol += kat;
			gozSag += kat;
		} while (son > 0);
		temp = arr;
		arr = tampon;
		tampon = temp;
		kat *= 2;
	} while (kat < size);
	free(tampon);
}
/* Driver program to test above functions */
int main()
{
	int size2 = 9999999; // Dizi boyutu
	int *arr2 = (int *)malloc(sizeof(int)*size2); // Dinamik olarak ayrılan dizi 
	
	srand(time(NULL));
	for (int i = 0; i < size2; i++) // Diziye rastgele sayılar yerleştiriliyor
	{
		arr2[i] = rand() % 1000000 + 1;
	}
	printf("\nSayilar hazir is \n");
	MergeSort(arr2, size2);
	printf("\nSayilar Siralandi \n");
	printArray(arr2, size2);
	
	//int arr[] = { 45, 4, 12, 56, 87, -6, 0, 587, -56, 4 };
	//int arr_size = sizeof(arr) / sizeof(arr[0]);

	//printf("Given array is \n");
	//printArray(arr, arr_size);
	//mergeSort(arr, 0, arr_size - 1);
	//printArray(arr, arr_size);
	
	
	//mergeSort(arr2, 0, size2 - 1);
	//printArray(arr2, size2);
	
	return 0;
}


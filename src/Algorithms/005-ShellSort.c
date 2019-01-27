/**	
 *	Author:	Fatih Ertuğral.
 *	Created on Aug 27, 2018, 1:13 AM
 *	Algoritma	: Shell Sırlama
 *	İngilizcesi	: Shell Sort
 *	Kararlılığı	: Kararsız
 *	Yöntem		: Parçala Fethet
 *  Açıklama	: https://www.youtube.com/watch?v=CmPA7zE8mx0
 *
 *
 *	■ Algoritma Hızı ■
 *	  • Ω En iyi 	: O(n log n)
 *	  • Θ Ortalama	: O(n^1.25)†  
 *	  • O En Kötü	: O(n^1.5)
 *	  • Açıklama	: -
 *	■ Hafıza Karmaşıklığı ■
 *	  • O(1)
 **/
#include <stdio.h>
#include <string.h>

void ShellSort(int arr[], int size);

int main()
{
	int arr[] = {5, 15, -5, 8, 22, 31,7,0,13,21,20};
	
	ShellSort(arr, 11);
	for(int i=0; i<11;i++)
	printf("%d ", arr[i]);
	return 0;
}
void ShellSort(int arr[], int size)
{
	int sSize,i, k, temp;
	sSize = size;
	while(sSize > 1)
	{
		sSize /=2;
		for(i = sSize -1; ++i < size;)
		{
			temp = arr[i];
			for(k = i;arr[k - sSize] > temp;)
			{
				arr[k] = arr[k - sSize];
				
				k -= sSize;
				if(k - sSize < 0)
					break;
			}
			arr[k] = temp;
		}
	}
}

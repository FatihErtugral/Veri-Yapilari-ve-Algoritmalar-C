/**	
 *	Author:	Fatih Ertuğral.
 *	Created on Aug 26, 2018, 22:30 PM
 *	Algoritma	: Sayarak Siralama
 *	İngilizcesi	: Coiting Sort
 *	Kararlılığı	: Kararsız
 *	Yöntem		: Sayarak
 *
 *
 *	■ Algoritma Hızı ■
 *	  • Ω En iyi 	: O ( n + k )
 *	  • Θ Ortalama	: O ( n + k )
 *	  • O En Kötü	: O ( n + k )
 *	  • Açıklama	: k ikinci dizinin boyutu.
 *	■ Hafıza Karmaşıklığı ■
 *	2n+k
 **/
#include <stdio.h>
#include <string.h>

#define A_SIZE 255 // ascii tablosu baz alınmıştır

void CountingSort(char arr[]);

int main(int argc, char *argv[]) 
{
	char arr[] = "fatih ertugral 12353242"; // string oluşturuluyor. 
 
    CountingSort(arr);
 
    printf("Sirali Karakter Dizisi: %s\n", arr);
	
	getchar();
	return 0;
}
void CountingSort(char arr[])
{
	// verilen string dizi boyutunda ikinci bir dizi oluşturuyor
	int aSize = strlen(arr);
	char output[aSize];
	
	// karakterleri asci tablodan işlemek için int türünde dizi oluşturuyor
	int count[A_SIZE + 1], i;
	
	// 256 indisli dizinin indislerine 0 yerleştiriliyor
	memset(count, 0, sizeof(count));
	
	// string içindeki \0 karakterine görene kadar döngü çalışıyor
	// arr[i] ifadesi count içerisinde karakteri tamsayı türünden temsil değiyor.
	// mesela indis içinde 'f' harfi var ise ascii tablosundan 102 decimal sayısını temsil ediyor
	// ++count[102] ifadesi aslında içinde 0 olan indisin bir arttırılması anlamına geliyor
	// böylece 'f' harfini her okuyuşunda 102 nolu indis bir arttırılıp, 
	// string içerindeki bütün f ler sayılmış oluyor.
	for(i = 0; arr[i]; i++)
		++count[arr[i]];

	int x=0;
	i=-1;
	// bütün diziyi sıfırladığımız için sıfır dışında rakama raslayanakadar indisler taranıyor
	do
	{
		i++;
		// Tarama sonucu bulunan indis değeri output dizisine ardaşık olarak yazılıyor
		// Bir nevi ascci kodlarını output indsine sıralı olarak kodluyoruz
		for(;count[i] != 0  &&  x < aSize ; x++, count[i]--)
			output[x] = i;
			
		if(x == aSize)
			break;
	}while(count[i] == 0 && i < A_SIZE);

	// output'a ascii kod olarak sıralanmış karakterler, arr dizisine yeniden aktarlıyor.
    for (i = 0; arr[i]; ++i)
        arr[i] = output[i];	
}
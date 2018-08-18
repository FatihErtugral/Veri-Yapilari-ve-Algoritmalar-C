/**	
 * 	Title: Heap and Heap Sort- [Yığın ve Yığın Sıralaması]
 *	Author:	Fatih Ertuğral.
 *	Created on July 31, 2018, 7:11 PM 
 *
 *  ■ Yığındaki Temel Özellikler ■
 *      ► Max Heap :  Her ata, kendisinden sonraki çocuklardan daha büyük olacak.
 *      ► Min Heap :  Her ata, kendisinden sonraki çocuklardan daha küçük olacak.
 *      ► N elemanlı yığın derinliği = |log2N|
 *      ► Mapping [Planlama] Yığın algoritması: 
 *          • Parent(i) = |i/2|
 *          • Left(i)   = 2i
 *          • Right(i)  = 2i + 1
 *      
 * 
 *	■ Yığındaki Temel Operasyonlar ■
 *  	► Ekleme(Insetion)
 *          • O(log N) adım.
 *          • Eklenecek olan bir x değeri heap’in en alt satırında ilk boşluğa yerleştirilir. 
 *          • Sonra ebeveyninin değeriyle karşılaştırılır. 
 *          • Eğer eklenecek x değeri ebeveyninin değerinden büyük ise yerleri değiştirilir (swap).
 *          • Tekrar ebeveyninden büyük mü diye bakılır. 
 *          • Bu işlem eklenecek verinin ebeveyninden büyük olmadığı duruma kadar devam eder.
 *      ► Silme(Deletion)
 *          • O(log N) adım.
 *          • Kökteki elemanı sil
 *          • En sondaki elamanı köke taşı
 *          • Tekrar heapi düzelt [heapify]
 *  	► Yığın Sıralaması[HeapSort]
 *          • N elamanı yığına ekleyerek yığın oluştur
 *          • N adımlı silme işlemi yap
 *          • O(N log N) sıralamadır.
 *          • Hafıza karmaşıklığı O(N)'dir.
 *
 **/
#include <stdio.h>
#include <stdlib.h>

#define ROOT 1

typedef struct _HEAP{
    int *dizi;
    int boyut;      //-----------------------> Dizinin boyutu.
    int bosIndis;   //-----------------------> Dizinin boş kısmının başlangıcını gösterir, veri eklendikçe adım atar.
} HEAP;

HEAP    *heapStart(HEAP *heap, int boyut);  // Hafızada belirtilen boyutta dizi oluşturur.
void    swap(int *x, int *y);   //-----------> Gönderilen iki değeri takas eder.
void    heapify(HEAP *h, int iter); //-------> Son ağaçtan başlayarak, Ebeveyn, sağ çocuk ve sol çocuk arasında karşılaştırma yaparak, yeniden yığınlar.
void    eklemeMaxHeap(HEAP *h, int data);   // En yüksek değeri, en üste koyacak şekilde ekleme yapar.
int     silmeMaxHeap(HEAP *h);  //-----------> Dizinin ilk elemanını değer olarak döndürür, sonra ilk elamanı son elemanla takaslar, son elamanı siler ve heapify yapar. 
void    printHeap(HEAP *h);

int main(int argc, char** argv) {

    HEAP *dizi = heapStart(dizi, 10);
    eklemeMaxHeap(dizi, 80);
    eklemeMaxHeap(dizi, 70);
    eklemeMaxHeap(dizi, 60);
    eklemeMaxHeap(dizi, 50);
    eklemeMaxHeap(dizi, 40);
    eklemeMaxHeap(dizi, 85);
    eklemeMaxHeap(dizi, 75);
    eklemeMaxHeap(dizi, 65);
    eklemeMaxHeap(dizi, 90);
    printHeap(dizi);
    for(int i=dizi->bosIndis, a=1; 1 < i; i--,a++)
        printf("SilinenDizi[%d]: %d\n", a, silmeMaxHeap(dizi));
    printf("\n");
    eklemeMaxHeap(dizi, 1);
    eklemeMaxHeap(dizi, 180);
    eklemeMaxHeap(dizi, -70);
    eklemeMaxHeap(dizi, 60);
    eklemeMaxHeap(dizi, 50);
    eklemeMaxHeap(dizi, 40);
    eklemeMaxHeap(dizi, 85);
    eklemeMaxHeap(dizi, 75);
    eklemeMaxHeap(dizi, 0);
    eklemeMaxHeap(dizi, 65);
    eklemeMaxHeap(dizi, 90);
    eklemeMaxHeap(dizi, 90);
    
    printHeap(dizi);
    for(int i=dizi->bosIndis, a=1; 1 < i; i--,a++)
        printf("SilinenDizi[%d]: %d\n", a, silmeMaxHeap(dizi));
    silmeMaxHeap(dizi);
    silmeMaxHeap(dizi);
    silmeMaxHeap(dizi);
    return (EXIT_SUCCESS);
}
/**************************************************************************/
HEAP *heapStart(HEAP *heap, int boyut){
    heap = (HEAP *)malloc(sizeof(HEAP));
    if(heap == NULL){
        printf("Malloc basarisiz. Yer ayrilamadi...");
        exit(1);
    }
    heap->boyut = (boyut);
    heap->dizi = (int *)malloc(sizeof(int) * ++heap->boyut);
    if(heap->dizi == NULL){
            printf("Malloc basarisiz. Yer ayrilamadi...");
        exit(1);
    }
    heap->bosIndis = ROOT;
    return heap;
}
/**************************************************************************/
void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}
/**************************************************************************/
void heapify(HEAP *h, int iter){
    int largest = iter;
    int left = 2*iter;
    int right = 2*iter+1;
    if(left < h->bosIndis && h->dizi[left] > h->dizi[largest])              
        largest = left;                                                     
    if(right < h->bosIndis && h->dizi[right] > h->dizi[largest])            
        largest = right;                                                    
    if(largest != iter){                                                    
        swap(&h->dizi[iter], &h->dizi[largest]);

        heapify(h, largest);
    }
    //      [1] largest     [1][2][3][4][5][6][7][8][9][10]
    //     /   \                       \                 \ 
    //  [2]     [3]                     bosIndıs        boyut
    // left     right
    //
}
/**************************************************************************/
void eklemeMaxHeap(HEAP *h, int data) {
    if(h->bosIndis == h->boyut){
        printf("Dizi tamamen doldu.\n");
        return;
    }
    int iter = h->bosIndis;
    int parent = iter /2;
    
    h->dizi[iter] = data;
    while(parent >= ROOT && h->dizi[parent] < h->dizi[iter]){
            swap(&h->dizi[parent], &h->dizi[iter]);
            iter = parent;
            parent /= 2;
    }
    h->bosIndis++;
}
/**************************************************************************/
int silmeMaxHeap(HEAP *h){
    if(h->bosIndis <= 1)
        return 0;

    int rvalue = h->dizi[ROOT];
    swap(&h->dizi[ROOT], &h->dizi[--h->bosIndis]);
    
    for (int i = h->bosIndis / 2; i >= 1; i--)
        heapify(h, i);
    return rvalue;
}
/**************************************************************************/
void printHeap(HEAP *h){
    for(int i=1; i < h->bosIndis; i++)
        printf("Dizi[%d]: %d\n", i, h->dizi[i]);
}


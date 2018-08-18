/**	
 * 	Title:	Data structures: Array implementation of Queue.
 * 			[Dizilerle kuyruk oluşturma]
 * 			FIFO [ilk giren ilk çıkar.]
 *	Author:	Fatih Ertuğral.
 *	Created on July 13, 2018, 1:30 AM
 **/
#include <stdio.h>
#include <stdlib.h>
int *dizi = NULL;
int giris = 0, cikis = 0, boyut = 2;
int deque(){
	if(dizi == NULL){
		printf("dizi mevcut degil");
		return -1;
	}
	if(giris == cikis){
		boyut = 2;
		int *dizi2 = (int *)malloc(sizeof(int)*boyut);
		free(dizi);
		dizi = dizi2;
		int temp = dizi[cikis];
		cikis = 0; giris = 0;
		return -1;
	}
	if((giris-cikis) <= (boyut/4)){
		boyut /= 2;
		int *dizi2 =(int *)malloc(sizeof(int)*boyut);
		for(int i=0; i < giris-cikis; i++){
			dizi2[i] = dizi[cikis+i];
		}
		free(dizi);
		dizi = dizi2;
		giris -= cikis;
		cikis = 0;
		return dizi[cikis++];
	}
	return dizi[cikis++];
};
void enque(int veri){
	if(dizi == NULL){
		dizi = (int *)malloc(sizeof(int)*boyut);
		dizi[giris++] = veri;
		return ;
	}
	if(giris == boyut){
		boyut *= 2;
		int *dizi2 = (int *)malloc(sizeof(int)*boyut);
		for(int i=0 ; i< giris-cikis ; i++){
			dizi2[i] = dizi[cikis+i];
		}
		free(dizi);
		dizi = dizi2;
		giris -=cikis;
		cikis = 0;
	}
	dizi[giris++] = veri;
}

int main(int argc, char *argv[]) {
	printf("%d\n",deque());
	printf("%d\n",deque());
	printf("%d\n",deque());
	printf("giris: %d cikis: %d giris-cikis: %d boyut: %d\n", giris,cikis,giris-cikis,boyut);
	enque(10);
	enque(20);
	enque(70);
	printf("%d\n",deque());
	enque(60);
	enque(50);
	printf("%d\n",deque());
	printf("giris: %d cikis: %d giris-cikis: %d boyut: %d\n", giris,cikis,giris-cikis,boyut);
	enque(40);
	enque(20);
	printf("%d\n",deque());
	printf("%d\n",deque());
	printf("%d\n",deque());
	printf("%d\n",deque());
	printf("%d\n",deque());
	printf("%d\n",deque());
	printf("giris: %d cikis: %d giris-cikis: %d boyut: %d\n", giris,cikis,giris-cikis,boyut);

	for (int i=0; i<50 ; i++){
		enque(i*10);
	}
	printf("giris: %d cikis: %d giris-cikis: %d boyut: %d\n", giris,cikis,giris-cikis,boyut);
	for (int i=0; i<35 ; i++){
		printf("%d\n", deque());
	}
	printf("giris: %d cikis: %d giris-cikis: %d boyut: %d\n", giris,cikis,giris-cikis,boyut);
	return 0;
}
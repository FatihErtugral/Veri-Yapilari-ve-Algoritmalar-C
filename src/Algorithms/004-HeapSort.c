/**	
 * 	Title:	Heap Sort
 *	Author:	Fatih Ertuğral.
 *	Created on July 19, 2018, 9:55 PM
 **/
#include <stdio.h>
 
#define A_SIZE 10
 
void heap_sort(int *p, int size);
void sift(int *p, int left, int right);
void print_array(int *p, int size);
 
 
int main(void)
{
   int a[A_SIZE] = {46, 5, 12, 56, 87, -7, 0, 567, -54, 5};
 
   print_array(a, A_SIZE);
   heap_sort(a, A_SIZE);
   print_array(a, A_SIZE);
   return 0;
}
/**************************************/
void heap_sort (int *p, int size)
{
   int  left, right, temp;
 
   if (size <= 1)
      return;
   left = size / 2;
   right = size - 1;
 
   while (--left >= 0)
      sift(p, left, right);
 
   for (;;) {
      temp = p[0];
      p[0] = p[right];
      p[right] = temp;
      if (--right <= 0)
         break;
      sift(p, 0, right);
   }
}
/**************************************/
void sift(int *p, int left, int right)
{
   int temp, i;
 
   i = left +left +1;
    temp = p[left];
 
   do {
      if (i < right && p[i] < p[i+1])
         i++;
      if (temp >= p[i])
         break;
      p[left] = p[i];
	   print_array(p, A_SIZE);
      left = i;
      i = 2 * i + 1;
   } while (i <= right);
   p[left] = temp;
    print_array(p, A_SIZE);
}
/**************************************/
void print_array(int *p, int size)
{
   int i;
 
   for (i = 0; i < size; i++)
      printf("%d\t", p[i]);
   putchar('\n');
}
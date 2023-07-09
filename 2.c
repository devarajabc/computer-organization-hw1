// description: cn = an * bn
#include <stdio.h>
int main ()
{
int a[10] = {0}, b[10]= {0}, c[10] = {0};
int i, arr_size = 10;
FILE *input = fopen("../input/2.txt","r");
for(i = 0; i<arr_size; i++) fscanf(input, "%d", &a[i]);
for(i = 0; i<arr_size; i++) fscanf(input, "%d", &b[i]);
for(i = 0; i<arr_size; i++) fscanf(input, "%d", &c[i]);
fclose(input);
int *p_a = &a[0];
 int *p_b = &b[0];
 int *p_c = &c[0];
/* Original C code segment
 for (int i = 0; i < arr_size; i++){
 *p_c++ = *p_a++ * *p_b++;
 }
 */
/*將 C/C++ 變數的值存儲在寄存器中（輸入操作數）
從寄存器中提取值並將其存儲在 C/C++ 變數中（輸出操作數）。*/
for (int i = 0; i < arr_size; i++)
 asm volatile(
              "lw x10,0(%[p_a])\n\t"
              "lw x11,0(%[p_b])\n\t"
              "mul x12,x10,x11\n\t"
              "sw x12,0(%[p_c])\n\t"
              "addi %[p_a],%[p_a],4\n\t"
              "addi %[p_b],%[p_b],4\n\t"
              "addi %[p_c],%[p_c],4\n\t"
            : [p_a] "+r" (p_a),[p_b] "+r" (p_b),[p_c] "+r" (p_c)
            :
            :"x10","x11","x12","memory"
 );

p_c = &c[0];
for (int i = 0; i < arr_size; i++)
printf("%d ", *p_c++);
return 0;
}

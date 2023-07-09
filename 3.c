// description: matrix muliply with two-level for loop
/*
 * description: 1x3 matrix - multiply benchmarking
 *
 * |h11 h12 h13|   |x1|   |y1|   | h11*x1+h12*x2+h13*x3 |
 * |h21 h22 h23| * |x2| = |y2| = | h21*x1+h22*x2+h23*x3 |
 * |h31 h32 h33|   |x3|   |y3|   | h31*x1+h32*x2+h33*x3 |
 *
 * Element are to store in following order:
 *
 * matrix h[9]={h11,h12,h13, h21,h22,h23, h31,h32,h33}
 * vector x[3]={x1,x2,x3}
 * vector y[3]={y1,y1,y3}
 */
#include<stdio.h>
int main()
{
 int f,i=0;
 int h[9]={0}, x[3]={0}, y[3]={0};
 FILE *input = fopen("../input/3.txt","r");
 for(i = 0; i<9; i++) fscanf(input, "%d", &h[i]);
 for(i = 0; i<3; i++) fscanf(input, "%d", &x[i]);
 for(i = 0; i<3; i++) fscanf(input, "%d", &y[i]);
 fclose(input);
 int *p_x = &x[0] ;
 int *p_h = &h[0] ;
 int *p_y = &y[0] ;

 for (i = 0 ; i < 3; i++)// 3 Row
 {

 p_x = &x[0] ;
 /*
  please convert the Level-2
  loop body (*p_y += *p_h++ * *p_x++; at line #37) into the inline assembly version. The example of your
  inline assembly version will look like the below code.
 */
 for (f = 0 ; f < 3; f++)//
 asm volatile(
         "lw x10, (%[p_x])\n\t"
         "lw x11, (%[p_h])\n\t"
         "lw x12, (%[p_y])\n\t"
         "mul x13, x11, x10\n\t"
         "add x12, x12, x13\n\t"
         "sw x12, (%[p_y])\n\t"
         "add %[p_x], %[p_x], 4\n\t"
         "add %[p_h], %[p_h], 4\n\t "
        "li x14, 2\n\t "
         "beq %[f],x14, YPP\n\t"
         "j exit\n\t"
         "YPP:\n\t"
         "add %[p_y], %[p_y], 4\n\t"
         "exit:\n\t"

         : [p_x] "+r" (p_x), [p_h] "+r" (p_h), [p_y] "+r" (p_y),[f]"+r"(f)
         :
         : "x10", "x11", "x12", "x13","x14"
        );

 }
 p_y = &y[0];
 for(i = 0; i<3; i++)
 printf("%d \n", *p_y++);
 return(0) ;

}

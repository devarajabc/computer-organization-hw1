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
// description: matrix muliply without for loop
#include<stdio.h>
int main()
{
 int i=0;
 int h[9]={0}, x[3]={0}, y[3]={0};
 FILE *input = fopen("../input/4.txt","r");
 for(i = 0; i<9; i++) fscanf(input, "%d", &h[i]);
 for(i = 0; i<3; i++) fscanf(input, "%d", &x[i]);
 for(i = 0; i<3; i++) fscanf(input, "%d", &y[i]);
 fclose(input);
 int *p_x = &x[0] ;
 int *p_h = &h[0] ;
 int *p_y = &y[0] ;
 asm volatile(  "li x14,2\n\t"//i<2,j<2
                "li x15,0\n\t"//int i=0;
                "li x16,0\n\t"//int j=0;
                "add x17, %[p_x], x0\n\t" // save the initial value of p_x
                "loop:\n\t"
                "lw x10, (%[p_x])\n\t"//get x[i]
                "lw x11, (%[p_h])\n\t"//get h[i]
                "lw x12, (%[p_y])\n\t"//get y[i]
                "mul x13, x11, x10\n\t"//x[i]*h[i]
                "add x12, x12, x13\n\t"//y[i]+=x[i]*h[i]
                "sw x12, (%[p_y])\n\t"//store the value of y[i] to y[i]
                "addi %[p_x], %[p_x], 4\n\t"//next 
                "addi %[p_h], %[p_h], 4\n\t "//next 
                "beq x16,x14, YPP\n\t"//if j==2,y[i]->y[i+1]
                "addi x16,x16,1\n\t"//j++
                "j loop\n\t"//if j<2
                "YPP:\n\t"//j==2 now
                "addi %[p_y], %[p_y], 4\n\t"//y1->y2
                "add %[p_x],x17,x0\n\t"//x1,x2,x3恢復
                "li x16, 0\n\t"//j=0
                "beq x14,x15,exit\n\t"//if i==2
                "addi x15,x15,1\n\t"//i++
                "j loop\n\t"//if i<2
                "exit:\n\t"

                : [p_x] "+r" (p_x), [p_h] "+r" (p_h), [p_y] "+r" (p_y)
                :
                : "x10", "x11", "x12", "x13","x14","x15","x16","x17"
 );

 p_y = &y[0];
 for(i = 0; i<3; i++)
 printf("%d \n", *p_y++);
 return(0) ;

}

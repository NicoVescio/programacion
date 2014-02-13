#include <stdio.h>

#define FIL1 4
#define COL1 5
#define FIL2 5
#define COL2 6

//PROTORIPOS//
void productoE(int[FIL1][COL1],int[FIL2][COL2],int[FIL1][COL2]);
void mostrarMatriz(int*,int,int);



//MAIN//
void main()
{
    int m1[FIL1][COL1]={{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20}};
    int m2[FIL2][COL2]={{2,3,4,2,3,4},{1,3,2,2,1,2},{3,1,5,4,5,6},{2,3,1,6,1,1},{1,1,4,3,2,5}};
    int m3[FIL1][COL2]={0};

    printf("MATRIZ 1\n");
    mostrarMatriz(m1,FIL1,COL1);
    printf("\nMATRIZ 2\n");
    mostrarMatriz(m2,FIL2,COL2);

    if(COL1!=FIL2)
    {
        printf("No se puede realizar el producto");
        exit(1);
    }

    productoE(m1,m2,m3);
    printf("MATRIZ RESULTANTE\n");
    mostrarMatriz(m3,FIL1,COL2);
}

//FUNCIONES//
void mostrarMatriz(int *m,int fil,int col)
{
    int i,j;
    for(i=0;i<fil;i++)
    {
        for(j=0;j<col;j++)
        {
            printf("%d\t",*(m+j+(i*col)));
        }
    printf("\n");
    }
}

void productoE(int m1[FIL1][COL1],int m2[FIL2][COL2],int m3[FIL1][COL2])
{
    int i,j,k,val=0;

    for(k=0;k<FIL1;k++)
    {
        for(i=0;i<COL2;i++)
        {
            for(j=0;j<COL1;j++)
            {
                val+=m1[k][j]*m2[j][i];
            }
            m3[k][i]=val;
            val=0;
        }
    }

}


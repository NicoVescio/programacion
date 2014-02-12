#include <stdio.h>

#define FIL1 4
#define COL1 5
#define FIL2 5
#define COL2 4

//PROTORIPOS//
void productoE(int[FIL1][COL1],int[FIL2][COL2],int[FIL1][COL2]);
void mostrarMatriz1(int[FIL1][COL1]);
void mostrarMatriz2(int[FIL2][COL2]);
void mostrarMatriz3(int[FIL1][COL2]);


//MAIN//
void main()
{
    int m1[FIL1][COL1]={{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20}};
    int m2[FIL2][COL2]={{2,3,4,2},{1,3,2,2},{3,1,5,4},{2,3,1,6},{1,1,4,3}};
    int m3[FIL1][COL2]={0};

    printf("MATRIZ 1\n");
    mostrarMatriz1(m1);
    printf("\nMATRIZ 2\n");
    mostrarMatriz2(m2);

    if(COL1!=FIL2)
    {
        printf("No se puede realizar el producto");
        exit(1);
    }

    productoE(m1,m2,m3);
    printf("MATRIZ RESULTANTE\n");
    mostrarMatriz3(m3);
}

//FUNCIONES//
void mostrarMatriz1(int m[FIL1][COL1])
{
    int i,j;
    for(i=0;i<FIL1;i++)
    {
        for(j=0;j<COL1;j++)
        {
            printf("%d\t",m[i][j]);
        }
    printf("\n");
    }
}

void mostrarMatriz2(int m[FIL2][COL2])
{
    int i,j;
    for(i=0;i<FIL2;i++)
    {
        for(j=0;j<COL2;j++)
        {
            printf("%d\t",m[i][j]);
        }
    printf("\n");
    }
}

void mostrarMatriz3(int m[FIL1][COL2])
{
    int i,j;
    for(i=0;i<FIL1;i++)
    {
        for(j=0;j<COL2;j++)
        {
            printf("%d\t",m[i][j]);
        }
    printf("\n");
    }
}

void productoE(int m1[FIL1][COL1],int m2[FIL2][COL2],int m3[FIL1][COL2])
{
    int i,j,k,val=0;

    for(k=0;k<FIL1;k++)
    {
        for(i=0;i<FIL1;i++)
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


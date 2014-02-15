#include <stdio.h>
#define TAM 100

typedef struct
{
    char nom[20];
    char ape[15];
    float n1;
    float n2;
    float n3;
}t_alumno;

//PROTOTIPOS//
void abrirArchivo(FILE**,char*,char*);
void estiloArchivo(FILE*);
void estiloFinal(FILE*,float);
float cargarDatos(t_alumno *);
void guardarEnArchivo(FILE*,t_alumno*,float,int);

//MAIN//
void main()
{
    t_alumno alumno;
    FILE *pf;
    t_alumno vec[TAM];
    int opc,cont=1,i=1;
    float prom,promgral=0;
    abrirArchivo(&pf,"C:\\ArchProII\\12Alu.txt","wt");
    estiloArchivo(pf);
    while(cont==1)
    {
        fflush(stdin);
        prom=cargarDatos(&alumno);
        guardarEnArchivo(pf,&alumno,prom,i);
        i++;
        promgral+=prom;
        printf("\nDesea cargar otro? (1:SI - 0:NO): ");
        scanf("%d",&cont);
        fflush(stdin);
    }
    promgral=promgral/(i-1);
    estiloFinal(pf,promgral);
    fclose(pf);
}

//FUNCIONES//
void abrirArchivo(FILE** file,char* ruta,char* modo)
{
    *file=fopen(ruta,modo);
    if(!file)
    {
        printf("\nNO SE PUDO ABRIR EL ARCHIVO");
        exit(1);
    }
}
void estiloArchivo(FILE* file)
{
    fprintf(file,"   Apellido/s, Nombre/s                 P. 1  P. 2  P. 3 - Prome\n   =================================== ===== ===== =====   =====\n\n");
}

float cargarDatos(t_alumno *alu)
{
    float nota,prom;
    printf("\nIngrese nombre: ");
    gets(alu->nom);
    printf("\nIngrese apellido: ");
    gets(alu->ape);
    printf("\nNota primer parcial: ");
    scanf("%f",&nota);
    alu->n1=nota;
    printf("\nNota segundo parcial: ");
    scanf("%f",&nota);
    alu->n2=nota;
    printf("\nNota tercer parcial: ");
    scanf("%f",&nota);
    alu->n3=nota;
    prom=(alu->n1+alu->n2+alu->n3)/3;
    return prom;
}
void guardarEnArchivo(FILE* file,t_alumno* alu,float pr, int i)
{
    fprintf(file,"%2d %s, %-*s %5.2f %5.2f %5.2f - %5.2f\n",i,alu->ape,35-(strlen(alu->ape))-2,alu->nom,alu->n1,alu->n2,alu->n3,pr);
}

void estiloFinal(FILE*file,float p)
{
    fprintf(file,"%64.2f",p);
}


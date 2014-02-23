#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int dni;
    char ape[20];
    char nom[20];
    int sueldo;
}t_empleado;

typedef struct
{
    int dni;
    char ape[20];
    char nom[20];
    float promedio;
}t_estudiante;

//**********PROTOTIPOS**********//
void abrirArchivo(FILE**,char*,char*);
void mostrarArchivoEmp(FILE*);
void mostrarArchivoEst(FILE*);
void procesarArchivos(FILE*,FILE*);
int comparar(t_empleado *,t_estudiante *);

//**********MAIN**********//
void main()
{
    FILE *pfEmp,*pfEst;

    printf("ARCHIVO EMPLEADOS\n");
    abrirArchivo(&pfEmp,"C:\\ArchProII\\empleados.dat","r+b");
    mostrarArchivoEmp(pfEmp);

    printf("\n\nARCHIVO ESTUDIANTES\n");
    abrirArchivo(&pfEst,"C:\\ArchProII\\estudiantes.dat","rb");
    mostrarArchivoEst(pfEst);

    procesarArchivos(pfEmp,pfEst);

    printf("\n\n**********ARCHIVO MODIFICADO**********\n");
    mostrarArchivoEmp(pfEmp);

    fclose(pfEmp);
    fclose(pfEst);
}

//**********FUNCIONES**********//
void abrirArchivo(FILE **file,char* ruta,char* modo)
{
    *file=fopen(ruta,modo);
    if(!(*file))
    {
        printf("\nNo se ha podido abrir el archivo");
        exit(1);
    }
}

void mostrarArchivoEmp(FILE* file)
{
    t_empleado empleado;
    int cont=1;
    fseek(file,0,0);
    fread(&empleado,sizeof(t_empleado),1,file);
    while(!feof(file))
    {
        printf("\n\n***REGISTRO %d***\n",cont);
        printf("\nDNI: %d",empleado.dni);
        printf("\nApellido: ");
        puts(empleado.ape);
        printf("Nombre: ");
        puts(empleado.nom);
        printf("Sueldo: $%d",empleado.sueldo);
        cont++;
        fread(&empleado,sizeof(t_empleado),1,file);
    }
}

void mostrarArchivoEst(FILE* file)
{
    t_estudiante estudiante;
    int cont=1;
    fseek(file,0,0);
    fread(&estudiante,sizeof(t_estudiante),1,file);
    while(!feof(file))
    {
        printf("\n\n***REGISTRO %d***\n",cont);
        printf("\nDNI: %d",estudiante.dni);
        printf("\nApellido: ");
        puts(estudiante.ape);
        printf("Nombre: ");
        puts(estudiante.nom);
        printf("Promedio: %.2f",estudiante.promedio);
        cont++;
        fread(&estudiante,sizeof(t_estudiante),1,file);
    }
}

void procesarArchivos(FILE *fileEmp, FILE *fileEst)
{
    t_empleado emple;
    t_estudiante estu;
    int cmp;
    int nuevoSueldo;

    fseek(fileEmp,0,0);
    fread(&emple,sizeof(t_empleado),1,fileEmp);
    fseek(fileEst,0,0);
    fread(&estu,sizeof(t_estudiante),1,fileEst);

    while(!feof(fileEmp) && !feof(fileEst))
    {
        cmp=comparar(&emple,&estu);
        while(cmp!=0)
        {
            if(cmp>0)
                fread(&estu,sizeof(t_estudiante),1,fileEst);
            else
                fread(&emple,sizeof(t_empleado),1,fileEmp);
            cmp=comparar(&emple,&estu);
        }

        if(cmp==0)
        {

            if(estu.promedio>=7)
            {
                nuevoSueldo=emple.sueldo*1.0728;
                emple.sueldo=nuevoSueldo;
                fseek(fileEmp,-sizeof(t_empleado),1);
                fwrite(&emple,sizeof(t_empleado),1,fileEmp);
                fseek(fileEmp,0,1);
            }
            fread(&emple,sizeof(t_empleado),1,fileEmp);
            fread(&estu,sizeof(t_estudiante),1,fileEst);
        }
    }
}

int comparar(t_empleado *emple,t_estudiante *estu)
{
    char cad1[50];
    char cad2[50];
    char dni1[9];
    char dni2[9];

    strcpy(cad1,emple->ape);
    strcat(cad1,emple->nom);
    strcat(cad1,itoa(emple->dni,dni1,10));

    strcpy(cad2,estu->ape);
    strcat(cad2,estu->nom);
    strcat(cad2,itoa(estu->dni,dni2,10));

    return strcmpi(cad1,cad2);
}

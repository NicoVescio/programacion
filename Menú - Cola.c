#include <stdio.h>
#define SIN_MEMORIA 0
#define COLA_VACIA 0

//***************ESTRUCTURAS***************//
typedef struct
{
    char nom[20];
}t_dato;

typedef struct s_nodo
{
    t_dato dato;
    struct s_nodo* sig;
}t_nodo;

typedef struct
{
    t_nodo* pri;
    t_nodo* ult;
}t_cola;

//***************PROTOTIPOS***************//
int cargarDato(t_dato*);
void crearCola(t_cola*);
int colaVacia(const t_cola*);
int colaLlena(const t_cola*);
int acolar(t_cola*,const t_dato*);
int desacolar(t_cola*,t_dato*);
void vaciarCola(t_cola *);
int verTope(const t_cola*,t_dato*);

void abrirArchivo(FILE**,char*);

//***************MAIN***************//
void main()
{
    FILE* pf;
    t_dato dato;
    t_cola cola;
    int opc,cantReg;

    printf("\n**********MENU DE OPCIONES**********\n\
1- Crear cola\n\
2- Acolar\n\
3- Desacolar\n\
4- Cola vacia?\n\
5- Cola llena?\n\
6- Vaciar cola\n\
7- Ver tope de cola\n\
8- Guardar cola en archivo\n\
9- Cargar cola de archivo\n\
0- SALIR\n\n\
INGRESE EL NUMERO DE OPCION: ");
    scanf("%d",&opc);

    while(opc && opc!=0)
    {
        switch(opc)
        {
        case 1:
            crearCola(&cola);
            printf("\nSe ha creado la cola");
        break;

        case 2:
            while(cargarDato(&dato))
                if(acolar(&cola,&dato))
                    printf("\nSe acolo el dato ingresado");
        break;

        case 3:
            if(desacolar(&cola,&dato))
                {
                    printf("Se desacolo el dato ");
                    puts(dato.nom);
                }
            else
                printf("No se pudo desacolar el dato");

        break;

        case 4:
            if(colaVacia(&cola))
                printf("La cola esta vacia");
            else
                printf("La cola NO esta vacia");
        break;

        case 5:
            if(colaLlena(&cola))
                printf("La cola esta llena");
            else
                printf("Todavia hay lugar en la cola");
        break;

        case 6:
            vaciarCola(&cola);
            printf("Se vacio la cola");
        break;

        case 7:
            if(verTope(&cola,&dato))
            {
                printf("El tope de cola es ");
                puts(dato.nom);
            }
            else
                printf("La cola esta vacia");
        break;

        case 8:
            abrirArchivo(&pf,"wb");
            while(desacolar(&cola,&dato))
                fwrite(&dato,sizeof(t_dato),1,pf);
            fclose(pf);
        break;

        case 9:
            abrirArchivo(&pf,"rb");
            fseek(pf,0,0);
            fread(&dato,sizeof(t_dato),1,pf);
            while(!feof(pf))
            {
                acolar(&cola,&dato);
                fread(&dato,sizeof(t_dato),1,pf);
            }
            fclose(pf);
        break;
        }
        printf("\n**********MENU DE OPCIONES**********\n\
1- Crear cola\n\
2- Acolar\n\
3- Desacolar\n\
4- Cola vacia?\n\
5- Cola llena?\n\
6- Vaciar cola\n\
7- Ver tope de cola\n\
8- Guardar cola en archivo\n\
9- Cargar cola de archivo\n\
0- SALIR\n\n\
INGRESE EL NUMERO DE OPCION: ");
        scanf("%d",&opc);
    }
}

//***************FUNCIONES***************//
int cargarDato(t_dato *d)
{
    int cont;
    printf("\nDesea ingresar un dato? (1:SI - 0:NO) ");
    scanf("%d",&cont);
    if(cont==0)
        return 0;
    fflush(stdin);
    printf("Ingrese el dato: ");
    gets(d->nom);
    return 1;
}

void crearCola(t_cola *pc)
{
    pc->pri=NULL;
    pc->ult=NULL;
}

int colaVacia(const t_cola *pc)
{
    return pc->pri==NULL;
}

int colaLlena(const t_cola *pc)
{
    void *aux;
    aux=malloc(sizeof(t_nodo));
    free(aux);
    return aux==NULL;
}

int acolar(t_cola *pc,const t_dato *d)
{
    t_nodo *nue;
    nue=(t_nodo *)malloc(sizeof(t_nodo));
    if(!nue)
        return SIN_MEMORIA;
    nue->dato=*d;
    nue->sig=NULL;
    if(pc->pri==NULL)
        pc->pri=nue;
    else
        pc->ult->sig=nue;
    pc->ult=nue;
    return 1;
}

int desacolar(t_cola *pc,t_dato *d)
{
    t_nodo *aux;
    if(pc->pri==NULL)
        return COLA_VACIA;
    aux=pc->pri;
    *d=aux->dato;
    if(pc->pri==pc->ult && pc->ult!=NULL)
        pc->ult=NULL;
    pc->pri=aux->sig;
    free(aux);
    return 1;
}

void vaciarCola(t_cola *pc)
{
    t_nodo *aux;
    while(pc->pri!=NULL)
    {
        aux=pc->pri;
        pc->pri=aux->sig;
        free(aux);
    }
    pc->ult=NULL;
}

int verTope(const t_cola *pc,t_dato *d)
{
    if(pc->pri==NULL)
        return COLA_VACIA;
    *d=pc->pri->dato;
    return 1;
}

void abrirArchivo(FILE **file,char *modo)
{
    *file=fopen("C:\\ArchProII\\MenuCola.dat",modo);
    if(!file)
    {
        printf("NO SE PUDO ABRIR EL ARCHIVO\n");
        exit(1);
    }
}

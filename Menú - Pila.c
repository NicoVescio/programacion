#include <stdio.h>
#define SIN_MEMORIA 0
#define PILA_VACIA 0

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

typedef t_nodo* t_pila;

//***************PROTOTIPOS***************//
int cargarDato(t_dato*);
void crearPila(t_pila*);
int pilaVacia(const t_pila*);
int pilaLlena(const t_pila*);
int apilar(t_pila*,const t_dato*);
int desapilar(t_pila*,t_dato*);
void vaciarPila(t_pila *);
int verTope(const t_pila*,t_dato*);

void abrirArchivo(FILE**,char*);

//***************MAIN***************//
void main()
{
    FILE* pf;
    t_dato dato;
    t_pila pila;
    int opc,cantReg,i;

    printf("\n**********MENU DE OPCIONES**********\n\
1- Crear pila\n\
2- Apilar\n\
3- Desapilar\n\
4- Pila vacia?\n\
5- Pila llena?\n\
6- Vaciar pila\n\
7- Ver tope de pila\n\
8- Guardar pila en archivo\n\
9- Cargar pila de archivo\n\
0- SALIR\n\n\
INGRESE EL NUMERO DE OPCION: ");
    scanf("%d",&opc);

    while(opc && opc!=0)
    {
        switch(opc)
        {
        case 1:
            crearPila(&pila);
            printf("\nSe ha creado la pila");
        break;

        case 2:
            while(cargarDato(&dato))
                if(apilar(&pila,&dato))
                    printf("\nSe apilo el dato ingresado");
        break;

        case 3:
            if(desapilar(&pila,&dato))
                {
                    printf("Se desapilo el dato ");
                    puts(dato.nom);
                }
            else
                printf("No se pudo desapilar el dato");

        break;

        case 4:
            if(pilaVacia(&pila))
                printf("La pila esta vacia");
            else
                printf("La pila NO esta vacia");
        break;

        case 5:
            if(pilaLlena(&pila))
                printf("La pila esta llena");
            else
                printf("Todavia hay lugar en la pila");
        break;

        case 6:
            vaciarPila(&pila);
            printf("Se vacio la pila");
        break;

        case 7:
            if(verTope(&pila,&dato))
            {
                printf("El tope de pila es ");
                puts(dato.nom);
            }
            else
                printf("La pila esta vacia");
        break;

        case 8:
            abrirArchivo(&pf,"wb");
            while(desapilar(&pila,&dato))
                fwrite(&dato,sizeof(t_dato),1,pf);
            fclose(pf);
        break;

        case 9:
            abrirArchivo(&pf,"rb");
            fseek(pf,0,2);
            cantReg=ftell(pf)/sizeof(t_dato);
            for(i=0;i<cantReg;i++)
            {
                fseek(pf,-sizeof(t_dato),1);
                fseek(pf,0,1);
                fread(&dato,sizeof(t_dato),1,pf);
                apilar(&pila,&dato);
                fseek(pf,-sizeof(t_dato),1);
            }
            fclose(pf);
        break;
        }
        printf("\n\n**********MENU DE OPCIONES**********\n\
1- Crear pila\n\
2- Apilar\n\
3- Desapilar\n\
4- Pila vacia?\n\
5- Pila llena?\n\
6- Vaciar pila\n\
7- Ver tope de pila\n\
8- Guardar pila en archivo\n\
9- Cargar pila de archivo\n\
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

void crearPila(t_pila *pp)
{
    *pp=NULL;
}

int pilaVacia(const t_pila *pp)
{
    return *pp==NULL;
}

int pilaLlena(const t_pila *pp)
{
    void *aux;
    aux=malloc(sizeof(t_nodo));
    free(aux);
    return aux==NULL;
}

int apilar(t_pila *pp,const t_dato *d)
{
    t_nodo *nue;
    nue=(t_nodo *)malloc(sizeof(t_nodo));
    if(!nue)
        return SIN_MEMORIA;
    nue->dato=*d;
    nue->sig=*pp;
    *pp=nue;
    return 1;
}

int desapilar(t_pila *pp,t_dato *d)
{
    t_nodo *aux;
    if(!(*pp))
        return PILA_VACIA;
    aux=*pp;
    *d=aux->dato;
    *pp=aux->sig;
    free(aux);
    return 1;
}

void vaciarPila(t_pila *pp)
{t_nodo *aux;
while(*pp)
	{
	    aux=*pp;
        *pp=aux->sig;
        free(aux);
   }
}

int verTope(const t_pila *pp,t_dato *d)
{
    if(!(*pp))
        return PILA_VACIA;
    *d=(*pp)->dato;
    return 1;
}

void abrirArchivo(FILE **file,char *modo)
{
    *file=fopen("C:\\ArchProII\\MenuPila.dat",modo);
    if(!file)
    {
        printf("NO SE PUDO ABRIR EL ARCHIVO\n");
        exit(1);
    }
}

#include <stdio.h>
#define TAM 5
#define PILA_LLENA 0
#define PILA_VACIA 0

//***************ESTRUCTURAS***************//
typedef struct
{
    char nom[20];
}t_dato;

typedef struct
{
    t_dato pila[TAM];
    int tope;
}t_pila;

//***************PROTOTIPOS***************//
void crearPila(t_pila *);
int pilaVacia(t_pila *);
int pilaLlena(t_pila *);
int apilar(t_pila *,t_dato *);
int desapilar(t_pila *,t_dato *);
void vaciarPila(t_pila *);
int verTope(t_pila *,t_dato *);

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
            while(pila.tope!=TAM)
            {
                cargarDato(&dato);
                if(apilar(&pila,&dato))
                    printf("\nSe apilo el dato ingresado");
            }
            printf("\nSE LLENO LA PILA");

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

        }
        printf("\n\n**********MENU DE OPCIONES**********\n\
1- Crear pila\n\
2- Apilar\n\
3- Desapilar\n\
4- Pila vacia?\n\
5- Pila llena?\n\
6- Vaciar pila\n\
7- Ver tope de pila\n\
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
    pp->tope=0;
}

int pilaVacia(t_pila *pp)
{
    return pp->tope==0;
}

int pilaLlena(t_pila *pp)
{
    return pp->tope==TAM;
}

int apilar(t_pila *pp,t_dato *d)
{
    if(pp->tope==TAM)
        return PILA_LLENA;
    pp->pila[pp->tope]=*d;
    pp->tope++;
    return 1;
}

int desapilar(t_pila *pp,t_dato *d)
{
    if(pp->tope==0)
        return PILA_VACIA;
    pp->tope--;
    *d=pp->pila[pp->tope];
    return 1;
}

void vaciarPila(t_pila *pp)
{
    pp->tope=0;
}

int verTope(t_pila *pp,t_dato *d)
{
    if(pp->tope==0)
        return PILA_VACIA;
    *d=pp->pila[(pp->tope)-1];
    return 1;
}


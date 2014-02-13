#include <stdio.h>
#define SIN_MEMORIA 0
#define COLA_VACIA 0

//***************ESTRUCTURAS***************//
typedef struct
{
    char nom[20];
}t_dato;

typedef struct
{
    int pri;
    t_dato cola[TAM];
    int ult;
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
        }
        printf("\n**********MENU DE OPCIONES**********\n\
1- Crear cola\n\
2- Acolar\n\
3- Desacolar\n\
4- Cola vacia?\n\
5- Cola llena?\n\
6- Vaciar cola\n\
7- Ver tope de cola\n\
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
    pc->pri=0;
    pc->ult=-1;
}

int colaVacia(const t_cola *pc)
{
    if(pc->pri==0 && pc->ult==-1)
        return 1;
    return 0;
}

int colaLlena(const t_cola *pc)
{
    if((pc->ult+1==TAM && pc->pri==0)||(pc->ult+1==pc->pri && pc->ult!=-1))
        return 1;
    return 0;
}

int acolar(t_cola *pc,const t_dato *d)
{
    if((pc->ult+1==TAM && pc->pri==0)||(pc->ult+1==pc->pri && pc->ult!=-1))
        return 0;
    pc->ult==(pc->ult+1)%TAM;
    pc->cola[pc->ult]=*d;
    return 1;
}

int desacolar(t_cola *pc,t_dato *d)
{
    if(pc->ult==-1)
        return 0;
    *d=pc->cola[pc->pri];
    if(pc->pri==pc->ult)
    {
       pc->pri=0;
       pc->ult=-1;
    }
    else
        pc->pri=(pc->pri+1)%TAM;
    return 1;
}

void vaciarCola(t_cola *pc)
{
    pc->pri=0;
    pc->ult=-1;
}

int verTope(const t_cola *pc,t_dato *d)
{
    if(pc->ult==-1)
        return COLA_VACIA;
    *d=pc->cola[pc->pri];
    return 1;
}



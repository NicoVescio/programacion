#include <stdio.h>
#define COLA_VACIA 0
#define SIN_MEMORIA 0

//**********ESTRUCTURAS**********//
typedef struct
{
    int codPr;
    int cantStock;
    int minStock;
}t_producto;

typedef struct
{
    int nCliente;
    int cod;
    int cant;
}t_pedido;

typedef struct s_nodo_pedido
{
    t_pedido pedido;
    struct s_nodo_pedido *sig;

}t_nodo_pedido;

typedef struct s_nodo_producto
{
    t_producto producto;
    struct s_nodo_producto *sig;
}t_nodo_producto;

typedef struct
{
    t_nodo_pedido *pri;
    t_nodo_pedido *ult;
}t_cola;

typedef t_nodo_producto* t_pila;
typedef t_nodo_pedido* t_lista;

//**********PROTOTIPOS**********//
void abrirArchivo(FILE**,char*);
void crearCola(t_cola*);
void crearPila(t_pila*);
void crearLista(t_lista*);
int acolar(t_cola*, t_pedido*);
int apilar(t_pila*, t_producto*);
int ponerEnLista(t_lista*, t_pedido*);
int desacolar(t_cola*, t_pedido*);
void mostrarArchivo(FILE*);

//**********MAIN**********//
void main()
{
    FILE* pf;
    t_cola cola;
    t_pila pila;
    t_lista lista;
    t_pedido ped;
    t_producto prod;
    int cont=1;

    abrirArchivo(&pf,"r+b");
    mostrarArchivo(pf);

    crearCola(&cola);
    crearPila(&pila);
    crearLista(&lista);
    printf("\nACOLAR\n");
    printf("\nIngrese numero de cliente: ");
    scanf("%d",&ped.nCliente);
    while(ped.nCliente!=0)
    {
        printf("Ingrese codigo de producto: ");
        scanf("%d",&ped.cod);
        printf("Ingrese cantidad pedida: ");
        scanf("%d",&ped.cant);
        acolar(&cola,&ped);
        printf("\nIngrese numero de cliente: ");
        scanf("%d",&ped.nCliente);
    }

    while(desacolar(&cola,&ped))
    {
        printf("\nCliente: %d\nProducto: %d\nCantidad: %d unidades\n",ped.nCliente,ped.cod,ped.cant);
        fseek(pf,0,0);
        fread(&prod,sizeof(t_producto),1,pf);
        while(!feof(pf))
        {
            if(ped.cod==prod.codPr)
            {

                if((prod.cantStock-ped.cant)>=prod.minStock)
                {
                    printf("\nPedido del cliente %d.Fue realizado exitosamente.\n",ped.nCliente);
                    prod.cantStock-=ped.cant;
                    fseek(pf,-sizeof(t_producto),1);
                    fwrite(&prod,sizeof(t_producto),1,pf);
                    fseek(pf,0,1);
                }
                else
                {
                    if((prod.cantStock-ped.cant)>=0)
                    {
                        printf("\nPedido del cliente %d.Fue realizado, stock por debajo del minimo necesario.\n",ped.nCliente);
                        prod.cantStock-=ped.cant;
                        fseek(pf,-sizeof(t_producto),1);
                        fwrite(&prod,sizeof(t_producto),1,pf);
                        fseek(pf,0,1);
                        apilar(&pila,&prod);
                    }
                    else
                    {
                        printf("\nPedido del cliente %d.No tenemos el suficiente stock para afrontar la venta.\n",ped.nCliente);
                        ponerEnLista(&lista,&ped);
                    }
                }
            }
            fread(&prod,sizeof(t_producto),1,pf);
        }
    }
    printf("\nARCHIVO ACTUALIZADO\n");
    fseek(pf,0,0);
    mostrarArchivo(pf);
    fclose(pf);
}

//**********FUNCIONES**********//
void abrirArchivo(FILE** file,char* modo)
{
    *file=fopen("C:\\ArchProII\\Stock.dat",modo);
    if(!file)
    {
        printf("NO SE PUDO ABRIR EL ARCHIVO\n");
        exit(1);
    }
}

void crearCola(t_cola *pc)
{
    pc->pri=NULL;
    pc->ult=NULL;
}

void crearPila(t_pila *pp)
{
    *pp=NULL;
}

void crearLista(t_lista *pl)
{
    *pl=NULL;
}

int acolar(t_cola *pc, t_pedido *ped)
{
    t_nodo_pedido *nue;
    nue=(t_nodo_pedido*)malloc(sizeof(t_nodo_pedido));
    if(!nue)
        return SIN_MEMORIA;
    nue->pedido=*ped;
    nue->sig=NULL;
    if(pc->pri==NULL)
        pc->pri=nue;
    else
        pc->ult->sig=nue;
    pc->ult=nue;
    return 1;
}

int apilar(t_pila *pp, t_producto *prod)
{
    t_nodo_producto *nue;
    nue=(t_nodo_producto*)malloc(sizeof(t_nodo_producto));
    if(!nue)
        return SIN_MEMORIA;
    nue->producto=*prod;
    nue->sig=*pp;
    *pp=nue;
    return 1;
}

int ponerEnLista(t_lista *pl, t_pedido *ped)
{
    t_nodo_pedido *nue;
    while(*pl)
        pl=&(*pl)->sig;
    nue=(t_nodo_pedido*)malloc(sizeof(t_nodo_pedido));
    if(!nue)
        return SIN_MEMORIA;
    nue->pedido=*ped;
    nue->sig=NULL;
    *pl=nue;
    return 1;
}

int desacolar(t_cola *pc, t_pedido *ped)
{
    t_nodo_pedido *aux;
    if(pc->pri==NULL)
        return COLA_VACIA;
    aux=pc->pri;
    *ped=aux->pedido;
    if(pc->pri==pc->ult && pc->ult!=NULL)
        pc->ult=NULL;
    pc->pri=aux->sig;
    free(aux);
    return 1;
}

void mostrarArchivo(FILE *file)
{
    t_producto prod;
    fread(&prod,sizeof(t_producto),1,file);
    while(!(feof(file)))
    {
        printf("Codigo de producto %d\n%d unidades en stock\n%d unidades de stock minimo\n\n",prod.codPr,prod.cantStock,prod.minStock);
        fread(&prod,sizeof(t_producto),1,file);
    }
}

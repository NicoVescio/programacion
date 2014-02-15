#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TAM 100

int tratarCadena(char*,int*,int*,int*);

void main()
{
    int repePri=1,cantPal=0,longPal=0;
    char cad[TAM];
    printf("Ingrese una cadena: ");
    gets(cad);
    tratarCadena(cad,&repePri,&cantPal,&longPal);
    printf("\nLa primer palabra aparece %d veces",repePri);
    printf("\nCantidad de palabras: %d",cantPal);
    printf("\nLongitud de palabra mas larga: %d",longPal);
}

int tratarCadena(char *c,int *rep,int *cant,int *lon)
{
    char *lec,*esc; //PUNTEROS PARA TRABAJAR LA CADENA
    int lonPri,may=0; //lonPri GUARDA LA LONGITUD DE LA PRIMER PALABRA, may PARA GUARDAR LA LONGITUD DEL MAYOR
    lec=c;
    esc=c;
    //PRIMER PALABRA//
    printf("\nLa primer palabra es: ");
    while(*esc && *esc!='.') //MIENTRAS HAYA UN CARACTER Y NO SEA UN '.'
    {
        printf("%c",*esc); //MUESTRO EL CARACTER
        may++; //INCREMENTO may
        esc++; //MUEVO EL PUNTERO DE ESCRITURA
    }
    lonPri=may; //EN lonPri GUARDO LA LONGITUD DE LA PRIMER PALABRA
    *lon=may; //EN *lon LONGITUD DE LA MAYOR PALABRA
    may=0; //INICIALIZO may EN 0 PARA VOLVER A CONTAR DESPUES
    (*cant)++; //SUMO UNO EN CANTIDAD DE PALABRAS
    if(!(*esc))
        return; //SI NO HAY NINGUN CARACTER MAS VUELVO DE LA FUNCION
    esc++; //PARA SALTARME EL PUNTO
    //SEGUNDA PALABRA//
    while(*esc)
    {
        while(*esc && *esc!='.') //MIENTRAS HAYA UN CARACTER Y SEA DISTINTO DE UN PUNTO
        {
            if(*esc==*lec && may<lonPri) //COMPARA CARACATER A CARACTER CON LA PRIMER PALABRA Y SI MAY ES MENOR A LA LONGITUD DE LA PRIMER PALABRA
            {
                lec++; //ME MUEVO EN LA PRIMER PALABRA
            }
            else
                lec=c; //SI NO SON IGUALES O ESTA PALABRA ES MAS GRANDE QUE LA PRIMERA, lec VUELVE AL PRINCIPIO
            esc++;
            if(may==(lonPri-1) && *lec=='.' && (*esc=='.' || *esc=='\0')) //SI LA LONG DE ESTA PALABRA ES IGUAL A LA PRIMERA Y lec ES UN PUNTO Y esc ES UN PUNTO O \0
                {
                    (*rep)++; //LA PRIMER PALABRA SE REPITE
                    lec=c; //lec VUELVE AL PRINCIPIO PARA COMPARAR LUEGO
                }
            may++;
        }
        if(may>(*lon)) //SI may ES MAYOR A *lon ENTONCES ES LA PALABRA MAS LARGA POR AHORA
            *lon=may;
        may=0;
        (*cant)++; //INCREMENTO LA CANTIDAD DE PALABRAS
        if(!(*esc))
            return;
        esc++;
    }

}

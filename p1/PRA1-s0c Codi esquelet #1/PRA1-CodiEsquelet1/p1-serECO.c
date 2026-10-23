/**************************************************************************/
/*                                                                        */
/* L'aplicació ECO amb sockets TCP/IP                                     */
/* Fitxer serECO.c que implementa el servidor ECO sobre la capa de        */
/* transport TCP (fent crides a la "nova" interfície de la capa de        */
/* transport o "nova" interfície de sockets).                             */
/*                                                                        */
/* Autors:                                                                */
/* Data:                                                                  */
/*                                                                        */
/**************************************************************************/

/* Inclusió de llibreries, p.e. #include <stdio.h> o #include "meu.h"     */

#include "p1-tTCP.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definició de constants, p.e.,                                          */

/* #define XYZ       1500                                                 */

/* Declaració de funcions INTERNES que es fan servir en aquest fitxer     */
/* (les  definicions d'aquestes funcions es troben més avall) per així    */
/* fer-les conegudes des d'aquí fins al final d'aquest fitxer, p.e.,      */

/* int FuncioInterna(arg1, arg2...);                                      */

int obtPort(void);

void comprovarError(int res);

int main(int argc,char *argv[])
{
 /* Declaració de variables, p.e., int n;                                 */
    int sesc, scon, i;
    int bytes_llegits, bytes_escrits;
    char buffer[200];
    char iploc[16];
    int portloc;
    char iprem[16];
    int portrem;

    strcpy(iploc, "0.0.0.0"); // Escolto a local i remot

 /* Expressions, estructures de control, crides a funcions, etc.          */
    portloc = obtPort();

    sesc = TCP_CreaSockServidor(iploc, portloc);
    comprovarError(sesc);

    scon = TCP_AcceptaConnexio(sesc, iprem, &portrem);
    comprovarError(scon);

    return 0;
}

/* Definició de funcions INTERNES, és a dir, d'aquelles que es faran      */
/* servir només en aquest mateix fitxer. Les seves declaracions es troben */
/* a l'inici d'aquest fitxer.                                             */

/* Descripció de la funció, dels arguments, valors de retorn, etc.        */
/*int FuncioInterna(arg1, arg2...)
{
	
} */

int obtPort(void){
    int port;

    printf("A quin port vols escotar? :) \n");
    scanf("%d", &port);

    return port;
}

void comprovarError(int res){
    int codiError;
    char *error;
    if(res == -1){
        error = T_ObteTextRes(&codiError);
        printf("Hem obtingut el seguent error: %s \n", error);
        printf("Amb el seguent codi: %d \n", codiError);

        exit(1);
    }
}

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

#define MAX_BUFFER 200
#define MAX_IP 16

/* Declaració de funcions INTERNES que es fan servir en aquest fitxer     */
/* (les  definicions d'aquestes funcions es troben més avall) per així    */
/* fer-les conegudes des d'aquí fins al final d'aquest fitxer, p.e.,      */

/* int FuncioInterna(arg1, arg2...);                                      */

int obtPort(void);

void comprovarError(int res);

int main(int argc,char *argv[])
{
 /* Declaració de variables, p.e., int n;                                 */
    int sesc, scon;
    int bytes_llegits;
    char buffer[MAX_BUFFER];
    char iploc[MAX_IP], iprem[MAX_IP];
    int portloc, portrem;
    char iplocCon[MAX_IP];
    int portlocCon;

    strcpy(iploc, "0.0.0.0"); // Escolto a local i remot

 /* Expressions, estructures de control, crides a funcions, etc.          */
    portloc = obtPort();

    sesc = TCP_CreaSockServidor(iploc, portloc);
    comprovarError(sesc);
    while(1){
        scon = TCP_AcceptaConnexio(sesc, iprem, &portrem);
        comprovarError(scon);
        comprovarError(TCP_TrobaAdrSockLoc(scon, iplocCon, &portlocCon));
        printf("Socket local: %s : %d\n", iplocCon, portlocCon);
        printf("Socket client: %s : %d\n", iprem, portrem);
        while(1){
            bytes_llegits = TCP_Rep(scon, buffer, MAX_BUFFER-1);
            if (!bytes_llegits)
            {
                printf("La connexio amb el client s'ha tancat\n");
                break;
            }
            comprovarError(bytes_llegits);
            buffer[bytes_llegits] = '\0';
            printf("%s", buffer);
            printf("Nombre de bytes rebuts: %d\n", bytes_llegits);
            comprovarError(TCP_Envia(scon, buffer, bytes_llegits));
        }
        comprovarError(TCP_TancaSock(scon));
    }
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

    printf("A quin port vols escoltar? :) \n");
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

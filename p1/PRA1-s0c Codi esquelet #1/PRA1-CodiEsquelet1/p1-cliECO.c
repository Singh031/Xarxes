/**************************************************************************/
/*                                                                        */
/* L'aplicació ECO amb sockets TCP/IP                                     */
/* Fitxer cliECO.c que implementa el client ECO sobre la capa de          */
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
#include <unistd.h>
#include <string.h>

/* Definició de constants, p.e.,                                          */
#define MAX_BUFFER 200
#define MAX_IP 16
#define LINIA_ESPECIAL "FI\n"
/* #define XYZ       1500                                                 */

/* Declaració de funcions INTERNES que es fan servir en aquest fitxer     */
/* (les  definicions d'aquestes funcions es troben més avall) per així    */
/* fer-les conegudes des d'aquí fins al final d'aquest fitxer, p.e.,      */

/* int FuncioInterna(arg1, arg2...);                                      */
void DemanaIpServidor(char *iprem);
int DemanaPortServidor(void);
void comprovarError(int res);

int main(int argc,char *argv[])
{
 /* Declaració de variables, p.e., int n;                                 */
 int sck, portrem, portloc, portremMostrar;
 int bytes_llegits, bytes_escrits;
 char buffer[MAX_BUFFER];
 char iprem[MAX_IP], ipremMostrar[MAX_IP], iploc[MAX_IP];
 char resposta;

 /* Expressions, estructures de control, crides a funcions, etc.          */
 while(1){
    DemanaIpServidor(iprem);
    portrem = DemanaPortServidor();
    sck = TCP_CreaSockClient("0.0.0.0", 0);
    comprovarError(sck);
    comprovarError(TCP_DemanaConnexio(sck, iprem, portrem));
    comprovarError(TCP_TrobaAdrSockLoc(sck, iploc, &portloc));
    comprovarError(TCP_TrobaAdrSockRem(sck, ipremMostrar, &portremMostrar));
    printf("Socket local: %s : %d\n", iploc, portloc);
    printf("Socket remot: %s : %d\n", ipremMostrar, portremMostrar);
    while(1){
        comprovarError(bytes_llegits = read(0, buffer, MAX_BUFFER-1));
        buffer[bytes_llegits] = '\0';
        if (!strcmp(LINIA_ESPECIAL, buffer)) break;
        comprovarError(bytes_escrits = TCP_Envia(sck, buffer, bytes_llegits));
        printf("Nombre de bytes enviats: %d\n", bytes_escrits);
        bytes_llegits = TCP_Rep(sck, buffer, MAX_BUFFER-1);
        if (!bytes_llegits)
        {
            printf("La connexio amb el servidor s'ha tancat\n");
            break;
        }
        comprovarError(bytes_llegits);
        buffer[bytes_llegits] = '\0';
        printf("%s", buffer);
    }
    comprovarError(TCP_TancaSock(sck));
    printf("Vols continuar o acabar (C/F):");
    scanf(" %c", &resposta);
    if (resposta == 'f' || resposta == 'F') break;
    }
}

/* Definició de funcions INTERNES, és a dir, d'aquelles que es faran      */
/* servir només en aquest mateix fitxer. Les seves declaracions es troben */
/* a l'inici d'aquest fitxer.                                             */

void DemanaIpServidor(char *iprem)
{
    printf("IP del servidor:");
    scanf("%15s", iprem);
}

int DemanaPortServidor()
{
    int port;
    printf("Port del servidor:");
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
/* Descripció de la funció, dels arguments, valors de retorn, etc.        */
/*int FuncioInterna(arg1, arg2...)
{
	
} */

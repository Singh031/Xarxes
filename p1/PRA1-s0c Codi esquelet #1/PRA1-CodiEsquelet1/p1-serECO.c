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
#include <signal.h>
#include <unistd.h>

/* Definició de constants, p.e.,                                          */

/* #define XYZ       1500                                                 */

#define MAX_BUFFER 200
#define MAX_IP 16

/* Declaració de funcions INTERNES que es fan servir en aquest fitxer     */
/* (les  definicions d'aquestes funcions es troben més avall) per així    */
/* fer-les conegudes des d'aquí fins al final d'aquest fitxer, p.e.,      */

/* int FuncioInterna(arg1, arg2...);                                      */

int sesc = -1;
int scon = -1;

int obtPort(void);
void comprovarError(int res, const char *crida);
void tancaSuaument(int senyal);

int main(int argc,char *argv[])
{
 /* Declaració de variables, p.e., int n;                                 */
    int bytes_llegits;
    char buffer[MAX_BUFFER];
    char iploc[MAX_IP], iprem[MAX_IP];
    int portloc, portrem;
    char iplocCon[MAX_IP], iplocEsc[MAX_IP];
    int portlocCon, portlocEsc;

    strcpy(iploc, "0.0.0.0"); // Escolto a local i remot
    if (argc > 1) {
        if (strlen(argv[1]) >= MAX_IP) {
            printf("L'@IP '%s' es massa llarga\n", argv[1]);
            exit(1);
        }
        strcpy(iploc, argv[1]);
    }

 /* Expressions, estructures de control, crides a funcions, etc.          */
    
    signal(SIGINT, tancaSuaument);

    portloc = obtPort();

    sesc = TCP_CreaSockServidor(iploc, portloc);
    comprovarError(sesc, "TCP_CreaSockServidor");
    while(1){
        scon = TCP_AcceptaConnexio(sesc, iprem, &portrem);
        comprovarError(scon, "TCP_AcceptaConnexio");
        comprovarError(TCP_TrobaAdrSockLoc(scon, iplocCon, &portlocCon), "TCP_TrobaAdrSockLoc(scon)");
        comprovarError(TCP_TrobaAdrSockLoc(sesc, iplocEsc, &portlocEsc), "TCP_TrobaAdrSockLoc(sesc)");
        printf("Socket local (scon): %s : %d\n", iplocCon, portlocCon);
        printf("Socket d'escolta (sesc): %s : %d\n", iplocEsc, portlocEsc);
        printf("Socket client: %s : %d\n", iprem, portrem);
        while(1){
            bytes_llegits = TCP_Rep(scon, buffer, MAX_BUFFER-1);
            if (bytes_llegits == 0)
            {
                printf("La connexio amb el client s'ha tancat\n");
                break;
            }
            comprovarError(bytes_llegits, "TCP_Rep");
            buffer[bytes_llegits] = '\0';
            printf("%s", buffer);
            printf("Nombre de bytes rebuts: %d\n", bytes_llegits);
            comprovarError(TCP_Envia(scon, buffer, bytes_llegits), "TCP_Envia");
        }
        comprovarError(TCP_TancaSock(scon), "TCP_TancaSock");
        scon = -1;
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
    if (scanf("%d", &port) != 1){
        printf("Port no valid\n");
        exit(1);
    }
    return port;
}

void comprovarError(int res, const char *crida){
    int codiError;
    char *error;
    if (res == -1){
        error = T_ObteTextRes(&codiError);
        printf("Error a %s: %s (errno = %d)\n", crida, error, codiError);
        exit(1);
    }
}

void tancaSuaument(int senyal)
{
    const char msg[] = "\nCtrl+C rebut: tanco els sockets i acabo.\n";
    ssize_t r;
    (void)senyal;
    r = write(1, msg, sizeof(msg) - 1);
    (void)r;
    if (scon != -1) TCP_TancaSock(scon);
    if (sesc != -1) TCP_TancaSock(sesc);
    _exit(0);
}
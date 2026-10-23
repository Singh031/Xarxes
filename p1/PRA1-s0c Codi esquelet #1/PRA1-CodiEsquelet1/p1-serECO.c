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

/* Definició de constants, p.e.,                                          */

/* #define XYZ       1500                                                 */

/* Declaració de funcions INTERNES que es fan servir en aquest fitxer     */
/* (les  definicions d'aquestes funcions es troben més avall) per així    */
/* fer-les conegudes des d'aquí fins al final d'aquest fitxer, p.e.,      */

/* int FuncioInterna(arg1, arg2...);                                      */
int obtPort();

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

 /* Expressions, estructures de control, crides a funcions, etc.          */
 portloc = obtPort();

 sesc = TCP_CreaSockServidor(iploc, portloc);
 comprovarError(sesc);

 scon = TCP_AcceptaConnexio(sesc, iprem, &portrem);
 comprovarError(scon);

}

/* Definició de funcions INTERNES, és a dir, d'aquelles que es faran      */
/* servir només en aquest mateix fitxer. Les seves declaracions es troben */
/* a l'inici d'aquest fitxer.                                             */

/* Descripció de la funció, dels arguments, valors de retorn, etc.        */
/*int FuncioInterna(arg1, arg2...)
{
	
} */

int obtPort(){
    int port;

    printf("A quin port et voldries conectar? :)");
    scanf(port);

    return port;
}

void comprovarError(int error){
    int codiError;
    if(error == -1){
        T_ObteTextRes(&codiError);
        exit();
    }
}

/* Codi solucio de la practica: CLIENT */

/* Inclusio de fitxers .h habituals */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Inclusio de fitxers .h per als sockets */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
 
#define MIDA_BUFFER 1024

int main(int argc, char **argv){
 
    if (argc != 2) {
        printf("Us: %s IP\n", argv[0]);
        exit(0);
    }
    
    int s;    /* Per treballar amb el socket */
    struct sockaddr_in adr;
    char buffer[MIDA_BUFFER];
    socklen_t mida;

    /* Volem socket d'internet i no orientat a la connexio */
    s = socket(AF_INET, SOCK_DGRAM, 0);

    adr.sin_family = AF_INET;
    adr.sin_port = htons(44444);

    /* L'adreca de comunicacio sera la IP del servidor, es a dir el parametre */
    adr.sin_addr.s_addr = inet_addr(argv[1]);
 
    int num1,num2;
    printf("Introdueix el primer nombre: ");
    scanf("%d", &num1);        
    printf("Introdueix el segon nombre: ");
    scanf("%d", &num2); 
    sprintf(buffer,"%d_%d", num1,num2);
    
    sendto(s, buffer, MIDA_BUFFER, 0, (struct sockaddr*)&adr, sizeof(adr));        
   
    printf("Esperant resultat del servidor\n");
    recvfrom(s, buffer, MIDA_BUFFER, 0, (struct sockaddr*)&adr, &mida);
    printf("El resultat es: %s\n", buffer);

    /* Tanquem el socket */
    close(s);
    return 0;
}
/* SERVIDOR */

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
 
int main( ){
 
    int s;    /* Per treballar amb el socket */
    struct sockaddr_in serv_adr, client_adr;
    char buffer[MIDA_BUFFER];
    socklen_t mida;
    int n;
    
    /* Volem socket d'internet i no orientat a la connexio */
    s = socket(AF_INET, SOCK_DGRAM, 0);

    /* Posem les dades del socket */
    
    serv_adr.sin_family =  AF_INET;
    serv_adr.sin_addr.s_addr = INADDR_ANY;
    serv_adr.sin_port =  htons(44444);
   
    /* Enllacem el socket */
    n = bind(s, (struct sockaddr*)&serv_adr, sizeof(serv_adr));

    if (n < 0)
    {
        printf("No s'ha pogut enllacar el socket\n");
    }
    else
    {
        
        /* Servidor operatiu! */
        printf("Servidor operatiu!\n");
        printf("Esperant peticions del client\n");
        recvfrom(s, buffer, MIDA_BUFFER, 0, (struct sockaddr*)&client_adr, &mida);
        
        printf("Peticio rebuda\n");
        int a,b;
        sscanf(buffer,"%d_%d", &a,&b);
        b = a*b;
        
        sprintf(buffer,"%d", b);
        
        sendto(s, buffer, MIDA_BUFFER, 0, (struct sockaddr*)&client_adr, sizeof(client_adr));
        
    }

    /* Tanquem el socket */
    close(s);
    return 0;
}
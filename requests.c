/* Mirciu Andrei-Constantin */
/* 323CD */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include "parson.h" /* pentru a putea utiliza functii de parsare JSON */

char *compute_get_request(const char *method, const char *host, const char *url, const char *url_params, 
    const char *token, const char *firstCookie, const char *secondCookie)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
  
    if (url_params != NULL)
    {
        sprintf(line, "%s %s?%s HTTP/1.1", method, url, url_params);
    }
    else
    {
        sprintf(line, "%s %s HTTP/1.1", method, url);
    }
    compute_message(message, line);

    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    if (token != NULL) {
        sprintf(line, "Authorization: Bearer %s", token);
        compute_message(message, line);
    }
    
    if (firstCookie != NULL && secondCookie != NULL) {
        sprintf(line, "Cookie: %s;%s", firstCookie, secondCookie);
        compute_message(message, line);
    }
    

    compute_message(message, "");
  
    return message;
}
char *compute_post_request(const char *method, const char *host, const char *url, const char *form_data, 
    const char *type, const char *firstCookie, const char *secondCookie)
{
    
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    memset(message, 0, BUFLEN);
    memset(line, 0, LINELEN);
   
    sprintf(line, "%s %s HTTP/1.1", method, url);
    compute_message(message, line);

    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    if (firstCookie != NULL && secondCookie != NULL) {
        sprintf(line, "Cookie: %s;%s", firstCookie, secondCookie);
        compute_message(message, line);
    }
    
    sprintf(line, "Content-Type: %s", type);
    compute_message(message, line);
    sprintf(line, "Content-Length: %ld", strlen(form_data));
    compute_message(message, line);

    compute_message(message, "");

    compute_message(message, form_data);

    return message;
}
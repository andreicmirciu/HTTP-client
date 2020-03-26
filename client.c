/* Mirciu Andrei-Constantin */
/* 323CD */
#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include "parson.h" /* pentru a putea utiliza functii de parsare JSON */

int main(int argc, char *argv[])
{
    char *message; // mesajul pe care il trimit
    char *response; // raspunsul pe care il primesc
    int sockfd;
    /* -----------------------TASK 1----------------------- */

    // deschid conexiunea la adresa IP si portul specificate
    sockfd = open_connection(IP_SERVER, PORT_SERVER, AF_INET, SOCK_STREAM, 0);
    // creez mesajul de request
    message = compute_get_request("GET", IP_SERVER, "/task1/start", NULL, NULL, NULL, NULL);
    // trimit mesajul
    send_to_server(sockfd, message);
    // primesc raspunsul
    response = receive_from_server(sockfd);
    // inchid conexiunea
    close_connection(sockfd);
    // afisez raspunsul primit in urma requestului
    printf("%s\n", response);
    free(message);
    
    /* -----------------------TASK 2----------------------- */

    // caut de unde incepe body-ul raspunsului primit (partea cu JSON)
    char *json_content_from_response = strchr(response, '{');
    // parsez JSON intr-un string
    JSON_Value *json_value = json_parse_string(json_content_from_response);
    // creez un obiect de tip JSON_Object pentru a putea extrage valorile
    // anumitor campuri, asemanator cu structurile
    JSON_Object *json_obj = json_value_get_object(json_value);
    // extrag informatiile primite in raspuns
    const char *url = json_object_dotget_string(json_obj, "url");
    const char *method = json_object_dotget_string(json_obj, "method");
    const char *type = json_object_dotget_string(json_obj, "type");
    const char *username = json_object_dotget_string(json_obj, "data.username");
    const char *password = json_object_dotget_string(json_obj, "data.password");

    // vector in care retin informatiile necesare pentru autentificare
    char login[BUFLEN];
    // folosesc strcpy la inceput ca sa nu afiseze garbage
    strcpy(login, "username=");
    strcat(login, username);
    strcat(login, "&");
    strcat(login, "password=");
    strcat(login, password);
    
    // vector in care retin raspunsul primit, deoarece functiile precum
    // strstr, strtok etc. modificau permanent raspunsul si nu il
    // puteam refolosi
    char retain_response[BUFLEN];
    strcpy(retain_response, response);

    // primul Cookie
    char *firstCookie;
    firstCookie = strstr(response, "prajiturica");
    firstCookie = strtok(firstCookie, ";");
    
    strcpy(response, retain_response);
   
    // al doilea Cookie 
    char *secondCookie;
    secondCookie = strstr(response, "prajiturica.sig");
    secondCookie = strtok(secondCookie, ";");

    // deschid conexiunea
    sockfd = open_connection(IP_SERVER, PORT_SERVER, AF_INET, SOCK_STREAM, 0);
    firstCookie = strtok(firstCookie, ";");
    // creez mesajul de request
    message = compute_post_request(method, IP_SERVER, url, login, 
        type, firstCookie, secondCookie);
    // trimit mesajul
    send_to_server(sockfd, message);
    // inainte sa primesc noul raspuns, eliberez ce era inainte
    free(response);
    // primesc raspunsul
    response = receive_from_server(sockfd);
    // inchid conexiunea
    close_connection(sockfd);
    // afisez raspunsul primit in urma requestului
    printf("\n%s\n", response);
    free(message);

    /* -----------------------TASK 3----------------------- */

    // retin raspunsul
    strcpy(retain_response, response);
    // caut de unde incepe body-ul raspunsului primit (partea cu JSON)
    json_content_from_response = strchr(response, '{');
    // parsez JSON intr-un string
    json_value = json_parse_string(json_content_from_response);
    json_obj = json_value_get_object(json_value);
    // extrag informatiile primite in raspuns
    url = json_object_dotget_string(json_obj, "url");
    method = json_object_dotget_string(json_obj, "method");
    const char *token = json_object_dotget_string(json_obj, "data.token");
    const char *id = json_object_dotget_string(json_obj, "data.queryParams.id");
    // retin informatiile necesare pentru autentificare
    memset(login, 0, BUFLEN);
    strcpy(login, "raspuns1=omul&raspuns2=numele&");
    strcat(login, "id=");
    strcat(login, id);

    // primul Cookie
    firstCookie = strstr(response, "prajiturica");
    firstCookie = strtok(firstCookie, ";");

    strcpy(response, retain_response);

    // al doilea Cookie 
    secondCookie = strstr(response, "prajiturica.sig");
    secondCookie = strtok(secondCookie, ";");
    // deschid conexiunea
    sockfd = open_connection(IP_SERVER, PORT_SERVER, AF_INET, SOCK_STREAM, 0);
    firstCookie = strtok(firstCookie, ";");
    // creez mesajul de request
    message = compute_get_request(method, IP_SERVER, url, login, token, firstCookie, secondCookie);
    // trimit mesajul
    send_to_server(sockfd, message);
    // inainte sa primesc noul raspuns, eliberez ce era inainte
    free(response);
    // primesc raspunsul
    response = receive_from_server(sockfd);
    // inchid conexiunea
    close_connection(sockfd);
    // afisez raspunsul primit in urma requestului
    printf("\n%s\n", response);
    free(message);

    /* -----------------------TASK 4----------------------- */

    // retin raspunsul
    strcpy(retain_response, response);
    // caut de unde incepe body-ul raspunsului primit (partea cu JSON)
    json_content_from_response = strchr(response, '{');
    // parsez JSON intr-un string
    json_value = json_parse_string(json_content_from_response);
    json_obj = json_value_get_object(json_value);
    // extrag informatiile primite in raspuns
    url = json_object_dotget_string(json_obj, "url");
    method = json_object_dotget_string(json_obj, "method");
    // primul Cookie
    firstCookie = strstr(response, "prajiturica");
    firstCookie = strtok(firstCookie, ";");

    strcpy(response, retain_response);

    // al doilea Cookie 
    secondCookie = strstr(response, "prajiturica.sig");
    secondCookie = strtok(secondCookie, ";");

    // deschid conexiunea
    sockfd = open_connection(IP_SERVER, PORT_SERVER, AF_INET, SOCK_STREAM, 0);
    firstCookie = strtok(firstCookie, ";");
    // creez mesajul de request
    message = compute_get_request(method, IP_SERVER, url, login, token, firstCookie, secondCookie);
    // trimit mesajul
    send_to_server(sockfd, message);
    // inainte sa primesc noul raspuns, eliberez ce era inainte
    free(response);
    // primesc raspunsul
    response = receive_from_server(sockfd);
    // inchid conexiunea
    close_connection(sockfd);
    // afisez raspunsul primit in urma requestului
    printf("\n%s\n", response);
    free(message);

    /* -----------------------TASK 5----------------------- */

    // retin raspunsul
    strcpy(retain_response, response);
    // caut de unde incepe body-ul raspunsului primit (partea cu JSON)
    json_content_from_response = strchr(response, '{');
    // parsez JSON intr-un string
    json_value = json_parse_string(json_content_from_response);
    json_obj = json_value_get_object(json_value);
    // extrag informatiile primite in raspuns
    url = json_object_dotget_string(json_obj, "url");
    method = json_object_dotget_string(json_obj, "method");
    type = json_object_dotget_string(json_obj, "type");
    // extrag URL-ul din data.url si celelalte info
    const char *newUrl = json_object_dotget_string(json_obj, "data.url");
    const char *q = json_object_dotget_string(json_obj, "data.queryParams.q");
    const char *APPID = json_object_dotget_string(json_obj, "data.queryParams.APPID");
    // retin informatiile necesare pentru cautare
    memset(login, 0, 100);
    strcpy(login, "q=");
    strcat(login, q);
    strcat(login, "&APPID=");
    strcat(login, APPID);
    // primul Cookie
    firstCookie = strstr(response, "prajiturica");
    firstCookie = strtok(firstCookie, ";");

    strcpy(response, retain_response);

    // al doilea Cookie 
    secondCookie = strstr(response, "prajiturica.sig");
    secondCookie = strtok(secondCookie, ";");

    // deschid conexiunea
    sockfd = open_connection(IP_SERVER, PORT_SERVER, AF_INET, SOCK_STREAM, 0);
    firstCookie = strtok(firstCookie, ";");
    // retin URL-ul din data.url
    char retain_newUrl[200];
    strcpy(retain_newUrl, newUrl);
    // extrag numele domeniului
    char *domainName = strtok (retain_newUrl, "/");
    // extrag restul continutului din URL
    newUrl = strstr(newUrl, "/");
    // obtin adresa IP pentru numele domeniului
    struct hostent *name;
    name = gethostbyname(domainName);
    struct in_addr *addr = (struct in_addr*)name -> h_addr_list;
    // creez mesajul de request
    message = compute_get_request(method, inet_ntoa(*addr), newUrl, login,
        NULL, NULL, NULL);
    // trimit mesajul
    send_to_server(sockfd, message);
    // inainte sa primesc noul raspuns, eliberez ce era inainte
    free(response);
    // primesc raspunsul
    response = receive_from_server(sockfd);
    // inchid conexiunea
    close_connection(sockfd);
    // afisez raspunsul primit in urma requestului
    printf("%s\n", response);
    free(message);
    free(response);

    return 0;
}
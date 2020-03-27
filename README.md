# HTTP-client
Realised an HTTP client in C which interacts with a REST API. Used an external library for parsing and creating JSON structures.

In implementarea temei, am realizat mai multe cereri de tip GET/POST la
adresa IP si portul puse la dispozitie. Toate task-urile rezolvate respecta
aproximativ aceeasi structura, in sensul ca am fost nevoit sa extrag anumite 
informatii primite in raspunsurile de la server (in format JSON) pentru a 
putea trimite alte cereri.
## Task1
  Tot ce am avut de facut a fost sa creez un mesaj de 
request de tip GET si sa afisez raspunsul primit.
## Task2
Am extras informatiile de care aveam nevoie in
continuare folosind biblioteca de parsare de JSON Parson pusa la dispozitie
pe github. Dupa ce am format in vectorul 'login' informatiile necesare pentru
autentificare si am extras cele doua cookie-uri, am trimis o cerere de tip 
POST la server.
## Task3
Am oferit raspunsul la cele doua intrebari (omul,
respectiv numele) si le-am imbinat in formatul cerut, am extras cookie-urile
si am trimis cererea de tip GET.
## Task4
In aceeasi maniera, am extras informatiile necesare
si am trimis request-ul GET.
## Task5
Am incercat sa trimit un request GET la adresa IP
obtinuta pe baza numelui domeniului site-ului extras din mesajul primit,
insa nu am reusit.
	Mentionez ca am folosit scheletul de cod de la laboratorul 10 (cel 
cu HTTP).

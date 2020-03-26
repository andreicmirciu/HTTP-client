/* Mirciu Andrei-Constantin */
/* 323CD */
#ifndef _REQUESTS_
#define _REQUESTS_

char *compute_get_request(const char *method, const char *host, const char *url, const char *url_params,
	const char *token, const char *firstCookie, const char *secondCookie);
char *compute_post_request(const char *method, const char *host, const char *url, const char *form_data, 
	const char *type, const char *firstCookie, const char *secondCookie);

#endif
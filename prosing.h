/*
 *	work with string single file library
 *	parsa mahmoudy 2022
 */
#ifndef _PROSING_H
#define _PROSING_H

typedef struct string_t {
	char *value;
	int len;
} string;

/*
 *	functions declerations
 */
int prosing_string_lenght(string *);

#endif

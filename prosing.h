/*
 *	work with string single file library
 *	parsa mahmoudy 2022
 */
#ifndef _PROSING_H
#define _PROSING_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct string_t {
	char *value;
	int len;
} string;

/*
 *	this is main routine for create new string
 *	we will caluculate value len
 */
string *prosing_string_init(char *value);

/*
 *	allocate and return duplicate of given string
 */
char *prosing_string_dup(char *);

/*
 *	reverse string and save it into given string
 */
void prosing_string_reverse(string *);

/*
 *	functions declerations, work with char
 *  because string struct have len prop and we
 *  dont need to call function to calculate string
 *  len
 */
int prosing_string_lenght(char *);

// ===========================
// implementation of functions
// ===========================

int prosing_string_lenght(char *str)
{
	int res = 0;
	char *temp = str;
	while (*temp++)
    	res++;
	return res;
}

char *prosing_string_dup(char *str)
{
    int len = prosing_string_lenght(str);
	char *new = (char *)malloc(len);
	memcpy(new,str,len);
	return new;
}

string *prosing_string_init(char *value)
{
    int len = prosing_string_lenght(value);
    string *str = malloc(sizeof(string));
    assert(str != NULL);
    str->value = prosing_string_dup(value);
    str->len = len;
	return str;
}

void prosing_string_reverse(string *s)
{
    char temp = 0;
	char *last_char = &s->value[s->len - 1],*first_char = s->value;
	char ch;
	for (int i=0;i < s->len / 2;i++) {
		ch = *last_char;
		*last_char = *first_char;
		*first_char = ch;
		first_char++;
		last_char--;
	}
}

#endif

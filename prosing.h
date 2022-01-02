/*
 *	work with string single file library
 *	parsa mahmoudy 2022
 */
#ifndef _PROSING_H
#define _PROSING_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

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
 *	check if given check exist in string
 */
bool prosing_string_contains_char(string *,char);

/*
 *	check if given string exist in string
 */
bool prosing_string_contains_string(string *,char *);

/*
 *	functions declerations, work with char
 *  because string struct have len prop and we
 *  dont need to call function to calculate string
 *  len
 */
int prosing_string_lenght(char *);

/*
 *	compare two string , it works like strcpm
 */
int prosing_string_compare(string *,char *);
int prosing_string_ncompare(string *,char *,int);

bool prosing_string_endwith(string *,char *);

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
	assert(new != NULL);
	memcpy(new,str,len);
	return new;
}

string *prosing_string_init(char *value)
{
	assert(value != NULL);
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

bool prosing_string_contains_char(string *str,char c)
{
	char *s = str->value;
	while (*s) {
		if (*s == c)
			return true;
		s++;
	}
	return false;
}

bool prosing_string_contains_string(string *str,char *s)
{
	int s_len = prosing_string_lenght(s);
	// if second string is bigger than first one , it's not possible to be in first one :)
	if (s_len > str->len)
		return false;
	int i,j,k;
	for (i = 0;i < str->len;i++) {
		if (str->value[i] == s[0]) {
			bool exist = true;
			for (k = i,j = 0;j < s_len;j++,k++) {
				if (str->value[k] == s[j])
					exist = true;
				else {
					exist = false;
					break;
				}
			}
			if (exist)
				return true;
		}
	}
	return false;
}

int prosing_string_compare(string *s1,char *s2)
{
    char *s = s1->value;
    char *t = s2;
	for (; *s == *t;s++,t++) {
		if (*s == '\0')
			return 0;
	}
	return *s - *t;
}

int prosing_string_ncompare(string *s1,char *s2,int n)
{
    char *s = s1->value;
    char *t = s2;
	for (; *s == *t ;s++,t++) {
		if (*s == '\0' || --n <= 0)
			return 0;
	}
	return *s - *t;
}

bool prosing_string_endwith(string *str,char *t)
{
    char *bs = str->value;
    char *bt = t;
    char *ptr = str->value;
    while (*ptr)
        ptr++;
    while (*t)
        t++;
    for (; *ptr == *t; ptr--,t--)
        if (t == bt || ptr == bs)
            break;
   	if (*ptr == *t && *t == *bt && *ptr != '\0')
       	return true;
   	return false;
}

#endif

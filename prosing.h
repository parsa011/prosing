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
char *prosing_string_reverse(string *);

/*
 *	check if given check exist in string
 */
bool prosing_string_contains_char(string *,char);
/*
 *	return how many time given char repeated in string
 */
int prosing_string_ncontains_char(string *,char);

/*
 *	check if given string exist in string
 */
bool prosing_string_contains_string(string *,char *);
/*
 *	return how many time given string repeated in string
 */
int prosing_string_ncontains_string(string *,char *);

/*
 *	functions declerations, work with char
 *  because string struct have len prop and we
 *  dont need to call function to calculate string
 *  len
 */
int prosing_string_length(char *);

/*
 *	compare two string , it works like strcpm
 */
int prosing_string_compare(string *,char *);
int prosing_string_ncompare(string *,char *,int);

bool prosing_string_endwith(string *,char *);

/*
 *	append t to last of str
 */
char *prosing_string_append(string *,char *);
char *prosing_string_append_char(string *,char);

/*
 *	insert char at specified location in string
 */
char *prosing_string_insert_char(string *,char,int);

/*
 *	insert string into string
 */
char *prosing_string_insert_string(string *,char *,int);

/*
 *	substing and save new string in given str
 */
char *prosing_string_substring(string *,int,int);

/*
 *	remove character at given position from string
 */
char *prosing_string_remove(string *,int);
char *prosing_string_remove_range(string *,int,int);

/*
 *	replace old with new in given string and return string
 */
char *prosing_string_replace(string *,char *,char *);

/*
 *	split given stirng by another string
 */
char **prosing_string_split(string *,char *);

// ===========================
// implementation of functions
// ===========================

int prosing_string_length(char *str)
{
	int res = 0;
	char *temp = str;
	while (*temp++)
    	res++;
	return res;
}

char *prosing_string_dup(char *str)
{
    int len = prosing_string_length(str);
	char *new = (char *)malloc(len + 1);
	assert(new != NULL);
	memcpy(new,str,len);
	return new;
}

string *prosing_string_init(char *value)
{
	assert(value != NULL);
    int len = prosing_string_length(value);
    string *str = malloc(sizeof(string));
    assert(str != NULL);
    str->value = prosing_string_dup(value);
    str->len = len;
	return str;
}

char *prosing_string_reverse(string *s)
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
	return s->value;
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

int prosing_string_ncontains_char(string *str,char c)
{
	char *s = str->value;
	int res = 0;
	while (*s) {
		if (*s == c)
			res++;
		s++;
	}
	return res;
}

bool prosing_string_contains_string(string *str,char *s)
{
	int s_len = prosing_string_length(s);
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

int prosing_string_ncontains_string(string *str,char *s)
{
	int s_len = prosing_string_length(s);
	// if second string is bigger than first one , it's not possible to be in first one :)
	if (s_len > str->len)
		return false;
	int i,j,k;
	int res = 0;
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
				res++;
		}
	}
	return res;
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

char *prosing_string_append(string *str,char *t)
{
	assert(t != NULL);
	int t_len = prosing_string_length(t);
	str->value = (char *)realloc(str->value,str->len + 1);
	char *ptr = str->value + str->len;
	while (*ptr++ = *t++);
	str->len += t_len;
	return str->value;
}

char *prosing_string_append_char(string *str,char c)
{
	str->len += 1;
	str->value = (char *)realloc(str->value,str->len + 1);
	char *ptr = str->value + str->len - 1;
	*ptr++ = c;
	*ptr = '\0';
	return str->value;
}

char *prosing_string_insert_char(string *str,char c,int at)
{
	at--;
	assert(at <= str->len && at >= 0);
	str->len++;
	str->value = (char *)realloc(str->value,str->len + 1);
	memcpy(&str->value[at + 1],&str->value[at],str->len - at + 1);
	str->value[at] = c;
	str->value[str->len] = '\0';
	return str->value;
}

char *prosing_string_insert_string(string *str,char *s,int at)
{
	at--;
	assert(at <= str->len && at >= 0);
	int s_len = prosing_string_length(s);
	str->len += s_len;
	str->value = (char *)realloc(str->value,str->len + 1);
	memcpy(&str->value[at + s_len],&str->value[at],str->len - s_len - at + 1);
	char *ptr = &str->value[at];
	while (*s) {
		*ptr++ = *s++;
	}
	return str->value;
}

char *prosing_string_substring(string *str,int from,int to)
{
	from--;
	to--;
	assert(to >= from && from >= 0 && to <= str->len - 1);
	str->len = to - from + 1;
	char *ptr_from = &str->value[from];
	for (int i = 0;i < str->len; i++) {
		str->value[i] = *ptr_from++;
	}
	str->value[str->len] = '\0';
	return str->value;
}

char *prosing_string_remove(string *str,int at)
{
	at--;
	assert(at <= str->len && at >= 0);
	str->len--;
	memcpy(&str->value[at],&str->value[at + 1],str->len - at);
	str->value[str->len] = '\0';
	return str->value;
}

char *prosing_string_remove_range(string *str,int from,int to)
{
	from--;
	to--;
	assert(to >= from && from >= 0 && to <= str->len - 1);
	int offset = to - from + 1;
	str->len -= offset;
	char *ptr = &str->value[to + 1];
	while (*ptr) {
    	*(ptr - offset) = *ptr;
    	ptr++;
	}
	str->value[str->len] = '\0';
	return str->value;
}

char *prosing_string_replace(string *str,char *old,char *new)
{
	int old_len = prosing_string_length(old);
	int new_len = prosing_string_length(new);
	// if second string is bigger than first one , it's not possible to be in first one :)
	if (old_len > str->len)
    	return str->value;
	int i,j,k;
	for (i = 0;i < str->len;i++) {
		if (str->value[i] == old[0]) {
			bool need_replace = true;
			for (k = i,j = 0;j < old_len;j++,k++) {
				if (str->value[k] == old[j])
					need_replace = true;
				else {
					need_replace = false;
					break;
				}
			}
			if (need_replace) {
    			prosing_string_remove_range(str,i + 1,k);
    			prosing_string_insert_string(str,new,i + 1);
    			i += new_len - 1;
			}
		}
	}
	return str->value;
}

char **prosing_string_split(string *str,char *delim)
{
#define BUFSIZE 5
#define ELEMSIZE 20
	int delim_len = prosing_string_length(delim);
	int buf_size = BUFSIZE;
	int elem_size = ELEMSIZE;
	char **buf = (char **)calloc(buf_size,sizeof(char *));
	char *elem = (char *)malloc(elem_size);
	int elemp = 0;
	int bufp = 0;
	for (int i = 0; i < str->len;i++) {
    	if (bufp == buf_size - 1) {
			buf_size += BUFSIZE;
			buf = (char **)realloc(buf,buf_size * sizeof(char *));
    	}
		if (elemp == elem_size - 1) {
			elem_size += ELEMSIZE;
			elem = (char *)realloc(elem,elem_size);
		}
		if (str->value[i] == delim[0]) {
			bool is_delim = true;
			int j,k;
			for (k = i,j = 0;j < delim_len;j++,k++) {
				if (str->value[k] == delim[j])
					is_delim = true;
				else {
					is_delim = false;
					break;
				}
			}
			if (is_delim) {
    			if (elemp == 0) {
        			goto go_next;
    			}
append:
    			elem[elemp] = 0;
    			buf[bufp++] = prosing_string_dup(elem);
    			elemp = 0;
    			elem_size = ELEMSIZE;
go_next:
    			i += delim_len - 1;
    			continue;
			}
		}
		*(elem + elemp++) = str->value[i];
		if (i == str->len - 1)
    		goto append;
	}
	buf[bufp] = 0;
#undef BUFSIZE
#undef ELEMSIZE
	return buf;
}

#endif

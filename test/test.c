#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "../prosing.h"

#define DEFAULT "\033[0m"
#define FAILED "\033[0;31m"
#define SUCCESS "\033[0;32m"

bool test_init_string()
{
    char *name = "parsa";
    int str_len = strlen(name);
    string *str = prosing_string_init(name);
    return str_len = str->len && strcmp(name,str->value) == 0;
}

bool test_string_dup()
{
    char *str = "parsa";
    char *new = prosing_string_dup(str);
    return strcmp(str,new) == 0;
}

bool test_string_length()
{
	return 5 == prosing_string_length("parsa");
}

bool test_string_reverse()
{
	string *str = prosing_string_init("parsa");
	prosing_string_reverse(str);
	return strcmp(str->value,"asrap") == 0;
}

bool test_contains_char()
{
	string *str = prosing_string_init("parsa");
	return prosing_string_contains_char(str,'a');
}

bool test_ncontains_char()
{
	string *str = prosing_string_init("/par/sa/ / /    mahmou/dy/");
	return prosing_string_ncontains_char(str,'/') == 7;
}

bool test_contains_string()
{
	string *str = prosing_string_init("parsa");
	return prosing_string_contains_string(str,"rsa");
}

bool test_ncontains_string()
{
	string *str = prosing_string_init("paars  ///aa aa maahmoudy");
	return prosing_string_ncontains_string(str,"aa") == 4;
}

bool test_string_compare()
{
	string *str = prosing_string_init("parsa");
	return prosing_string_compare(str,"parsa") == 0;
}

bool test_string_ncompare()
{
	string *str = prosing_string_init("parsa");
	return prosing_string_ncompare(str,"parsa",3) == 0;
}

bool test_endwith()
{
	string *str = prosing_string_init("parsa");
	return prosing_string_endwith(str,"sa");
}

bool test_string_append()
{
	string *str = prosing_string_init("parsa");
	prosing_string_append(str," mahmoudy");
	return strcmp(str->value,"parsa mahmoudy") == 0;
}

bool test_string_append_char()
{
	string *str = prosing_string_init("parsa");
	prosing_string_append_char(str,'1');
	prosing_string_append_char(str,'2');
	return strcmp(str->value,"parsa12") == 0;
}

bool test_insert_char()
{
	string *str = prosing_string_init("prsa");
	prosing_string_insert_char(str,'a',2);
	return prosing_string_compare(str,"parsa") == 0;
}

bool test_insert_string()
{
	string *str = prosing_string_init("pmahmoudy");
	prosing_string_insert_string(str,"arsa ",2);
	return prosing_string_compare(str,"parsa mahmoudy") == 0;

}

bool test_substring()
{
	string *str = prosing_string_init("parsa");
	prosing_string_substring(str,4,5);
	return prosing_string_compare(str,"sa") == 0;

}

bool test_remove_at()
{
	string *str = prosing_string_init("p1arsa");
	prosing_string_remove(str,2);
	return prosing_string_compare(str,"parsa") == 0;
}

bool test_remove_range()
{
	string *str = prosing_string_init("p    arsa");
	prosing_string_remove_range(str,2,5);
	return prosing_string_compare(str,"parsa") == 0;

}

const char *test_functions_names[] = {
    "init string",
    "string duplicate",
	"string length",
	"reverse string",
	"string contains char",
	"string ncontains cahr ",
	"string contains string",
	"string ncontains string",
	"compare string full",
	"ncompare test",
	"end with",
	"string append",
	"string append char",
	"string insert char",
	"string insert string",
	"substring",
	"remove at",
	"remove range"
};

bool (*test_functions[])() = {
    test_init_string,
    test_string_dup,
	test_string_length,
	test_string_reverse,
	test_contains_char,
	test_ncontains_char,
	test_contains_string,
	test_ncontains_string,
	test_string_compare,
	test_string_ncompare,
	test_endwith,
	test_string_append,
	test_string_append_char,
	test_insert_char,
	test_insert_string,
	test_substring,
	test_remove_at,
	test_remove_range
};

void log_res(char *state,const char *fmt,...)
{
    printf("%s",state);
	char msg[256];
	va_list ap;
	va_start(ap,fmt);
	vsnprintf(msg,256,fmt,ap);
	va_end(ap);
	printf("result : %s%s",DEFAULT,msg);
	putchar('\n');
}

int main(int argc,char *argv)
{
    int test_func_count = sizeof(test_functions) / sizeof(test_functions[0]);
    for (int i = 0;i < test_func_count;i++) {
		if ((*test_functions[i])() == true) {
    		log_res(SUCCESS,"'%s' passed",test_functions_names[i]);
		} else {
    		log_res(FAILED,"'%s' failed",test_functions_names[i]);
		}
    }
    return 0;
}

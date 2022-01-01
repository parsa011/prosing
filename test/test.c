#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include "../prosing.h"

#define DEFAULT "\033[0m"
#define FAILED "\033[0;31m"
#define SUCCESS "\033[0;32m"

bool test_string_length()
{
	return 6 == prosing_string_lenght("parsa");
}

const char *test_functions_names[] = {
	"test string length"
};

bool (*test_functions[])() = {
	test_string_length
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

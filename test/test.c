#include <stdio.h>
#include <stdbool.h>
#include "../prosing.h"

bool test_string_length()
{
	return 5 == prosing_string_lenght("parsa");
}

bool (*test_function[])() = {
	test_string_length
};

int main(int argc,char *argv)
{
    printf("Hello ,i'm working :))\n");
    int test_func_count = sizeof(test_function) / sizeof(test_function[0]);
    for (int i = 0;i < test_func_count;i++) {
		if ((*test_function[i])() == true) {
			printf("TEST DONE\n");
		}
    }
    return 0;
}

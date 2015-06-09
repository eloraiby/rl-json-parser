#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json-parser.h"

void
test_simple() {
	const char*		json_str	= "{\n\"key\":\"value\"\n}";
	json_value_t*	val			= json_parse(json_str);
}

int
main(int argc, char* argv[]) {

	return 0;
}

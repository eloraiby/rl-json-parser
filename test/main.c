#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json-parser.h"

void
dump(json_value_t* v) {
	switch( v->tag ) {
	case JSON_ARRAY:	printf("Array\n"); break;
	case JSON_BOOLEAN:	printf("Boolean\n"); break;
	case JSON_NONE:		printf("None\n"); break;
	case JSON_NUMBER:	printf("Number\n"); break;
	case JSON_OBJECT:	printf("Object\n"); break;
	case JSON_STRING:	printf("String\n"); break;
	default: break;
	}
}

void
test_simple() {
	const char*		json_str	= "{\n\"key\":\"value\"\n}";
	json_value_t*	val			= json_parse(json_str);
	dump(val);
}

int
main(int argc, char* argv[]) {
	test_simple();
	return 0;
}

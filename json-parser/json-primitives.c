/*
** json-parser Copyright 2015(c) Wael El Oraiby. All Rights Reserved
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** Under Section 7 of GPL version 3, you are granted additional
** permissions described in the GCC Runtime Library Exception, version
** 3.1, as published by the Free Software Foundation.
**
** You should have received a copy of the GNU General Public License and
** a copy of the GCC Runtime Library Exception along with this program;
** see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
** <http://www.gnu.org/licenses/>.
**
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "./private/private.h"

json_pair_t
json_pair		(char* key, json_value_t* value) {
	json_pair_t	pair;
	pair.key	= key;
	pair.value	= value;
	return pair;
}


json_value_t*
json_object		() {
	json_value_t*	object	= (json_value_t*)malloc(sizeof(json_value_t));
	object->tag	= JSON_OBJECT;
	object->value.members	= json_pair_array_new();
	return object;
}

json_value_t*
json_add_pair		(json_pair_t p, json_value_t* v) {
	assert(v->tag == JSON_OBJECT);
	json_pair_array_push(&(v->value.members), p);
	return v;
}

json_value_t*
json_array		() {
	json_value_t*	arr	= (json_value_t*)malloc(sizeof(json_value_t));
	arr->tag	= JSON_ARRAY;
	arr->value.array	= json_value_array_new();

	return arr;
}

json_value_t*
json_add_element	(json_value_t* e, json_value_t* v) {
	assert(v->tag == JSON_ARRAY);
	json_value_array_push(&(v->value.array), e);
	return v;
}

json_value_t*
json_boolean		(bool b) {
	json_value_t*	ret = (json_value_t*)malloc(sizeof(json_value_t));
	ret->tag	= JSON_BOOLEAN;
	ret->value.boolean	= b;
	return ret;
}

json_value_t*
json_number			(double n) {
	json_value_t*	ret = (json_value_t*)malloc(sizeof(json_value_t));
	ret->tag	= JSON_NUMBER;
	ret->value.number	= n;
	return ret;
}

json_value_t*
json_string			(const char* str) {
	json_value_t*	ret = (json_value_t*)malloc(sizeof(json_value_t));
	ret->tag	= JSON_STRING;
	ret->value.string	= (char*)malloc(strlen(str) + 1);
	memcpy(ret->value.string, str, strlen(str) + 1);
	return ret;
}

json_value_t*
json_none			()  {
	json_value_t*	ret = (json_value_t*)malloc(sizeof(json_value_t));
	ret->tag	= JSON_NONE;
	return ret;
}

void
json_free(json_value_t* v) {
	switch( v->tag ) {
	case JSON_STRING:
		free(v->value.string);
		break;

	case JSON_NUMBER:
		break;

	case JSON_OBJECT:
		for( size_t c = 0; c < v->value.members.count; ++c ) {
			free(v->value.members.array[c].key);
			json_free(v->value.members.array[c].value);
		}
		json_pair_array_release(&(v->value.members));
		break;

	case JSON_ARRAY:
		for( size_t c = 0; c < v->value.array.count; ++c ) {
			json_free(v->value.array.array[c]);
		}
		json_value_array_release(&(v->value.array));
		break;

	case JSON_BOOLEAN:
		break;

	case JSON_NONE:
		break;
	}

	free(v);
}

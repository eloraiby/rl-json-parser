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

static inline json_value_t*
json_alloc() {
	json_value_t*	v	= (json_value_t*)malloc(sizeof(json_value_t));
	memset(v, 0, sizeof(json_value_t));
	return v;
}

json_pair_t
json_pair		(token_t key, json_value_t* value) {
	json_pair_t	pair;
	pair.key	= (char*)malloc(key.string.e - key.string.s + 1);
	memcpy(pair.key, key.string.s, key.string.e - key.string.s);
	pair.key[key.string.e - key.string.s]	= '\0';
	pair.value	= value;
	return pair;
}


json_value_t*
json_object		() {
	json_value_t*	object	= json_alloc();
	object->tag	= JSON_OBJECT;
	object->members	= json_pair_array_new();
	return object;
}

json_value_t*
json_add_pair		(json_pair_t p, json_value_t* v) {
	assert(v->tag == JSON_OBJECT);
	json_pair_array_push(&(v->members), p);
	return v;
}

json_value_t*
json_array		() {
	json_value_t*	arr	= json_alloc();
	arr->tag	= JSON_ARRAY;
	arr->array	= json_value_array_new();

	return arr;
}

json_value_t*
json_add_element	(json_value_t* e, json_value_t* v) {
	assert(v->tag == JSON_ARRAY);
	json_value_array_push(&(v->array), e);
	return v;
}

json_value_t*
json_boolean		(bool b) {
	json_value_t*	ret = json_alloc();
	ret->tag	= JSON_BOOLEAN;
	ret->boolean	= b;
	return ret;
}

json_value_t*
json_number			(double n) {
	json_value_t*	ret = json_alloc();
	ret->tag	= JSON_NUMBER;
	ret->number	= n;
	return ret;
}

json_value_t*
json_string			(const char *s, const char *e) {
	json_value_t*	ret = json_alloc();
	ret->tag	= JSON_STRING;
	ret->string	= (char*)malloc(e - s + 1);
	memcpy(ret->string, s, e - s);
	ret->string[e - s]	= '\0';

	return ret;
}

json_value_t*
json_none			()  {
	json_value_t*	ret = json_alloc();
	ret->tag	= JSON_NONE;
	return ret;
}

void
json_free(json_value_t* v) {
	if( v ) {
		switch( v->tag ) {
		case JSON_STRING:
			free(v->string);
			break;

		case JSON_NUMBER:
			break;

		case JSON_OBJECT:
			for( size_t c = 0; c < v->members.count; ++c ) {
				free(v->members.array[c].key);
				json_free(v->members.array[c].value);
			}
			json_pair_array_release(&(v->members));
			break;

		case JSON_ARRAY:
			for( size_t c = 0; c < v->array.count; ++c ) {
				json_free(v->array.array[c]);
			}
			json_value_array_release(&(v->array));
			break;

		case JSON_BOOLEAN:
			break;

		case JSON_NONE:
			break;
		}

		free(v);
	}
}

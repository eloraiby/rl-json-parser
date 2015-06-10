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

json_pair_t*
json_make_pair		(json_value_t* key, json_value_t* value) {
	assert(key->tag == JSON_STRING);
	json_pair_t*	pair	= (json_pair_t*)malloc(sizeof(json_pair_t));
	pair->key	= key->value.string;
	pair->value	= value;
	return pair;
}

json_members_t*
json_make_members	(json_pair_t* p, json_members_t* m) {
	json_members_t*	nm	= (json_members_t*)malloc(sizeof(json_members_t));
	nm->value	= p;
	nm->next	= m;
	return nm;
}

static int
json_members_count	(json_members_t* m) {
	int	count	= 0;
	while( m ) {
		++count;
		m	= m->next;
	}
	return count;
}

static json_pair_array_t
json_members_to_array	(json_members_t* m) {
	json_pair_array_t	parr;

	if ( m ) {
		parr.count	= json_members_count(m);
		parr.pairs	= (json_pair_t*)malloc(sizeof(json_pair_t) * parr.count);
		int	index	= parr.count - 1;

		while( m ) {
			parr.pairs[index]	= *(m->value);
			m			= m->next;
			--index;
		}

	} else {
		parr.count	= 0;
		parr.pairs	= NULL;
	}
	return parr;
}

/*
 * free the list and the pairs (keep the keys/values)
 */
void
json_free_members(json_members_t* m) {
	json_members_t*	tmp	= NULL;

	while( m ) {
		tmp	= m->next;

		if( m->value ) {
			free(m->value);
		}

		free(m);
		m	= tmp;
	}
}

json_value_t*
json_make_object	(json_members_t* m) {
	json_value_t*	object	= (json_value_t*)malloc(sizeof(json_value_t));
	object->tag	= JSON_OBJECT;
	object->value.members	= json_members_to_array(m);
	return object;
}

json_elements_t*
json_make_elements	(json_value_t* v, json_elements_t* e) {
	json_elements_t*	ne	= (json_elements_t*)malloc(sizeof(json_elements_t));
	ne->value	= v;
	ne->next	= e;
	return ne;
}

/*
 * free the list (keep the values)
 */
void
json_free_elements	(json_elements_t* e) {
	json_elements_t*	tmp	= NULL;

	while( e ) {
		tmp	= e->next;

		free(e);
		e	= tmp;
	}
}

static int
json_elements_count	(json_elements_t* e) {
	int	count	= 0;
	while( e ) {
		++count;
		e	= e->next;
	}
	return count;
}

json_value_t*
json_make_array(json_elements_t* e) {
	json_value_t*	arr	= (json_value_t*)malloc(sizeof(json_value_t));
	arr->tag	= JSON_ARRAY;

	if ( e ) {
		arr->value.array.count	= json_elements_count(e);
		arr->value.array.values	= (json_value_t**)malloc(sizeof(json_value_t*) * arr->value.array.count);
		int		index	= arr->value.array.count - 1;

		while( e ) {
			arr->value.array.values[index]	= e->value;
			e	= e->next;
			--index;
		}

	} else {
		arr->value.array.count	= 0;
		arr->value.array.values	= NULL;
	}

	return arr;
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
		for( int c = 0; c < v->value.members.count; ++c ) {
			free(v->value.members.pairs[c].key);
			json_free(v->value.members.pairs[c].value);
		}
		free(v->value.members.pairs);
		break;

	case JSON_ARRAY:
		for( int c = 0; c < v->value.array.count; ++c ) {
			json_free(v->value.array.values[c]);
		}
		free(v->value.array.values);
		break;

	case JSON_BOOLEAN:
		break;

	case JSON_NONE:
		break;
	}

	free(v);
}

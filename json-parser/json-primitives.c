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
#include <assert.h>

#include "./private/private.h"

json_pair_t*
json_make_pair		(json_value_t* key, json_value_t* value) {
	json_pair_t*	pair	= (json_pair_t*)malloc(sizeof(json_pair_t));
	pair->key	= key;
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

json_value_t*
json_make_object	(json_members_t* m) {
	json_value_t*	object	= (json_value_t*)malloc(sizeof(json_value_t));
	object->tag	= JSON_OBJECT;
	object->value.members	= members_to_array(m);
	free_members(m);
	return object;
}

json_elements_t*	json_make_elements	(json_value_t*, json_elements_t*);

json_value_t*		json_make_array		(json_elements_t*);

json_value_t*		json_boolean		(bool);
json_value_t*		json_number			(double);
json_value_t*		json_string			(const char*);
json_value_t*		json_none			();

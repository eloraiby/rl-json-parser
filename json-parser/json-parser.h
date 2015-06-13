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
#ifndef JSON_PARSER__H
#define JSON_PARSER__H

#ifndef __cplusplus
#	ifndef bool
#		define bool char
#	endif

#	ifndef false
#		define false 0
#	endif

#	ifndef true
#		define	true (!false)
#	endif
#endif

#ifndef MIN
#	define MIN(a, b)	((a) < (b) ? (a) : (b))
#endif

#include <string.h>

#define DECLARE_VEC_TYPE(NAME, TYPE)	\
			typedef struct { \
				size_t	count; \
				size_t  _max; \
				TYPE*	array; \
			} NAME; \
			static inline NAME	NAME ## _new()					{ NAME v; v.count = 0; v._max = 0; v.array = NULL; return v; } \
			static inline void	NAME ## _release(NAME* v)			{ v->count = 0; v->_max = 0; free(v->array); v->array = NULL; } \
			static inline TYPE	NAME ## _get(NAME* v, size_t idx)		{ return v->array[idx]; } \
			static inline void	NAME ## _set(NAME* v, size_t idx, TYPE t)	{ v->array[idx] = t; } \
			static inline TYPE	NAME ## _pop(NAME* v)				{ TYPE t = v->array[--(v->count)]; return t; } \
			static inline void	NAME ## _push(NAME* v, TYPE e)			{ if( v->count == v->_max ) { \
												       v->_max = v->_max ? (v->_max) << 1 : 2; \
												       v->array = (TYPE*)realloc(v->array, sizeof(TYPE) * v->_max);	\
												  } \
												  v->array[(v->count)++] = e; \
												} \
			static inline NAME	NAME ## _copy(NAME* orig)			{ NAME dest; \
												  dest.count = orig->count; \
												  dest._max = orig->_max; \
												  dest.array = (TYPE*)malloc(sizeof(TYPE) * orig->_max); \
												  memcpy(dest.array, orig->array, sizeof(TYPE) * orig->_max); \
												  return dest; \
												} \
			static inline void	NAME ## _resize(NAME* v, size_t s)		{ v->_max = s; v->count = MIN(v->count, s); v->array = (TYPE*)realloc(v->array, sizeof(TYPE) * s); }



#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	JSON_STRING,
	JSON_NUMBER,
	JSON_OBJECT,
	JSON_ARRAY,
	JSON_BOOLEAN,
	JSON_NONE
} JSON_TYPE;

struct json_value_s;

typedef struct {
	char*			key;
	struct json_value_s*	value;
} json_pair_t;

DECLARE_VEC_TYPE(json_pair_array_t, json_pair_t)
DECLARE_VEC_TYPE(json_value_array_t, struct json_value_s*)

typedef struct json_value_s {
	JSON_TYPE			tag;

	union {
		bool			boolean;
		char*			string;
		double			number;
		json_pair_t		pair;
		json_pair_array_t	members;
		json_value_array_t	array;
	} value;
} json_value_t;

extern json_value_t*	json_parse(const char* str);
extern void		json_free(json_value_t*);
#ifdef __cplusplus
}
#endif

#endif // JSON_PARSER__H


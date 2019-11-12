#pragma once

#ifndef OBJECT_H_
#define OBJECT_H_
#ifdef __cplusplus
extern "C" {
#endif
#define JObject_HEAD \
	struct _object *_next,*_prev;	\
	int refcnt;	\
	struct _typeObject* type;

#define JObject_HEAD_INIT(type)	0,0,1,type,

#define JObject_VAR_HEAD \
	JObject_HEAD	\
	int size;

typedef struct _object {
	JObject_HEAD
}JObject;

typedef enum {
	OBJ_INT,
	OBJ_PAIR
}ObjectType;

typedef struct {
	JObject_VAR_HEAD
}JVarObject;

typedef struct sObject {
	struct sObject* next;
	unsigned char marked;
	ObjectType type;
	union {
		int value;
		struct {
			struct sObject* head;
			struct sObject* tail;
		};
	};
}Object;

typedef int (*printfunc)(JObject*);
typedef JObject * (*getattr)(JObject*);
typedef long (*hashfunc)(JObject*);

typedef JObject * (*binaryfunc)(JObject*, JObject*);

typedef struct {
	binaryfunc nb_add;
	binaryfunc nb_sub;
	binaryfunc nb_mul;
	binaryfunc nb_div;
}JNumberMethods;

typedef struct _typeObject {
	JObject_VAR_HEAD

	const char* name;

	int basic_size, itemsize;

	printfunc f_print;
	getattr f_getattr;
	hashfunc f_hash;

	JNumberMethods* tp_number;

}JTypeObject;
#ifdef __cplusplus
}
#endif
#endif // !OBJECT_H_
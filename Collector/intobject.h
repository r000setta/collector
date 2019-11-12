#pragma once
#ifndef J_INTOBJECT_H
#define J_INTOBJECT_H
#include "Object.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	JObject_HEAD	\
	long value;
}JIntObject;

#ifndef NSMALLPOSINTS
#define NSMALLPOSINTS 256
#endif // !NSMALLPOSINTS

#ifndef NSMALLNEGINTS
#define NSMALLNEGINTS 5
#endif // !NSMALLNEGINTS

#if NSMALLNEGINTS+NSMALLPOSINTS>0
static JIntObject* small_ints[NSMALLNEGINTS + NSMALLPOSINTS];
#endif // 

#define BLOCK_SIZE 1000
#define BHEAD_SIZE 8
#define N_INT_OBJECTS ((BLOCK_SIZE-BHEAD_SIZE)/sizeof(JIntObject))


typedef struct _intBlock {
	struct _intBlock* next;
	JIntObject objects[N_INT_OBJECTS];
}JIntBlock;

JIntObject* fill_free_list();
void int_dealloc(JIntObject* v);
JObject* JInt_FromLong(long val);
int int_print(JIntObject* obj);
long int_hash(JIntObject* obj);
JObject* int_add(JIntObject* v, JIntObject* w);
JObject* int_mul(JIntObject* v, JIntObject* w);
JObject* int_div(JIntObject* v, JIntObject* w);
JObject* int_sub(JIntObject* v, JIntObject* w);

#ifdef __cplusplus
}
#endif
#endif // !J_INTOBJECT_H
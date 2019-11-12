#include "Jython.h"

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

static JIntBlock* blockList = NULL;
static JIntObject* freeList = NULL;

/*
创建新的Block
*/
static JIntObject* fill_free_list() {
	JIntObject* p, * q;
	p = (JIntObject*)malloc(sizeof(JIntBlock));
	((JIntBlock*)p)->next = blockList;	//链接到已有的block list中
	//将objects转换为单向链表
	p = &((JIntBlock*)p)->objects[0];
	q = p + N_INT_OBJECTS;
	while (--q > p) {
		q->type = (struct _typeObject*)(q - 1);
	}
	q->type = NULL;
	return p + N_INT_OBJECTS - 1;
}

static void int_dealloc(JIntObject* v) {
	v->type = (struct _typeObject*)freeList;
	freeList = v;
}
extern JTypeObject JType_Type;

//int _JInt_Init() {
//	JIntObject* v;
//	int val;
//#if NSMALLNEGINTS+NSMALLPOSINTS>0
//	for (val = -NSMALLNEGINTS; val < NSMALLPOSINTS; val++) {
//		if (!freeList && (freeList = fill_free_list()) == NULL)
//			return 0;
//		v = freeList;
//		freeList = (JIntObject*)v->type;
//		v->value = val;
//		small_ints[val + NSMALLNEGINTS] = v;
//	}
//#endif // 
//}

JObject* JInt_FromLong(long val) {
	JIntObject* v;
	if (-NSMALLNEGINTS <= val && val < NSMALLPOSINTS &&
		(v = small_ints[val + NSMALLNEGINTS]) != NULL) {
		return (JObject*)v;
	}
	if (freeList == NULL) {
		if ((freeList = fill_free_list()) == NULL)
			return NULL;
	}
	v = freeList;
	freeList = (JIntObject*)v->type;
	// TODO: Object Impl
	v->value = val;
#if NSMALLNEGINTS+NSMALLPOSINTS>0
	if (-NSMALLNEGINTS <= val && val < NSMALLPOSINTS) {
		small_ints[val + NSMALLNEGINTS] = v;
	}
#endif // 
	return (JObject*)v;
}


static int int_print(JIntObject* obj) {
	printf("%ld",obj->value);
	return 0;
}

static long int_hash(JIntObject* obj) {
	long x = obj->value;
	if (x == -1)
		x -= 2;
	return x;
}

static JObject* int_add(JIntObject* v, JIntObject* w) {
	register long a, b, x;
	a = v->value;
	b = w->value;
	x = a + b;
	return JInt_FromLong(x);
}

static JObject* int_mul(JIntObject* v, JIntObject* w) {
	register long a, b, x;
	a = v->value;
	b = w->value;
	x = a * b;
	return JInt_FromLong(x);
}

static JObject* int_div(JIntObject* v, JIntObject* w) {
	register long a, b, x;
	a = v->value;
	b = w->value;
	x = a / b;
	return JInt_FromLong(x);
}

static JObject* int_sub(JIntObject* v, JIntObject* w) {
	register long a, b, x;
	a = v->value;
	b = w->value;
	x = a - b;
	return JInt_FromLong(x);
}

static JNumberMethods int_as_number = {
	(binaryfunc)int_add,
	(binaryfunc)int_sub,
	(binaryfunc)int_mul,
	(binaryfunc)int_div,
};

JTypeObject JInt_Type = {
	JObject_HEAD_INIT(&JType_Type)
	0,
	"int",
	sizeof(JIntObject),
	0,
	(printfunc)int_print,
	NULL,
	(hashfunc)int_hash,
	&int_as_number,
};

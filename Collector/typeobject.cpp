#include "Jython.h"

JTypeObject JType_Type = {
	JObject_HEAD_INIT(&JType_Type)
	0,	/*size*/
	"type",	/*name*/
	sizeof(JTypeObject),
	0,	/*item_size*/
	0,	/*func_print*/
	0,	/*func_getattr*/
	0,	/*func_hash*/
	0,	/*tp_number*/
};
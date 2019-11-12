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
#ifdef __cplusplus
}
#endif
#endif // !J_INTOBJECT_H
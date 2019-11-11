#pragma once
#ifndef VM_H_
#define VM_H_
#include "Object.h"
#include <stdlib.h>
#include <cassert>

#define STACK_MAX 256

typedef struct {
	Object* stack[STACK_MAX];
	int stackSize;
	Object* firstObject;
	int numObject;
	int maxObject;
}VM;
VM* newVM();
void push(VM* vm, Object* object);
Object* pop(VM* vm);
void pushInt(VM* vm, int value);
Object* pushPair(VM* vm);
Object* newObject(VM* vm, ObjectType type);

#endif // !GC_H_
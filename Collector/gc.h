
#ifndef GC_H_
#define GC_H_
#include "Object.h"
#include "VM.h"
#include <stdlib.h>
#include <cassert>
#include <stdio.h>

void markAll(VM* vm);
void mark(Object* object);
void sweep(VM* vm);

void gc(VM* vm);
void freeVM(VM* vm);

#endif
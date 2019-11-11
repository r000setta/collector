#include "gc.h"


void markAll(VM* vm) {
	for (int i = 0; i < vm->stackSize; i++) {
		mark(vm->stack[i]);
	}
}

void mark(Object* object) {
	if(object->marked){
		return;
	}
	object->marked = 1;
	if (object->type == OBJ_PAIR) {
		mark(object->head);
		mark(object->tail);
	}
}

void sweep(VM* vm) {
	Object** object = &vm->firstObject;
	while (*object)
	{
		if (!(*object)->marked) {
			Object* unreached = *object;
			*object = unreached->next;
			free(unreached);
			vm->numObject--;
		}
		else {
			(*object)->marked = 0;
			object = &(*object)->next;
		}
	}
}

void gc(VM* vm) {
	int numObjects = vm->numObject;
	markAll(vm);
	sweep(vm);
	vm->maxObject = vm->numObject * 2;
	printf("Collected %d objects, %d remaining.\n", numObjects - vm->numObject,
		vm->numObject);
}

void freeVM(VM* vm) {
	vm->stackSize = 0;
	gc(vm);
	free(vm);
}

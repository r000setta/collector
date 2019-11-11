#include "VM.h"


VM* newVM() {
	VM* vm = (VM*)malloc(sizeof(VM));
	vm->firstObject = NULL;
	vm->numObject = 0;
	vm->maxObject = 8;
	vm->stackSize = 0;
	return vm;
}

void push(VM* vm, Object* object) {
	assert(vm->stackSize < STACK_MAX, "Stack overflow!");
	vm->stack[vm->stackSize++] = object;
}

Object* pop(VM* vm) {
	assert(vm->stackSize > 0, "Stack underflow!");
	return vm->stack[vm->stackSize--];
}

Object* newObject(VM* vm, ObjectType type) {
	/*if (vm->numObject == vm->maxObject) {
		gc(vm);
	}*/
	Object* object = (Object*)malloc(sizeof(Object));
	object->type = type;
	object->next = vm->firstObject;
	vm->firstObject = object;
	object->marked = 0;
	vm->numObject++;
	return object;
}

void pushInt(VM* vm, int value) {
	Object* object = newObject(vm, OBJ_INT);
	object->value = value;
	push(vm, object);
}

Object* pushPair(VM* vm) {
	Object* object = newObject(vm, OBJ_PAIR);
	object->tail = pop(vm);
	object->head = pop(vm);

	push(vm, object);
	return object;
}
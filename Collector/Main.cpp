#include "gc.h"
#include <stdio.h>

int main() {
	VM* vm = newVM();
	pushInt(vm, 1);
	pushInt(vm, 2);
	pushInt(vm, 3);
	pop(vm);
	pop(vm);
	gc(vm);
	freeVM(vm);
}
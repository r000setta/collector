#include "Jython.h"

int main() {
	JObject* a = JInt_FromLong(100L);
	JObject* b = JInt_FromLong(110L);
	int_print((JIntObject*)int_add((JIntObject*)a, (JIntObject*)b));
}
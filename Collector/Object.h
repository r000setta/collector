#pragma once

#ifndef OBJECT_H_
#define OBJECT_H_

typedef enum {
	OBJ_INT,
	OBJ_PAIR
}ObjectType;

typedef struct sObject {
	struct sObject* next;
	unsigned char marked;
	ObjectType type;
	union {
		int value;
		struct {
			struct sObject* head;
			struct sObject* tail;
		};
	};
}Object;

#endif // !OBJECT_H_
#ifndef BT_H
#define BT_H

typedef enum 
{
	NUMBER_NODE,
	PLUS_NODE,
	MINUS_NODE,
	TIMES_NODE,
	OVER_NODE
} NodeKind;

struct node;

typedef struct node BT;


#endif

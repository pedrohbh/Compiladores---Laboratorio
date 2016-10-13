#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Bt.h"

struct node
{
	NodeKind kind;
	char data[ 60 ];
	struct node *dir;
	struct node *esq;
};

BT *create_node( NodeKind kind )
{
	BT *node = (BT *)malloc( sizeof( BT ) );
	node->kind = kind;
	node->esq = node->dir = NULL;
	return node;
}

BT *new_leaf( NodeKind kind, char *data )
{
	BT *leaf = create_node( kind );
	strcpy( leaf->data, data );
	return leaf;
}

BT *new_node( NodeKind kind, BT *esq, BT *dir )
{
	BT *node = create_node( kind );
	node->esq = esq;
	node->dir = dir;
	return node;
}

void print_node( BT *node, int level )
{
	printf("%d: Node -- Addr: %p -- Kind: %d -- Data: %d -- Left: %p -- Right: %p\n", level, node, node->kind, node->data, node->l, node->r);

}

void print_bt( BT *tree, int level )
{
	if ( tree->esq != NULL )
		print_bt( tree->esq, level + 1 );
	print_node( tree, level );
	if ( tree->dir != NULL )
		print_bt( tree->dir, level + 1 );
}

void print_tree( BT *tree )
{
	print_bt( tree, 0 );
}

void free_tree( BT *tree )
{
	if ( tree != NULL )
	{
		free_tree( tree->l );
		free_tree( tree->r );
		free( tree );
	}
}



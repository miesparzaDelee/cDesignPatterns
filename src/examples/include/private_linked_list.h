#ifndef PRIVATE_LINKED_LIST
#define PRIVATE_LINKED_LIST

struct sLinL_node
{
	struct sLinL_node* next;
};

struct sLinL_list
{
	hLinL_node head;
	hLinL_node tail;
	LinL_iterateCallback* foreachIterator;
};

#endif

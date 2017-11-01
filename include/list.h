#ifndef __LIST_H_
#define __LIST_H_


struct list_head {
	struct list_head *next, *prev;
};

static inline void list_init(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

static inline void node_list_add(struct list_head *node,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = node;
	node->next = next;
	node->prev = prev;
	prev->next = node;
}

static inline void list_add(struct list_head *node, struct list_head *head)
{
	node_list_add(node, head, head->next);
}


static inline void node_list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
	prev->next = next;
}

static inline void list_del(struct list_head *entry)
{
	node_list_del(entry->prev, entry->next);
	list_init(entry);
}

static inline bool list_empty(struct list_head *head)
{
	return head->next == head;
}

#define list_for_each(pos, head)  for (pos = (head)->next; pos != (head); pos = pos->next)




#endif

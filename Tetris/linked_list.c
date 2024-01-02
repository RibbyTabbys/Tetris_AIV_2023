#include <stddef.h>

struct list_item
{
    struct linked_list *next;
};

struct list_item* list_get_tail(struct list_item* head, struct list_item* item)
{
    if (!head)
    {
        return NULL;
    }
    
    struct list_item* current_item = head;
    struct
};

struct int_item
{
    struct list_item list_item;
    int value;    
};

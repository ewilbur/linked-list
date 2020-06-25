#include "list.h"

node_p node_mknode(void *, node_p);
void   *node_rmnode(node_p *);

void print_int(void *datum) {
    printf("%d:", *(int*)datum);
}

node_p node_mknode(void *datum, node_p next) {
    /* Node costructor. Creates a node with datum and next */
    node_p new_node = NULL;
    if ((new_node = (node_p)malloc(sizeof(node))) != NULL) {
        /* If the memory is properly allocatied for the node, set the
         * corresponding members to the passed parameters
         */
        new_node->datum = datum;
        new_node->next  = next;
    }
    return new_node;
}

void *node_rmnode(node_p *n) {
    /* Remove a node. n gets assigned to the next element
     * and the program returns the pointer to the data that was removed.
     */
    void *datum = NULL;
    node_p tmp_next = NULL;
    if (n != NULL && *n != NULL) {
        node_p tmp_next = (*n)->next;
        datum = (*n)->datum;
        free(*n);
        *n = tmp_next;
    }
    return datum;
}

list list_mklist() {
    /* Create a new empty list */
    list new_list = (list)malloc(sizeof(node_p));
    *new_list = NULL;
    return new_list;
}

void list_rmlist(list l) {
    /* Remove and free all nodes from the list */
    while (!list_empty(l))
        list_popHead(l);
}

void *list_head(list l) {
    /* Return the datam (if it exists) that is at the front of 
     * the list 
     */
    return list_at(l, 0);
}

void *list_last(list l) {
    return list_at(l, list_size(l) - 1);
}

void *list_at(list l, size_t index) {
    size_t i = 0;
    for (i = 0; i < index; ++i) {
        if (*l == NULL) return NULL;
        l = &(*l)->next;
    }
    return (*l)->datum;
}

bool list_empty(list l) {
    return (l == NULL) || (*l == NULL);
}

void list_fmap(list l, functor f) {
    while (*l != NULL) {
        (*l)->datum = f((*l)->datum);
        l = &(*l)->next;
    }
}

void list_imap(list l, ifunctor f) {
    size_t i = 0;
    for (i = 0; *l != NULL; ++i) {
        (*l)->datum = f(i, (*l)->datum);
        l = &(*l)->next;
    }
}

void list_sequence_(list l, action f) {
    while (*l != NULL) {
        f((*l)->datum);
        l = &(*l)->next;
    }
}

void *counter(void *d, void *count) {
    ++*(size_t*)count;
    return count;
}

size_t list_size(list l) {
    size_t count = 0;
    return *(size_t*)list_foldr(counter, &count, l);
}

void *list_foldr(accumulator f, void *initial_datum, list l) {
    if (list_empty(l)) return initial_datum;
    return list_foldr(f, f((*l)->datum, initial_datum), &(*l)->next);
}

void list_cons(list l, void *datum) {
    *l = node_mknode(datum, *l);    
}

void list_snoc(list l, void *datum) {
    for (; *l != NULL; l = &(*l)->next)
        ;
    list_cons(l, datum);
}

void *list_popLast(list l) {
    void *datum = NULL;
    if (!list_empty(l)) {
        while ((*l)->next != NULL)
            l = &(*l)->next;
        datum = (*l)->datum;
        node_rmnode(l);
    }
    return datum;
}

void *list_popHead(list l) {
    void *datum = NULL;
    if (list_empty(l)) return NULL;
    datum = (*l)->datum;
    node_rmnode(l);
    return datum;
}

void list_print(list l, action f) {
    list_sequence_(l, f);
    printf("[]\n");
}

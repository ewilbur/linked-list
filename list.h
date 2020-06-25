#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef void *(*functor)(void*);
typedef void *(*ifunctor)(size_t, void*);
typedef void (*action)(void *);
typedef void *(*accumulator)(void *, void *);

typedef struct node {
    struct node *next;
    void *datum;
} node, *node_p;

typedef node_p *list;
typedef void (*destructor)(void *);


/* List constructor/destructor */
list list_mklist(); /* Construct an empty list */
void list_rmlist(list); /* Delete the list and free all the memory */

/* List accessors */
void *list_head(list); /* Return datum from first element of list */
void *list_last(list); /* Return datum from last element of list */
void *list_at(list, size_t); /* Return datum from index. Null if out of bounds */

/* List query */
bool list_empty(list); /* Returns true if list is empty or list is NULL */
size_t list_size(list); /* Return the size of the list */

/* Functor methods */
void list_fmap(list, functor); /* Apply a function (functor) to every element of the list */
void list_imap(list, ifunctor); /* Apply functor with an additional index argument */

/* Traversable methods */
/* Performs an action, in order, in the list. Userful for printing */
void list_sequence_(list, action); /* Apply an action on every element of the list */

/* Foldable methods */
void *list_foldr(accumulator, void *, list); /* Loop through list, accumulating values */

/* List modification */
void list_cons(list, void *); /* Prepend to the list */
void list_snoc(list, void *); /* Append to the list */
void *list_popLast(list); /* Remove the last element from the list and return the datum */
void *list_popHead(list); /* Remove the fist element from the list and return the datum */

/* List misc */
void list_print(list, action); /* Print the list using the action */

#endif /* LIST_H_ */

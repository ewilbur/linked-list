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
list list_mklist();
void list_rmlist(list);

/* List accessors */
void *list_head(list);
void *list_last(list);
void *list_at(list, size_t);

/* List query */
bool list_empty(list);
size_t list_size(list);

/* Functor methods */
void list_fmap(list, functor);
void list_imap(list, ifunctor); /* Apply functor with an additional index argument */

/* Traversable methods */
void list_sequence_(list, action);

/* Foldable methods */
void *list_foldr(accumulator, void *, list);

/* List modification */
void list_cons(list, void *);
void list_snoc(list, void *);
void *list_popLast(list);
void *list_popHead(list);

/* List misc */
void list_print(list, action);

#endif /* LIST_H_ */

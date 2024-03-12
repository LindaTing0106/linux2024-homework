#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef struct __node {
    struct list_head list;
    long value;
} node_t;


struct list_head *list_new()
{
    struct list_head *newnode = malloc(sizeof(struct list_head));
    if (!newnode)
        return NULL;
    INIT_LIST_HEAD(newnode);
    return newnode;
}
bool list_insert_head(struct list_head *head, int i)
{
    if (!head)
        return false;
    node_t *newnode = malloc(sizeof(node_t));
    if (!newnode)
        return false;
    newnode -> value = i;
    
    list_add(&newnode->list,head);
    return true;
}

/* Return number of elements in list */
int list_size(struct list_head *head)
{
    if (!head|list_empty(head)) return 0;
    int len = 0;
    struct list_head *li;

    list_for_each (li, head)
        len++;
    return len;
}

void list_free(struct list_head *list)
{
    node_t *li, *safe;
    list_for_each_entry_safe(li, safe, list,list){
        free(li);
    }
    free(list);

}
/* shuffle array, only work if n < RAND_MAX */
void shuffle(int *array, size_t n)
{
    if (n <= 0)
        return;

    for (size_t i = 0; i < n - 1; i++) {
        size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

/* Verify if list is order */
static bool list_is_ordered(struct list_head *list)
{       
    bool first = true;
    int value;
    struct list_head *li;
    list_for_each(li, list)
        if (first) {
            value = list_entry(li, node_t, list)->value;
            first = false;
        }
        else {
            if (list_entry(li, node_t, list)->value < value)
                return false;
            value = list_entry(li, node_t, list)->value;
        }
    return true;
}

void quick_sort(struct list_head *list)
{
    int n = list_size(list);
    int value;
    int i = 0;
    int max_level = 2 * n;
    struct list_head *begin[max_level];
    struct list_head *result = list_new() , *left = list_new(), *right = list_new();
    
    for (int be = 0; be < max_level; be++){
        begin[be] = list_new();
    }

    begin[0] = list;
            
    while (i >= 0) {
        struct list_head *L = begin[i]->next, *R = begin[i]->prev;
        if (L != R) {
            struct list_head *pivot = L;
            node_t *pivot_node = list_entry(pivot, node_t, list);
            value = pivot_node->value;

            struct list_head *p = pivot->next;
            list_del(pivot);

            while (!list_empty(p)) {
                struct list_head *n = p;
                p = p->next;
                node_t *n_node = list_entry(n, node_t, list);
                list_move(n, n_node->value > value ? right : left); 
            }

            list_splice_init(left, begin[i]);
            list_splice_init(right, begin[i + 2]);
            list_add(pivot, begin[i + 1]);

            i += 2;
        } else {
            if (!list_empty(L))
                list_move(L, result);
            i--;
        }
    }
    list_splice_init(result, list);
}

int main(int argc, char **argv)
{
    struct list_head *list = list_new();
    
    size_t count = 100000;//100000;

    int *test_arr = malloc(sizeof(int) * count);

    for (int i = 0; i < count; ++i)
        test_arr[i] = i;
    shuffle(test_arr, count);

    while (count--)
        list_insert_head(list, test_arr[count]);

    quick_sort(list);

    assert(list_is_ordered(list));
    
    list_free(list);

    free(test_arr);

    return 0;
}
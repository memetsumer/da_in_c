#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define GROWTH_FACTOR 2
#define SHRINK_FACTOR 25
#define INITIAL_CAPACITY 256
size_t reallocation_grow_count = 0;
size_t reallocation_shrink_count = 0;

typedef struct
{
    int *items;
    size_t count;
    size_t capacity;
} da;

da *da_init()
{
    da *da = malloc(sizeof(da));

    if (da == NULL)
    {
        goto fail;
    }

    da->capacity = INITIAL_CAPACITY;
    da->count = 0;
    da->items = malloc(da->capacity * sizeof(int));

    if (da->items == NULL)
    {
        free(da);
        goto fail;
    }

    return da;

fail:
    fprintf(stderr, "Error: Memory allocation failed for da struct.\n");
    exit(1);
}

void da_append(da *da, int item)
{
    if (da->count >= da->capacity)
    {
        reallocation_grow_count++;
        da->items = realloc(da->items, (da->capacity *= GROWTH_FACTOR) * sizeof(int));
    }
    da->items[da->count++] = item;
}

int da_pop(da *da)
{
    if (da->count <= 0)
    {
        fprintf(stderr, "There's no item in the da.\n");
        exit(1);
    }

    int last_item = da->items[da->count - 1];

    size_t capacity_divided_by_growth = da->capacity / SHRINK_FACTOR;
    if (da->count <= capacity_divided_by_growth)
    {
        if (capacity_divided_by_growth > INITIAL_CAPACITY)
        {
            printf("setting capacity to: %zu\n", capacity_divided_by_growth);
            da->capacity = capacity_divided_by_growth;
        }
        else
        {
            da->capacity = INITIAL_CAPACITY;
        }
        reallocation_shrink_count++;
        da->items = realloc(da->items, da->capacity * sizeof(int));
    }

    da->count--;

    return last_item;
}

void da_destroy(da *da)
{
    if (da == NULL)
    {
        return;
    }

    if (da->items != NULL)
    {
        free(da->items);
    }

    free(da);
}
int main(void)
{
    clock_t start_time = clock();
    da *da = da_init();
    printf("da capacity: %zu\n", da->capacity);
    for (int i = 0; i < __INT_MAX__; i++)
    {
        da_append(da, (int)i);
    }

    size_t count = da->count;

    for (size_t i = 0; i < count; i++)
    {
        int x = da_pop(da);
        // printf("popped: %d\n", x);
    }

    printf("da count:%zu\n", da->count);
    printf("da capacity: %zu\n", da->capacity);

    printf("total growed: %zu\n", reallocation_grow_count);
    printf("total shrinked: %zu\n", reallocation_shrink_count);

    da_destroy(da);

    clock_t end_time = clock();
    double elapsed_seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f seconds\n", elapsed_seconds);

    return 0;
}
// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size)
{
    /* TODO: Implement malloc(). */
    void *start = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (start == MAP_FAILED)
        return NULL;

    if (mem_list_add(start, size) != 0) {
        return NULL;
    }

    return start;
}

void *calloc(size_t nmemb, size_t size)
{
	/* TODO: Implement calloc(). */
    // Calculam size-ul total de alocat
    size_t total_size = nmemb * size;

    // Folosim mmap pentru alocare memorie
    void *ptr = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    // Verificam daca s-a alocat memoria
    if (ptr == MAP_FAILED) {
        return NULL;
    }

	// setam toate val la 0
	memset(ptr, 0, total_size);

    return ptr;
}

void free(void *ptr)
{
    struct mem_list *item;
    item = mem_list_find(ptr);

    size_t lungimeBloc = item->len;

    mem_list_del(item->start);
    munmap(ptr, lungimeBloc);
}

void *realloc(void *ptr, size_t size)
{
	/* TODO: Implement realloc(). */

    if (ptr == NULL) {
        return malloc(size);
    }

    if (size == 0) {
        free(ptr);
        return NULL;
    }

    // Aloc bloc nou de memorie
    void *new_ptr = malloc(size);

    // Verific daca s-a alocat memorie
    if (new_ptr == NULL) {
        return NULL;  // Memory allocation failed
    }

    // Fac copierea datelor vechi in blocul de memorie nou alocat
    memcpy(new_ptr, ptr, size);

	// Eliberez blocul gol
    free(ptr);

    return new_ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */

    // Calculez marimea completa
    size_t fullSize = nmemb * size;

    // Use realloc to resize the memory block
    void *new_ptr = realloc(ptr, fullSize);

    return new_ptr;
}

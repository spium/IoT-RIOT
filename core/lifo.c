/*
 * Copyright (C) 2013 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup     core_util
 * @{
 * @file        lifo.c
 * @brief       LIFO buffer implementation
 *
 * @author      Heiko Will <hwill@inf.fu-berlin.de>
 * @}
 */

#include "lifo.h"

#define ENABLE_DEBUG (0)
#include "debug.h"

int lifo_empty(int *array)
{
    return array[0] == -1;
}

void lifo_init(int *array, int n)
{
    DEBUG("lifo_init(%i)\n", n);
    for (int i = 0; i <= n; i++) {
        array[i] = -1;
    }
}

void lifo_insert(int *array, int i)
{
    DEBUG("lifo_insert(%i)\n", i);

    int index = i + 1;

#if DEVELHELP
    if ((array[index] != -1) && (array[0] != -1)) {
        //printf("lifo_insert: overwriting array[%i] == %i with %i\n\n\n\t\tThe lifo is broken now.\n\n\n", index, array[index], array[0]);
    }
#endif

    array[index] = array[0];
    array[0] = i;
}

int lifo_get(int *array)
{
    DEBUG("lifo_get\n");
    int head = array[0];

    if (head != -1) {
        array[0] = array[head + 1];
    }

#if DEVELHELP
    /* make sure a double insert does not result in an infinite
     * resource of values */
    array[head+1] = -1;
#endif

    DEBUG("lifo_get: returning %i\n", head);
    return head;
}


#ifdef WITH_MAIN
#include <stdio.h>
int main()
{
    int array[5];

    lifo_init(array, 4);

    lifo_insert(array, 2);
    lifo_insert(array, 1);
    lifo_insert(array, 3);
    lifo_insert(array, 0);
    lifo_insert(array, 3);
    //printf("get: %i\n", lifo_get(array));
    //printf("get: %i\n", lifo_get(array));
    //printf("get: %i\n", lifo_get(array));
    //printf("get: %i\n", lifo_get(array));
    //printf("get: %i\n", lifo_get(array));
    //printf("get: %i\n", lifo_get(array));
    //printf("get: %i\n", lifo_get(array));
    //printf("get: %i\n", lifo_get(array));
    //printf("get: %i\n", lifo_get(array));

    return 0;
}
#endif

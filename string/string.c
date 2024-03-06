// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>
#define K_ARRAY_SIZE 100

//Pentru implementare am folosit site-ul https://www.techiedelight.com care contine implementari ale acestor functii

char *strcpy(char *destination, const char *source)
{
	/* TODO: Implement strcpy(). */
	if (destination == NULL) {
		return NULL;
	}
	//pointer la inceputul destinatiei
	char *currentPositionDest = destination;

	while (*source != '\0') {
		*destination = *source;
		destination++;
		source++;
	}
	*destination = '\0';

	destination = currentPositionDest;

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncpy(). */
	if (destination == NULL)
		return NULL;

	if (len == 0)
		return destination;

	char *currentPositionDest = destination;

	while (*source != '\0' && len > 0) {
		*destination = *source;
		destination++;
		source++;
		len--;
	}
	// cand sursa e '\0'
	if (len > 0) {
		*destination = '\0';
	}

	destination = currentPositionDest;

	return destination;
}

char *strcat(char *destination, const char *source)
{
	/* TODO: Implement strcat(). */
	if (source == NULL || destination == NULL) {
		return NULL;
	}

	char *start = destination;

	while (*destination != '\0') {
		destination++;
	}

	while(*source != '\0') {
		*destination = *source;
		destination++;
		source++;
	}
	*destination = '\0';

	destination = start;

	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncat(). */
	if (source == NULL || destination == NULL)
		return NULL;

	if (len == 0)
		return destination;

	char *start = destination;

	while (*destination != '\0') {
		destination++;
	}

	while(*source != '\0' && len > 0) {
		*destination = *source;
		destination++;
		source++;
		len--;
	}

	*destination = '\0';

	destination = start;

	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	/* TODO: Implement strcmp(). */
	if (str1 == NULL && str2 == NULL)
		return 0;
	else if (str1 == NULL)
		return -1;
	else if (str2 == NULL)
		return 1;

	while (*str1 != '\0' && *str2 != '\0') {
		if (*str1 != *str2)
			break;

		str1++;
		str2++;
	}

	return *str1 - *str2;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	/* TODO: Implement strncmp(). */
	if (len == 0)
		return 0;

	if (str1 == NULL && str2 == NULL)
		return 0;
	else if (str1 == NULL)
		return -1;
	else if (str2 == NULL)
		return 1;

	while (*str1 != '\0' && *str2 != '\0' && len > 1) {
		if (*str1 != *str2)
			return *str1 - *str2;

		str1++;
		str2++;
		len--;
	}

	return *str1 - *str2;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	/* TODO: Implement strchr(). */
	if (str == NULL)
		return NULL;

	while (*str != c && *str != '\0') {
		str++;
	}

	if (*str == '\0')
		return NULL;

	return (char *)str;
}

char *strrchr(const char *str, int c)
{
	/* TODO: Implement strrchr(). */
	if (str == NULL)
		return NULL;

	const char *lastOccurence = NULL;
	while (*str != '\0') {
		if (*str == c )
			lastOccurence = str;

		str++;
	}

	if (lastOccurence == NULL)
		return NULL;
	else
		return (char *)lastOccurence;
}

char *strstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strstr(). */
	if (haystack == NULL || needle == NULL)
		return NULL;


	size_t lenNeedle = strlen(needle);
	int equal = -1;

	while (*haystack != '\0') {
		if(*haystack == *needle) {
			equal = strncmp(haystack, needle, lenNeedle);
			if (equal == 0)
				return (char *)haystack;
		}
		haystack++;
	}

	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strrstr(). */
	if (haystack == NULL || needle == NULL)
		return NULL;


	size_t lenNeedle = strlen(needle);
	const char *lastOccurence = NULL;
	int equal = -1;

	while (*haystack != '\0') {
		if(*haystack == *needle) {
			equal = strncmp(haystack, needle, lenNeedle);
			if (equal == 0)
				lastOccurence = haystack;
		}

		haystack++;
	}

	if (lastOccurence != NULL)
		return (char *)lastOccurence;

	return NULL;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memcpy(). */
	//cast la char pt destinatie si sursa
	char *dst = (char *) destination;
	char *src = (char *) source;

	if (dst == NULL && src == NULL)
		return NULL;

	while (num > 0) {
		*dst = *src;
		dst++;
		src++;
		num--;
	}

	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memmove(). */
	//cast la char pentru destinatie si sursa
	char *dst = (char *) destination;
	char *src = (char *) source;

	if (dst == src)
		return destination;

	char buf[K_ARRAY_SIZE];

	for (size_t i = 0; i < num; i++) {
		buf[i] = *src;
		src++;
	}

	for(size_t i = 0; i < num; i++) {
		*dst = buf[i];
		dst++;
	}

	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* TODO: Implement memcmp(). */
	unsigned char *str1 = (unsigned char *)ptr1;
    unsigned char *str2 = (unsigned char *)ptr2;

    while (num > 0) {
        if (*str1 < *str2)
            return -1;
        else if (*str1 > *str2)
            return 1;

		str1++;
		str2++;
		num--;
    }

    return 0;
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */

	unsigned char *src = (unsigned char *)source;

	while (num > 0) {
		*src = (unsigned char)value;
		src++;
		num--;
	}

	return source;
}

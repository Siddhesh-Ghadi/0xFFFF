
#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

extern int simulate;
extern int noverify;
extern int verbose;

#define VERBOSE(...) do { if ( verbose ) { fprintf(stderr, __VA_ARGS__); } } while (0)
#define WARNING(...) do { fprintf(stderr, "Warning: "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); } while (0)
#define ERROR_INFO_STR(str, ...) do { if ( str[0] ) fprintf(stderr, "Error: %s: ", str); else fprintf(stderr, "Error: "); fprintf(stderr, __VA_ARGS__); if ( errno ) fprintf(stderr, ": %s\n", strerror(errno)); else fprintf(stderr, "\n"); } while (0)
#define ERROR_STR(str, ...) do { errno = 0; ERROR_INFO_STR(str, __VA_ARGS__); } while (0)
#define ERROR_INFO(...) do { ERROR_INFO_STR("", __VA_ARGS__); } while (0)
#define ERROR(...) do { ERROR_STR("", __VA_ARGS__); } while (0)
#define ERROR_RETURN(str, ...) do { ERROR("%s", str); return __VA_ARGS__; } while (0)

#define ALLOC_ERROR() do { ERROR("Cannot allocate memory"); } while (0)
#define ALLOC_ERROR_RETURN(...) do { ALLOC_ERROR(); return __VA_ARGS__; } while (0)

#define MSLEEP(msec) do { nanosleep(&(struct timespec){ (msec / 1000), (1000L * 1000L * (msec % 1000)) }, NULL); } while (0)

static inline void * MEMMEM(void *haystack, size_t haystacklen, const void *needle, size_t needlelen) {
	for ( size_t i = 0; i < haystacklen; ++i ) {
		for ( size_t j = 0; j < needlelen; ++j ) {
			if ( ((char *)haystack)[i+j] != ((const char *)needle)[j] )
				break;
			if ( j != needlelen - 1 )
				continue;
			return (char *)haystack + i;
		}
	}
	return NULL;
}

#endif

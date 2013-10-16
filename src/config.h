#ifndef LUAFASTCGI_CONFIG_H_
#define LUAFASTCGI_CONFIG_H_

#include <stdbool.h>

typedef struct {
	char listen[32];
	unsigned int backlog;
	unsigned int threads;

	bool sandbox;
	size_t mem_max;
	size_t output_max;
	long int cpu_usec;
	long int cpu_sec;

	char content_type[256];
} LF_config;

LF_config *LF_createconfig(void);
int LF_loadconfig(LF_config *, const char *);

#endif

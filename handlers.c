#include "main.h"

/* Define the flags that can be used in the format string. */
typedef enum {
	PLUS = 1 << 0,
	SPACE = 1 << 1,
	HASH = 1 << 2,
	ZERO = 1 << 3,
	NEG = 1 << 4,
} flag_t;

/* Define the possible length modifiers. */
typedef enum {
	SHORT,
	LONG,
} length_t;

/* Define a structure for storing information about a flag. */
typedef struct {
	char flag;
	flag_t value;
} flag_info_t;

/* Define a structure for storing information about a length modifier. */
typedef struct {
	char modifier;
	length_t value;
} length_info_t;

/* Define a function for handling flags in the format string. */
static unsigned char handle_flags(const char **format, flag_t *flags) {
	flag_info_t flag_info[] = {
		{'+', PLUS},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{0, 0}
	};
	unsigned char ret = 0;
	const char *p = *format;
	while (*p) {
		int i;
		for (i = 0; flag_info[i].flag != 0; i++) {
			if (*p == flag_info[i].flag) {
				ret |= flag_info[i].value;
				p++;
				break;
			}
		}
		if (flag_info[i].flag == 0) {
			break;
		}
	}
	*format = p;
	*flags = ret;
	return ret;
}

/* Define a function for handling length modifiers in the format string. */
static length_t handle_length(const char **format) {
	length_info_t length_info[] = {
		{'h', SHORT},
		{'l', LONG},
		{0, 0}
	};
	const char *p = *format;
	length_t ret = 0;
	for (int i = 0; length_info[i].modifier != 0; i++) {
		if (*p == length_info[i].modifier) {
			p++;
			ret = length_info[i].value;
			break;
		}
	}
	*format = p;
	return ret;
}

/* Define a function for handling the width specifier in the format string. */
static int handle_width(const char **format, va_list args) {
	int ret = 0;
	const char *p = *format;
	while (*p) {
		if (*p == '*') {
			ret = va_arg(args, int);
			p++;
		} else if (*p >= '0' && *p <= '9') {
			ret *= 10;
			ret += (*p - '0');
			p++;
		} else {
			break;
		}
	}
	*format = p;
	return ret;
}

/* Define a function for handling the precision specifier in the format string. */
static int handle_precision(const char **format, va_list args) {
	const char *p = *format;
	int ret = -1;
	if (*p == '.') {
		p++;
		ret = 0;
		if (*p == '*') {
			ret = va_arg(args, int);
			p++;
		} else {
			while (*p >= '0' && *p <= '9') {
				ret *= 10;
				ret += (*p - '0


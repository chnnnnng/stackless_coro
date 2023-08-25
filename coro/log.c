#include "log.h"
#include "common.h"


char log_name[20] = "";


static const char *level_strings[] =
{
  "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};


static const char *level_strings_simple[] =
{
  "T", "D", "I", "W", "E", "F"
};


#ifdef LOG_COMPLEX
static const char *level_colors[] =
{
  "\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"
};
#endif


void log_log(int level, const char *file, int line, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

#ifdef LOG_COMPLEX
	printf("%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ",
		log_name,
		level_colors[level],
		level_strings[level],
		file,
		line
	);
#else
	printf("%s %s: ",
		log_name,
		level_strings_simple[level]
	);
#endif
	vprintf(fmt, ap);
	printf("\n");

	va_end(ap);
}

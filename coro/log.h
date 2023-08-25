#ifndef LOG_H
#define LOG_H

#include <stdarg.h>

/***************************************************************************************************/
/*                                      USER DEFINE HERE                                           */
/***************************************************************************************************/
// #define LOG_COMPLEX

#define LOG_LEVEL_TRACE
// #define LOG_LEVEL_DEBUG
// #define LOG_LEVEL_INFO
// #define LOG_LEVEL_WARN
// #define LOG_LEVEL_ERROR
// #define LOG_LEVEL_FATAL
// #define LOG_LEVEL_QUIET

/***************************************************************************************************/
/*                                      USER DEFINE END                                            */
/***************************************************************************************************/

#ifdef LOG_COMPLEX
  #define filename(x) strrchr(x,'/')?strrchr(x,'/')+1:x
  #define _log(level, ...) log_log(level, filename(__FILE__), __LINE__, __VA_ARGS__)
#else
  #define _log(level, ...) log_log(level, NULL, 0, __VA_ARGS__)
#endif

#ifdef LOG_LEVEL_TRACE
  #define log_trace(...) _log(LOG_TRACE, __VA_ARGS__)
  #define log_debug(...) _log(LOG_DEBUG, __VA_ARGS__)
  #define log_info(...) _log(LOG_INFO, __VA_ARGS__)
  #define log_warn(...) _log(LOG_WARN, __VA_ARGS__)
  #define log_error(...) _log(LOG_ERROR, __VA_ARGS__)
  #define log_fatal(...) _log(LOG_FATAL, __VA_ARGS__)
#endif

#ifdef LOG_LEVEL_DEBUG
  #define log_trace(...)
  #define log_debug(...) _log(LOG_DEBUG, __VA_ARGS__)
  #define log_info(...) _log(LOG_INFO, __VA_ARGS__)
  #define log_warn(...) _log(LOG_WARN, __VA_ARGS__)
  #define log_error(...) _log(LOG_ERROR, __VA_ARGS__)
  #define log_fatal(...) _log(LOG_FATAL, __VA_ARGS__)
#endif

#ifdef LOG_LEVEL_INFO
  #define log_trace(...)
  #define log_debug(...)
  #define log_info(...) _log(LOG_INFO, __VA_ARGS__)
  #define log_warn(...) _log(LOG_WARN, __VA_ARGS__)
  #define log_error(...) _log(LOG_ERROR, __VA_ARGS__)
  #define log_fatal(...) _log(LOG_FATAL, __VA_ARGS__)
#endif

#ifdef LOG_LEVEL_WARN
  #define log_trace(...)
  #define log_debug(...)
  #define log_info(...) 
  #define log_warn(...) _log(LOG_WARN, __VA_ARGS__)
  #define log_error(...) _log(LOG_ERROR, __VA_ARGS__)
  #define log_fatal(...) _log(LOG_FATAL, __VA_ARGS__)
#endif

#ifdef LOG_LEVEL_ERROR
  #define log_trace(...)
  #define log_debug(...)
  #define log_info(...) 
  #define log_warn(...)
  #define log_error(...) _log(LOG_ERROR, __VA_ARGS__)
  #define log_fatal(...) _log(LOG_FATAL, __VA_ARGS__)
#endif

#ifdef LOG_LEVEL_FATAL
  #define log_trace(...)
  #define log_debug(...)
  #define log_info(...) 
  #define log_warn(...)
  #define log_error(...)
  #define log_fatal(...) _log(LOG_FATAL, __VA_ARGS__)
#endif

#ifdef LOG_LEVEL_QUIET
  #define log_trace(...)
  #define log_debug(...)
  #define log_info(...) 
  #define log_warn(...)
  #define log_error(...)
  #define log_fatal(...)
#endif

extern char log_name[20];

enum { LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL };

void log_log(int level, const char *file, int line, const char *fmt, ...);

#endif

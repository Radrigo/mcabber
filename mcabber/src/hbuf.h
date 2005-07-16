#ifndef __HBUF_H__
#define __HBUF_H__ 1

#include <time.h>
#include <glib.h>

// With current implementation a message must fit in a hbuf block,
// so we shouldn't choose a too small size.
#define HBB_BLOCKSIZE   4096    // > 20 please

// Flags:
// - ALLOC: the ptr data has been allocated, it can be freed
// - PERSISTENT: this is a new history line
#define HBB_FLAG_ALLOC      1
#define HBB_FLAG_PERSISTENT 2

#define HBB_PREFIX_IN       1
#define HBB_PREFIX_OUT      2
#define HBB_PREFIX_STATUS   4
#define HBB_PREFIX_AUTH     8
#define HBB_PREFIX_INFO    16
#define HBB_PREFIX_ERR     32

typedef struct {
  time_t timestamp;
  guchar flags;
  char *text;
} hbb_line;

void hbuf_add_line(GList **p_hbuf, const char *text, time_t timestamp,
        guint prefix_flags, guint width);
void hbuf_free(GList **p_hbuf);
void hbuf_rebuild(GList **p_hbuf, unsigned int width);
GList *hbuf_previous_persistent(GList *l_line);

hbb_line **hbuf_get_lines(GList *hbuf, unsigned int n);

#endif /* __HBUF_H__ */

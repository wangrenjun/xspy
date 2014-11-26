#ifndef _XSPYIMPL_H_
#define _XSPYIMPL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

    int pinyin_init(const char *pinyin_db_path);

    int hanzi_to_pinyin(const char *hanzi,
        size_t hanzi_len,
        char **pinyin,
        size_t *pinyin_len,
        int fuzzy,
        int abbr);

    int pinyin_deinit();

#ifdef __cplusplus
}
#endif

#endif /* _XSPYIMPL_H_ */

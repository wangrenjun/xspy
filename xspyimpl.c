#include "xspyimpl.h"

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

#include "pinyin.h"

static int has_8bit_char(const char *s);
static int to_pinyin(char **buf, const char *text, size_t text_len, int fuzzy, int abbr);

int pinyin_init(const char *pinyin_db_path)
{
    if (py_dict_load(pinyin_db_path) < 0)
        return -1;
    return 0;
}

int hanzi_to_pinyin(const char *hanzi,
    size_t hanzi_len,
    char **pinyin,
    size_t *pinyin_len,
    int fuzzy,
    int abbr)
{
    char *pybuf = NULL;

    if (has_8bit_char(hanzi)) {
        int r = to_pinyin(&pybuf, hanzi, hanzi_len, fuzzy, abbr);
        if (r) {
            efree(pybuf);
            return r;
        }
    } else
        return -1;
    *pinyin = pybuf;
    *pinyin_len = strlen(pybuf);
    return 0;
}

int pinyin_deinit()
{
    py_dict_unload();
    return 0;
}

static int has_8bit_char(const char *s)
{
    unsigned char *p = (unsigned char *)s;
    while (*p) {
        if (*p++ & 0x80)
            return 1;
    }
    return 0;
}

static int to_pinyin(char **buf, const char *text, size_t text_len, int fuzzy, int abbr)
{
    py_list *pl, *cur;

    pl = py_convert(text, text_len);
    if (pl == NULL)
        return -1;
    if (fuzzy)
        py_fuzzy_fix(pl);
    char *p = *buf = (char *)emalloc(text_len * 4);
    if (p == NULL)
        return -2;
    for (cur = pl; cur != NULL; cur = cur->next) {
        if (abbr == 0) {
            strcpy(p, cur->py);
            p += strlen(cur->py);
            if (cur->next != NULL)  {
                if (PY_ILLEGAL(cur) && PY_ILLEGAL(cur->next))
                    *p++ = ' ';
                else if (PY_ZEROSM(cur->next))
                    *p++ = '\'';
            }
        } else {
            *p++ = cur->py[0];
            *p = '\0';
        }
    }
    py_list_free(pl);

    return 0;
}

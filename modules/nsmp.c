#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utone.h"
#include "ini.h"

int nano_dict_add(nano_dict *dict, const char *name)
{
    nano_entry *entry = malloc(sizeof(nano_entry));
    entry->size = 0;
    entry->speed = 1;
    entry->pos = 0;
    strcpy(entry->name, name);
    dict->last->next = entry;
    dict->last = entry;
    dict->nval++;
    return UT_OK;
}

int nano_ini_handler(void *user, const char *section, const char *name,
        const char *value)
{
    nanosamp *ss = user;
    nano_dict *dict = &ss->dict;
    const char *entry_name = dict->last->name;

    if(dict->init) {
        nano_dict_add(dict, section);
        dict->init = 0;
    } else if(strncmp(entry_name, section, 50) != 0) {
        nano_dict_add(dict, section);
    }

    dict->last->speed = 1.0;

    if(strcmp(name, "pos") == 0) {
        dict->last->pos = (uint32_t)(atof(value) * ss->sr);
    } else if(strcmp(name, "size") == 0) {
        dict->last->size = (uint32_t)(atof(value) * ss->sr);
    } else if(strcmp(name, "speed") == 0) {
        dict->last->speed = atof(value);
    }

    return UT_OK;
}

int nano_create(nanosamp **smp, const char *ini, int sr)
{
    *smp = malloc(sizeof(nanosamp));
    nanosamp *psmp = *smp;
    strcpy(psmp->ini, ini);
    psmp->dict.last = &psmp->dict.root;
    psmp->dict.nval = 0;
    psmp->dict.init = 1;
    psmp->selected = 0;
    psmp->curpos = 0;
    psmp->sr = sr;
    if(ini_parse(psmp->ini, nano_ini_handler, psmp) < 0) {
        printf("Can't load file %s\n", psmp->ini);
        return UT_NOT_OK;
    }

    return UT_OK;
}

int nano_select_from_index(nanosamp *smp, uint32_t pos)
{
    pos %= smp->dict.nval;
    smp->selected = 1;
    smp->sample = smp->index[pos];
    smp->curpos = 0;
    return UT_OK;
}

uint32_t nano_keyword_to_index(nanosamp *smp, const char *keyword)
{
    uint32_t i;
    for (i = 0; i < smp->dict.nval; i++) {
        if(strcmp(keyword, smp->index[i]->name)) {
            return i;
        }
    }
    return 0;
}

int nano_select(nanosamp *smp, const char *keyword)
{
    uint32_t i;
    nano_dict *dict = &smp->dict;
    nano_entry *entry = dict->root.next;
    smp->curpos = 0;
    smp->selected = 0;
    for(i = 0; i < dict->nval; i++) {
        if(strncmp(keyword, entry->name, 50) == 0) {
            smp->selected = 1;
            smp->sample = entry;
            smp->curpos = 0;
            break;
        } else {
            entry = entry->next;
        }
    }

    if(smp->selected == 1) return UT_OK;
    else return UT_NOT_OK;
}


int nano_compute(ut_data *ut, nanosamp *smp, UTFLOAT *out)
{
    if(!smp->selected) {
        *out = 0;
        return UT_NOT_OK;
    }

    if(smp->curpos < (UTFLOAT)smp->sample->size) {
        UTFLOAT x1 = 0 , x2 = 0, frac = 0, tmp = 0;
        uint32_t index = 0;
        UTFLOAT *tbl = smp->ft->tbl;
        tmp = (smp->curpos + smp->sample->pos);
        index = floorf(tmp);
        frac = fabs(tmp - index);

        if(index >= smp->ft->size) {
            index = smp->ft->size - 1;
        }

        x1 = tbl[index];
        x2 = tbl[index + 1];
        *out = x1 + (x2 - x1) * frac;
        smp->curpos += smp->sample->speed;
    } else {
        smp->selected = 0;
        *out = 0;
    }

    return UT_OK;
}

int nano_dict_destroy(nano_dict *dict)
{
    int i;
    nano_entry *entry, *next;
    entry = dict->root.next;

    for(i = 0; i < dict->nval; i++) {
        next = entry->next;
        free(entry);
        entry = next;
    }
    return UT_OK;
}

int nano_destroy(nanosamp **smp)
{
    nanosamp *psmp = *smp;
    nano_dict_destroy(&psmp->dict);
    free(*smp);
    return UT_OK;
}



int nano_create_index(nanosamp *smp)
{
    nano_dict *dict = &smp->dict;
    smp->index = malloc(dict->nval * sizeof(nano_entry *));
    int i;
    nano_entry *entry, *next;
    entry = dict->root.next;

    for(i = 0; i < dict->nval; i++) {
        next = entry->next;
        smp->index[i] = entry;
        entry = next;
    }
    return UT_OK;
}

int nano_destroy_index(nanosamp *smp)
{
    free(smp->index);
    return UT_OK;
}

int ut_nsmp_create(ut_nsmp **p)
{
    *p = malloc(sizeof(ut_nsmp));
    return UT_OK;
}

int ut_nsmp_destroy(ut_nsmp **p)
{
    ut_nsmp *pp = *p;
    nano_destroy_index(pp->smp);
    nano_destroy(&pp->smp);
    free(*p);
    return UT_OK;
}

int ut_nsmp_init(ut_data *ut, ut_nsmp *p, ut_ftbl *ft, int sr, const char *ini)
{
    if (nano_create(&p->smp, ini, sr) == UT_NOT_OK) {
        nano_destroy(&p->smp);
        return UT_NOT_OK;
    }
    nano_create_index(p->smp);
    p->smp->sr = sr;
    p->index= 0;
    p->triggered = 0;
    p->smp->ft = ft;
    return UT_OK;
}

int ut_nsmp_compute(ut_data *ut, ut_nsmp *p, UTFLOAT *trig, UTFLOAT *out)
{
    if (*trig != 0) {
       p->triggered = 1;
       nano_select_from_index(p->smp, p->index);
    }

    if(p->triggered == 1) {
        nano_compute(ut, p->smp, out);
    } else {
        *out = 0;
    }

    return UT_OK;
}

int ut_nsmp_print_index(ut_data *ut, ut_nsmp *p)
{
    uint32_t i;
    for(i = 0; i < p->smp->dict.nval; i++) {
        printf("%d: key = %s\n", i, p->smp->index[i]->name);
    }
    return UT_OK;
}


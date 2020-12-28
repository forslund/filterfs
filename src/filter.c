#include <fcntl.h>
#include <fnmatch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "filter.h"


int default_exclude = 0;

/**
 * Appends a single rule to the filter chain.
 */
int append_rule(char *pattern, int exclude)
{
    struct rule *rule = malloc(sizeof(struct rule));

    if (!rule)
        return -1;

    rule->pattern = pattern;
    rule->exclude = exclude;
    rule->next = NULL;

    if (!chain.head) {
        chain.head = rule;
        chain.tail = rule;
    }
    else {
        chain.tail->next = rule;
        chain.tail = rule;
    }

    return 0;
}

/**
 * Appends multiple rules to the filter chain.
 */
int append_rules(char *patterns, int exclude)
{
    char *str = patterns;

    while (1) {
        if (append_rule(str, exclude) == -1)
            return -1;

        if (!(str = strchr(str, ':')))
            break;

        *str = '\0';
        str++;
    }

    return 0;
}

/**
 * Checks whether the provided path should be excluded.
 */
int exclude_path(const char *path)
{
    struct stat st, symt;
    lstat(path, &st);

    int result = default_exclude;
    /* directories must not be filtered (currently) */
    if (S_ISDIR(st.st_mode))
        return 0;

    /* symlinks might point to directories */
    if (S_ISLNK(st.st_mode)) {
        stat(path, &symt);

        if (S_ISDIR(symt.st_mode))
            return 0;
    }

    const char * check = strstr(path, "//");
    if (check == (void *)0)
        check = path;

    struct rule *curr_rule = chain.head;

    while (curr_rule) {
        if (fnmatch(curr_rule->pattern, check, 0) == 0)
        {
            result = curr_rule->exclude;
        }
        curr_rule = curr_rule->next;
    }

    return result;
}

/**
 * Checks if str1 begins with str2. If so, returns a pointer to the end of
 * the match. Otherwise, returns null.
 */
const char *str_consume(const char *str1, char *str2)
{
    if (strncmp(str1, str2, strlen(str2)) == 0) {
        return str1 + strlen(str2);
    }

    return 0;
}

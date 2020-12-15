
#pragma once

struct rule {
    char *pattern;
    int exclude;
    struct rule *next;
};

struct {
    struct rule *head;
    struct rule *tail;
} chain;


int default_exclude;

int append_rule(char *pattern, int exclude);

int append_rules(char *patterns, int exclude);

int exclude_path(const char *path);

const char *str_consume(const char *str1, char *str2);


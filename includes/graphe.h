#ifndef GRAPH_H
    #define GRAPH_H

    #define MAX_INT 2147483646

typedef struct arc_s {
    struct arc_s *next;
    double w;
    struct sommet_s *sommet;
} arc_t;

typedef struct sommet_s {
    int x;
    int y;
    int color;
    struct sommet_s *pred;
    double dist;
    arc_t *arc;
} sommet_t;

typedef struct maillon_s {
    sommet_t *sommet;
    struct maillon_s *next;
} maillon_t;

typedef struct file_s {
    maillon_t *start;
    maillon_t *end;
} file_t;

#endif /*GRAPH_H*/
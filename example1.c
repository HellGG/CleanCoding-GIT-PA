#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
    int data;
    struct Node *next;
} NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct g
{
    int v;
    int *vis;
    struct Node **alst;
} GPH;

typedef struct s{
    int t;
    int scap;
    int *arr;
} STK;

NODE *create_node(int v){
    NODE *nn=malloc(sizeof(NODE));
    nn->data=v;
    nn->next=NULL;
    return nn;
}

void add_edge(GPH *g,int src,int dest)
{
    NODE *nn=create_node(dest);
    nn->next=g->alst[src];
    g->alst[src]=nn;
    nn=create_node(src);
    nn->next=g->alst[dest];
    g->alst[dest]=nn;
}

GPH *create_g(int v)
{
    int i;
    GPH *g=malloc(sizeof(GPH));
    g->v=v;
    g->alst=malloc(v * sizeof(NODE *));
    g->vis=malloc(v * sizeof(int));

    for (i=0; i<v; i++)
    {
        g->alst[i]=NULL;
        g->vis[i]=0;
    }
    return g;
}

STK *create_s(int scap)
{
    STK *s=malloc(sizeof(STK));
    s->arr=malloc(scap*sizeof(int));
    s->t = -1;
    s->scap=scap;

    return s;
}

void push(STK *s, int pshd)
{
    s->t=s->t+1;
    s->arr[s->t]=pshd;
}

void DFS(GPH *g, STK *s, int v_nr)
{
    NODE *adj_list=g->alst[v_nr];
    NODE *aux=adj_list;
    g->vis[v_nr]=1;
    printf("%d ", v_nr);
    push(s, v_nr);

    while (aux != NULL){
        int con_ver=aux->data;
        if (g->vis[con_ver]==0)
            DFS(g, s, con_ver);
        aux=aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr, int nrv)
{
    int src, dest, i;
    printf("adauga %d munchii (de la 0 la %d)\n", edg_nr, nrv-1);
    for (i=0; i<edg_nr; i++)
    {
        scanf("%d%d", &src, &dest);
        if(src >= 0 && src < nrv && dest >= 0 && dest < nrv) {
            add_edge(g, src, dest);
        } else {
            printf("Valori invalide! Incearca din nou.\n");
            i--;
        }
    }
}

void wipe(GPH *g, int nrv)
{
    int i;
    for (i=0; i<nrv; i++)
    {
        g->vis[i] = 0;
    }
}

// Verifica daca exista drum intre doua restaurante
int check_path(GPH *g, int start, int end)
{
    STK *s = create_s(g->v);
    wipe(g, g->v);

    DFS(g, s, start);

    // Daca nodul final a fost vizitat, exista drum
    return g->vis[end];
}

void free_memory(GPH *g, STK *s1, STK *s2)
{
    int i;

    // Eliberam memoria pentru liste de adiacenta
    for(i = 0; i < g->v; i++) {
        NODE *current = g->alst[i];
        while(current != NULL) {
            NODE *temp = current;
            current = current->next;
            free(temp);
        }
    }

    // Eliberam memoria pentru graf si stive
    free(g->alst);
    free(g->vis);
    free(g);
    free(s1->arr);
    free(s1);
    free(s2->arr);
    free(s2);
}

int main()
{
    int nrv;
    int edg_nr;
    int src, dest;
    int i;
    int vortex_1;
    int virtex_2;
    int ans;

    printf("cate noduri are graful? ");
    scanf("%d", &nrv);

    printf("cate muchii are graful? ");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);
    STK *s1 = create_s(2 * nrv);
    STK *s2 = create_s(2 * nrv);

    insert_edges(g, edg_nr, nrv);

    printf("Introduceti cele doua restaurante pentru verificare (de la 0 la %d): ", nrv-1);
    scanf("%d %d", &vortex_1, &virtex_2);

    if(vortex_1 >= 0 && vortex_1 < nrv && virtex_2 >= 0 && virtex_2 < nrv) {
        ans = check_path(g, vortex_1, virtex_2);

        if(ans) {
            printf("Exista drum intre restaurantul %d si restaurantul %d\n", vortex_1, virtex_2);
        } else {
            printf("NU exista drum intre restaurantul %d si restaurantul %d\n", vortex_1, virtex_2);
        }
    } else {
        printf("Restaurante invalide!\n");
    }

    free_memory(g, s1, s2);

    return 0;
}
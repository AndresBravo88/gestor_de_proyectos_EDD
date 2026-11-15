#include <stdio.h>
#include <stdlib.h>
#include "integrantes.h"
#include "usuarios.h"
#include "estado.h"
#include "utilidades.h"

int esIntegrante(const Proyecto *p, const Usuario *u) {
    for (NodoIntegrante *n = p->integrantes; n; n = n->sig)
        if (n->usuario == u) return 1;
    return 0;
}
int agregarIntegrante(Proyecto *p, Usuario *u) {
    if (esIntegrante(p, u)) return 1;
    NodoIntegrante *ni = malloc(sizeof *ni);
    NodoProyecto   *np = malloc(sizeof *np);
    if (!ni || !np) { free(ni); free(np); return -1; }
    ni->usuario = u;  ni->sig = p->integrantes;  p->integrantes = ni;      /* nodo en el proyecto */
    np->proyecto = p; np->sig = u->proyectos;    u->proyectos = np;        /* nodo en el usuario  */
    return 0;
}
int eliminarIntegrante(Proyecto *p, Usuario *u) {
    if (!esIntegrante(p, u)) return 1;
    if (p->creador == u) return 2;

    NodoIntegrante *ant = NULL, *ni = p->integrantes;         /* desenlazar de la lista del proyecto */
    while (ni && ni->usuario != u) { ant = ni; ni = ni->sig; }
    if (ant) ant->sig = ni->sig; else p->integrantes = ni->sig;
    free(ni);

    NodoProyecto *antP = NULL, *np = u->proyectos;            /* desenlazar de la lista del usuario */
    while (np && np->proyecto != p) { antP = np; np = np->sig; }
    if (np) {
        if (antP) antP->sig = np->sig; else u->proyectos = np->sig;
        free(np);
    }

    for (Tarea *t = p->tareas; t; t = t->sig)                 /* sus tareas quedan sin asignar */
        if (t->idResponsable == u->id) t->idResponsable = 0;
    return 0;
}
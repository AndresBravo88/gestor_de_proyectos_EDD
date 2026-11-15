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
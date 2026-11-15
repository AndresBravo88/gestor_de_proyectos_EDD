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
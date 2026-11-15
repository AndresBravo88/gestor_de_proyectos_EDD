#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proyectos.h"
#include "integrantes.h"
#include "estado.h"


unsigned hashEntero(int id) {
  return (unsigned)id % TAM_MAPA;
}

Proyecto *buscarProyecto(int id) {
  if (id <= 0) return NULL;
  Proyecto *p = mapaProyectos[hashEntero(id)];
  while (p && p->id != id) p = p->sigCubeta;
  return p;
}
Proyecto *crearProyecto(Usuario *creador, const char *nombre, const char *descripcion) {
    if (!creador || !nombre) return NULL;

    Proyecto *p = malloc(sizeof *p);
    if (!p) return NULL;

    p->id = siguienteIdProyecto++;
    snprintf(p->nombre, sizeof p->nombre, "%s", nombre);
    snprintf(p->descripcion, sizeof p->descripcion, "%s", descripcion ? descripcion : "");
    p->creador = creador;
    p->integrantes = NULL;
    p->tareas = NULL;
    p->siguienteIdTarea = 1;

    unsigned c = hashEntero(p->id);
    p->sigCubeta = mapaProyectos[c];
    mapaProyectos[c] = p;

    if (agregarIntegrante(p, creador) != 0) {
        mapaProyectos[c] = p->sigCubeta;
        siguienteIdProyecto--;
        free(p);
        return NULL;
    }

    return p;
}
}
void listarProyectos(const Usuario *u) {
  if (!u) return;
      printf("\n=== PROYECTOS DE %s ===\n", u->username);
      if (!u->proyectos) {
          printf("   (no participas en ningun proyecto)\n");
          return;
      }
      for (NodoProyecto *n = u->proyectos; n; n = n->sig)
          printf("   [ID %d] %-24s %s\n", n->proyecto->id, n->proyecto->nombre, n->proyecto->descripcion);
}
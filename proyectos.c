#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proyectos.h"
#include "integrantes.h"
#include "estado.h"
#include "utilidades.h"

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
    (void)u;
    noImplementado("listarProyectos"); // falta implementar, solo esta agregada para luego hacerla como corresponde
}
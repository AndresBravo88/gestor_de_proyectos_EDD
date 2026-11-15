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
    (void)creador; (void)nombre; (void)descripcion;
    noImplementado("crearProyecto");
    return NULL;
}
void listarProyectos(const Usuario *u) {
    (void)u;
    noImplementado("listarProyectos");
}
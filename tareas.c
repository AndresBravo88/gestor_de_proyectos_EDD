#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tareas.h"
#include "usuarios.h"
#include "integrantes.h"

Tarea *buscarTarea(Proyecto *p, int id) {
  if (!p) return NULL ;
  Tarea *actual = p->tareas ;
  while (actual != NULL) {
    if (actual->id == id) {
      return actual ;
    }
    actual = actual->sig;
  }
  return NULL ;
}

Tarea *crearTarea(Proyecto *p, const char *nombre, const char *descripcion, int prioridad) {
  if (!p) return NULL ;
  Tarea *nueva = (Tarea *)malloc(sizeof(Tarea)) ;
  if (!nueva) return NULL ;

  nueva->id = p->siguienteIdTarea++ ;
  snprintf(nueva->nombre, sizeof(nueva->nombre), "%s", nombre) ;
  snprintf(nueva->descripcion, sizeof(nueva->descripcion), "%s", descripcion) ;
  nueva->prioridad = prioridad ;
  nueva->estado = POR_HACER ;
  nueva->idResponsable = 0 ;
  
  nueva->sig = p->tareas ;
  p->tareas = nueva ;
  return nueva ;
}

int eliminarTarea(Proyecto *p, int id) {
  if (!p || !p->tareas) return 0 ;
  Tarea *actual = p->tareas ;
  Tarea *anterior = NULL ;
  while (actual != NULL && actual->id != id) {
    anterior = actual ;
    actual = actual->sig ;
  }
  if (!actual) return 0 ;

  if (anterior == NULL) {
    p->tareas = actual->sig ;
  } else {
    anterior->sig = actual->sig ;
  }
  free(actual) ;
  return 1 ;
}

int asignarTarea(Proyecto *p, Tarea *t, const char *username) {
  if (!p || !t || !username) return 1 ;

  Usuario *u = buscarUsuario(username) ;
  if (!u) return 1 ;

  NodoIntegrante *curr = p->integrantes ;
  int pertenece = 0 ;
  while (curr != NULL) {
    if (curr->usuario && curr->usuario->id == u->id) {
      pertenece = 1 ;
      break ;
    }
    curr = curr->sig ;
  }
  if (!pertenece) return 2;

  t->idResponsable = u->id ;
  return 0 ;
}

int cambiarEstado(Tarea *t, int nuevoEstado) {
  if (!t) return -1 ;
  if (nuevoEstado < POR_HACER || nuevoEstado > TERMINADA) {
    return -1 ;
  }
  t->estado = (Estado)nuevoEstado ;
  return 0 ;
}
#ifndef TAREAS_H
#define TAREAS_H

#include "tipos.h"

Tarea *buscarTarea(Proyecto *p, int id) ;
Tarea *crearTarea(Proyecto *p, const char *nombre, const char *descripcion, int prioridad) ;
int eliminarTarea(Proyecto *p, int id) ;
int asignarTarea(Proyecto *p, Tarea *t, const char *username) ;
int cambiarEstado(Tarea *t, int nuevoEstado) ;

#endif
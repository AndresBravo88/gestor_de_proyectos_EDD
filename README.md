# Gestor Colaborativo de Proyectos

Programa de consola en **C** para el curso de Estructuras de Datos. Permite registrar usuarios,
crear proyectos, administrar integrantes y gestionar tareas en un tablero Kanban
(Por hacer / En progreso / Terminada).

> **Importante:** el programa guarda los datos solo en memoria. Al cerrarlo (opción `0`) se pierde todo.

---

## 1. ¿Qué necesito para usarlo?

- Tener **todos los archivos** `.c` y `.h` del repositorio en **una misma carpeta**.
  Con un archivo faltante el programa no compila.
- Un compilador de C (**gcc**).
  - **Windows:** instala [MSYS2 / MinGW-w64](https://www.msys2.org/) o usa **WSL** (Ubuntu).
  - **Linux / WSL:** `sudo apt install build-essential`
  - **macOS:** `xcode-select --install`
- Opcional: `make` (viene con `build-essential` o con MSYS2). Si no lo tienes, hay una alternativa abajo.

Para comprobar que gcc está instalado, abre una terminal y escribe: `gcc --version`

---

## 2. Paso a paso: descargar, compilar y ejecutar

### Paso 1. Descargar los archivos

**Opción A: con Git (recomendada)**

```bash
git clone https://github.com/AndresBravo88/testEDD.git
cd testEDD
```

**Opción B: sin Git**

En la página del repositorio en GitHub: botón verde **Code → Download ZIP**. Descomprime el ZIP
y abre una terminal **dentro de esa carpeta**.

Después del paso 1, la carpeta debe contener, entre otros, `main.c`, `tipos.h`, `Makefile`,
`usuarios.c`, `proyectos.c`, `tareas.c`, etc. Compruébalo con `dir` (Windows) o `ls` (Linux).

### Paso 2. Compilar

Elige **una** de las dos formas:

```bash
make
```

o, si no tienes `make`:

```bash
gcc -Wall -Wextra -g *.c -o gestor
```

Si todo sale bien, no se muestra ningún error y aparece un archivo nuevo llamado `gestor`
(en Windows con MinGW, `gestor.exe`). Pueden aparecer advertencias (*warnings*); los errores
(*error:*) sí impiden compilar.

### Paso 3. Ejecutar

Se ejecuta **desde la terminal** (no haciendo doble clic, porque la ventana se cerraría sola):

| Sistema | Comando |
|---|---|
| Linux / WSL / macOS | `./gestor` |
| Windows (PowerShell) | `.\gestor.exe` |

Para cerrar el programa usa la opción `0` del menú inicial.
Para borrar los archivos compilados: `make clean`.

---

## 3. Cómo usar el programa

El programa muestra menús numerados. Escribes el número y presionas Enter.

**Menú inicial**

| Opción | Qué hace |
|---|---|
| 1 | Registrarse (nombre, username y contraseña; el username no puede repetirse) |
| 2 | Iniciar sesión |
| 0 | Salir |

**Menú del usuario** (después de iniciar sesión)

| Opción | Qué hace |
|---|---|
| 1 | Ver mis proyectos |
| 2 | Crear proyecto (el sistema entrega un ID) |
| 3 | Abrir un proyecto por su ID (solo si eres integrante) |
| 4 | Revisar las tareas que me han asignado |
| 0 | Cerrar sesión |

**Menú del proyecto**

| Opción | Qué hace |
|---|---|
| 1 | Visualizar el tablero Kanban |
| 2 | Crear tarea (nombre, descripción y prioridad 1 a 3) |
| 3 | Modificar tarea (Enter vacío mantiene el valor actual) |
| 4 | Eliminar tarea |
| 5 | Asignar responsable (debe ser integrante del proyecto) |
| 6 | Cambiar estado de una tarea |
| 7 | Administrar integrantes (agregar o eliminar) |
| 0 | Volver |

**Prueba rápida sugerida:** registra a `ana` y a `beto` → inicia sesión como `ana` → crea un proyecto →
ábrelo y crea dos tareas → agrega a `beto` como integrante → asígnale la tarea 1 → cambia su estado →
mira el tablero.

---

## 4. Estructuras de datos usadas

- **Mapas (tablas hash) con cubetas encadenadas:** usuarios (clave: username) y proyectos (clave: ID).
- **Listas enlazadas:** proyectos de cada usuario, integrantes de cada proyecto y tareas de cada proyecto.

La relación usuario ↔ proyecto se guarda en **ambos lados** (el usuario conoce sus proyectos y el
proyecto conoce a sus integrantes), y las dos listas se actualizan siempre juntas.

---

## 5. Qué contiene cada archivo

```
tipos.h            structs y constantes (Usuario, Proyecto, Tarea, nodos de listas)
estado.h/.c        mapas globales y contadores de ID
utilidades.h/.c    lectura segura de teclado y textos de estado/prioridad
usuarios.h/.c      mapa hash de usuarios
auth.h/.c          inicio de sesión
menu_usuario.h/.c  menú inicial y menú del usuario
proyectos.h/.c     mapa hash de proyectos
integrantes.h/.c   relación usuario <-> proyecto
tareas.h/.c        lista de tareas
vistas.h/.c        tablero Kanban y listados
menu_proyecto.h/.c menú del proyecto
memoria.h/.c       liberación de toda la memoria al cerrar
main.c             programa principal
Makefile           instrucciones para compilar con `make`
.gitignore         archivos que Git no debe subir (ejecutables, .o)
```

---

## 6. Decisiones de diseño

- Las contraseñas se guardan y comparan en texto plano.
- El creador de un proyecto no puede ser eliminado del mismo.
- Cada tarea tiene un ID propio dentro de su proyecto (T-01, T-02...).
- Si se elimina a un integrante, sus tareas quedan sin asignar.

---

## 7. Comprobar fugas de memoria (Linux / WSL)

```bash
valgrind --leak-check=full ./gestor
```

Al salir con la opción `0` debe decir: `All heap blocks were freed -- no leaks are possible`.

---

## 8. Solución de problemas

| Problema | Causa probable |
|---|---|
| `gcc` o `make` "no se reconoce como comando" | No está instalado o no está en el PATH (ver sección 1) |
| `fatal error: xxx.h: No such file or directory` | Falta ese archivo en la carpeta: descarga el repo completo |
| `undefined reference to ...` | Falta un `.c`, o compilaste solo algunos archivos. Usa `make` o `gcc *.c` |
| Se cierra la ventana al hacer doble clic | Ejecútalo desde la terminal, como en el paso 3 |
| Aparecen letras raras (tildes) | Es solo la consola; el programa funciona igual |

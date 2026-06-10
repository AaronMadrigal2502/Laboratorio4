# Universidad de Costa Rica

## Escuela de Ingeniería Eléctrica

### IE-0117 Programación Bajo Plataformas Abiertas

# Laboratorio #4

**Estudiante:** Aarón Madrigal Marín C14373
**Profesora:** Carolina Trejos Quirós
**Periodo:** I-2026

---

## Descripción

Este repositorio contiene la solución del Laboratorio #4 del curso IE-0117 Programación Bajo Plataformas Abiertas.

Durante el desarrollo del laboratorio se implementaron programas en lenguaje C enfocados en el uso de:

* Memoria dinámica
* Aritmética de punteros
* Matrices dinámicas
* Recorrido lineal de memoria
* Manejo de archivos
* Lectura y escritura de imágenes en formato PGM
* Procesamiento básico de imágenes
* Uso de `malloc` y `free`
* Verificación de fugas de memoria con Valgrind

Además, se utilizó Git y GitHub para el control de versiones, creando un branch independiente para cada ejercicio y posteriormente integrándolos a la rama principal (`main`).

---

## Contenido

* `ejercicio1.c`

  * Reserva dinámica de una matriz cuadrada
  * Llenado aleatorio con valores binarios
  * Recorrido mediante aritmética de punteros
  * Búsqueda de la secuencia más larga de unos consecutivos
  * Liberación correcta de memoria dinámica

* `ejercicio2.c`

  * Lectura de imágenes PGM en formato P2
  * Almacenamiento dinámico de píxeles
  * Aplicación de filtro de umbral
  * Generación de imagen negativa
  * Escritura de archivos PGM de salida
  * Cálculo de estadísticas de la imagen

* `input.pgm`

  * Imagen de prueba utilizada para aplicar el filtro de umbral y generar el negativo


---

## Compilación

Para compilar el Ejercicio 1:

```bash
gcc -Wall ejercicio1.c -o ej1
```

Para ejecutar:

```bash
./ej1
```

Para compilar el Ejercicio 2:

```bash
gcc -Wall ejercicio2.c -o ej2
```

Para ejecutar:

```bash
./ej2
```

---

## Verificación con Valgrind

Para comprobar que el Ejercicio 1 no presenta fugas de memoria:

```bash
valgrind --leak-check=full ./ej1
```

Para comprobar que el Ejercicio 2 no presenta fugas de memoria:

```bash
valgrind --leak-check=full ./ej2
```

En ambos casos se debe verificar que la salida indique:

```text
definitely lost: 0 bytes in 0 blocks
indirectly lost: 0 bytes in 0 blocks
possibly lost: 0 bytes in 0 blocks
```

---

## Archivos de salida del Ejercicio 2

Al ejecutar el programa del Ejercicio 2 se generan los siguientes archivos:

* `output_threshold.pgm`

  * Imagen resultante después de aplicar el filtro de umbral

* `output_negative.pgm`

  * Imagen negativa generada a partir de la imagen umbralizada

---

## Conversión de imágenes

Si se desea convertir las imágenes PGM a PNG para visualizarlas o incluirlas en el reporte, se puede utilizar ImageMagick:

```bash
convert input.pgm input.png
convert output_threshold.pgm output_threshold.png
convert output_negative.pgm output_negative.png
```

---

## Control de versiones

El desarrollo se organizó mediante branches independientes para cada ejercicio:

* `ejercicio1`
* `ejercicio2`

Posteriormente, ambos branches fueron integrados a la rama principal:

* `main`

---



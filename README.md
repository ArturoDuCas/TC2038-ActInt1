# TC2038-ActInt1

## Descripción

**Actividad Integradora 1: Análisis y Diseño de Algoritmos Avanzados (TC2038)**

Esta actividad tiene como propósito analizar y detectar posibles códigos maliciosos en archivos de transmisión. Se busca identificar patrones y secuencias específicas que indiquen la presencia de estos códigos y se generará un reporte detallado de los hallazgos.

## Subcompetencias a Evaluar

Con la entrega de esta actividad, se busca evidenciar las siguientes subcompetencias:

- **SICT0101**: Explicación y modelado de sistemas computacionales y sus interacciones.
- **SICT0401**: Aplicación de estándares y normas relevantes en el dominio del problema.
- **STC0101**: Implementación de algoritmos confiables y correctos para solucionar problemas.
- **STC0102**: Optimización de algoritmos robustos y eficientes para el desarrollo de soluciones.

## Especificaciones de la Evidencia

### Requisitos de Entrada

- Los archivos que se deben analizar son: `transmission1.txt`, `transmission2.txt`, `transmission3.txt`, y `mcode.txt`. Estos deben existir en la misma ruta donde se ejecuta el programa.

### Funcionalidades del Programa

1. **Detección de Códigos Maliciosos**: El programa busca coincidencias entre el archivo `mcode.txt` (que contiene posibles códigos maliciosos) y los archivos de transmisión.
2. **Búsqueda de Palíndromos**: Dada la naturaleza "espejeada" de algunos códigos maliciosos, el programa busca secuencias palíndromas dentro de los archivos de transmisión.
3. **Análisis de Similitud**: El programa compara y analiza similitudes entre combinaciones de los archivos de transmisión.

### Salida

El programa genera un archivo llamado `checking.txt` que contiene:
- Cantidad de incidencias de cada posible código malicioso en los archivos de transmisión y sus posiciones.
- Subsecuencia del código con un caracter menos del original más encontrado.
- El palíndromo más largo de cada archivo de transmisión y su posición.
- Substrings más largos entre las combinaciones de los archivos de transmisión.

### Ejecución

```bash
$ ./nombre_del_programa


# Monte Carlo esferas duras 2D

Simulación de Monte Carlo para esferas duras en 2D

Proyecto de tesis y de investigación con el Dr. Adrián Huerta, Universidad Veracruzana.

El programa principal saca como resultado el par densidad y presión, para que, por muchas ejecuciones en paralelo, en sistemas multiprocesador, se genere la ecuación de estado. Dentro de esto, el programa escribe en archivo g_r.txt la función de distribución radial de la simulación. Al final del programa se escribe en configuración.txt si la opción está activa dentro del código.

Compilación:

make all

Uso:

Uso:
monte_carlo [particulas] [¿leer configuraciones?] [pared derecha] [pared  izquierda] [pared arriba] [pared abajo] [número de simulaciones] [¿Visualizacion?]

Ejemplo de uso:

$ ./monte_carlo 100 0 10 10 10 10 1000 0

El primer parámetro es el número de esferas duras de la simulación. El segundo parámetro [leer configuraciones] es sólo o 1 o 0, para leer desde el archivo de datos "configuracion.txt". Los tamaños de la pared son en unidades del sistema, y establece longitudes hacia la derecha, hacia la izquierda, hacia arriba, y hacia abajo. El [número de simulaciones] define la cantidad de corridas de Monte Carlo para la obtención del dato final de presión.

Se pueden configurar parámetros dentro del código para realizar visualización con PGPlot.


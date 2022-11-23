# Tarea Programada 2
**Integrantes:**
********************
* Isaac Vargas (C08195) - isaac.vargasjimenez20@ucr.ac.cr</br>

* Nathan Murillo (B95506) - joseph.murillovargas@ucr.ac.cr</br>
********************

**Explicacion:**</br>
Resumen:</br>
Para hacer el proyecto, es necesario utilizar el modelo SIMD y el conjunto de instrucciones AVX2. Se tiene que abrir un bitmap en modo binario a través de ensamblador para poder modificar sus valores y con esto, aplicar una serie de filtros y transformaciones. Se tiene que ser capaz de diferenciar los headers del BMP y hacer las transcripciones entre little endian y big endian. Finalmente, se tiene que poder generar un archivo transformado de formato BMP.</br>

Descripcion Requisitos:
1.	Abrir un archivo y cargar los pixeles a un vector de memoria para ser alterados.
2.	Ajustar el brillo (sumar número constante a todos los pixeles con las instrucciones AVX2).
3.	Contraste, se va a usar la funcion del profesor.
4.	Colores negativos, básicamente implicaría reemplazar cada pixel individual (R, G ,B) por el pixel (255-R, 255- G, 255-B) respectivo.
5.	Escalado de la imagen, se tendría que cuadruplicar el tamaño de la imagen, duplicar su dimensión en "X" y en "Y" para luego hacer una reubicación y respectiva copia de cada pixel adyacente en los nuevos espacios vacíos.
6.	Espejado de la imagen, se debe reubicar cada pixel en orden inverso en términos de su dimensión "X", esto implica mover los pixeles finales de la imagen por cada hilera hacia el frente de la misma.
7.	Mostrar la imagen resultante en pantalla a través de un panel en Qt.
8.	Generar un archivo nuevo con las modificaciones efectuadas a la imagen original y guardar el archivo en formato BMP.

**Diseño:**</br>
Un panel para ver la imagen original, a la par otro panel que muestre la copia (imagen a modificar).
5 botones, un botón para aplicar cada uno de los filtros y transformaciones, si es necesario el botón desplegara un input, por ejemplo, el brillo para colocar la cantidad de brillo por aumentar.
Un botón para generar/guardar la imagen.



**Diagrama de Flujo**
![Diagrama flujo base](https://user-images.githubusercontent.com/102835455/202092625-3dd26ffb-31aa-4967-ac85-cba172bf663a.png)



**Tareas (por definir):**

1) Implementar Lectura/Escritura Imagenes BMP C++. ( Isaac ) 
2) Menu Basico Ensamblador. ( Isaac ) 
3) Conectar C++ con Ensamblador ( NASM ). ( Isaac & Nathan )
4) Elaborar Interfaz Grafica. ( Isaac & Nathan [Elaborado en clase] )
5) Programar Algoritmos ( Negativo, Contraste, Brillo, Escalado...etc. ). ( Isaac (Subir Brillo) )

**Referencias:**
1) "Reading a Bitmap Image (.bmp) using C++ | Tutorial" - Designed by Hugo:
https://www.youtube.com/watch?v=NcEE5xmpgQ0&t=56s&ab_channel=DesignedbyHugo

2) "Creating a Bitmap Image (.bmp) using C++ | Tutorial" - Designed by Hugo:
https://www.youtube.com/watch?v=vqT5j38bWGg&t=1s&ab_channel=DesignedbyHugo

3) "QT C++ GUI Tutorial 24- How to use QFileDialog" - ProgrammingKnowledge:
https://www.youtube.com/watch?v=tKdfpA74HYY&t=499s&ab_channel=ProgrammingKnowledge





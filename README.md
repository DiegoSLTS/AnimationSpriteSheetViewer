# AnimationSpriteSheetViewer

Este proyecto fue parte de un test para un trabajo. La idea era hacer una aplicación que sirva para visualizar animaciones guardadas en un sprite sheet en formato PNG.

----

This project was part of a test for a job. The task was to create an application to view animations stored as spritesheets in a PNG file.

----

# Requisitos / Requirements

Me pidieron que cumpla lo siguiente:
* Podía elegir la tecnología a usar
* La aplicación muestra una ventana vacía al abrirla
* Al hacer clic en alguna parte de la ventana se empieza a reproducir la animación en loop infinito en la posición del cursor en ese momento
* Cada clic inicia una nueva reproducción, sin interrumpir las anteriores
* Las reproducciones son independientes, cada una empieza desde el frame 0 al momento de hacer clic
* Se tiene que cargar el spritesheet una sola vez independientemente el número de animaciones
* El nombre del archivo y otros settings se definen a través de argumentos de la línea de comandos

----

I was asked to follow this instructions:
* I could choose the technology
* The application shows an empty windows on start
* Clicking anywhere on the screen starts playing the animation in an infinite loop where the mouse cursor was at that moment
* Each clic starts a new animation, without interrupting the previous ones
* The animations are independent from each other, each one starts from frame 0
* The spritesheet file must be loaded in memory only once, regardless of the amount of playing animations
* The file name and other settings are passed as command line arguments

# Compilación / Compiling

El proyecto lo probé en Visual Studio 2017, pero debería poder compilarse sin problemas con cualquier otro compilador o IDE.

----

I tested the project in Visual Studio 2017, but it should compile without issues in any compiler or IDE.

# Setup

El desarrollo es en C++ usando SDL2, así que hay que descargar SDL2 y configurar el proyecto con los paths a los include y las libs.

Una vez compilado el proyecto en Release o Debug hay que copiar las siguientes .dll junto al ejecutable:
* SDL2.dll
* SDL2_image.dll
* libpng16-16.dll

----

The application is writen in C++ using SDL2, so you mas download the SDL2 library and setup the proyect with the paths to the include and lib folders.

Once the project is compiled either in Release or Debug, you must copy the following .dlls to the same folder of the executable:
* SDL2.dll
* SDL2_image.dll
* libpng16-16.dll

# Uso / Usage

## Línea de comandos

Los argumentos válidos son:
* "-p" seguido del path relativo al archivo png con el spritesheet. El path es relativo a la carpeta del ejecutable. El nombre del archivo tiene que incluir la extensión.
* "-s" seguido del tamaño de cada cuadro de la animación en pixeles, en el formato "ANCHOxALTO"
* "-t" seguido de la cantidad de cuadros de la animación
* "-f" seguido de la cantidad de cuadros por segundo a la que se tiene que reproducir la animación

Si alguno de estos argumentos falta o tiene algún error, los valores por defecto que se usan son:
* path: example.png
* tamaño de los cuadros: 128x128
* cantidad de cuadros: se deduce del tamaño de la imagen y del tamaño de los cuadros
* fps: 25

----

The valid arguments are:
* "-p" followed by the relative path to the png file with the spritesheet. The path is relative to the folder with the executable. The name of the file must contain the .png extension.
* "-s" followed by the size of the frames of the animation, in pixels, in the format "WIDTHxHEIGHT"
* "-t" followed by the number of frames of the animation
* "-f" followed by the number of frames per second at which the animation should be played

If any argument is missing or can't be parsed, these are the default values:
* path: example.png
* frame size: 128x128
* frames count: infered from the image and frame sizes
* fps: 25

## Controles / Controls

Clic en la pantalla inicia una nueva reproducción de la animación.

Escape o clic en la X cierran la aplicación.

----

Clic anywhere on the screen to start new animations.

Pressing the escape key or clicking the X closes the application

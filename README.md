# ProyectoIntegrador

Proyecto Integrador Algoritmos II Unne LCI 2025 .
MINI JUEGOS
El presente proyecto Integrador consiste en un laucher (lanzador) desarrollado en C, que enlaza 4 subproyectos, permitiendo seleccionar y ejecutar diferentes mini-juegos através de un menú interactivo controlado con las flechas del teclado.

Para ejecutar el laucher el usuario simplemente debe hacer doble click sobre el archivo nombrado como "launcher.exe".

Al ejecutar el launcher el usuario podrá acceder a cualquiera de los 4 juegos disponibles, desplazandose con las teclas de direccion del teclado a algunos de los siguentes juegos:
1- WORDLE.
2- SPACE TRACKER.
3- TA-TE-TI
4- AHORCADO.

Una vez que el usuario se encuentre en el juego deseado, simplemente debe presionar la tecla "enter" y este será inmediatamente redireccionado al menu del juego correspondiente, donde podrá disfrutar del mismo.



**COMPILACIÓN**

En caso de no encontrar el ejecutable launcher.exe, puede generarse nuevamente compilando el archivo launcher.c con cualquier compilador o IDE compatible con el lenguaje C.



Desde un compilador como GCC:

Abrir una terminal en la carpeta del proyecto y ejecutar:

gcc launcher.c -o launcher.exe



Desde cualquier IDE (Dev-C++, Code::Blocks, Visual Studio Code, etc.):

Abrir launcher.c y utilizar la opción de compilar y ejecutar que ofrezca el entorno.



Es importante mantener la estructura de carpetas donde se encuentran los mini-juegos (wordle, spacetracker, tateti y ahorcado), ya que el launcher los ejecuta a partir de esas rutas.


# World 3D
Un mundo virtual en tres dimensiones, algunas construcciones y un cielo mayormente nublado. Se usa la API de Win32 combinado con OpenGL para el diseño gráfico.  

## Especificaciones
El proyecto fue desarrollado inicialmente con Code::Blocks 17.12. Note que algunas librerías deben ser importadas en la configuración 
del compilador, entre ellas: libopengl32,libgdi32,libglu32,libglaux. Si abre el archivo "World3D.cbp" directamente en la versión del 
IDE antes mencionado, estas librerías deberían cargarse automáticamente, en dependencia de donde lo tenga instalado. No obstante, puede
cargarlas manualmente:  
![screen](https://github.com/Alvarez-Bermudez/World3D/blob/main/screenshots/setting_up.png)  
y una vez en la Linker Settings Tab, proceder a añadir manualmente las librerías.
![screen](https://github.com/Alvarez-Bermudez/World3D/blob/main/screenshots/build_options_codeblocks.png)  
En mi caso la ruta para estas librerías fueron: 
"C:/Program Files (x86)/CodeBlocks/MinGW/lib/libopengl32.a",  
"C:/Program Files (x86)/CodeBlocks/MinGW/lib/libgdi32.a",  
"C:/Program Files (x86)/CodeBlocks/MinGW/lib/libglu32.a",  
"C:/Program Files (x86)/CodeBlocks/MinGW/lib/libglaux.a".  
Pero si no es tu caso, deberías encontrar estas librerías en la carpeta "/lib" de tu compilador.  

## Algunas indicaciones

- Controles

| Descripción | Tecla |
|---|---|
| Dirigir objetivo cámara | (Mouse control) |
| Mover hacia adelante | Up Arrow / W |
| Mover hacia atrás | Down Arrow / S | 
| Mover izquierda | Left Arrow / A |
| Mover derecha | Right Arrow / D |  
  
## Screenshots

![screen](https://github.com/Alvarez-Bermudez/World3D/blob/main/screenshots/screenshot001.png)  
![screen](https://github.com/Alvarez-Bermudez/World3D/blob/main/screenshots/screenrecorder001.gif)    
![screen](https://github.com/Alvarez-Bermudez/World3D/blob/main/screenshots/screenrecorder002.gif)  
   
... Espero que te diviertas usándolo😆! ¡Gracias!!! 



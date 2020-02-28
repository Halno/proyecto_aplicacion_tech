# APLICACIÓN TECH:

**CONCEPTO DE LA APLICACIÓN**

La idea de este proyecto es crear una aplicación que permita a la comunidad de un juego de lucha (en este caso, de Street Fighter V) poder
compartir tech entre ellos.

¿Y qué es tech?

Tech es una palabra empleada en este tipo de juegos para referirse a información del juego que puede aplicarse para crear estrategias.
Este tipo de juegos tienen una gran profundidad, y existe tal infinidad de interacciones entre personajes y situaciones que se pueden dar
que es imposible descubrirlo todo por uno mismo; por lo que las comunidades de estos juegos suelen compartir este tipo de contenido para
ayudar al resto a mejorar.

No obstante, la tech de un juego suele estar desperdigada entre foros de internet, vídeos de youtube, reddit, redes sociales, etcétera.
Por lo que la idea de esta aplicación es tener un lugar cuyo único fin sea recopilar toda esta tech o información en un único sitio, y 
que sean los propios usuarios los que puedan crear este contenido.



**FUNCIONAMIENTO**

Al acceder a la página web, uno se puede o bien registrar si no tiene cuenta o iniciar sesión en el caso de que ya la tenga.

Una vez se ha iniciado sesión, se procede a seleccionar el personaje del que se quiere buscar/publicar tech a través de una 
combobox.

Tras seleccionar el personaje, se puede pulsar el botón de Buscar tech si lo que se desea es buscar información de ese personaje, lo
que cargará todas las entradas de la base de datos que sean de ese personaje, o bien el de enviar tech para añadir la información insertada 
en la caja de texto para ese personaje, lo que creará una nueva entrada en la base de datos de información para ese personaje.

Una vez el usuario ya no quiere realizar ninguna acción más, puede pulsar el botón para Cerrar sesión.



**ESTADO DE LA APLICACIÓN**

La aplicación realiza las funciones básicas para la que fue diseñada: los usuarios pueden registrare e iniciar sesión, 
buscar tech, añadir nueva tech y cerrar sesión.

No obstante, aún quedan tareas que se podrían realizar:

- Mejorar el apartado visual del cliente.
- Añadir funcionalidad para que el creador de una entrada pudiera modificar o borrar esa entrada.
- Mostrar el nombre del creador de cada entrada al lado de dicha entrada.
- Poder bloquear usuarios que no emplearan de manera correcta la aplicación.
- Añadir todos los personajes del juego (en este caso, Street Fighter V tiene 40 personajes, y tan solo existen 4 de esos 40 en la aplicación).
- Que la aplicación fuera genérica en lugar de pertenecer a un único juego (que se pudiera emplear para cualquier juego de lucha en lugar de 
únicamente para Street Fighter V).
- Funcionalidad para poder votar tech (votos positivos y negativos), y organizar la tech encontrada en base al total de sus votos.
- Funcionalidad para poder responder a una pieza de tech, como para aportar una idea mejor o aclarar porqué esa pieza está obsoleta o 
no es aplicable a una partida real, por ejemplo (poder dar feedback).
- Funcionalidad para poder traducir piezas de tech (la mayoría de esta información suele estar en inglés, y sería de gran ayuda poder
traducirla para aquellos que no tengan un buen dominio del idioma).
- La contraseña debería guardarse de manera encriptada en el servidor.



**TECNOLOGÍA EMPLEADA**

- La base de datos que emplea la aplicación ha sido creada empleando PostgreSQL.
- El cliente es un cliente web creado con HTML, CSS y JavaScript.
- El servidor es un servidor WebSocket que ha sido creado como una aplicación en C++ de QT.
- La comunicación entre el cliente y el servidor se realiza mediante mensajes JSON.
- El flujo de la aplicación es el siguiente:
    · Cliente realiza peticiones al servidor enviando mensajes JSON.
    · El servidor recibe el JSON y realiza una tarea u otra en función del campo "tipo" del JSON.
    · El servidor realiza operaciones en la base de datos en función de las instrucciones indicadas en el JSON recibido.
    · Tras realizar la operación en cuestión, el servidor construye y envía un JSON de respuesta al cliente indicando el resultado de la operación.
    · El cliente realiza operaciones según el contenido del JSON enviado por el servidor.



**GESTIÓN DE ERRORES**

Durante la realización de este proyecto han ido surgiendo multitud de problemas que he resuelto de distintas maneras, entre ellas las más comunes
eran buscar por Internet en sitios como StackOverflow y preguntar a mi profesor o a compañeros de clase.

He tenido problemas como:
- Formar la estructura que iba a seguir el flujo del programa (entender cómo se gestionaba el envío/recepción de mensajes)
- Crear la base de datos empleando PostgreSQL
- Realizar conversiones de datos (pasar de una std::string a una QString, de un valor de un JSON a una string, etcétera)
- Entender el funcionamiento del Websocket
- Realizar las clases y los métodos para poder comunicar el servidor con la base de datos de manera correcta
- Encontrar código muerto







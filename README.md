# Trabajo Practico 2 - Taller de programacion I

**Nombre:**  Santiago Pablo Fernandez Caruso

**Padron:** 105267

**Repositorio:** https://github.com/SaFernandezC/Tp3-Taller



## Descripcion

El presente trabajo consta de la implementacion de un juego tateti multijugador que se realizo con el fin de introducirse a la programacion multihilo y multijugador.



## Detalles Implementacion

**Cliente:**

A continuacion se presenta un diagrama de clases para ilustrar el modelo del lado del cliente.

![](/home/santiago/Escritorio/Fiuba/Taller I/Tp3-Taller/img/clasesCliente.png)

Se omiten los metodos del analizador, del protocolo y del socket para facilitar la lectura.

Como vemos cada cliente cuenta con su propio socket a traves del cual se conecta e intercambia mensajes con el servidor. Tambien hace uso de un analizador y un protocolo. El analizador tiene como funcion principal parsear y analizar cada jugada que el usuario ingresa por teclado. Por otra parte, el prtocolo es el encargado de la comunicacion, le indica al socket que mensajes mandar para cumplir con lo pedido.



##### **Server:**

A continuacion se presenta un diagrama de clases para ilustrar el modelo del lado del server.

![](/home/santiago/Escritorio/Fiuba/Taller I/Tp3-Taller/img/clasesServer.png)

Se omiten los metodos para facilitar lectura.



**Conexion:**

El servidor lanza un hilo Listener el cual tiene como atributo el socket aceptador, un organiazdor y un bool seguirAceptando. Mientras el bool (es atomico ya que se accede desde otro hilo main) indique que siga aceptando el socket aceptador hara los accept y luego el organizador creara un nuevo hilo Jugador al que le asignara dicho socket aceptado, iniciara el hilo e insertara cada jugador en una lista de Jugador*. A su vez, cuando se agrega un nuevo jugador se recorre la lista para ir matando los jugadores que ya no corren mas. 

De esa manera ya queda establecida la coneccion del cliente con el servidor.



**Juego:**

 El organizador, ademas de la lista de jugadores, crea un monitor de partidas. Es necesario un monitor ya que el mapa donde se almacenan los punteros a partidas es accedido por multiples hilos de forma concurrente, es por eso que se maneja con un monitor que a su vez usa un mutex para evitar race conditions.

Cada vez que el organizador crea un jugador le pasa una referencia a dicho monitor, de esta manera cuandoel  Jugador se comunica con el cliente y  es necesario puede acceder al monitor para crear u obtener una partida. Para que el jugador no deba pasar por el monitor de partidas cada vez que desea modificar la partida a la cual esta conectado, se opto por incluir un atributo de puntero a partida y de esa forma no generar problemas. 

Como mas de un jugador tendra acceso a una misma partida (ambos tienen puntero a ella) se utilizo mutex y condition_variable para administrar de manera eficiente los turnos y no generar race conditions. Cuando no es el turno del jugador no se le permite obtener el tablero ni realizar jugadas.

Para lo que es el juego en si, cada partida tiene un atributo juego del tipo Tateti. Dicha clase es la encargada de implementar el tablero, indicar cuando hay ganador o empate y de construir el string de tablero que sera enviado a traves del socket, mediante el protocolo. 





**Secuencia importante**

A continuacion un diagrama de secuencia del lado del servidor de un jugador creando una partida.

![](/home/santiago/Escritorio/Fiuba/Taller I/Tp3-Taller/img/SecuenciaConectar.png)

Cabe mencionar que cuando el protocolo envia y recibe mensajes utilza el socket del jugador (no se icluyo en el diagrama para facilitar la lectura). El proceso para unirse a las partidas es muy similar.



**Aclaraciones:**

- Cuando un jugador intenta crear una partida que ya existe o unirse a una que no existe se corta la conexion.
- No se considera el caso donde mas de dos clientes se conectan a la misma partida.
- No se considera el caso donde se juega una posicion ya ocupada.
- Las partidas son borradas una vez termina el servidor.
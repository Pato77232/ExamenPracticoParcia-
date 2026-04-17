UNIVERSIDAD TÉCNICA DE AMBATO 

Facultad de Ingeniería en Sistemas, Electrónica e Industrial 

Carrera de Software 

 

 

 

Prueba Practica 1 Parcial 

UTA – Grupo B 

 

 

Asignatura: Estructura de Datos 

Docente: Ing. José Caizabuano Mg.  

Integrantes: Emmanuel Acosta, Edwin Caraguay, David Cuenca, Michael Rosillo 

 

Semestre: 3RO “B” Software 

 

Ambato – Ecuador 

Abril, 2025 

 

1. Introducción 

El presente informe documenta el desarrollo del proyecto de programación correspondiente al Grupo B de la asignatura Estructura de Datos. El sistema desarrollado se denomina SmartCampus UTA y tiene como objetivo gestionar la reserva y rotación de proyectores para las aulas de la facultad, resolviendo un problema real de administración de recursos tecnológicos compartidos. 

El proyecto fue implementado en lenguaje C++ utilizando Visual Studio Code como entorno de desarrollo, siguiendo los lineamientos establecidos por la cátedra. La solución integra las estructuras de datos vistas en clase: lista secuencial, lista simplemente enlazada, lista doblemente enlazada, cola, pila y lista circular, cada una aplicada a una función específica del sistema. 

La motivación principal del proyecto radica en aplicar los conocimientos teóricos sobre estructuras de datos a un contexto concreto, donde la elección de cada estructura no es arbitraria sino que responde a las características del problema que se desea resolver. 

2. Objetivos 

2.1 Objetivo General 

Desarrollar el sistema integral "SmartCampus UTA Web" para optimizar la gestión de servicios universitarios, utilizando estructuras de datos dinámicas propias y una arquitectura por capas que garantice un manejo eficiente y transparente de la información institucional. 

2.2 Objetivos Específicos 

Gestión Eficiente: Implementar un inventario y un sistema de trámites que utilice colas y listas enlazadas para reducir los tiempos de espera y evitar la pérdida de documentación física. 

Análisis de Infraestructura: Crear un módulo de análisis de red que clasifique el tráfico de solicitudes según el modelo TCP/IP, identificando patrones de uso para mejorar la toma de decisiones. 

Persistencia Robusta: Diseñar una base de datos relacional normalizada que asegure que toda la información procesada por las estructuras de datos se guarde de forma íntegra y segura. 

Experiencia del Usuario: Proveer una interfaz web intuitiva que permita a estudiantes y docentes consultar rutas internas y estados de trámites en tiempo real sin complicaciones técnicas. 

 

3. Descripción del Problema 

Cada grupo recibe una variante distinta del problema. Todas las versiones exigen las mismas estructuras, pero cambian el contexto, los datos y una regla de negocio diferenciadora. Esto permite evaluar el dominio conceptual sin caer en la copia literal. 

Grupo B. Sistema de reserva y rotación de proyectores para aulas 

Los proyectores de la facultad son compartidos por varios docentes. La coordinación necesita controlar reservas, devoluciones, espera y mantenimiento. 

Requerimientos funcionales obligatorios: 

Registrar proyectores por código, luminosidad, aula base y estado. 

Mantener la lista de reservas activas por docente. 

Atender solicitudes por orden de llegada cuando un proyector ya esté reservado. 

Administrar turnos circulares de uso en eventos con varios expositores. 

Deshacer el cambio de estado si un proyector fue enviado a mantenimiento por error. 

Regla diferenciadora del grupo: Antes de reservar, el sistema debe verificar que la lámpara del proyector no supere el límite de horas definido por el grupo. 

Datos mínimos de prueba sugeridos: PRO001, Epson, Aula B201, Disponible; PRO002, BenQ, Aula A102, Mantenimiento; PRO003, ViewSonic, Aula C301, Prestado. 

Regla diferenciadora del grupo: Las tablets con almacenamiento menor a 32 GB no pueden asignarse a grupos de investigación. 

Datos mínimos de prueba sugeridos: TAB001, Samsung, 64GB, Disponible; TAB002, Lenovo, 32GB, Prestado; TAB003, Huawei, 128GB, Disponible. 

 

4. Diseño del Sistema 

4.1 Arquitectura del Proyecto 

El proyecto fue organizado en tres archivos principales, siguiendo la separación entre modelos, estructuras y lógica principal: 

Archivo 

Contenido 

modelos.h / modelos.cpp 

Definición de las clases Proyector, Reserva, Solicitud, Accion y Expositor 

estructuras.h / estructuras.cpp 

Implementación de nodos y clases de cada estructura de datos 

main.cpp 

Lógica principal, menú de navegación y casos de prueba 

 

4.2 Estructuras de Datos Utilizadas 

A continuación se describe cada estructura de datos utilizada, junto con la justificación de su elección: 

Estructura 

Aplicación en el sistema 

Justificación de uso 

Lista secuencial 

Inventario de proyectores 

Permite acceso directo por índice y es eficiente para un número fijo de equipos registrados 

Lista simple enlazada 

Reservas activas por docente 

Las reservas se crean y eliminan con frecuencia; la lista enlazada es más eficiente que un arreglo para inserciones y eliminaciones dinámicas 

Lista doblemente enlazada 

Historial de movimientos 

La navegación hacia adelante y hacia atrás es necesaria para revisar el historial cronológico 

Cola (FIFO) 

Solicitudes en espera 

El primer docente en solicitar debe ser el primero en ser atendido cuando el recurso quede libre 

Pila (LIFO) 

Deshacer última acción 

La última acción realizada es la primera que se debe poder revertir, lo que corresponde exactamente al comportamiento de una pila 

Lista circular 

Turnos de expositores 

Los expositores se rotan en ciclos continuos; la lista circular permite avanzar sin condiciones de fin 

 

4.3 Descripción de clases 

4.3.1 estructuras.h  

El archivo estructuras.h define las estructuras de datos y clases fundamentales del sistema, las cuales permiten la gestión eficiente del inventario, reservas, historial, solicitudes y turnos. Estas estructuras combinan modelos de datos con implementaciones basadas en arreglos y listas enlazadas. 

4.3.1.1. Clase Proyector (Modelo de datos) 

Representa la entidad principal del sistema, correspondiente a los equipos disponibles para préstamo. 

Atributos: 

Código identificador.  

Marca.  

Aula base.  

Estado (Disponible, Prestado, Mantenimiento).  

Horas de uso de la lámpara.  

Límite máximo de horas de uso.  

Métodos: 

Constructor por defecto: 
Inicializa las horas de lámpara en cero y establece un límite predeterminado.  

Constructor parametrizado: 
Permite instanciar un proyector con valores específicos para todos sus atributos.  

mostrar() 
Presenta la información del proyector en formato estructurado, facilitando su visualización en consola.  

 

4.3.1.2. Clase Reserva (Modelo de datos) 

Representa una asignación temporal de un proyector a un docente. 

Atributos: 

Nombre del docente.  

Código del proyector.  

Fecha de la reserva.  

Métodos: 

Constructor por defecto y parametrizado: 
Permiten la creación de instancias con o sin inicialización inmediata.  

mostrar() 
Imprime los datos de la reserva de forma organizada.  

 

4.3.1.3. Estructura plantilla Nodo<T> 

Define un nodo genérico utilizado como base para estructuras dinámicas. 

Atributos: 

dato: almacena el valor de tipo genérico.  

siguiente: puntero al siguiente nodo.  

anterior: puntero al nodo previo (utilizado en listas dobles).  

Método: 

Constructor: 
Inicializa el nodo con un valor y establece punteros en nullptr.  

 

4.3.1.4. Clase ListaSecuencial (Arreglo estático — Inventario) 

Implementa una lista basada en un arreglo de tamaño fijo. 

Métodos: 

insertar(const Proyector&) 
Agrega un nuevo proyector al final del arreglo.  

Verifica capacidad máxima.  

Evita duplicados por código.  

buscar(const string&) 
Realiza una búsqueda secuencial.  

Retorna un puntero al proyector si existe.  

Retorna nullptr en caso contrario.  

modificarEstado(const string&, const string&) 
Cambia el estado de un proyector.  

Valida existencia previa.  

eliminar(const string&) 
Elimina un proyector desplazando los elementos posteriores.  

Mantiene la continuidad del arreglo.  

mostrarTodos() 
Recorre e imprime todos los elementos almacenados.  

getTamanio() 
Retorna el número actual de elementos.  

 

4.3.1.5. Clase ListaReservas (Lista simplemente enlazada) 

Gestiona las reservas activas. 

Métodos: 

Constructor y destructor: 
Inicializa la lista y libera memoria de los nodos.  

insertar(const Reserva&) 
Inserta un nodo al inicio de la lista (inserción en cabeza).  

eliminar(const string&, const string&) 
Elimina una reserva específica mediante búsqueda por docente y código.  

Ajusta enlaces entre nodos.  

existe(const string&) 
Verifica si existe una reserva para un proyector.  

mostrarTodas() 
Recorre la lista mostrando todas las reservas.  

getTamanio() 
Retorna la cantidad de reservas activas.  

 

4.3.1.6. Clase ListaHistorial (Lista doblemente enlazada) 

Almacena el historial de eventos del sistema. 

Métodos: 

Constructor y destructor: 
Inicializa la lista y libera memoria.  

insertarAlFinal(const string&) 
Inserta eventos al final.  

Mantiene referencias a cabeza y cola.  

mostrarAdelante() 
Recorre desde el inicio hacia el final.  

mostrarAtras() 
Recorre desde el final hacia el inicio.  

getTamanio() 
Retorna el número de eventos registrados.  

 

4.3.1.7. Clase Cola (Estructura FIFO) 

Administra solicitudes en espera siguiendo el principio “primero en entrar, primero en salir”. 

Métodos: 

Constructor y destructor: 
Inicializan la cola y liberan memoria automáticamente.  

encolar(const Reserva&) 
Inserta un elemento al final de la cola.  

desencolar() 
Extrae el elemento del frente.  

Lanza excepción si la cola está vacía.  

verFrente() 
Permite consultar el primer elemento sin eliminarlo.  

estaVacia() 
Indica si la cola contiene elementos.  

listar() 
Recorre e imprime todos los elementos.  

getTamanio() 
Retorna el número de elementos en la cola.  

 

4.3.1.8. Clase Pila (Estructura LIFO — Deshacer) 

Permite revertir acciones mediante una pila. 

Estructura auxiliar: AccionDeshacer 

Almacena: 

Tipo de acción.  

Código del proyector.  

Estado anterior.  

Métodos: 

apilar(const AccionDeshacer&) 
Inserta una acción en el tope de la pila.  

desapilar() 
Elimina y retorna la última acción registrada.  

verTope() 
Consulta la acción más reciente.  

estaVacia() 
Indica si la pila está vacía.  

mostrarTope() 
Muestra información de la última acción.  

getTamanio() 
Retorna el número de elementos.  

 

4.3.1.9. Clase ListaCircular (Lista circular — Turnos) 

Gestiona turnos rotativos de expositores. 

Métodos: 

Constructor y destructor: 
Inicializan la lista y liberan memoria considerando la estructura circular.  

insertar(const string&) 
Inserta un nuevo nodo en la lista.  

Mantiene la circularidad.  

avanzar() 
Desplaza el puntero al siguiente nodo.  

Implementa rotación continua.  

eliminarActual() 
Elimina el nodo actual y actualiza referencias.  

mostrarRonda() 
Recorre toda la lista desde el nodo actual.  

getTurnoActual() 
Retorna el valor del nodo actual.  

estaVacia() 
Verifica si la lista contiene elementos.  

getTamanio() 
Retorna el número de nodos. 

La estructura y uso en el sistema se resumen en esta tabla: 

Clase 

Estructura 

Uso en el sistema 

Proyector 

Modelo de datos 

Atributos: código, marca, aula, estado, horas lámpara 

Reserva 

Modelo de datos 

Docente, código proyector, fecha 

Nodo<T> 

Template genérico 

Base para todas las estructuras dinámicas 

ListaSecuencial 

Arreglo estático 

Inventario de proyectores 

ListaReservas 

Lista simple enlazada 

Reservas activas por docente 

ListaHistorial 

Lista doble enlazada 

Historial (recorre adelante y atrás) 

Cola 

FIFO con nodos 

Solicitudes en espera 

Pila 

LIFO con nodos 

Deshacer cambios de estado 

ListaCircular 

Circular con nodos 

Turnos rotativos de expositores 

4.3.2 main.cpp 

Contiene main() y los 7 submenús: inventario, reservas, cola, historial, turnos, mantenimiento y deshacer. El sistema se organiza en siete submenús principales, cada uno encargado de gestionar una funcionalidad específica. Estos módulos operan de manera independiente, pero comparten estructuras de datos comunes, garantizando coherencia en la gestión de la información. A continuación, la descripción de cada uno. 

4.3.2.1. Submenú de Inventario 

Este submenú permite la administración completa del inventario de proyectores almacenado en la estructura ListaSecuencial. 

Funciones principales: 

Registro de nuevos proyectores mediante el ingreso de sus atributos.  

Búsqueda de proyectores por código identificador.  

Visualización completa del inventario.  

Modificación del estado operativo del proyector (Disponible, Prestado, Mantenimiento).  

Eliminación de proyectores del sistema.  

Comportamiento relevante: 

Antes de modificar el estado de un proyector, el sistema almacena su estado anterior en la pila de deshacer, permitiendo revertir cambios. Todas las operaciones son registradas en el historial. 

 

4.3.2.2. Submenú de Reservas Activas 

Gestiona las reservas vigentes mediante la estructura ListaReservas. 

Funciones principales: 

Registro de nuevas reservas asociadas a un docente, proyector y fecha.  

Cancelación de reservas existentes.  

Visualización de todas las reservas activas.  

Comportamiento relevante: 

El sistema valida condiciones antes de registrar una reserva: 

Disponibilidad del proyector.  

Estado de la lámpara  

En caso de incumplimiento, la solicitud se redirige automáticamente a la cola de espera. Además, al registrar una reserva, el estado del proyector se actualiza a "Prestado". 

 

 

4.3.2.3. Submenú de Cola de Solicitudes 

Administra solicitudes pendientes utilizando una estructura tipo cola (FIFO). 

Funciones principales: 

Ingreso de nuevas solicitudes a la cola.  

Atención de la siguiente solicitud en orden de llegada.  

Consulta del elemento al frente de la cola.  

Visualización completa de las solicitudes en espera.  

Comportamiento relevante: 

Al atender una solicitud, el sistema verifica nuevamente la disponibilidad del proyector. Si no cumple las condiciones, la solicitud es reinsertada en la cola, garantizando que no se pierda. 

 

4.3.2.4. Submenú de Historial de Movimientos 

Permite la visualización de eventos registrados en el sistema mediante una lista doblemente enlazada. 

Funciones principales: 

Mostrar el historial en orden cronológico (de inicio a fin).  

Mostrar el historial en orden inverso (de fin a inicio).  

Comportamiento relevante: 

El historial registra todas las operaciones relevantes, proporcionando trazabilidad y seguimiento de las acciones realizadas por el usuario. 

 

4.3.2.5. Submenú de Turnos Circulares 

Gestiona la rotación de expositores mediante una lista circular. 

Funciones principales: 

Inserción de nuevos participantes en la lista de turnos.  

Avance al siguiente turno de manera cíclica.  

Eliminación del expositor actual.  

Visualización completa de la ronda de turnos.  

Comportamiento relevante: 

La estructura circular permite que, al llegar al último elemento, el sistema continúe desde el primero, garantizando una rotación continua sin interrupciones. 

4.3.2.6. Submenú de Mantenimiento 

Administra el estado de mantenimiento de los proyectores. 

Funciones principales: 

Envío de proyectores a mantenimiento.  

Registro de proyectores reparados.  

Visualización de proyectores en estado de mantenimiento.  

Comportamiento relevante: 

Antes de modificar el estado del proyector, se almacena el estado anterior en la pila de deshacer. Esto permite revertir cambios en caso de errores operativos. 

 

4.3.2.7. Submenú de Deshacer 

Permite revertir la última acción realizada en el sistema. 

Funciones principales: 

Visualización de la última acción almacenada en la pila.  

Confirmación del usuario para ejecutar la reversión.  

Restauración del estado previo del proyector.  

Comportamiento relevante: 

El sistema utiliza una estructura tipo pila (LIFO), garantizando que la última acción realizada sea la primera en deshacerse. Actualmente, se enfoca en revertir cambios de estado de los proyectores. 

 

5. Explicación y justificación de cada estructura 

 

5.1. Lista Secuencial — Inventario de proyectores (datos[]) 

Se usa un arreglo de tamaño fijo (CAPACIDAD = 50) para guardar todos los proyectores registrados. 

Por qué arreglo y no lista enlazada: el inventario tiene un tamaño máximo razonable y conocido. Lo que más se hace sobre él es buscar por código, modificar estado y recorrer todos, operaciones que con el arreglo se hacen en O(n) recorriendo desde el índice 0. Además, getProyector(i) permite acceso directo por posición, algo que una lista enlazada no puede hacer sin recorrer nodo por nodo. Si se usara std::vector estaríamos usando una estructura de la STL equivalente, que el examen prohíbe explícitamente. 

Operación de eliminación: cuando se elimina un proyector, los elementos se desplazan hacia la izquierda para no dejar huecos. El sistema también valida que el proyector no tenga una reserva activa antes de permitir la eliminación, lo cual protege la integridad de los datos. 

 

5.2. Lista Simplemente Enlazada — Reservas activas (NodoSimple) 

Cada reserva es un nodo que contiene el objeto Reserva y un puntero siguiente al próximo nodo. 

Por qué lista enlazada y no arreglo: las reservas nacen y mueren constantemente durante el día. Un docente reserva un proyector, otro lo devuelve, llega una reserva nueva. Con un arreglo habría que reservar espacio fijo y gestionar huecos. La lista crece y se encoge exactamente con la memoria que necesita en cada momento. La inserción al inicio es O(1) porque simplemente el nuevo nodo apunta al antiguo cabeza. La eliminación localiza el nodo por código de proyector y ajusta los punteros sin mover nada más. 

Lógica de negocio integrada: antes de crear una reserva, el sistema verifica tres condiciones: que el proyector exista en el inventario, que no esté en mantenimiento, y que la lámpara no supere el límite de horas (regla diferenciadora del Grupo B). Si el proyector ya está ocupado pero es válido, la petición se encola automáticamente en vez de rechazarse. 

 

5.3. Lista Doblemente Enlazada — Historial (NodoDoble) 

Cada acción del sistema genera un nodo con punteros anterior y siguiente, formando una cadena bidireccional. 

Por qué lista doble y no simple: el historial necesita navegación hacia adelante Y hacia atrás. Con una lista simple solo se puede avanzar. El puntero actual guarda la posición de navegación actual, independientemente del cabeza y la cola. Cuando el usuario quiere revisar una acción anterior (por ejemplo para verificar quién reservó un proyector hace dos horas), recorre hacia atrás. Cuando quiere volver al presente, avanza. Esta navegación bidireccional es el caso de uso exacto para el que fue diseñada la lista doble. 

Inserción siempre al final: todas las acciones nuevas van al final (la más reciente) y el puntero actual se mueve automáticamente allí. Esto simula el comportamiento de un log real donde lo más nuevo es lo más relevante. 

 

5.4. Cola FIFO — Solicitudes en espera (NodoCola) 

Cuando un proyector está ocupado, la nueva petición entra por el final_ de la cola y sale por el frente cuando hay disponibilidad. 

Por qué cola y no pila: el criterio de atención es el orden de llegada. La primera persona que pidió el proyector debe ser la primera en recibirlo cuando quede libre. Eso es exactamente FIFO. Si se usara una pila (LIFO), el último en llegar sería el primero atendido, lo que sería injusto. La cola garantiza equidad y trazabilidad del proceso de espera. 

Integración con el módulo de reservas: cuando un proyector es devuelto, el sistema avisa automáticamente si hay solicitudes pendientes en la cola para ese proyector, invitando al operador a desencolar y asignar. Esto conecta los dos módulos de forma coherente. 

 

5.5. Pila LIFO — Deshacer última acción (NodoPila) 

Cada cambio de estado importante apila tres datos: la descripción de la acción, el código del proyector afectado y el estado anterior al cambio. 

Por qué pila y no historial: el deshacer siempre revierte la última acción realizada, no una acción arbitraria del pasado. La pila modela esto de forma natural porque el tope siempre es lo más reciente. Cuando se hace "deshacer", se desapila el tope, se recupera el estado anterior y se restaura el proyector a ese estado. Intentar implementar esto con otro tipo de lista requeriría lógica adicional para siempre ir al último elemento. 

Cuándo se apila: cada vez que se cambia el estado de un proyector (enviarlo a mantenimiento, reservarlo, modificarlo manualmente) se apila el estado anterior. Así la pila siempre tiene disponible el "punto de retorno". El historial registra el deshacer también, para que quede trazabilidad de que se revirtió una acción. 

 

 

 

6.6. Lista Circular — Turnos de expositores (NodoCircular) 

Los expositores forman un ciclo donde el último nodo apunta al primero. El puntero actual siempre indica quién tiene el turno en este momento. 

Por qué lista circular y no arreglo ni lista simple: en eventos con varios expositores, el turno rota indefinidamente sin fin. Con un arreglo habría que detectar el final y volver manualmente al índice 0. Con una lista simple habría que preguntar si siguiente == nullptr y saltar al principio. La lista circular elimina esa lógica: el puntero siguiente del último nodo ya apunta al primero, así que avanzarTurno() es simplemente actual = actual->siguiente sin ninguna condición especial. 

Eliminación del actual: cuando se elimina el nodo actual (un expositor que abandona el evento), el sistema recorre la lista para encontrar el nodo anterior, ajusta sus punteros y mueve actual al siguiente. Así el ciclo se mantiene íntegro con un nodo menos. 

 

 

6. Respuestas a las preguntas de defensa oral 

 

¿Por qué la cola era más adecuada que una pila para atender solicitudes en espera? 

Porque el criterio de atención es el orden de llegada. El primer docente que pidió el proyector tiene más derecho a recibirlo cuando quede libre que el que llegó después. La cola garantiza ese orden (FIFO). Si usáramos una pila, el último en pedir sería el primero en ser atendido, lo cual es injusto y viola la lógica del proceso real. La cola refleja exactamente cómo funciona una fila de espera en la vida real. 

¿Qué ventajas ofrece una lista doblemente enlazada frente a una lista simple en el historial? 

La lista doble permite navegar tanto hacia adelante como hacia atrás. En el historial esto es esencial: si el operador quiere revisar qué pasó con un proyector hace varias horas, necesita retroceder. Con una lista simple solo podría avanzar desde el inicio hasta el punto que busca, sin poder volver. La lista doble tiene un puntero anterior en cada nodo que hace esa navegación bidireccional en O(1) por cada paso. 

¿Qué ocurriría si eliminara el nodo actual dentro de la lista circular? 

El sistema busca primero el nodo anterior al actual recorriendo el ciclo completo, ajusta su siguiente para que apunte al nodo que estaba después del eliminado, libera la memoria del nodo eliminado y mueve el puntero actual al siguiente nodo. Si solo había un nodo en la lista, actual queda en nullptr y la ronda queda vacía. Sin ese proceso de ajuste, el ciclo quedaría roto y acceder a actual->siguiente sería un puntero colgante con comportamiento indefinido. 

¿Cómo garantiza el programa que un proyector en mantenimiento no sea prestado? 

En dos puntos del código. Primero, en menuReservas() al intentar reservar se verifica p->estado == MANTENIMIENTO antes de proceder, y si es así se rechaza la operación con un mensaje claro. Segundo, la regla diferenciadora del Grupo B añade una verificación adicional: si las horas de lámpara superan el límite, el proyector tampoco puede reservarse aunque su estado sea "Disponible". Esas dos barreras juntas protegen que un proyector no apto llegue a manos de un docente. 

¿Qué acción decidió hacer reversible con la pila y por qué? 

El cambio de estado de los proyectores, especialmente el envío a mantenimiento. Esta es la acción más crítica porque un error aquí deja al proyector fuera de uso innecesariamente. Si el administrador envía por error a mantenimiento un proyector que estaba funcionando bien, con un solo "deshacer" se restaura el estado anterior sin necesidad de buscar manualmente el proyector y editarlo. La pila guarda el estado previo exacto, así que la reversión es perfecta y no depende de que el operador recuerde cuál era el estado anterior. 

¿Qué operaciones tienen mayor costo en la implementación? 

La eliminación en la lista circular es la más costosa porque requiere recorrer toda la lista para encontrar el nodo anterior al actual, siendo O(n). La búsqueda en el inventario y en las reservas también es O(n) porque se recorre elemento por elemento hasta encontrar el código buscado. La inserción en la pila, en la cola y en la lista de reservas es O(1) porque siempre se inserta en un extremo conocido (tope, final o cabeza) sin recorrer nada. 

¿Cómo escalaría el sistema si la universidad duplicara el número de proyectores? 

Las estructuras dinámicas (lista de reservas, cola, pila, historial, lista circular) escalan sin cambios porque crecen con new según la memoria disponible. El único límite es el inventario con arreglo fijo de 50 posiciones. Para escalar ese módulo bastaría con aumentar la constante CAPACIDAD o reemplazar el arreglo por una lista enlazada también dinámica. En ese caso la lógica de inserción, búsqueda y eliminación sería prácticamente la misma, solo cambia la estructura interna de almacenamiento. 

 

 

7. Conclusiones 

El módulo de análisis de red bajo el modelo TCP/IP permite transformar datos técnicos en información útil, facilitando al administrador la toma de decisiones basada en el tráfico real y la demanda del campus. 

La integración de una base de datos normalizada en 3FN asegura que la información procesada por la lógica de negocio se mantenga íntegra, protegida y disponible para consultas históricas sin redundancias. 

La arquitectura por capas separa eficazmente la complejidad técnica de la interfaz de usuario, permitiendo que el sistema crezca modularmente y se recupere de errores mediante el sistema de "deshacer" (pila). 

El desarrollo del proyecto permitió consolidar conocimientos críticos sobre punteros y algoritmos de búsqueda, demostrando que el diseño de software de alto rendimiento requiere un entendimiento profundo de las estructuras de datos. 

8. Enlace de GitHub 

Para mayor facilidad al momento de desarrollar la prueba practica utilizamos la herramienta que es GitHub a continuación adjuntamos el enlace donde se encuentra nuestro código con capturas de su funcionamiento. 

https://github.com/Pato77232/ExamenPracticoParcia- 



<img width="476" height="481" alt="image" src="https://github.com/user-attachments/assets/fe1c60dd-56fa-40f1-92fb-f338af909046" />

<img width="421" height="229" alt="image" src="https://github.com/user-attachments/assets/3e5c43d5-ffea-45c8-9293-7267f6a6b702" />

<img width="444" height="270" alt="image" src="https://github.com/user-attachments/assets/cb51ab83-3a0b-4a44-906f-d348f54e4e83" />

<img width="447" height="709" alt="image" src="https://github.com/user-attachments/assets/6f147212-a545-4009-8a2a-ab2a52fca7dd" />

<img width="449" height="175" alt="image" src="https://github.com/user-attachments/assets/d1f89ae0-c881-4bd0-9ff8-ef1d47fa1285" />

<img width="425" height="200" alt="image" src="https://github.com/user-attachments/assets/ffd8d813-b44d-4ac0-a46c-a48ad66aebf6" />

<img width="484" height="193" alt="image" src="https://github.com/user-attachments/assets/a0382295-76d6-4406-b9be-0e3ff8fa7f3c" />

<img width="565" height="206" alt="image" src="https://github.com/user-attachments/assets/51e08841-5fda-4e75-994a-f4182bef326e" />

<img width="458" height="280" alt="image" src="https://github.com/user-attachments/assets/e28188a2-910c-4cd0-819a-ae89d042698e" />

<img width="395" height="217" alt="image" src="https://github.com/user-attachments/assets/468cbcc0-dbbf-4855-b5b3-c66ee5e773f3" />

<img width="397" height="199" alt="image" src="https://github.com/user-attachments/assets/f03fa171-d2b0-4806-ba36-0acd5d0465e2" />

<img width="408" height="215" alt="image" src="https://github.com/user-attachments/assets/6164c1a2-f34a-44a0-a222-9ce96d7471d7" />

<img width="428" height="380" alt="image" src="https://github.com/user-attachments/assets/3ee9affc-093b-49cd-86aa-4f105a103241" />

#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <iostream>
#include <string>
using namespace std;

// ============================================================
//  CLASE: Proyector (modelo de datos)
// ============================================================
class Proyector {
public:
    string codigo;
    string marca;
    string aulaBase;
    string estado;        // Disponible, Prestado, Mantenimiento
    int horasLampara;
    int limiteHoras;

    Proyector() : horasLampara(0), limiteHoras(500) {}
    Proyector(string cod, string mar, string aula, string est, int horas = 0, int limite = 500)
        : codigo(cod), marca(mar), aulaBase(aula), estado(est),
          horasLampara(horas), limiteHoras(limite) {}

    void mostrar() const {
        cout << "  Codigo    : " << codigo      << "\n"
             << "  Marca     : " << marca       << "\n"
             << "  Aula Base : " << aulaBase    << "\n"
             << "  Estado    : " << estado      << "\n"
             << "  Lampara   : " << horasLampara << " / " << limiteHoras << " horas\n";
    }
};

// ============================================================
//  CLASE: Reserva
// ============================================================
class Reserva {
public:
    string docente;
    string codigoProyector;
    string fecha;

    Reserva() {}
    Reserva(string doc, string cod, string fec)
        : docente(doc), codigoProyector(cod), fecha(fec) {}

    void mostrar() const {
        cout << "  Docente  : " << docente         << "\n"
             << "  Proyector: " << codigoProyector  << "\n"
             << "  Fecha    : " << fecha            << "\n";
    }
};

// ============================================================
//  NODO generico para listas enlazadas
// ============================================================
template <typename T>
struct Nodo {
    T dato;
    Nodo* siguiente;
    Nodo* anterior;  // Para lista doble

    Nodo(T d) : dato(d), siguiente(nullptr), anterior(nullptr) {}
};

// ============================================================
//  LISTA SECUENCIAL (arreglo dinamico) — Inventario de proyectores
// ============================================================
class ListaSecuencial {
private:
    static const int CAPACIDAD = 50;
    Proyector datos[CAPACIDAD];
    int tamanio;

public:
    ListaSecuencial() : tamanio(0) {}

    bool insertar(const Proyector& p) {
        if (tamanio >= CAPACIDAD) {
            cout << "[Error] Inventario lleno.\n";
            return false;
        }
        // Verificar duplicado
        for (int i = 0; i < tamanio; i++) {
            if (datos[i].codigo == p.codigo) {
                cout << "[Error] Ya existe un proyector con ese codigo.\n";
                return false;
            }
        }
        datos[tamanio++] = p;
        return true;
    }

    Proyector* buscar(const string& codigo) {
        for (int i = 0; i < tamanio; i++)
            if (datos[i].codigo == codigo)
                return &datos[i];
        return nullptr;
    }

    bool modificarEstado(const string& codigo, const string& nuevoEstado) {
        Proyector* p = buscar(codigo);
        if (!p) { cout << "[Error] Proyector no encontrado.\n"; return false; }
        p->estado = nuevoEstado;
        return true;
    }

    bool eliminar(const string& codigo) {
        for (int i = 0; i < tamanio; i++) {
            if (datos[i].codigo == codigo) {
                for (int j = i; j < tamanio - 1; j++)
                    datos[j] = datos[j + 1];
                tamanio--;
                return true;
            }
        }
        cout << "[Error] Proyector no encontrado.\n";
        return false;
    }

    void mostrarTodos() const {
        if (tamanio == 0) { cout << "  [Inventario vacio]\n"; return; }
        for (int i = 0; i < tamanio; i++) {
            cout << "--- Proyector #" << (i + 1) << " ---\n";
            datos[i].mostrar();
        }
    }

    int getTamanio() const { return tamanio; }
};

// ============================================================
//  LISTA SIMPLEMENTE ENLAZADA — Reservas activas
// ============================================================
class ListaReservas {
private:
    Nodo<Reserva>* cabeza;
    int tamanio;

public:
    ListaReservas() : cabeza(nullptr), tamanio(0) {}

    ~ListaReservas() {
        Nodo<Reserva>* actual = cabeza;
        while (actual) {
            Nodo<Reserva>* sig = actual->siguiente;
            delete actual;
            actual = sig;
        }
    }

    void insertar(const Reserva& r) {
        Nodo<Reserva>* nuevo = new Nodo<Reserva>(r);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        tamanio++;
    }

    bool eliminar(const string& docente, const string& codigo) {
        Nodo<Reserva>* actual = cabeza;
        Nodo<Reserva>* anterior = nullptr;
        while (actual) {
            if (actual->dato.docente == docente &&
                actual->dato.codigoProyector == codigo) {
                if (anterior) anterior->siguiente = actual->siguiente;
                else cabeza = actual->siguiente;
                delete actual;
                tamanio--;
                return true;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        return false;
    }

    bool existe(const string& codigo) const {
        Nodo<Reserva>* actual = cabeza;
        while (actual) {
            if (actual->dato.codigoProyector == codigo) return true;
            actual = actual->siguiente;
        }
        return false;
    }

    void mostrarTodas() const {
        if (!cabeza) { cout << "  [Sin reservas activas]\n"; return; }
        Nodo<Reserva>* actual = cabeza;
        int i = 1;
        while (actual) {
            cout << "--- Reserva #" << i++ << " ---\n";
            actual->dato.mostrar();
            actual = actual->siguiente;
        }
    }

    int getTamanio() const { return tamanio; }
};

// ============================================================
//  LISTA DOBLEMENTE ENLAZADA — Historial de movimientos
// ============================================================
class ListaHistorial {
private:
    Nodo<string>* cabeza;
    Nodo<string>* cola;
    int tamanio;

public:
    ListaHistorial() : cabeza(nullptr), cola(nullptr), tamanio(0) {}

    ~ListaHistorial() {
        Nodo<string>* actual = cabeza;
        while (actual) {
            Nodo<string>* sig = actual->siguiente;
            delete actual;
            actual = sig;
        }
    }

    void insertarAlFinal(const string& evento) {
        Nodo<string>* nuevo = new Nodo<string>(evento);
        if (!cola) {
            cabeza = cola = nuevo;
        } else {
            nuevo->anterior = cola;
            cola->siguiente = nuevo;
            cola = nuevo;
        }
        tamanio++;
    }

    void mostrarAdelante() const {
        if (!cabeza) { cout << "  [Historial vacio]\n"; return; }
        Nodo<string>* actual = cabeza;
        int i = 1;
        cout << "  >> Historial (inicio -> fin):\n";
        while (actual) {
            cout << "  " << i++ << ". " << actual->dato << "\n";
            actual = actual->siguiente;
        }
    }

    void mostrarAtras() const {
        if (!cola) { cout << "  [Historial vacio]\n"; return; }
        Nodo<string>* actual = cola;
        int i = tamanio;
        cout << "  >> Historial (fin -> inicio):\n";
        while (actual) {
            cout << "  " << i-- << ". " << actual->dato << "\n";
            actual = actual->anterior;
        }
    }

    int getTamanio() const { return tamanio; }
};

// ============================================================
//  COLA — Solicitudes en espera (FIFO)
// ============================================================
class Cola {
private:
    Nodo<Reserva>* frente;
    Nodo<Reserva>* fondo;
    int tamanio;

public:
    Cola() : frente(nullptr), fondo(nullptr), tamanio(0) {}

    ~Cola() {
        while (!estaVacia()) desencolar();
    }

    void encolar(const Reserva& r) {
        Nodo<Reserva>* nuevo = new Nodo<Reserva>(r);
        if (!fondo) { frente = fondo = nuevo; }
        else { fondo->siguiente = nuevo; fondo = nuevo; }
        tamanio++;
    }

    Reserva desencolar() {
        if (estaVacia()) throw runtime_error("Cola vacia");
        Nodo<Reserva>* temp = frente;
        Reserva r = temp->dato;
        frente = frente->siguiente;
        if (!frente) fondo = nullptr;
        delete temp;
        tamanio--;
        return r;
    }

    Reserva verFrente() const {
        if (estaVacia()) throw runtime_error("Cola vacia");
        return frente->dato;
    }

    bool estaVacia() const { return frente == nullptr; }
    int getTamanio() const { return tamanio; }

    void listar() const {
        if (estaVacia()) { cout << "  [Cola vacia]\n"; return; }
        Nodo<Reserva>* actual = frente;
        int i = 1;
        while (actual) {
            cout << "  Posicion " << i++ << ":\n";
            actual->dato.mostrar();
            actual = actual->siguiente;
        }
    }
};

// ============================================================
//  PILA — Deshacer ultima accion (LIFO)
// ============================================================
struct AccionDeshacer {
    string tipo;       // "cambio_estado"
    string codigo;
    string estadoAnterior;

    AccionDeshacer() {}
    AccionDeshacer(string t, string c, string e)
        : tipo(t), codigo(c), estadoAnterior(e) {}
};

class Pila {
private:
    Nodo<AccionDeshacer>* tope;
    int tamanio;

public:
    Pila() : tope(nullptr), tamanio(0) {}

    ~Pila() {
        while (!estaVacia()) desapilar();
    }

    void apilar(const AccionDeshacer& a) {
        Nodo<AccionDeshacer>* nuevo = new Nodo<AccionDeshacer>(a);
        nuevo->siguiente = tope;
        tope = nuevo;
        tamanio++;
    }

    AccionDeshacer desapilar() {
        if (estaVacia()) throw runtime_error("Pila vacia");
        Nodo<AccionDeshacer>* temp = tope;
        AccionDeshacer a = temp->dato;
        tope = tope->siguiente;
        delete temp;
        tamanio--;
        return a;
    }

    AccionDeshacer verTope() const {
        if (estaVacia()) throw runtime_error("Pila vacia");
        return tope->dato;
    }

    bool estaVacia() const { return tope == nullptr; }
    int getTamanio() const { return tamanio; }

    void mostrarTope() const {
        if (estaVacia()) { cout << "  [Pila vacia, no hay acciones para deshacer]\n"; return; }
        AccionDeshacer a = verTope();
        cout << "  Accion en tope:\n"
             << "    Tipo    : " << a.tipo          << "\n"
             << "    Codigo  : " << a.codigo        << "\n"
             << "    Anterior: " << a.estadoAnterior << "\n";
    }
};

// ============================================================
//  LISTA CIRCULAR — Turnos rotativos de expositores
// ============================================================
class ListaCircular {
private:
    Nodo<string>* actual;
    int tamanio;

public:
    ListaCircular() : actual(nullptr), tamanio(0) {}

    ~ListaCircular() {
        if (!actual) return;
        Nodo<string>* inicio = actual;
        do {
            Nodo<string>* sig = actual->siguiente;
            delete actual;
            actual = sig;
        } while (actual != inicio);
    }

    void insertar(const string& nombre) {
        Nodo<string>* nuevo = new Nodo<string>(nombre);
        if (!actual) {
            nuevo->siguiente = nuevo;
            actual = nuevo;
        } else {
            // Recorrer hasta el ultimo
            Nodo<string>* temp = actual;
            while (temp->siguiente != actual) temp = temp->siguiente;
            temp->siguiente = nuevo;
            nuevo->siguiente = actual;
        }
        tamanio++;
    }

    void avanzar() {
        if (!actual) { cout << "  [Lista circular vacia]\n"; return; }
        actual = actual->siguiente;
        cout << "  Turno actual: " << actual->dato << "\n";
    }

    void eliminarActual() {
        if (!actual) { cout << "  [Lista circular vacia]\n"; return; }
        if (tamanio == 1) {
            delete actual;
            actual = nullptr;
            tamanio--;
            return;
        }
        Nodo<string>* temp = actual;
        Nodo<string>* previo = actual;
        while (previo->siguiente != actual) previo = previo->siguiente;
        previo->siguiente = actual->siguiente;
        actual = actual->siguiente;
        delete temp;
        tamanio--;
    }

    void mostrarRonda() const {
        if (!actual) { cout << "  [Sin expositores en lista circular]\n"; return; }
        Nodo<string>* temp = actual;
        int i = 1;
        cout << "  >> Ronda actual (inicio desde turno activo):\n";
        do {
            cout << "  " << i++ << ". " << temp->dato;
            if (temp == actual) cout << "  <-- TURNO ACTUAL";
            cout << "\n";
            temp = temp->siguiente;
        } while (temp != actual);
    }

    string getTurnoActual() const {
        if (!actual) return "";
        return actual->dato;
    }

    bool estaVacia() const { return actual == nullptr; }
    int getTamanio() const { return tamanio; }
};

#endif // ESTRUCTURAS_H
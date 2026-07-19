#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

/*Elaborado por: Juan Blondell 32409160
                 Maria Marcacci 32397269
                 Ernesto Gutierrez 32523545*/

struct Especie {
    int id;
    string nombre;
    int salud;
    int damage;
    int rapidez;
};

struct Clase {
    int id;
    string nombre;
    int salud;
    int damage;
    int rapidez;
};

struct Arma {
    int id;
    string nombre;
    string tipo;
    int damage;
    int peso;
};

struct Escudo {
    int id;
    string nombre;
    string tipo;
    int capacidad;
    int recarga;
    int consumo;
};

struct Heroes {
    int id;
    string nombre;
    int salud;
    int damage;
    int rapidez;
};

struct PersonajeCombinado {
    string nombreCompleto;
    int saludTotal;
    int damageTotal;
    int rapidezTotal;
};

struct NodoEspecie {
    Especie dato;
    NodoEspecie* siguiente = nullptr;
};

struct NodoClase {
    Clase dato;
    NodoClase* siguiente = nullptr;
};

struct NodoHeroe {
    Heroes dato;
    NodoHeroe* siguiente = nullptr;
};

struct NodoArma {
    Arma dato;
    NodoArma* siguiente = nullptr;
};

struct NodoEscudo {
    Escudo dato;
    NodoEscudo* siguiente = nullptr;
};

struct Personaje {
    string nombre;
    PersonajeCombinado Personaje_comb;
    int ID_Clave;
    int ID_Bando;
    int Clase_ID;
    NodoEscudo* escudos = nullptr;
    NodoArma*   arsenal = nullptr;
};

struct NodoBtree {
    Personaje* Personajes[3] = {nullptr, nullptr, nullptr};
    int cant_pj = 0;
    NodoBtree* hijos[4] = {nullptr, nullptr, nullptr, nullptr};
    bool hoja = true;
};

NodoBtree* Raiz_Btree = nullptr;

void cambiarTurno(int& turnoActual) {
    turnoActual = (turnoActual == 1) ? 2 : 1;
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int lanzarDado(int mod) {
    return (rand() % mod) + 1;
}

void pausar() {
    cout << "\nPresione Enter para continuar...";
    string p;
    getline(cin, p);
}

int extraerCampo(ifstream& archivo) {
    string linea;
    while (getline(archivo, linea)) {
        string limpia = "";
        for (char c : linea)
            if (c != ' ' && c != '\t' && c != '\r') limpia += c;
        if (limpia.empty()) continue;
        if (limpia.find("---") != string::npos) return -999;
        if (limpia == "-") return -1;
        try { return stoi(limpia); } catch (...) { continue; }
    }
    return -1;
}

int extraerValor(ifstream& archivo) {
    string linea;
    while (getline(archivo, linea)) {
        string limpia = "";
        for (char c : linea)
            if (c != ' ' && c != '\t' && c != '\r') limpia += c;
        if (limpia.empty() || limpia == "-" || limpia.find("---") != string::npos) continue;
        try { return stoi(limpia); } catch (...) { continue; }
    }
    return 0;
}

void insertarEspecie(NodoEspecie*& cabeza, const Especie& e) {
    NodoEspecie* n = new NodoEspecie{e, nullptr};
    if (!cabeza) { cabeza = n; return; }
    NodoEspecie* t = cabeza;
    while (t->siguiente) t = t->siguiente;
    t->siguiente = n;
}

NodoEspecie* leerEspecies(const string& ruta) {
    NodoEspecie* cabeza = nullptr;
    ifstream archivo(ruta);
    if (!archivo.is_open()) { cout << " No se pudo abrir " << ruta << "\n"; return cabeza; }
    string linea;
    getline(archivo, linea);
    getline(archivo, linea);
    while (getline(archivo, linea)) {
        if (!linea.empty() && linea.back() == '\r') linea.pop_back();
        if (linea.empty() || linea.find("---") != string::npos) continue;
        Especie esp;
        try { esp.id = stoi(linea); } catch (...) { continue; }
        getline(archivo, esp.nombre);
        if (!esp.nombre.empty() && esp.nombre.back() == '\r') esp.nombre.pop_back();
        int campos[4] = {0, 0, 0, 0};
        for (int i = 0; i < 4; i++) {
            int v = extraerCampo(archivo);
            if (v == -999) break;
            campos[i] = v;
        }
        if (campos[0] == -1) {
            esp.damage  = campos[1];
            esp.salud   = campos[2];
            esp.rapidez = campos[3];
        } else {
            esp.salud   = campos[0];
            esp.damage  = campos[2];
            esp.rapidez = campos[3];
        }
        insertarEspecie(cabeza, esp);
    }
    archivo.close();
    return cabeza;
}

void insertarClase(NodoClase*& cabeza, const Clase& c) {
    NodoClase* n = new NodoClase{c, nullptr};
    if (!cabeza) { cabeza = n; return; }
    NodoClase* t = cabeza;
    while (t->siguiente) t = t->siguiente;
    t->siguiente = n;
}

NodoClase* leerClases(const string& ruta) {
    NodoClase* cabeza = nullptr;
    ifstream archivo(ruta);
    if (!archivo.is_open()) { cout << " No se pudo abrir " << ruta << "\n"; return cabeza; }
    string linea;
    getline(archivo, linea);
    getline(archivo, linea);
    while (getline(archivo, linea)) {
        if (!linea.empty() && linea.back() == '\r') linea.pop_back();
        if (linea.empty() || linea.find("---") != string::npos) continue;
        Clase cls;
        try { cls.id = stoi(linea); } catch (...) { continue; }
        getline(archivo, cls.nombre);
        if (!cls.nombre.empty() && cls.nombre.back() == '\r') cls.nombre.pop_back();
        int campos[4] = {0, 0, 0, 0};
        for (int i = 0; i < 4; i++) {
            int v = extraerCampo(archivo);
            if (v == -999) break;
            campos[i] = v;
        }
        if (campos[0] == -1) {
            cls.damage  = campos[1];
            cls.salud   = campos[2];
            cls.rapidez = campos[3];
        } else {
            cls.salud   = campos[0];
            cls.damage  = campos[2];
            cls.rapidez = campos[3];
        }
        insertarClase(cabeza, cls);
    }
    archivo.close();
    return cabeza;
}

void insertarArma(NodoArma*& cabeza, const Arma& a) {
    NodoArma* n = new NodoArma{a, nullptr};
    if (!cabeza) { cabeza = n; return; }
    NodoArma* t = cabeza;
    while (t->siguiente) t = t->siguiente;
    t->siguiente = n;
}

NodoArma* leerArmas(const string& ruta) {
    NodoArma* cabeza = nullptr;
    ifstream archivo(ruta);
    if (!archivo.is_open()) { cout << " No se pudo abrir " << ruta << "\n"; return cabeza; }
    string linea;
    getline(archivo, linea);
    getline(archivo, linea);
    while (getline(archivo, linea)) {
        if (!linea.empty() && linea.back() == '\r') linea.pop_back();
        if (linea.empty() || linea.find("---") != string::npos) continue;
        Arma arm;
        try { arm.id = stoi(linea); } catch (...) { continue; }
        getline(archivo, arm.nombre);
        if (!arm.nombre.empty() && arm.nombre.back() == '\r') arm.nombre.pop_back();
        getline(archivo, arm.tipo);
        if (!arm.tipo.empty() && arm.tipo.back() == '\r') arm.tipo.pop_back();
        arm.damage = extraerValor(archivo);
        arm.peso   = extraerValor(archivo);
        insertarArma(cabeza, arm);
    }
    archivo.close();
    return cabeza;
}

void insertarEscudo(NodoEscudo*& cabeza, const Escudo& e) {
    NodoEscudo* n = new NodoEscudo{e, nullptr};
    if (!cabeza) { cabeza = n; return; }
    NodoEscudo* t = cabeza;
    while (t->siguiente) t = t->siguiente;
    t->siguiente = n;
}

NodoEscudo* leerEscudos(const string& ruta) {
    NodoEscudo* cabeza = nullptr;
    ifstream archivo(ruta);
    if (!archivo.is_open()) { cout << " No se pudo abrir " << ruta << "\n"; return cabeza; }
    string linea;
    getline(archivo, linea);
    getline(archivo, linea);
    while (getline(archivo, linea)) {
        if (!linea.empty() && linea.back() == '\r') linea.pop_back();
        if (linea.empty() || linea.find("---") != string::npos) continue;
        Escudo esc;
        try { esc.id = stoi(linea); } catch (...) { continue; }
        getline(archivo, esc.nombre);
        if (!esc.nombre.empty() && esc.nombre.back() == '\r') esc.nombre.pop_back();
        getline(archivo, esc.tipo);
        if (!esc.tipo.empty() && esc.tipo.back() == '\r') esc.tipo.pop_back();
        esc.capacidad = extraerValor(archivo);
        esc.recarga   = extraerValor(archivo);
        esc.consumo   = extraerValor(archivo);
        insertarEscudo(cabeza, esc);
    }
    archivo.close();
    return cabeza;
}

void insertarHeroe(NodoHeroe*& cabeza, const Heroes& h) {
    NodoHeroe* n = new NodoHeroe{h, nullptr};
    if (!cabeza) { cabeza = n; return; }
    NodoHeroe* t = cabeza;
    while (t->siguiente) t = t->siguiente;
    t->siguiente = n;
}

NodoHeroe* leerHeroe(const string& ruta) {
    NodoHeroe* cabeza = nullptr;
    ifstream archivo(ruta);
    if (!archivo.is_open()) { cout << " No se pudo abrir " << ruta << "\n"; return cabeza; }
    string linea;
    getline(archivo, linea);
    getline(archivo, linea);
    while (getline(archivo, linea)) {
        if (!linea.empty() && linea.back() == '\r') linea.pop_back();
        if (linea.empty() || linea.find("---") != string::npos) continue;
        Heroes h;
        try { h.id = stoi(linea); } catch (...) { continue; }
        getline(archivo, h.nombre);
        if (!h.nombre.empty() && h.nombre.back() == '\r') h.nombre.pop_back();
        int campos[4] = {0, 0, 0, 0};
        for (int i = 0; i < 4; i++) {
            int v = extraerCampo(archivo);
            if (v == -999) break;
            campos[i] = v;
        }
        if (campos[0] == -1) {
            h.damage  = campos[1];
            h.salud   = campos[2];
            h.rapidez = campos[3];
        } else {
            h.salud   = campos[0];
            h.damage  = campos[2];
            h.rapidez = campos[3];
        }
        insertarHeroe(cabeza, h);
    }
    archivo.close();
    return cabeza;
}

PersonajeCombinado combinarEstadisticas(const Especie& esp, const Clase& cls) {
    PersonajeCombinado pj;
    pj.nombreCompleto = esp.nombre + " " + cls.nombre;
    pj.saludTotal    = esp.salud   + cls.salud;
    pj.damageTotal   = esp.damage  + cls.damage;
    pj.rapidezTotal  = esp.rapidez + cls.rapidez;
    return pj;
}

void liberarLista(NodoEspecie* c) { 
    while (c) { 
        auto t = c; 
        c = c->siguiente; 
        delete t; 
    } 
}
void liberarLista(NodoClase*   c) { 
    while (c) { 
        auto t = c; 
        c = c->siguiente; 
        delete t; 
    } 
}
void liberarLista(NodoArma*    c) { 
    while (c) { 
        auto t = c; 
        c = c->siguiente; 
        delete t; 
    } 
}
void liberarLista(NodoEscudo*  c) { 
    while (c) { 
        auto t = c; 
        c = c->siguiente; 
        delete t; 
    } 
}
void liberarLista(NodoHeroe*   c) { 
    while (c) { auto t = c; 
        c = c->siguiente; 
        delete t; 
    } 
}

void apilar_escudos(Personaje* pj, Escudo e) {
    NodoEscudo* n = new NodoEscudo;
    n->dato      = e;
    n->siguiente = pj->escudos;
    pj->escudos  = n;
}

void desapilar_escudo(Personaje* pj) {
    if (!pj->escudos) {
        cout << pj->nombre << " no tiene escudos.\n";
        return;
    }
    NodoEscudo* aux = pj->escudos;
    cout << " Escudo destruido: " << aux->dato.nombre << "\n";
    pj->escudos = aux->siguiente;
    delete aux;
}

int contar_escudos(Personaje* pj) {
    int c = 0;
    for (NodoEscudo* a = pj->escudos; a; a = a->siguiente) c++;
    return c;
}

void encolarArma(Personaje* pj, Arma a) {
    NodoArma* n = new NodoArma;
    n->dato = a;
    n->siguiente = nullptr;
    if (!pj->arsenal) { 
        pj->arsenal = n; 
        return; 
    }
    NodoArma* t = pj->arsenal;
    while (t->siguiente) t = t->siguiente;
    t->siguiente = n;
}

int descartarMunicion(Personaje* pj) {
    if (!pj->arsenal) {
        cout << "  Arsenal de " << pj->nombre << " vacio.\n";
        return 0;
    }
    NodoArma* n = pj->arsenal;
    int dmg     = n->dato.damage;
    cout << "   [DISPARO] " << pj->nombre << " usa " << n->dato.nombre
         << " (Danio base: " << dmg << ")\n";
    pj->arsenal = n->siguiente;
    delete n;
    return dmg;
}

void robarEquipo(Personaje* ganador, Personaje* caido) {
    cout << ganador->nombre << " recoge el equipo de " << caido->nombre << "!\n";
    while (caido->escudos) {
        NodoEscudo* aux = caido->escudos;
        apilar_escudos(ganador, aux->dato);
        caido->escudos = aux->siguiente;
        delete aux;
    }
    while (caido->arsenal) {
        NodoArma* aux = caido->arsenal;
        encolarArma(ganador, aux->dato);
        caido->arsenal = aux->siguiente;
        delete aux;
    }
    cout << " Escudos ahora: " << contar_escudos(ganador)
         << " Prox. arma: " << (ganador->arsenal ? ganador->arsenal->dato.nombre : "ninguna") << "\n";
}

void dividirHijo(NodoBtree* padre, int i, NodoBtree* hijoLleno) {
    NodoBtree* nuevoNodo = new NodoBtree();
    nuevoNodo->hoja = hijoLleno->hoja;
    nuevoNodo->cant_pj = 1;
    nuevoNodo->Personajes[0] = hijoLleno->Personajes[2];
    if (!hijoLleno->hoja) {
        nuevoNodo->hijos[0] = hijoLleno->hijos[2];
        nuevoNodo->hijos[1] = hijoLleno->hijos[3];
        hijoLleno->hijos[2] = nullptr;
        hijoLleno->hijos[3] = nullptr;
    }
    hijoLleno->cant_pj = 1;
    for (int j = padre->cant_pj; j >= i + 1; j--)
        padre->hijos[j + 1] = padre->hijos[j];
    padre->hijos[i + 1] = nuevoNodo;
    for (int j = padre->cant_pj - 1; j >= i; j--)
        padre->Personajes[j + 1] = padre->Personajes[j];
    padre->Personajes[i] = hijoLleno->Personajes[1];
    padre->cant_pj++;
}

void insertarEnNodoNoLleno(NodoBtree* nodo, Personaje* pj) {
    int i = nodo->cant_pj - 1;
    if (nodo->hoja) {
        while (i >= 0 && nodo->Personajes[i]->ID_Clave > pj->ID_Clave) {
            nodo->Personajes[i + 1] = nodo->Personajes[i];
            i--;
        }
        nodo->Personajes[i + 1] = pj;
        nodo->cant_pj++;
    } else {
        while (i >= 0 && nodo->Personajes[i]->ID_Clave > pj->ID_Clave) i--;
        i++;
        if (nodo->hijos[i]->cant_pj == 3) {
            dividirHijo(nodo, i, nodo->hijos[i]);
            if (nodo->Personajes[i]->ID_Clave < pj->ID_Clave) i++;
        }
        insertarEnNodoNoLleno(nodo->hijos[i], pj);
    }
}

void insertarBtree(NodoBtree*& raiz, Personaje* pj) {
    if (!raiz) {
        raiz = new NodoBtree();
        raiz->Personajes[0] = pj;
        raiz->cant_pj = 1;
        return;
    }
    if (raiz->cant_pj == 3) {
        NodoBtree* nuevaRaiz  = new NodoBtree();
        nuevaRaiz->hoja       = false;
        nuevaRaiz->hijos[0]   = raiz;
        dividirHijo(nuevaRaiz, 0, raiz);
        int i = (nuevaRaiz->Personajes[0]->ID_Clave < pj->ID_Clave) ? 1 : 0;
        insertarEnNodoNoLleno(nuevaRaiz->hijos[i], pj);
        raiz = nuevaRaiz;
    } else {
        insertarEnNodoNoLleno(raiz, pj);
    }
}

void fusionarHijos(NodoBtree* padre, int i) {
    NodoBtree* hijoIzq = padre->hijos[i];
    NodoBtree* hijoDer = padre->hijos[i + 1];
    hijoIzq->Personajes[hijoIzq->cant_pj] = padre->Personajes[i];
    hijoIzq->cant_pj++;
    for (int j = 0; j < hijoDer->cant_pj; j++) {
        hijoIzq->Personajes[hijoIzq->cant_pj] = hijoDer->Personajes[j];
        hijoIzq->cant_pj++;
    }
    if (!hijoIzq->hoja) {
        int base = hijoIzq->cant_pj - hijoDer->cant_pj;
        for (int j = 0; j <= hijoDer->cant_pj; j++)
            hijoIzq->hijos[base + j] = hijoDer->hijos[j];
    }
    for (int j = i; j < padre->cant_pj - 1; j++)
        padre->Personajes[j] = padre->Personajes[j + 1];
    for (int j = i + 1; j < padre->cant_pj; j++)
        padre->hijos[j] = padre->hijos[j + 1];
    padre->hijos[padre->cant_pj] = nullptr;
    padre->cant_pj--;
    delete hijoDer;
}

void prestarDeIzquierda(NodoBtree* padre, int i) {
    NodoBtree* hijoV   = padre->hijos[i];
    NodoBtree* hermano = padre->hijos[i - 1];
    hijoV->hijos[1]      = hijoV->hijos[0];
    hijoV->Personajes[0] = padre->Personajes[i - 1];
    hijoV->cant_pj++;
    padre->Personajes[i - 1] = hermano->Personajes[hermano->cant_pj - 1];
    if (!hijoV->hoja) {
        hijoV->hijos[0]                    = hermano->hijos[hermano->cant_pj];
        hermano->hijos[hermano->cant_pj]   = nullptr;
    }
    hermano->cant_pj--;
}

void prestarDeDerecha(NodoBtree* padre, int i) {
    NodoBtree* hijoV   = padre->hijos[i];
    NodoBtree* hermano = padre->hijos[i + 1];
    hijoV->Personajes[hijoV->cant_pj] = padre->Personajes[i];
    hijoV->cant_pj++;
    padre->Personajes[i] = hermano->Personajes[0];
    if (!hijoV->hoja)
        hijoV->hijos[hijoV->cant_pj] = hermano->hijos[0];
    for (int j = 1; j < hermano->cant_pj; j++)
        hermano->Personajes[j - 1] = hermano->Personajes[j];
    if (!hermano->hoja) {
        for (int j = 1; j <= hermano->cant_pj; j++)
            hermano->hijos[j - 1] = hermano->hijos[j];
        hermano->hijos[hermano->cant_pj] = nullptr;
    }
    hermano->cant_pj--;
}

Personaje* obtenerAntecesor(NodoBtree* nodo) {
    NodoBtree* a = nodo;
    while (!a->hoja) a = a->hijos[a->cant_pj];
    return a->Personajes[a->cant_pj - 1];
}

Personaje* obtenerSucesor(NodoBtree* nodo) {
    NodoBtree* a = nodo;
    while (!a->hoja) a = a->hijos[0];
    return a->Personajes[0];
}

void eliminarRecursivo(NodoBtree* nodo, int clave) {
    int i = 0;
    while (i < nodo->cant_pj && nodo->Personajes[i]->ID_Clave < clave) i++;
    if (i < nodo->cant_pj && nodo->Personajes[i]->ID_Clave == clave) {
        if (nodo->hoja) {
            for (int j = i + 1; j < nodo->cant_pj; j++)
                nodo->Personajes[j - 1] = nodo->Personajes[j];
            nodo->Personajes[nodo->cant_pj - 1] = nullptr;
            nodo->cant_pj--;
        } else {
            if (nodo->hijos[i]->cant_pj > 1) {
                Personaje* ant = obtenerAntecesor(nodo->hijos[i]);
                nodo->Personajes[i] = ant;
                eliminarRecursivo(nodo->hijos[i], ant->ID_Clave);
            } else if (nodo->hijos[i + 1]->cant_pj > 1) {
                Personaje* suc = obtenerSucesor(nodo->hijos[i + 1]);
                nodo->Personajes[i] = suc;
                eliminarRecursivo(nodo->hijos[i + 1], suc->ID_Clave);
            } else {
                fusionarHijos(nodo, i);
                eliminarRecursivo(nodo->hijos[i], clave);
            }
        }
    } else {
        if (nodo->hoja) {
            cout << "   [!] ID " << clave << " no existe en el arbol.\n";
            return;
        }
        if (nodo->hijos[i]->cant_pj == 1) {
            if (i > 0 && nodo->hijos[i - 1]->cant_pj > 1)
                prestarDeIzquierda(nodo, i);
            else if (i < nodo->cant_pj && nodo->hijos[i + 1]->cant_pj > 1)
                prestarDeDerecha(nodo, i);
            else {
                if (i > 0) { fusionarHijos(nodo, i - 1); i--; }
                else         fusionarHijos(nodo, i);
            }
        }
        eliminarRecursivo(nodo->hijos[i], clave);
    }
}

void eliminarBtree(NodoBtree*& raiz, int clave) {
    if (!raiz) { cout << "   [!] El arbol esta vacio.\n"; return; }
    eliminarRecursivo(raiz, clave);
    if (raiz->cant_pj == 0) {
        NodoBtree* vieja = raiz;
        raiz = raiz->hoja ? nullptr : raiz->hijos[0];
        delete vieja;
    }
}

NodoBtree* buscarPersonaje(NodoBtree* raiz, int id) {
    if (!raiz) return nullptr;
    int i = 0;
    while (i < raiz->cant_pj && id > raiz->Personajes[i]->ID_Clave) i++;
    if (i < raiz->cant_pj && id == raiz->Personajes[i]->ID_Clave) return raiz;
    if (raiz->hoja) return nullptr;
    return buscarPersonaje(raiz->hijos[i], id);
}

Personaje* buscarPJPtr(NodoBtree* raiz, int id) {
    NodoBtree* nodo = buscarPersonaje(raiz, id);
    if (!nodo) return nullptr;
    for (int i = 0; i < nodo->cant_pj; i++)
        if (nodo->Personajes[i]->ID_Clave == id)
            return nodo->Personajes[i];
    return nullptr;
}

void imprimirBtreeRecursivo(NodoBtree* nodo, int prof) {
    if (!nodo) return;
    string margen(prof * 4, ' ');
    cout << margen << "[Nivel " << prof << "]: { ";
    for (int i = 0; i < nodo->cant_pj; i++) {
        Personaje* p = nodo->Personajes[i];
        cout << p->ID_Clave << ":" << p->nombre
             << " HP:" << p->Personaje_comb.saludTotal
             << " B:" << p->ID_Bando;
        if (i < nodo->cant_pj - 1) cout << "  |  ";
    }
    cout << " }\n";
    if (!nodo->hoja)
        for (int i = 0; i <= nodo->cant_pj; i++)
            imprimirBtreeRecursivo(nodo->hijos[i], prof + 1);
}

void imprimirBtree(NodoBtree* raiz) {
    if (!raiz) { cout << "   El arbol esta vacio.\n"; return; }
    cout << "============= ARBOL B - YGGDRASIL =============\n";
    imprimirBtreeRecursivo(raiz, 0);
    cout << "===============================================\n";
}

bool aplicarDanio(Personaje* defensor, int danio) {
    cout << "      Dano total: " << danio << " -> ";
    while (defensor->escudos && danio > 0) {
        int cap = defensor->escudos->dato.capacidad;
        if (danio >= cap) {
            danio -= cap;
            cout << "[Escudo '" << defensor->escudos->dato.nombre << "' destruido, resta " << danio << "] ";
            desapilar_escudo(defensor);
        } else {
            defensor->escudos->dato.capacidad -= danio;
            cout << "[Escudo absorbe " << danio << ", cap restante "<< defensor->escudos->dato.capacidad << "] ";
            danio = 0;
        }
    }
    if (danio > 0) {
        defensor->Personaje_comb.saludTotal -= danio;
        cout << "[HP " << defensor->nombre << ": "<< defensor->Personaje_comb.saludTotal << "]";
    }
    cout << "\n";
    return defensor->Personaje_comb.saludTotal <= 0;
}

bool combatirPar(NodoBtree*& raiz, Personaje* atacante, Personaje* defensor) {
    int dmgArma  = descartarMunicion(atacante);
    int dmgTotal = dmgArma + atacante->Personaje_comb.damageTotal;
    bool muerto  = aplicarDanio(defensor, dmgTotal);
    if (muerto) {
        cout << "   [MUERTE] " << defensor->nombre << " (ID:" << defensor->ID_Clave << ") ha caido!\n";
        robarEquipo(atacante, defensor);
        eliminarBtree(raiz, defensor->ID_Clave);
        delete defensor;
        return true;
    }
    return false;
}

bool combatirNodoRecursivo(NodoBtree* nodo, NodoBtree*& raiz) {
    if (!nodo) return false;
    bool hayBando1 = false, hayBando2 = false;
    for (int i = 0; i < nodo->cant_pj; i++) {
        if (nodo->Personajes[i]->ID_Bando == 1) hayBando1 = true;
        if (nodo->Personajes[i]->ID_Bando == 2) hayBando2 = true;
    }
    if (hayBando1 && hayBando2) {
        Personaje* pj1 = nullptr;
        Personaje* pj2 = nullptr;
        int rap1 = -1, rap2 = -1;
        for (int i = 0; i < nodo->cant_pj; i++) {
            Personaje* p = nodo->Personajes[i];
            if (p->ID_Bando == 1 && p->Personaje_comb.rapidezTotal > rap1) {
                rap1 = p->Personaje_comb.rapidezTotal; pj1 = p;
            }
            if (p->ID_Bando == 2 && p->Personaje_comb.rapidezTotal > rap2) {
                rap2 = p->Personaje_comb.rapidezTotal; pj2 = p;
            }
        }
        if (pj1 && pj2) {
            cout << "\n   [COMBATE EN NODO]\n";
            cout << "      " << pj1->nombre << " (B1, Rap:" << rap1 << ") VS " << pj2->nombre << " (B2, Rap:" << rap2 << ")\n";
            Personaje* primero = (rap1 >= rap2) ? pj1 : pj2;
            Personaje* segundo = (rap1 >= rap2) ? pj2 : pj1;
            cout << "   [1ro] Ataca: " << primero->nombre << "\n";
            if (combatirPar(raiz, primero, segundo)) return true;
            if (buscarPJPtr(raiz, segundo->ID_Clave)) {
                cout << "   [2do] Contraataca: " << segundo->nombre << "\n";
                if (combatirPar(raiz, segundo, primero)) return true;
            }
        }
    }
    if (!nodo->hoja)
        for (int i = 0; i <= nodo->cant_pj; i++)
            if (combatirNodoRecursivo(nodo->hijos[i], raiz)) return true;
    return false;
}

void faseCombateAutomatico(NodoBtree* raiz, NodoBtree*& raizRef) {
    if (!raiz) return;
    cout << "\n======= FASE DE COMBATE AUTOMATICO =======\n";
    bool huboMuerte = true;
    while (huboMuerte)
        huboMuerte = combatirNodoRecursivo(raizRef, raizRef);
    cout << "==========================================\n";
}

void contarBandos(NodoBtree* nodo, int& c1, int& c2) {
    if (!nodo) return;
    for (int i = 0; i < nodo->cant_pj; i++) {
        if (nodo->Personajes[i]->ID_Bando == 1) c1++;
        else c2++;
    }
    if (!nodo->hoja)
        for (int i = 0; i <= nodo->cant_pj; i++)
            contarBandos(nodo->hijos[i], c1, c2);
}

bool verificarVictoria(NodoBtree* raiz, int inyeccionesB1, int inyeccionesB2, int& turnosRaizB1, int& turnosRaizB2) {
    if (!raiz) {
        cout << "\n*** EMPATE TECNICO: El arbol quedo vacio. ***\n";
        return true;
    }

    int c1 = 0, c2 = 0;
    contarBandos(raiz, c1, c2);

    if (c1 == 0) {
        cout << "\n*** VICTORIA POR ANIQUILACION ***\n";
        cout << "    La Resistencia Neon (Bando 2) elimino a todos los Omegas!\n";
        return true;
    }
    if (c2 == 0) {
        cout << "\n*** VICTORIA POR ANIQUILACION ***\n";
        cout << "    La Corporacion OMEGA (Bando 1) elimino a todos los Neones!\n";
        return true;
    }

    if (inyeccionesB1 >= 50) {
        cout << "\n*** VICTORIA POR INYECCIONES ***\n";
        cout << "    La Corporacion OMEGA (Bando 1) alcanzo 50 inyecciones!\n";
        return true;
    }
    if (inyeccionesB2 >= 50) {
        cout << "\n*** VICTORIA POR INYECCIONES ***\n";
        cout << "    La Resistencia Neon (Bando 2) alcanzo 50 inyecciones!\n";
        return true;
    }

    bool soloB1 = (raiz->cant_pj > 0);
    bool soloB2 = (raiz->cant_pj > 0);
    for (int i = 0; i < raiz->cant_pj; i++) {
        if (raiz->Personajes[i]->ID_Bando != 1) soloB1 = false;
        if (raiz->Personajes[i]->ID_Bando != 2) soloB2 = false;
    }

    if (soloB1)      { turnosRaizB1++; turnosRaizB2 = 0; }
    else if (soloB2) { turnosRaizB2++; turnosRaizB1 = 0; }
    else             { turnosRaizB1 = 0; turnosRaizB2 = 0; }

    if (turnosRaizB1 >= 3) {
        cout << "\n*** VICTORIA POR DOMINIO DE LA RAIZ ***\n";
        cout << "    La Corporacion OMEGA (Bando 1) controlo la raiz 3 turnos seguidos!\n";
        return true;
    }
    if (turnosRaizB2 >= 3) {
        cout << "\n*** VICTORIA POR DOMINIO DE LA RAIZ ***\n";
        cout << "    La Resistencia Neon (Bando 2) controlo la raiz 3 turnos seguidos!\n";
        return true;
    }

    return false;
}

void buscarAliadoMenorHP(NodoBtree* raiz, int bando, int idSanador,
                          Personaje*& objetivo, int& menor_hp) {
    if (!raiz) return;
    for (int i = 0; i < raiz->cant_pj; i++) {
        Personaje* p = raiz->Personajes[i];
        if (p->ID_Bando == bando && p->ID_Clave != idSanador
            && p->Personaje_comb.saludTotal < menor_hp) {
            menor_hp = p->Personaje_comb.saludTotal;
            objetivo = p;
        }
    }
    if (!raiz->hoja)
        for (int i = 0; i <= raiz->cant_pj; i++)
            buscarAliadoMenorHP(raiz->hijos[i], bando, idSanador, objetivo, menor_hp);
}

void habilidadSanador(NodoBtree* raiz, int bando, int id) {
    Personaje* sanador = buscarPJPtr(raiz, id);
    if (!sanador) { cout << " Sanador ID " << id << " no encontrado.\n"; return; }
    Personaje* objetivo = nullptr;
    int menor_hp = 999999;
    buscarAliadoMenorHP(raiz, bando, id, objetivo, menor_hp);
    const int costo = 30;
    if (!objetivo) { cout << " No hay aliados heridos que curar.\n"; return; }
    if (sanador->Personaje_comb.saludTotal <= costo) {
        cout << "   " << sanador->nombre << " no tiene HP suficiente (costo: " << costo << ").\n";
        return;
    }
    sanador->Personaje_comb.saludTotal  -= costo;
    objetivo->Personaje_comb.saludTotal += costo;
    cout << "   [SANACION] " << sanador->nombre << " cura a " << objetivo->nombre << ". HP aliado: " << objetivo->Personaje_comb.saludTotal << "\n";
}

void controlMental(NodoBtree* raiz, int idObjetivo) {
    Personaje* obj = buscarPJPtr(raiz, idObjetivo);
    if (!obj) { cout << "   Objetivo ID " << idObjetivo << " no encontrado.\n"; return; }
    int anterior = obj->ID_Bando;
    obj->ID_Bando = (obj->ID_Bando == 1) ? 2 : 1;
    cout << "   [CONTROL MENTAL] " << obj->nombre << " paso del Bando " << anterior << " al Bando " << obj->ID_Bando << "!\n";
}

void robarEscudosTodos(NodoBtree* raiz, Personaje* ladron) {
    if (!raiz) return;
    for (int i = 0; i < raiz->cant_pj; i++) {
        Personaje* p = raiz->Personajes[i];
        if (p->ID_Bando != ladron->ID_Bando && p->escudos) {
            cout << "   [ROBO] " << ladron->nombre << " roba escudos de " << p->nombre << "\n";
            while (p->escudos) {
                apilar_escudos(ladron, p->escudos->dato);
                NodoEscudo* aux = p->escudos;
                p->escudos = aux->siguiente;
                delete aux;
            }
        }
    }
    if (!raiz->hoja)
        for (int i = 0; i <= raiz->cant_pj; i++)
            robarEscudosTodos(raiz->hijos[i], ladron);
}

void menu_habilidades(NodoBtree*& raiz, Personaje* pj_activo, int bandoActual) {
    limpiarPantalla();
    cout << "========================================\n";
    cout << "   HABILIDADES DE: " << pj_activo->nombre << "\n";
    cout << "========================================\n";
    if (pj_activo->Clase_ID == 3)
        cout << "  1. Control Mental (Solo Hacker de Combate)\n";
    else
        cout << "  1. Control Mental [NO DISPONIBLE - requiere Hacker de Combate]\n";
    cout << "  2. Sanacion (sacrifica 30 HP para curar aliado mas herido)\n";
    cout << "  3. Robo de Escudos (roba escudos de todos los enemigos)\n";
    cout << "  0. Cancelar\n";
    cout << ">> ";
    char op;
    cin >> op;
    cin.ignore(10000, '\n');
    limpiarPantalla();
    switch (op) {
        case '1':
            if (pj_activo->Clase_ID != 3) {
                cout << " Solo el Hacker de Combate puede usar Control Mental.\n";
                break;
            }
            {
                int id;
                cout << "ID del enemigo a controlar: ";
                cin >> id;
                cin.ignore(10000, '\n');
                controlMental(raiz, id);
            }
            break;
        case '2':
            {
                int id;
                cout << "Tu ID de sanador: ";
                cin >> id;
                cin.ignore(10000, '\n');
                habilidadSanador(raiz, bandoActual, id);
            }
            break;
        case '3':
            robarEscudosTodos(raiz, pj_activo);
            break;
        case '0':
            cout << "   Cancelado.\n";
            break;
        default:
            cout << "   Opcion no valida.\n";
            break;
    }
    pausar();
}

int leerEnteroValidado(const string& mensaje, int minVal, int maxVal) {
    int valor = 0;
    bool valido = false;
    do {
        if (!mensaje.empty()) cout << mensaje;
        string entrada;
        cin >> entrada;
        try {
            valor = stoi(entrada);
            if (valor >= minVal && valor <= maxVal) valido = true;
            else cout << "   Ingrese un valor entre " << minVal << " y " << maxVal << ".\n";
        } catch (...) {
            cout << "   Entrada invalida, solo numeros.\n";
        }
    } while (!valido);
    return valor;
}

Especie crearEspecieCustom() {
    Especie e;
    e.id = 0; 
 
    cout << "\n--- CREACION DE ESPECIE PERSONALIZADA ---\n";
    cin.ignore();
    cout << "Nombre de la especie: ";
    getline(cin, e.nombre);
 
    e.salud   = leerEnteroValidado("Puntos de Vida/Salud (HP)  [0-500]: ", 0, 500);
    e.damage  = leerEnteroValidado("Puntos de Danio (DMG)      [0-500]: ", 0, 500);
    e.rapidez = leerEnteroValidado("Puntos de Rapidez (RAP)    [0-500]: ", 0, 500);
 
    cout << " Especie personalizada '" << e.nombre << "' creada -> "<< "HP:" << e.salud << " DMG:" << e.damage << " RAP:" << e.rapidez << "\n";
    return e;
}

Especie elegirEspecie(NodoEspecie* listaEspecies) {
    cout << "\n========================================\n";
    cout << "   SELECCION DE ESPECIE\n";
    cout << "========================================\n";
    cout << "  1. Elegir una especie existente\n";
    cout << "  2. Crear una especie personalizada\n";
    int modo = leerEnteroValidado(">> ", 1, 2);
 
    if (modo == 2) {
        return crearEspecieCustom();
    }
 
    cout << "\nElige una especie:\n";
    cout << "  1.  Humano      | HP:+120 DMG:+70  RAP:+60\n";
    cout << "  2.  Elfo        | HP:+80  DMG:+65  RAP:+90\n";
    cout << "  3.  Enano       | HP:+150 DMG:+100 RAP:+40\n";
    cout << "  4.  Mago        | HP:+95  DMG:+55  RAP:+50\n";
    cout << "  5.  Caballero   | HP:+130 DMG:+90  RAP:+60\n";
    cout << "  6.  Ladron      | HP:+70  DMG:+60  RAP:+110\n";
    cout << "  7.  Orco        | HP:+80  DMG:+90  RAP:+50\n";
    cout << "  8.  Troll       | HP:+40  DMG:+60  RAP:+80\n";
    cout << "  9.  Vampiro     | HP:+25  DMG:+75  RAP:+60\n";
    cout << "  10. Golem       | HP:+200 DMG:+110 RAP:+20\n";
    cout << "  11. Licantropo  | HP:+30  DMG:+85  RAP:+70\n";
    cout << "  12. Necrofago   | HP:+300 DMG:+200 RAP:+50\n";
 
    int Especie_pj = leerEnteroValidado(">> ", 1, 12);
 
    Especie espElegida = {0, "Desconocida", 0, 0, 0};
    for (NodoEspecie* a = listaEspecies; a; a = a->siguiente)
        if (a->dato.id == Especie_pj) { espElegida = a->dato; break; }
 
    return espElegida;
}

Escudo crearEscudoCustom() {
    Escudo e;
    e.id = 0; 
 
    cout << "\n--- CREACION DE ESCUDO PERSONALIZADO ---\n";
    cin.ignore();
    cout << "Nombre del escudo: ";
    getline(cin, e.nombre);
    cout << "Tipo de escudo (ej: Energia, Fisico, Cuantico): ";
    getline(cin, e.tipo);
 
    e.capacidad = leerEnteroValidado("Capacidad del escudo   [1-999]: ", 1, 999);
    e.recarga   = leerEnteroValidado("Velocidad de recarga   [0-999]: ", 0, 999);
    e.consumo   = leerEnteroValidado("Consumo de energia     [0-999]: ", 0, 999);
 
    cout << "\n[OK] Escudo personalizado '" << e.nombre << "' creado -> Cap:" << e.capacidad
         << " Recarga:" << e.recarga << " Consumo:" << e.consumo << "\n";
    return e;
}

void asignarEscudos(Personaje*& pj, NodoEscudo* listaEscudos) {
    bool valido   = false;
    int id_escudo = 0;
    do {
        cout << "\nElige un escudo:\n";
        cout << "  1. Barrera de Energia Cinetica  | Cap:150\n";
        cout << "  2. Proyector de Campo Deflector | Cap:300\n";
        cout << "  3. Blindaje Reactivo            | Cap:120\n";
        cout << "  4. Cortafuegos Cuantico         | Cap:250\n";
        cout << "  5. Modulo de Camuflaje Optico   | Cap:50\n";
        cout << "  6. Crear escudo personalizado\n";
        cout << ">> ";
        string entrada;
        cin >> entrada;
        try {
            id_escudo = stoi(entrada);
            if (id_escudo >= 1 && id_escudo <= 6) valido = true;
            else cout << " Elige entre 1 y 6.\n";
        } catch (...) { cout << " Solo numeros.\n"; }
    } while (!valido);
 
    if (id_escudo == 6) {
        Escudo custom = crearEscudoCustom();
        int cantidad = lanzarDado(3);
        cout << "   [DADO] " << cantidad << " escudo(s) asignados: " << custom.nombre << "\n";
        for (int i = 0; i < cantidad; i++) apilar_escudos(pj, custom);
        return;
    }
 
    NodoEscudo* actual = listaEscudos;
    while (actual && actual->dato.id != id_escudo) actual = actual->siguiente;
    if (!actual) { cout << "   Escudo no encontrado en el archivo.\n"; return; }
 
    int cantidad = lanzarDado(3);
    cout << "   [DADO] " << cantidad << " escudo(s) asignados: " << actual->dato.nombre << "\n";
    for (int i = 0; i < cantidad; i++) apilar_escudos(pj, actual->dato);
}

void asignarArsenal(Personaje* pj, NodoArma* listaArmas) {
    if (!listaArmas) { cout << "   Error: No hay armas cargadas.\n"; return; }
    int cantidadArmas = lanzarDado(3);
    cout << "   [DADO] Arsenal de " << pj->nombre << ": " << cantidadArmas << " arma(s).\n";
    for (int i = 0; i < cantidadArmas; i++) {
        bool valido   = false;
        int  id_arma  = 0;
        do {
            cout << "\n   Slot " << (i + 1) << "/" << cantidadArmas << " - Elige arma:\n";
            cout << "   1. Canon de Plasma Pesado    | DMG:180\n";
            cout << "   2. Rifle Francotirador Gauss | DMG:250\n";
            cout << "   3. Espada de Iones           | DMG:130\n";
            cout << "   4. Granada de Pulso EMP      | DMG:90\n";
            cout << "   5. Inyector de Malware       | DMG:60 (Solo Hacker de Combate)\n";
            cout << "   >> ";
            string entrada;
            cin >> entrada;
            try {
                id_arma = stoi(entrada);
                if (id_arma >= 1 && id_arma <= 5) {
                    if (id_arma == 5 && pj->Clase_ID != 1)
                        cout << " El Inyector de Malware es exclusivo del Hacker de Combate.\n";
                    else
                        valido = true;
                } else cout << " Elige entre 1 y 5.\n";
            } catch (...) { cout << "   Solo numeros.\n"; }
        } while (!valido);

        NodoArma* actual = listaArmas;
        while (actual && actual->dato.id != id_arma) actual = actual->siguiente;
        if (!actual) { cout << "   Arma no encontrada.\n"; continue; }
        encolarArma(pj, actual->dato);
        cout << "   >> " << actual->dato.nombre << " encolada.\n";
    }
}

void Insertar_PJ(int bando, NodoEspecie* listaEspecies, NodoClase* listaClases, NodoArma* listaArmas, NodoEscudo* listaEscudos) {
    limpiarPantalla();
    cout << "========================================\n";
    cout << "   CREANDO PERSONAJE - BANDO " << bando
         << (bando == 1 ? " (Omegas)" : " (Neones)") << "\n";
    cout << "========================================\n";

    Personaje* nuevo = new Personaje;
    nuevo->ID_Bando  = bando;

    bool idValido = false;
    do {
        string e;
        cout << "ID personalizada (1-1000): ";
        cin >> e;
        try {
            int v = stoi(e);
            if (v >= 1 && v <= 1000) {
                if (buscarPersonaje(Raiz_Btree, v))
                    cout << "   Ya existe un personaje con ese ID.\n";
                else { nuevo->ID_Clave = v; idValido = true; }
            } else cout << "   Rango 1-1000.\n";
        } catch (...) { cout << "   Solo numeros.\n"; }
    } while (!idValido);

    cin.ignore();
    cout << "Nombre: ";
    getline(cin, nuevo->nombre);

    cout << "\nElige una clase:\n";
    cout << "  1. Hacker de Combate   | HP:+90  DMG:+80  RAP:+110\n";
    cout << "  2. Infanteria Pesada   | HP:+160 DMG:+150 RAP:+40\n";
    cout << "  3. Ingeniero de Nodos  | HP:+100 DMG:+100 RAP:+70\n";
    cout << "  4. Dron Centinela      | HP:+120 DMG:+60  RAP:+130\n";
    cout << "  5. Virus Mutante       | HP:+180 DMG:+90  RAP:+90\n";

    bool claseValida = false;
    int  Clase_pj   = 0;
    do {
        string e;
        cout << ">> ";
        cin >> e;
        try {
            Clase_pj = stoi(e);
            if (Clase_pj >= 1 && Clase_pj <= 5) claseValida = true;
            else cout << "   Elige 1-5.\n";
        } catch (...) { cout << "   Solo numeros.\n"; }
    } while (!claseValida);
    nuevo->Clase_ID = Clase_pj;

    Especie espElegida = elegirEspecie(listaEspecies);

    Clase clsElegida = {0, "Desconocida", 0, 0, 0};
    for (NodoClase* a = listaClases; a; a = a->siguiente)
        if (a->dato.id == Clase_pj) { clsElegida = a->dato; break; }

    nuevo->Personaje_comb = combinarEstadisticas(espElegida, clsElegida);

    cout << "\n   [STATS FINALES] HP:" << nuevo->Personaje_comb.saludTotal
         << " DMG:" << nuevo->Personaje_comb.damageTotal
         << " RAP:" << nuevo->Personaje_comb.rapidezTotal << "\n";

    asignarEscudos(nuevo, listaEscudos);
    asignarArsenal(nuevo, listaArmas);
    insertarBtree(Raiz_Btree, nuevo);

    cout << "\n[OK] '" << nuevo->nombre << "' (ID:" << nuevo->ID_Clave
         << ") insertado en el Bando " << nuevo->ID_Bando << ".\n";
    pausar();
}

int Piedra_Papel_Tijera() {
    char r1, r2;
    bool x    = true;
    int  turno = 0;
    limpiarPantalla();
    cout << "========================================\n";
    cout << "   PIEDRA PAPEL TIJERA\n";
    cout << "   (Decide quien inserta primero)\n";
    cout << "========================================\n";
    while (x) {
        cout << "\nJugador 1 - 1(Piedra) 2(Papel) 3(Tijera): ";
        cin >> r1;
        cin.ignore(10000, '\n');
        if (r1 < '1' || r1 > '3') { cout << "   Opcion invalida.\n"; continue; }
        limpiarPantalla();
        cout << "========================================\n";
        cout << "   PIEDRA PAPEL TIJERA\n";
        cout << "========================================\n";
        cout << "\nJugador 2 - 1(Piedra) 2(Papel) 3(Tijera): ";
        cin >> r2;
        cin.ignore(10000, '\n');
        limpiarPantalla();
        cout << "========================================\n";
        if (r2 < '1' || r2 > '3') { cout << "   Opcion invalida.\n"; continue; }
        if (r1 == r2) { cout << "   EMPATE. Otra ronda.\n"; continue; }
        if ((r1 == '1' && r2 == '3') || (r1 == '2' && r2 == '1') || (r1 == '3' && r2 == '2'))
            { cout << "   >> GANO JUGADOR 1. Inserta primero!\n"; turno = 1; }
        else
            { cout << "   >> GANO JUGADOR 2. Inserta primero!\n"; turno = 2; }
        cout << "========================================\n";
        x = false;
    }
    pausar();
    return turno;
}

Personaje* obtenerPersonajeActivoRec(NodoBtree* nodo, int bando) {
    if (!nodo) return nullptr;
    for (int i = 0; i < nodo->cant_pj; i++)
        if (nodo->Personajes[i]->ID_Bando == bando) return nodo->Personajes[i];
    if (!nodo->hoja)
        for (int i = 0; i <= nodo->cant_pj; i++) {
            Personaje* p = obtenerPersonajeActivoRec(nodo->hijos[i], bando);
            if (p) return p;
        }
    return nullptr;
}

int turnoInsercion(int bando, int turnoNum, int inyecciones, NodoEspecie* listaEspecies, NodoClase* listaClases, NodoArma* listaArmas, NodoEscudo* listaEscudos) {
    limpiarPantalla();
    cout << "========================================\n";
    cout << "   TURNO " << turnoNum << " - FASE DE INSERCION\n";
    cout << "   JUGADOR " << bando << (bando == 1 ? " (Omegas)" : " (Neones)") << "\n";
    cout << "   Inyecciones acumuladas: " << inyecciones << "/50\n";
    cout << "========================================\n";

    int dado = lanzarDado(3);
    cout << "\n   [DADO] El jugador " << bando << " saco: " << dado
         << " personaje(s) para insertar.\n";
    pausar();

    for (int i = 0; i < dado; i++) {
        limpiarPantalla();
        cout << "   Insertando personaje " << (i + 1) << " de " << dado
             << " (Bando " << bando << ")\n";
        cout << "----------------------------------------\n";
        Insertar_PJ(bando, listaEspecies, listaClases, listaArmas, listaEscudos);
    }
    return dado;
}


void Menu_Juego(NodoBtree*& raiz, NodoEspecie* listaEspecies, NodoClase* listaClases, NodoArma* listaArmas, NodoEscudo* listaEscudos) {
    limpiarPantalla();
    cout << "========================================\n";
    cout << "      OPERACION YGGDRASIL\n";
    cout << "      LA GUERRA HA COMENZADO\n";
    cout << "========================================\n";
    pausar();

    int bandoInicia  = Piedra_Papel_Tijera();
    int bandoEspera  = (bandoInicia == 1) ? 2 : 1;
    int turnoNum     = 0;
    int inyeccionesB1 = 0;
    int inyeccionesB2 = 0;
    int turnosRaizB1  = 0;
    int turnosRaizB2  = 0;
    bool jugando      = true;

    while (jugando) {
        turnoNum++;

        inyeccionesB1 += turnoInsercion(bandoInicia, turnoNum, inyeccionesB1, listaEspecies, listaClases, listaArmas, listaEscudos);
        inyeccionesB2 += turnoInsercion(bandoEspera,  turnoNum, inyeccionesB2, listaEspecies, listaClases, listaArmas, listaEscudos);

        limpiarPantalla();
        cout << "========================================\n";
        cout << "   TURNO " << turnoNum << " - FASE DE HABILIDADES\n";
        cout << "   Inyecciones -> B1(Omegas):" << inyeccionesB1 << "  B2(Neones):" << inyeccionesB2 << "\n";
        cout << "   Dominio raiz -> B1:" << turnosRaizB1 << " turno(s)  B2:" << turnosRaizB2 << " turno(s)\n";
        cout << "========================================\n";
        imprimirBtree(raiz);

        cout << "\n--- JUGADOR " << bandoInicia
             << (bandoInicia == 1 ? " (Omegas)" : " (Neones)") << " ---\n";
        Personaje* pj1 = obtenerPersonajeActivoRec(raiz, bandoInicia);
        if (pj1) {
            cout << "   Activo: " << pj1->nombre << " | HP:" << pj1->Personaje_comb.saludTotal << " | RAP:" << pj1->Personaje_comb.rapidezTotal << "\n";
            cout << "   1. Usar habilidad\n   2. Pasar\n   0. Rendirse\n>> ";
            char res; cin >> res; cin.ignore(10000, '\n');
            if (res == '0') { cout << "   Bando " << bandoInicia << " se rinde.\n"; jugando = false; break; }
            if (res == '1') menu_habilidades(raiz, pj1, bandoInicia);
        }

        limpiarPantalla();
        cout << "========================================\n";
        cout << " TURNO " << turnoNum << " - FASE DE HABILIDADES\n";
        cout << " Inyecciones -> B1(Omegas):" << inyeccionesB1 << " B2(Neones):" << inyeccionesB2 << "\n";
        cout << " Dominio raiz -> B1:" << turnosRaizB1 << " turno(s)  B2:" << turnosRaizB2 << " turno(s)\n";
        cout << "========================================\n";
        imprimirBtree(raiz);

        cout << "\n--- JUGADOR " << bandoEspera
             << (bandoEspera == 1 ? " (Omegas)" : " (Neones)") << " ---\n";
        Personaje* pj2 = obtenerPersonajeActivoRec(raiz, bandoEspera);
        if (pj2) {
            cout << "   Activo: " << pj2->nombre << " | HP:" << pj2->Personaje_comb.saludTotal << " | RAP:" << pj2->Personaje_comb.rapidezTotal << "\n";
            cout << "   1. Usar habilidad\n   2. Pasar\n   0. Rendirse\n>> ";
            char res; cin >> res; cin.ignore(10000, '\n');
            if (res == '0') { cout << "   Bando " << bandoEspera << " se rinde.\n"; jugando = false; break; }
            if (res == '1') menu_habilidades(raiz, pj2, bandoEspera);
        }

        limpiarPantalla();
        cout << "========================================\n";
        cout << "   TURNO " << turnoNum << " - FASE DE COMBATE\n";
        cout << "========================================\n";
        faseCombateAutomatico(raiz, raiz);
        cout << "\n";
        imprimirBtree(raiz);

        if (verificarVictoria(raiz, inyeccionesB1, inyeccionesB2, turnosRaizB1, turnosRaizB2)) {
            jugando = false;
            break;
        }

        cout << " Inyecciones B1:" << inyeccionesB1 << " B2:" << inyeccionesB2<< " | Dominio raiz B1:" << turnosRaizB1 << " B2:" << turnosRaizB2 << "\n";

        cambiarTurno(bandoInicia);
        cambiarTurno(bandoEspera);

        pausar();
    }

    limpiarPantalla();
    cout << "========================================\n";
    cout << "         FIN DE LA PARTIDA\n";
    cout << "========================================\n";
    imprimirBtree(raiz);
    int c1 = 0, c2 = 0;
    contarBandos(raiz, c1, c2);
    cout << "Bando 1 (Omegas): " << c1 << " operativos vivos\n";
    cout << "Bando 2 (Neones): " << c2 << " operativos vivos\n";
    pausar();
}

void mostrarPersonajes() {
    limpiarPantalla();
    cout << "============================================\n";
    cout << "            CLASES DISPONIBLES\n";
    cout << "============================================\n";
    cout << " ID | Nombre              |  HP  | DMG | RAP\n";
    cout << "----|---------------------|------|-----|-----\n";
    cout << "  1 | Hacker de Combate   |   90 |  80 | 110\n";
    cout << "  2 | Infanteria Pesada   |  160 | 150 |  40\n";
    cout << "  3 | Ingeniero de Nodos  |  100 | 100 |  70\n";
    cout << "  4 | Dron Centinela      |  120 |  60 | 130\n";
    cout << "  5 | Virus Mutante       |  180 |  90 |  90\n";
    cout << "\n============================================\n";
    cout << "    ESPECIES (bonus sumados a la clase)\n";
    cout << "============================================\n";
    cout << " ID | Nombre       | +HP  | +DMG | +RAP\n";
    cout << "----|--------------|------|------|------\n";
    cout << "  1 | Humano       | +120 |  +70 |  +60\n";
    cout << "  2 | Elfo         |  +80 |  +65 |  +90\n";
    cout << "  3 | Enano        | +150 | +100 |  +40\n";
    cout << "  4 | Mago         |  +95 |  +55 |  +50\n";
    cout << "  5 | Caballero    | +130 |  +90 |  +60\n";
    cout << "  6 | Ladron       |  +70 |  +60 | +110\n";
    cout << "  7 | Orco         |  +80 |  +90 |  +50\n";
    cout << "  8 | Troll        |  +40 |  +60 |  +80\n";
    cout << "  9 | Vampiro      |  +25 |  +75 |  +60\n";
    cout << " 10 | Golem        | +200 | +110 |  +20\n";
    cout << " 11 | Licantropo   |  +30 |  +85 |  +70\n";
    cout << " 12 | Necrofago    | +300 | +200 |  +50\n";
    cout << "============================================\n";
    pausar();
}

void mostrarArmamento() {
    limpiarPantalla();
    cout << "============================================\n";
    cout << "              ARSENAL\n";
    cout << "============================================\n";
    cout << "  1. Canon de Plasma Pesado    | DMG:180 Peso:50\n";
    cout << "  2. Rifle Francotirador Gauss | DMG:250 Peso:120\n";
    cout << "  3. Espada de Iones           | DMG:130 Peso:2\n";
    cout << "  4. Granada de Pulso EMP      | DMG:90  Peso:30\n";
    cout << "  5. Inyector de Malware       | DMG:60  Peso:15 (Solo Hacker de Combate)\n";
    cout << "\n============================================\n";
    cout << "              ESCUDOS\n";
    cout << "============================================\n";
    cout << "  1. Barrera de Energia Cinetica  | Cap:150\n";
    cout << "  2. Proyector de Campo Deflector | Cap:300\n";
    cout << "  3. Blindaje Reactivo            | Cap:120\n";
    cout << "  4. Cortafuegos Cuantico         | Cap:250\n";
    cout << "  5. Modulo de Camuflaje Optico   | Cap:50\n";
    cout << "============================================\n";
    pausar();
}

void Sinopsis_Historia() {
    limpiarPantalla();
    cout << "============================================\n";
    cout << "         OPERACION YGGDRASIL\n";
    cout << "============================================\n";
    cout << " Anno 2145. Tras el Colapso, la supervivencia\n";
    cout << " de la civilizacion depende de 'Yggdrasil',\n";
    cout << " un superordenador cuantico subterraneo.\n\n";
    cout << " Dos facciones luchan por su control:\n";
    cout << "   Bando 1: La Corporacion OMEGA\n";
    cout << "   Bando 2: La Resistencia Neon\n\n";
    cout << " La guerra se libra en el ciberespacio.\n";
    cout << " Los operativos son inyectados en un Arbol\n";
    cout << " B-4 que es el nucleo de Yggdrasil.\n\n";
    cout << " Cada turno, ambos jugadores tiran un dado\n";
    cout << " (1-3) para saber cuantos personajes insertan.\n";
    cout << " Al final del turno el combate es automatico.\n";
    cout << " Gana quien elimine a todos los enemigos.\n";
    cout << "============================================\n";
    pausar();
}

void Menu_Bienvenida(NodoEspecie* listaEspecies, NodoClase* listaClases, NodoArma* listaArmas, NodoEscudo* listaEscudos) {
    char res = 0;
    while (res != '6') {
        limpiarPantalla();
        cout << "========================================\n";
        cout << "           OPERACION YGGDRASIL\n";
        cout << "       -- La Guerra Estructural --\n";
        cout << "========================================\n";
        cout << "  1. Iniciar Guerra\n";
        cout << "  2. Historia / Sinopsis\n";
        cout << "  3. Ver clases y especies\n";
        cout << "  4. Ver armamento y escudos\n";
        cout << "  5. Ver Arbol B actual\n";
        cout << "  6. Salir\n";
        cout << ">> ";
        cin >> res;
        cin.ignore(10000, '\n');
        switch (res) {
            case '1':
                Menu_Juego(Raiz_Btree, listaEspecies, listaClases, listaArmas, listaEscudos);
                break;
            case '2':
                Sinopsis_Historia();
                break;
            case '3':
                mostrarPersonajes();
                break;
            case '4':
                mostrarArmamento();
                break;
            case '5':
                limpiarPantalla();
                imprimirBtree(Raiz_Btree);
                pausar();
                break;
            case '6':
                limpiarPantalla();
                cout << " Hasta luego.\n";
                break;
            default:
                cout << " Opcion invalida.\n";
                break;
        }
    }
}

int main() {
    srand(time(0));

    NodoEspecie* listaEspecies = leerEspecies("especie.txt");
    NodoClase*   listaClases   = leerClases("personajes.txt");
    NodoArma*    listaArmas    = leerArmas("armas.txt");
    NodoEscudo*  listaEscudos  = leerEscudos("escudos.txt");
    NodoHeroe*   listaHeroes   = leerHeroe("heroes.txt");

    if (!listaEspecies) cout << " especie.txt no cargado.\n";
    if (!listaClases)   cout << " personajes.txt no cargado.\n";
    if (!listaArmas)    cout << " armas.txt no cargado.\n";
    if (!listaEscudos)  cout << " escudos.txt no cargado.\n";

    Menu_Bienvenida(listaEspecies, listaClases, listaArmas, listaEscudos);

    liberarLista(listaEspecies);
    liberarLista(listaClases);
    liberarLista(listaArmas);
    liberarLista(listaEscudos);
    liberarLista(listaHeroes);

    return 0;
}
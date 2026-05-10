#include <iostream>
#include <string>
#include <cstdlib> 
using namespace std;

/*Elaborado por: Juan Blondell 32409160
                 Maria Marcacci 32397269
                 Ernesto Gutierrez 32523545*/ 

struct Arma_Blasts{
    int ataque;
    int id_arma;
    string nombre;
};

struct Pila_Defensa {
    int escudo;
    Pila_Defensa *prox;
};

struct Cola_Arsenal {
    Arma_Blasts Arma;
    Cola_Arsenal *prox;
};

struct personaje {
    string nombre;
    int ID_Clave;
    int ID_Bando;
    int HP_Base;
    int dano_base;
    int clase;
    Pila_Defensa *escudos = nullptr;
    Cola_Arsenal *arsenal = nullptr;
    personaje *prox = nullptr;
};

personaje *listas_personajes = nullptr;

bool lista_vacia(){
    return(listas_personajes==nullptr);
}

void limpiarPantalla() {
    system("cls");
}

int lanzarDado3() {
    int resultado = (rand() % 3) + 1;
    return resultado;
}

int lanzarDado6() {
    int resultado = (rand() % 6) + 1;
    return resultado;
}

int lanzarDado4() {
    int resultado = (rand() % 4) + 1;
    return resultado;
}

int lanzarDado5() {
    int resultado = (rand() % 5) + 1;
    return resultado;
}

void asignarEscudos(personaje *pj, int clase) {
    int cantidad = 0;
    int i = 0;
    if (clase == 1) {
        cantidad = 3;
    }
    else if (clase == 2) {
        cantidad = 2;
    }

    for (i; i < cantidad; i++) {
        Pila_Defensa *nuevoEscudo = new Pila_Defensa;
        nuevoEscudo->escudo = 30;
        nuevoEscudo->prox = pj->escudos;
        pj->escudos = nuevoEscudo;
    }
}

void asignarArsenal(personaje *pj, int clase){

    int cantidad;
    int arma_id;

    if(clase == 3){
        cantidad = lanzarDado4();
        for( int i = 0; i < cantidad; i++){

            Cola_Arsenal *nuevo_arsenal = new Cola_Arsenal;

            arma_id = lanzarDado5();
            switch (arma_id){
            case 1:
                nuevo_arsenal->Arma.nombre = "Laser Estandar";
                nuevo_arsenal->Arma.ataque = 25;
                nuevo_arsenal->Arma.id_arma = 1;
                break;
            
            case 2:
                nuevo_arsenal->Arma.nombre = "Perforante EMP";
                nuevo_arsenal->Arma.ataque = 50;
                nuevo_arsenal->Arma.id_arma = 2;
                
                break;

            case 3:
                nuevo_arsenal->Arma.nombre = "Disrupcion";
                nuevo_arsenal->Arma.ataque = 0;
                nuevo_arsenal->Arma.id_arma = 3;
                
                break;
            
            case 4:
                nuevo_arsenal->Arma.nombre = "Racimo";
                nuevo_arsenal->Arma.ataque = 20;
                nuevo_arsenal->Arma.id_arma = 4;
                
                break;
            case 5:
                nuevo_arsenal->Arma.nombre = "Troyano";
                nuevo_arsenal->Arma.ataque = 0;
                nuevo_arsenal->Arma.id_arma = 5;
            
            default:
                break;
            }
            
            Cola_Arsenal* actual = pj->arsenal;

            if(actual == nullptr){
                pj->arsenal = nuevo_arsenal;
                nuevo_arsenal->prox = nullptr;
            }
            else{
                while (actual->prox != nullptr)
            {
                actual = actual->prox;
            }
                actual->prox = nuevo_arsenal;
                nuevo_arsenal->prox = nullptr;
            }
        }

    }
    else{

        cantidad = lanzarDado4();
        for( int i = 0; i < cantidad; i++){

            Cola_Arsenal *nuevo_arsenal = new Cola_Arsenal;

            arma_id = lanzarDado4();
            switch (arma_id){
            case 1:
                nuevo_arsenal->Arma.nombre = "Laser Estandar";
                nuevo_arsenal->Arma.ataque = 25;
                nuevo_arsenal->Arma.id_arma = 1;
                break;
            
            case 2:
                nuevo_arsenal->Arma.nombre = "Perforante EMP";
                nuevo_arsenal->Arma.ataque = 50;
                nuevo_arsenal->Arma.id_arma = 2;
                
                break;

            case 3:
                nuevo_arsenal->Arma.nombre = "Disrupcion";
                nuevo_arsenal->Arma.ataque = 0;
                nuevo_arsenal->Arma.id_arma = 3;
                
                break;
            
            case 4:
                nuevo_arsenal->Arma.nombre = "Racimo";
                nuevo_arsenal->Arma.ataque = 20;
                nuevo_arsenal->Arma.id_arma = 4;
                
                break;
            
            default:
                break;
            }
            
            Cola_Arsenal* actual = pj->arsenal;

            if(actual == nullptr){
                pj->arsenal = nuevo_arsenal;
                nuevo_arsenal->prox = nullptr;
            }
            else{
                while (actual->prox != nullptr)
            {
                actual = actual->prox;
            }
                actual->prox = nuevo_arsenal;
                nuevo_arsenal->prox = nullptr;
            }
        }
    }
}

void desapilar_escudo(personaje *pj){
Pila_Defensa *aux;

    if (pj->escudos == nullptr)
    {
        cout << pj->nombre << " no tiene mas escudos";
        return;
    }
    else{
       aux =  pj->escudos;
       pj->escudos = pj->escudos->prox;
       delete aux;
    }
}

void apilar_escudo(personaje *pj){
Pila_Defensa *aux = new Pila_Defensa;
aux->escudo = 30;
aux->prox = pj->escudos;
pj->escudos = aux;    
}

void encolar_arma(personaje* pj){
    int arma_id;
    Cola_Arsenal *nuevo_arsenal = new Cola_Arsenal;

    if (pj->clase == 3)
    {
        arma_id = lanzarDado5();
            switch (arma_id){
            case 1:
                nuevo_arsenal->Arma.nombre = "Laser Estandar";
                nuevo_arsenal->Arma.ataque = 25;
                nuevo_arsenal->Arma.id_arma = 1;
                break;
            
            case 2:
                nuevo_arsenal->Arma.nombre = "Perforante EMP";
                nuevo_arsenal->Arma.ataque = 50;
                nuevo_arsenal->Arma.id_arma = 2;
                
                break;

            case 3:
                nuevo_arsenal->Arma.nombre = "Disrupcion";
                nuevo_arsenal->Arma.ataque = 0;
                nuevo_arsenal->Arma.id_arma = 3;
                
                break;
            
            case 4:
                nuevo_arsenal->Arma.nombre = "Racimo";
                nuevo_arsenal->Arma.ataque = 20;
                nuevo_arsenal->Arma.id_arma = 4;
                
                break;
            case 5:
                nuevo_arsenal->Arma.nombre = "Troyano";
                nuevo_arsenal->Arma.ataque = 0;
                nuevo_arsenal->Arma.id_arma = 5;
            
            default:
                break;
    }  
}
else{
    arma_id = lanzarDado4();
            switch (arma_id){
            case 1:
                nuevo_arsenal->Arma.nombre = "Laser Estandar";
                nuevo_arsenal->Arma.ataque = 25;
                nuevo_arsenal->Arma.id_arma = 1;
                break;
            
            case 2:
                nuevo_arsenal->Arma.nombre = "Perforante EMP";
                nuevo_arsenal->Arma.ataque = 50;
                nuevo_arsenal->Arma.id_arma = 2;
                
                break;

            case 3:
                nuevo_arsenal->Arma.nombre = "Disrupcion";
                nuevo_arsenal->Arma.ataque = 0;
                nuevo_arsenal->Arma.id_arma = 3;
                
                break;
            
            case 4:
                nuevo_arsenal->Arma.nombre = "Racimo";
                nuevo_arsenal->Arma.ataque = 20;
                nuevo_arsenal->Arma.id_arma = 4;
                break;
            
            default:
                break;
            }
}
            Cola_Arsenal* actual = pj->arsenal;

            if(actual == nullptr){
                pj->arsenal = nuevo_arsenal;
                nuevo_arsenal->prox = nullptr;
            }
            else{
                while (actual->prox != nullptr)
            {
                actual = actual->prox;
            }
                actual->prox = nuevo_arsenal;
                nuevo_arsenal->prox = nullptr;
            }
}

void desencolar_arma(personaje* pj){
    Cola_Arsenal* aux;
    if (pj->escudos == nullptr)
    {
        return;
    }
    else{
        aux =  pj->arsenal;
        pj->arsenal = pj->arsenal->prox;
        delete aux;
    }
}

void Insertar_PJ() { 

    personaje *nueva_lista_pj = new personaje;
    int Clase_pj, Bando_pj;
    bool claseValida = false;
    bool bandoValido = false;

    cout << "ID personalizada: "; 
    cin >> nueva_lista_pj->ID_Clave;
    
    cin.ignore();
    cout << "Nombre: "; 
    getline(cin, nueva_lista_pj->nombre);

    do {
        cout << "Clase (1:Juggernaut, 2:Ejecutor, 3:Hacker): "; 
        cin >> Clase_pj;

        switch (Clase_pj) {
            case 1:
                nueva_lista_pj->HP_Base = 150;
                nueva_lista_pj->dano_base = 15;
                nueva_lista_pj->clase = 1;
                claseValida = true;
                break;
            case 2:
                nueva_lista_pj->HP_Base = 100;
                nueva_lista_pj->dano_base = 25;
                nueva_lista_pj->clase = 2;
                claseValida = true;
                break;
            case 3:
                nueva_lista_pj->HP_Base = 80;
                nueva_lista_pj->dano_base = 10;
                nueva_lista_pj->clase = 3;
                claseValida = true;
                break;
            default:
                cout << "Clase no valida.\n";
                break;
        }
    } while (!claseValida);

    do {
        cout << "Selecciona Bando (1: Omegas, 2: Neones): ";
        cin >> Bando_pj;

        if (Bando_pj == 1) {
            nueva_lista_pj->ID_Bando = 1;
            bandoValido = true;
        } 
        else if (Bando_pj == 2) {
            nueva_lista_pj->ID_Bando = 2;
            bandoValido = true;
        } 
        else {
            cout << "Bando no valido. Intentalo de nuevo.\n";
        }
    } while (!bandoValido);

    asignarEscudos(nueva_lista_pj, Clase_pj);


    asignarArsenal(nueva_lista_pj, Clase_pj);

    if (listas_personajes == nullptr)
    {
        listas_personajes = nueva_lista_pj;
        nueva_lista_pj ->prox = nullptr;
    }
    else{


        nueva_lista_pj->prox = listas_personajes;
        listas_personajes = nueva_lista_pj;
    }
    
    
    cout << "Personaje insertado en el bando " << nueva_lista_pj->ID_Bando << " con exito.\n";
}

void eliminar_lista_completa(){

personaje* actual = listas_personajes;

while (actual != nullptr) {
    
    while (actual->escudos != nullptr) {
        Pila_Defensa* aux = actual->escudos;
        actual->escudos = actual->escudos->prox; 
        delete aux;
    }

    while (actual->arsenal != nullptr) {
        Cola_Arsenal* aux = actual->arsenal;
        actual->arsenal = actual->arsenal->prox; 
        delete aux;
    }

    personaje* nodo_a_borrar = actual;
    actual = actual->prox; 
    delete nodo_a_borrar;
}
listas_personajes = nullptr;
}

void imprimir_lista_personajes(){

    if(lista_vacia()){
        cout << "\nNo hay personajes insertados ";
        return;
    }
    else{
    int pj = 1;
    personaje* actual = listas_personajes;
    cout << "Los personajes insertados son: ";
    while(actual!=nullptr){
         cout <<"\n\nPersonaje " <<pj << ": " << actual->nombre << " ID: " << actual->ID_Clave << " Bando: ";
         if (actual->ID_Bando == 1)
         {
            cout << "Omega (1) ";
         }
         else{
            cout << "Neon (2) ";
         }
        switch (actual->clase)
        {
        case 1:
            cout << "Clase: Juggernaut ";
            break;
        case 2:
            cout << "Clase: Ejecutor ";
            break;
        case 3:
            cout << "Clase: Hacker ";
            break;
        default:
            break;
        }
    Pila_Defensa* aux_escudos = actual->escudos;
    int cont = 0;
        while (aux_escudos != nullptr)
        {
            cont += 1;
            aux_escudos = aux_escudos->prox;
        }
    cout << " Escudos: " << cont;

    Cola_Arsenal* aux_armas = actual->arsenal;
    cout << " Armas en cola: ";
        while (aux_armas != nullptr)
        {
            cout<< aux_armas->Arma.nombre <<": Ataque " << aux_armas->Arma.ataque << " ";
            aux_armas = aux_armas->prox;
        }

        actual = actual->prox;
        pj += 1;
    }
    }
}

void actualizar_lista_personajes(){
    if (lista_vacia()){
        cout<<"\nNo hay personajes insertados "<<endl;
    } else {
        personaje* actual = listas_personajes;
        int id_person;
        cout<<"Ingrese el ID del personaje que desea actualizar: "<<endl;
        cin>>id_person;
        while(actual!=nullptr && actual->ID_Clave != id_person){
            actual = actual->prox;
        }
        if (actual == nullptr)
        {
            cout<<"\nNo se encontro un personaje con ese ID\n";
            return;
        }
        
        int res, x, id_nueva;
        string n;
        do{ limpiarPantalla();
        cout<<"La informacion del personaje es:\n";
        cout<<"Nombre: " << actual->nombre<<'\n'<<"ID Clave: " << actual->ID_Clave <<'\n' << "ID Bando: " << actual->ID_Bando<<'\n'<< "HP Base: " << actual->HP_Base<<'\n'<< "Ataque base: " << actual->dano_base<<'\n'<<endl;
        
        cout<<"Indique el dato que desea actualizar:\n0. Salir \n1. nombre\n2. ID de bando\n3. Clase\n4. ID Clave\n5.Eliminar 1 escudo\n6.Insertar 1 escudo\n7.Encolar arma\n8. Desencolar arma"<<endl;
        cin>>res;
        switch(res){
            case 1:
                cin.ignore();
                cout<<"Ingrese el nuevo nombre: ";
                getline(cin, n);
                actual->nombre = n;
                break;
            case 2:
                cout<<"Selecciona el nuevo Bando (1: Omegas, 2: Neones): "; 
                cin>>x;
                if (x!=1 && x!=2){
                    cout<<"Opcion no valida.";
                } else {
                    actual->ID_Bando = x;
                    switch (x)
                    {
                    case 1:
                        actual->HP_Base = 150;
                        actual->dano_base = 15;
                        break;
                    case 2:
                        actual->HP_Base = 100;
                        actual->dano_base = 25;
                        break;
                    case 3:
                        actual->HP_Base = 80;
                        actual->dano_base = 10;
                        break;
                    default:
                        break;
                    }
                }
                break;
            case 3:
                cout<<"Ingrese la nueva clase (1:Juggernaut, 2:Ejecutor, 3:Hacker): ";
                cin>>x;
                if (x!=1 && x!=2 && x!=3){
                    cout<<"Opcion no valida.";
                } else{
                    actual->clase = x;
                }
                break;
            case 4:
                cout << "Ingresa una nueva ID Clave: ";
                cin >> id_nueva;
                actual->ID_Clave= id_nueva;
                break;
            case 5:
                    desapilar_escudo(actual);
                    break;
            case 6:
                    apilar_escudo(actual);
                    break;
            case 7:
                    encolar_arma(actual);
                    break;
            case 8: desencolar_arma(actual);
                    break;
            default:
                cout<<"Ingrese una opcion valida "<<endl;
                break;
        }
    } while(res != 0);
    }
}

void mostrarPersonajes() {
    string pausa;
    limpiarPantalla();
    cout << "====================================================" << endl;
    cout << "          PERFILES DE UNIDADES Y HEROES             " << endl;
    cout << "====================================================" << endl;
    cout << "Presione Enter para ver las clases base...";
    getline(cin, pausa);
    
    limpiarPantalla();
    cout << "\n>>> CLASES DISPONIBLES <<<" << endl;
    cout << "1. JUGGERNAUT (Tanque):" << endl;
    cout << "   - HP: 150 | Daño: 15 | Escudos: 3 Fisicos." << endl;
    cout << "2. EJECUTOR (Asesino):" << endl;
    cout << "   - HP: 100 | Daño: 30 | Escudos: 1 Anti-Plasma." << endl;
    cout << "3. ESPECTRO (Hacker):" << endl;
    cout << "   - HP: 60  | Daño: 10 | Escudos: 0." << endl;
    cout << "   - Habilidad Unica: Puede usar 'Control Mental' (Troyano)." << endl;  
    
    cout << "\nPresione Enter para ver los Avatares Historicos (Heroes)...";
    getline(cin, pausa);
    
    limpiarPantalla();
    cout << "\n>>> HEROES DE LA RESISTENCIA NEON (EQUIPO 1) <<<" << endl;
    cout << "* Borin 'Corazon de Bronce': ID 10 | Clase Tanque." << endl;
    cout << "  - Carga: 2 Blasts de Racimo encolados." << endl;
    cout << "* Dra. Emily Carter: ID 20 | Clase Hacker." << endl;
    cout << "  - Carga: 3 Blasts Troyanos encolados." << endl;
    
    cout << "\n>>> HEROES DE LA CORPORACION OMEGA (EQUIPO 2) <<<" << endl;
    cout << "* Gnashrak 'El Asediador': ID 990 | Clase Asesino." << endl;
    cout << "  - Carga: 2 Blasts EMP y 1 Disrupcion." << endl;
    cout << "* El Alfa / Paciente Cero: ID 880 | Clase Tanque." << endl;
    cout << "  - Carga: 1 Escudo Espejo y 3 Blasts de Racimo." << endl;
    
    cout << "\n====================================================" << endl;
    cout << "NOTA: Los IDs de los heroes son fijos para testear el Arbol B." << endl;
    cout << "Presione Enter para volver al menu.";
    getline(cin, pausa);
    limpiarPantalla();
}

void mostrarArmamento() {
    string pausa;
    limpiarPantalla();
    cout << "====================================================" << endl;
    cout << "           ARSENAL DE DATOS: TIPOS DE BLASTS        " << endl;
    cout << "====================================================" << endl;
    cout << "Presione Enter para ver el armamento estandar...";
    getline(cin, pausa);
    
    limpiarPantalla();
    cout << "\n>>> MUNICIONES DE ATAQUE DIRECTO <<<" << endl;
    cout << "1. LASER ESTANDAR:" << endl;
    cout << "   - Daño: 25 puntos directos." << endl;
    cout << "2. PERFORANTE (EMP):" << endl;
    cout << "   - Daño: 50 puntos masivos." << endl;
    cout << "   - Nota: Diseñado para destruir escudos rapidamente." << endl;
    
    cout << "\nPresione Enter para ver las armas tacticas y de area...";
    getline(cin, pausa);
    
    limpiarPantalla();
    cout << "\n>>> PROTOCOLOGOS ESPECIALES <<<" << endl;
    cout << "3. TROYANO (Control Mental):" << endl;
    cout << "   - Exclusivo de la clase ESPECTRO." << endl;
    cout << "   - Efecto: Ignora escudos y cambia el bando del enemigo permanentemente." << endl;
    cout << "4. DISRUPCION:" << endl;
    cout << "   - Efecto: Expulsa al enemigo del nodo actual." << endl;
    cout << "   - Consecuencia: El enemigo debe re-insertarse desde la Raiz." << endl;
    cout << "5. RACIMO (AoE):" << endl;
    cout << "   - Daño: 20 puntos de daño en area." << endl;
    cout << "   - Alcance: Afecta a enemigos en el nodo actual y en los nodos hijos directos." << endl;
    
    cout << "\n====================================================" << endl;
    cout << "REGLA DE COMBATE: Las armas se disparan en orden estricto" << endl;
    cout << "segun fueron encoladas (Cola FIFO)." << endl;
    cout << "Presione Enter para finalizar.";
    getline(cin, pausa);
    limpiarPantalla();
}

void mostrarTutorial() {
    string pausa;
    limpiarPantalla();
    cout << "====================================================" << endl;
    cout << "        BIENVENIDO A LA OPERACION YGGDRASIL         " << endl;
    cout << "====================================================" << endl;
    cout << "Presione Enter para comenzar el tutorial...";
    getline(cin, pausa);
    
    limpiarPantalla();
    cout << "\n1. EL NUCLEO (ARBOL B-4):" << endl;
    cout << "* El campo de batalla es un Arbol B de Grado 4 (2-3-4)." << endl;
    cout << "* Cada 'Estacion' (nodo) tiene capacidad para 3 operativos." << endl;
    cout << "* Los operativos se ordenan estrictamente por su ID_Clave." << endl;
    cout << "Presione Enter para ver la Dinamica de Turno...";
    getline(cin, pausa);
    
    limpiarPantalla();
    cout << "\n2. DINAMICA DE TURNO (PASOS):" << endl;
    cout << "* PASO 1 (Dado): Define cuantas unidades inyectar (1 a 3)." << endl;
    cout << "* PASO 2 (Carga): Se asignan Blasts aleatorios a la Cola de Arsenal." << endl;
    cout << "* PASO 3 (Inyeccion): La unidad entra al arbol. Si el nodo se llena," << endl;
    cout << "  ocurre un SPLIT (la mediana sube al padre)." << endl;
    cout << "Presione Enter para aprender sobre el Combate...";
    getline(cin, pausa);
    
    limpiarPantalla();
    cout << "\n3. FASE DE BATALLA Y LIMPIEZA:" << endl;
    cout << "* El conflicto ocurre si coexisten Neones y Omegas en un nodo." << endl;
    cout << "* Se ataca al enemigo con el ID mas alto del nodo." << endl;
    cout << "* El daño impacta primero la Pila de Escudos (LIFO)." << endl;
    cout << "* Muerte (HP <= 0): La unidad es eliminada y el arbol se re-balancea" << endl;
    cout << "  mediante prestamos (Borrow) o fusiones (Merge)." << endl;
    cout << "Presione Enter para ver las Condiciones de Victoria...";
    getline(cin, pausa);
    
    limpiarPantalla();
    cout << "\n4. COMO GANAR LA GUERRA:" << endl;
    cout << "* Aniquilacion: Eliminar o hackear a todo el equipo contrario." << endl;
    cout << "* Dominio: Controlar la RAIZ del arbol por 3 turnos seguidos." << endl;
    cout << "* Limite: Al llegar a 60 inyecciones, gana el bando con mas sobrevivientes." << endl;
    cout << "====================================================" << endl;
    cout << "Tutorial finalizado. Presione Enter para ir al menu principal.";
    getline(cin, pausa);
    limpiarPantalla();
}

void Sinopsis_Historia() {
    cout << "\n====================================================" << endl;
    cout << "           1. SINOPSIS E HISTORIA" << endl;
    cout << "====================================================" << endl;
    cout << "Año 2145. Tras el Colapso, la supervivencia de la" << endl;
    cout << "civilizacion depende de \"Yggdrasil\", un" << endl;
    cout << "superordenador cuantico subterraneo. Dos facciones," << endl;
    cout << "La Resistencia Neon (Equipo 1) y La Corporacion OMEGA" << endl;
    cout << "(Equipo 2), luchan por su control absoluto." << endl;
    cout << endl;
    cout << "La guerra se libra enteramente en el ciberespacio." << endl;
    cout << "Los operativos son digitalizados e inyectados" << endl;
    cout << "directamente en el Nucleo de Yggdrasil, el cual esta" << endl;
    cout << "blindado por una estricta arquitectura matematica:" << endl;
    cout << "un Arbol B de Grado 4 (2-3-4). Dentro de los nodos" << endl;
    cout << "de este arbol, los operativos utilizaran sus arsenales" << endl;
    cout << "de datos para eliminarse entre si, hackear mentes" << endl;
    cout << "enemigas y forzar re-balanceos estructurales" << endl;
    cout << "(Splits y Merges) para tomar por la fuerza la" << endl;
    cout << "Raiz del sistema y controlar la red mundial." << endl;
    cout << "====================================================" << endl;
    cout << "Seleccione  cualquier numero para volver al menu: ";
    int pausa;
    cin >> pausa;
    limpiarPantalla();
}

void Menu_Bienvenida() {
    int res = 0;

    while (res != 9) {
        srand(time(0));
        cout<<"\n   OPERACION YGGDRASY"<<endl;
        cout<<"--La guerra estructural--"<<endl;
        cout<<"------MENU DE OPCIONES------"<<endl;
        cout<<"1. Insertar personaje\n2. Historia/Sinopsis \n3. Tutorial\n4. Ver personajes\n5. Ver armas\n6. Ver lista de personajes agregados\n7. Eliminar lista de personajes agregados.\n8. Actualizar informacion de personajes\n9. Salir"<<endl;
        cin>>res;
        switch (res) {
            case 1: 
                Insertar_PJ();
                cout<<"PJ insertado \n";
                break;
            case 2: 
                Sinopsis_Historia();
                break;
            case 3:
                mostrarTutorial();
                break;
            case 4:
                mostrarPersonajes();
                break;
            case 5:
                mostrarArmamento();
                break;
            case 6:
                imprimir_lista_personajes();
                cout <<"\n";
                break;
            case 7:
                eliminar_lista_completa();
                cout<<"\nLista eliminada \n";
                break;
            case 8:
                actualizar_lista_personajes();
                break;
            case 9:
                cout << "Hasta luego ";
                break;
            default:
                cout<<"Ingrese una opcion valida "<<endl;
                break;
        }
    }
}

int main() {
    Menu_Bienvenida();
    return 0;
}
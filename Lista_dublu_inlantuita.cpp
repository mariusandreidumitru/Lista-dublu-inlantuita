#include <iostream>
#include <cstring>
using namespace std;

// Structura pentru nodul listei dublu înlănțuite
struct Nod {
    int numar;
    string info;
    Nod* urmator;
    Nod* anterior;
};

// Functie pentru a crea un nou nod
Nod* creeazaNod(int numar, const string& info) {
    Nod* nouNod = new Nod;
    nouNod->numar = numar;
    nouNod->info = info;
    nouNod->urmator = nullptr;
    nouNod->anterior = nullptr;
    return nouNod;
}

// Funcție pentru a adauga un nod la sfarsitul listei
void adaugaLaSfarsit(Nod*& head, Nod*& coada, int numar, const string& info) {
    Nod* nouNod = creeazaNod(numar, info);
    if (!coada) {
        head = coada = nouNod;
    } else {
        coada->urmator = nouNod;
        nouNod->anterior = coada;
        coada = nouNod;
    }
}

// Functie pentru a elimina un nod de pe o poziție specificata
void eliminaDeLaPozitie(Nod*& head, Nod*& coada, int pozitie) {
    if (!head) return;

    Nod* curent = head;
    int contor = 0;

    while (curent && contor < pozitie) {
        curent = curent->urmator;
        contor++;
    }

    if (!curent) return;

    if (curent->anterior) {
        curent->anterior->urmator = curent->urmator;
    } else {
        head = curent->urmator;
    }

    if (curent->urmator) {
        curent->urmator->anterior = curent->anterior;
    } else {
        coada = curent->anterior;
    }

    delete curent;
}

// Functie pentru a adauga un nod pe o pozitie specificata
void adaugaLaPozitie(Nod*& head, Nod*& coada, int pozitie, int numar, const string& info) {
    Nod* nouNod = creeazaNod(numar, info);
    if (pozitie == 0) {
        nouNod->urmator = head;
        if (head) {
            head->anterior = nouNod;
        }
        head = nouNod;
        if (!coada) {
            coada = head;
        }
        return;
    }

    Nod* curent = head;
    int contor = 0;

    while (curent && contor < pozitie - 1) {
        curent = curent->urmator;
        contor++;
    }

    if (!curent) {
        adaugaLaSfarsit(head, coada, numar, info);
        return;
    }

    nouNod->urmator = curent->urmator;
    nouNod->anterior = curent;
    if (curent->urmator) {
        curent->urmator->anterior = nouNod;
    } else {
        coada = nouNod;
    }
    curent->urmator = nouNod;
}

// Functie pentru a afisa lista
void afiseazaLista(Nod* head) {
    Nod* curent = head;
    while (curent) {
        cout << "(" << curent->numar << ", " << curent->info << ") ";
        curent = curent->urmator;
    }
   cout << endl;
}

// Functie pentru a elibera memoria
void elibereazaLista(Nod*& head) {
    Nod* curent = head;
    while (curent) {
        Nod* urmatorNod = curent->urmator;
        delete curent;
        curent = urmatorNod;
    }
    head = nullptr;
}

// Funcția principala pentru testarea aplicatiei
int main() {
    Nod* head = nullptr;
    Nod* coada = nullptr;

    adaugaLaSfarsit(head, coada, 1, "primul");
    adaugaLaSfarsit(head, coada, 2, "al doilea");
    adaugaLaSfarsit(head, coada, 3, "al treilea");

    cout << "Lista initiala: ";
    afiseazaLista(head);

    adaugaLaPozitie(head, coada, 1, 4, "inserat la poz 1");
    cout << "Dupa adaugare la pozitia 1: ";
    afiseazaLista(head);

    eliminaDeLaPozitie(head, coada, 2);
    cout << "Dupa eliminare de la pozitia 2: ";
    afiseazaLista(head);

    elibereazaLista(head);

    return 0;
}

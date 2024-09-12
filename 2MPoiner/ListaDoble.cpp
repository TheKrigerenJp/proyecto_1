//
// Created by josepa on 04/09/24.
//

#include "ListaDoble.h"

void ListaDoble::createMpointer(int info, void *address, TipoDato tipo_dato) {
    node* new_node = new node(info,  address,1, nullptr, tipo_dato);
    if(head == nullptr) {
        head = new_node;

    } else {
        node* temp = head;
        while(temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new_node;
    }

}

void ListaDoble::incrementRef(int identifier) {
    node* temp = head;
    while(temp != nullptr) {
        if (temp->info == identifier) {
            temp->i++;
            return;
        }
        temp = temp->next;
    }
}


int ListaDoble::decrementRef(int identifier) {
    node* temp = head;
    while(temp != nullptr) {
        if (temp->info == identifier) {
            temp->i--;
            return temp->i;
        }
        temp = temp->next;
    }
    return -1;
}

//El debugger e el profe pidio
void ListaDoble::display() {
    cout<<"INICIOOO"<<endl;
    node* temp = head;
    while(temp != nullptr) {
        switch (temp->dato) {
            case TipoDato::UNKNOWN: {
                cout<<"ID: "<< temp->info
                    <<"DIrección: "<< temp->address
                    <<"Referencias:"<< temp->i
                    <<endl;
                break;
            }
            case TipoDato::INT: {
                int* intPtr = static_cast<int*>(temp->address);
                cout<<"ID: "<< temp->info
                    <<"DIrección: "<< temp->address
                    <<"Referencias:"<< temp->i
                    <<"Valor: "<< *intPtr
                    <<endl;
                break;
            }
            case TipoDato::FLOAT: {
                float* floatPtr = static_cast<float*>(temp->address);
                cout<<"ID: "<< temp->info
                    <<"DIrección: "<< temp->address
                    <<"Referencias:"<< temp->i
                    <<"Valor: "<< *floatPtr
                    <<endl;
                break;
            }
            case TipoDato::DOUBLE:{
                double* doublePtr = static_cast<double*>(temp->address);
                cout<<"ID: "<< temp->info
                    <<"DIrección: "<< temp->address
                    <<"Referencias:"<< temp->i
                    <<"Valor: "<< *doublePtr
                    <<endl;
                break;
            }
        }
        temp = temp->next;
    }
    cout << "FINAAAL" << endl;

}

int ListaDoble::getSize() const {
    int size = 0;
    node* temp = head;
    while(temp != nullptr) {
        size++;
        temp = temp->next;
    }
    return size;
}

int ListaDoble::getIDAt(int index) const {
    node* temp = head;
    int size = 0;
    while(temp != nullptr) {
        if (temp->info == index) {
            return temp->info;
        }
        size++;
        temp = temp->next;
    }
    return -1;
}

void ListaDoble::deleteNode(int identifier) {
    node* temp = head;
    node* temp2 = nullptr;

    while(temp != nullptr && temp->info != identifier) {
        temp2 = temp;
        temp = temp->next;
    }

    if (temp == nullptr) return;

    if (temp2 == nullptr) {
        head = temp->next;
    } else {
        temp2->next = temp->next;
    }
    delete temp;
}

void ListaDoble::cambioAddress(int Cid, void *addressC) {
    node* temp = head;
    while (temp != nullptr) {
            if (temp->info=Cid) {
                temp->address = addressC;
            }
        temp = temp->next;
    }
}


int ListaDoble::getRefCount(int id) const {
    node* temp = head;
    while (temp != nullptr) {
        if (temp->info == id) {
            return temp->i;
        }
        temp = temp->next;
    }
    return -1;
}





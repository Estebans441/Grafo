//
// Created by diego on 30/10/2022.
//

#ifndef TEORIA_DE_GRAFOS_ARISTA_HXX
#define TEORIA_DE_GRAFOS_ARISTA_HXX
#include "Arista.h"

template<class A, class V>
Arista<A, V>::Arista() = default;

template<class A, class V>
Arista<A, V>::~Arista() = default;

template<class A, class V>
Arista<A, V>::Arista(V valorVerticeDestino) {

}

template<class A, class V>
Arista<A, V>::Arista(A peso, V valorVerticeDestino):peso(peso), valorVerticeDestino(valorVerticeDestino) {}

template<class A, class V>
A Arista<A, V>::getPeso() const {
    return peso;
}

template<class A, class V>
void Arista<A, V>::setPeso(A peso) {
    Arista::peso = peso;
}

template<class A, class V>
V Arista<A, V>::getValorVerticeDestino() const {
    return valorVerticeDestino;
}

template<class A, class V>
void Arista<A, V>::setValorVerticeDestino(V valorVerticeDestino) {
    Arista::valorVerticeDestino = valorVerticeDestino;
}


#endif //TEORIA_DE_GRAFOS_ARISTA_HXX

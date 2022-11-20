//
// Created by diego on 30/10/2022.
//

#ifndef TEORIA_DE_GRAFOS_VERTICE_HXX
#define TEORIA_DE_GRAFOS_VERTICE_HXX
#include "Vertice.h"

template<class V, class A>
Vertice<V, A>::Vertice() = default;

template<class V, class A>
Vertice<V, A>::~Vertice() = default;

template<class V, class A>
V Vertice<V, A>::getValor() const {
    return valor;
}

template<class V, class A>
void Vertice<V, A>::setValor(V valor) {
    Vertice::valor = valor;
}

template<class V, class A>
Vertice<V, A>::Vertice(V valor):valor(valor) {}


template<class V, class A>
std::ostream &operator<<(std::ostream &os, const Vertice<V, A> &vertice) {
    os << "Vertice: " << vertice.valor << std::endl;
    return os;
}

template<class V, class A>
Vertice<V, A>::Vertice(const std::vector<Arista<A, V> *> &aristas):aristas(aristas) {}

template<class V, class A>
Vertice<V, A>::Vertice(V valor, const std::vector<Arista<A, V> *> &aristas):valor(valor), aristas(aristas) {}

template<class V, class A>
std::vector<Arista<A, V> *> &Vertice<V, A>::getAristas(){
    return aristas;
}

template<class V, class A>
void Vertice<V, A>::setAristas(const std::vector<Arista<A, V> *> &aristas) {
    Vertice::aristas = aristas;
}

template<class V, class A>
bool Vertice<V, A>::getMarcado(){ return marcado; }

template<class V, class A>
void Vertice<V, A>::setMarcado(bool marcado){ Vertice::marcado = marcado; }

template<class V, class A>
void Vertice<V, A>::agregarAristaEnVertice(V valor) {
    auto* aristaAgregar = new Arista<A, V>(valor);
    this->aristas.push_back(aristaAgregar);
}

template<class V, class A>
void Vertice<V, A>::agregarAristaEnVertice(V valor, A peso) {
    auto* aristaAgregar = new Arista<A, V>(peso, valor);
    this->aristas.push_back(aristaAgregar);
}

#endif //TEORIA_DE_GRAFOS_VERTICE_HXX

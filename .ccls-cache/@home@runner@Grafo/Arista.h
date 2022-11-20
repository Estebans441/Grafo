#ifndef TEORIA_DE_GRAFOS_ARISTA_H
#define TEORIA_DE_GRAFOS_ARISTA_H
#include <ostream>

template <class A, class V>
class Arista{
private:
    A peso;
    V valorVerticeDestino;
public:
    //CONSTRUCTORES:
    Arista();
    ~Arista();
    explicit Arista(V valorVerticeDestino);
    Arista(A peso, V valorVerticeDestino);

    //GETTERS Y SETTERS:
    V getValorVerticeDestino() const;
    void setValorVerticeDestino(V valorVerticeDestino);
    A getPeso() const;
    void setPeso(A peso);
};

#include "Arista.hxx"
#endif //TEORIA_DE_GRAFOS_ARISTA_H

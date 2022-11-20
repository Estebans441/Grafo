#ifndef TEORIA_DE_GRAFOS_GRAFO_HXX
#define TEORIA_DE_GRAFOS_GRAFO_HXX
#include <limits>
#include "Grafo.h"
#include "Vertice.hxx"
#include <iostream>
#include <queue>

//CONSTRUCTORES:
template<class V, class A>
Grafo<V, A>::Grafo() {}

template<class V, class A>
Grafo<V, A>::~Grafo() = default;

template<class V, class A>
Grafo<V, A>::Grafo(bool dirigido):dirigido(dirigido) {}

template<class V, class A>
Grafo<V, A>::Grafo(const std::vector<Vertice<V, A>> &vertices, bool dirigido):vertices(vertices),dirigido(dirigido) {}

//GETTER Y SETTERS:

template<class V, class A>
const std::vector<Vertice<V, A>> &Grafo<V, A>::getVertices() const {
    return vertices;
}

template<class V, class A>
void Grafo<V, A>::setVertices(const std::vector<Vertice<V, A>> &vertices) {
    Grafo::vertices = vertices;
}

template<class V, class A>
Grafo<V, A>::Grafo(const std::vector<Vertice<V, A>> &vertices):vertices(vertices) {}

template<class V, class A>
Grafo<V, A>::Grafo(const std::vector<Vertice<V, A>> &vertices, bool dirigido, bool ponderado):vertices(vertices), dirigido(dirigido), ponderado(ponderado) {}

template<class V, class A>
Grafo<V, A>::Grafo(bool dirigido, bool ponderado):dirigido(dirigido), ponderado(ponderado) {}

template<class V, class A>
bool Grafo<V, A>::isDirigido() const {
    return dirigido;
}

template<class V, class A>
void Grafo<V, A>::setDirigido(bool dirigido) {
    Grafo::dirigido = dirigido;
}

template<class V, class A>
bool Grafo<V, A>::isPonderado() const {
    return ponderado;
}

template<class V, class A>
void Grafo<V, A>::setPonderado(bool ponderado) {
    Grafo::ponderado = ponderado;
}

template<class V, class A>
int Grafo<V, A>::getValorVertice(int i){
  return vertices[i].getValor();
}

template<class V, class A>
std::vector<V> Grafo<V, A>::getSucesores(int i){
  std::vector<V> retorno;
  for(int j = 0; j < vertices[i].getAristas().size(); j++){
    retorno.push_back(vertices[i].getAristas()[j]->getValorVerticeDestino());
  }
  return retorno;
}

template<class V, class A>
std::vector<Arista<int, int>*> &Grafo<V, A>::getAristasVertice(int i){
  return vertices[i].getAristas();
}

template<class V, class A>
int Grafo<V, A>::ordenGrafo(){
  return vertices.size();
}

template<class V, class A>
void Grafo<V, A>::setMarcaVertice(int i, bool marcado){
  vertices[i].setMarcado(marcado);
}

template<class V, class A>
bool Grafo<V, A>::verticeMarcado(int i){
  return vertices[i].getMarcado();
}

//MÉTODOS REALES:
template<class V, class A>
bool Grafo<V, A>::verificarExistencia(V valor){
    for (int i = 0; i < this->vertices.size(); i++){
        if(this->vertices[i].getValor() == valor){
            return true;
        }
    }
    return false;
}

template<class V, class A>
bool Grafo<V, A>::agregarVertice(V valor){
    bool existe = verificarExistencia(valor);
    if(!existe){
        auto* nuevoVertice = new Vertice<V, A>(valor);
        this->vertices.push_back(*nuevoVertice);
        return true;
    }
    else{
        return false;
    }
}

template<class V, class A>
bool Grafo<V, A>::esVacio(){
    if(vertices.empty()) {
        return true;
    }
    return false;
}

template<class V, class A>
void Grafo<V, A>::imprimirGrafo(){
    if(esVacio()){
        std::cout << "El grafo esta vacio!" << std::endl;
        return;
    } else{
        for (int i = 0; i < this->vertices.size(); i++){
            std::cout << "Vertice " << vertices[i].getValor() << ":" << std::endl << "Marcado: " << vertices[i].getMarcado() << std::endl << std::endl;
            if (vertices[i].getAristas().empty()){
                std::cout << "\tEste vertice no tiene aristas" << std::endl << std::endl;
            }else{
                std::cout << "\tAristas: " << std::endl;
                for(int j = 0; j < vertices[i].getAristas().size(); j++){
                    std::cout << "\t - "
                              << vertices[i].getValor()
                              << " -> "
                              << vertices[i].getAristas()[j]->getValorVerticeDestino()
                              << " Peso: "
                              << vertices[i].getAristas()[j]->getPeso() << std::endl;
                }
            }
            std::cout << std::endl;
        }
    }
}

template<class V, class A>
bool Grafo<V, A>::agregarArista(V valorOrigen, V valorDestino) {
    bool existenciaOrigen;
    bool existenciaDestino;
    existenciaOrigen = verificarExistencia(valorOrigen);
    existenciaDestino = verificarExistencia(valorDestino);
    if (existenciaOrigen && existenciaDestino) {
        for(int i = 0; i < this->vertices.size(); i++){
            if(valorOrigen == vertices[i].getValor()){
                vertices[i].agregarAristaEnVertice(valorDestino);
            }
            if(valorDestino == vertices[i].getValor() && !dirigido){
                vertices[i].agregarAristaEnVertice(valorOrigen);
            }
        }
    } else {
        std::cout << "Vertices invalidos!" << std::endl;
    }
}

template<class V, class A>
bool Grafo<V, A>::agregarArista(V valorOrigen, V valorDestino, A peso) {
    bool existenciaOrigen;
    bool existenciaDestino;
    existenciaOrigen = verificarExistencia(valorOrigen);
    existenciaDestino = verificarExistencia(valorDestino);
    if (existenciaOrigen && existenciaDestino) {
        for(int i = 0; i < this->vertices.size(); i++){
            if(valorOrigen == vertices[i].getValor()){
                vertices[i].agregarAristaEnVertice(valorDestino, peso);
            }
            if(valorDestino == vertices[i].getValor() && !dirigido){
                vertices[i].agregarAristaEnVertice(valorOrigen, peso);
            }
        }

    } else {
        std::cout << "Vertices invalidos!" << std::endl;
      return false;
    }
  return true;
}

template<class V, class A>
void Grafo<V, A>::desmarcarGrafo(){
  for(int i = 0 ; i < vertices.size() ; i++){
      vertices[i].setMarcado(false);
  }
}

template<class V, class A>
int Grafo<V, A>::verticeToIndice(V vertice){
  for(int i = 0 ; i < vertices.size() ; i++){
    if(vertice == vertices[i].getValor())
      return i;
  }
  return -1;
}

template<class V, class A>
A Grafo<V, A>::costoArco(int origen, int destino){
  std::vector<Arista<A, V>*> aristas = vertices[origen].getAristas();
  for(int i = 0 ; i < aristas.size() ; i++)
    if(aristas[i]->getValorVerticeDestino() == vertices[destino].getValor()) return aristas[i]->getPeso();
  return -1;
}

template<class V, class A>
A *Grafo<V, A>::Dijkstra(int v, std::vector<std::vector<V>> &caminos){
  int i, nv = ordenGrafo();
  A c;
  A * costosmin = new A[nv];
  desmarcarGrafo();
  std::vector<V> caminoBase;
  for(i = 0; i < nv ; i++){
    caminos.push_back(caminoBase);
    if((costosmin[i] = costoArco(v, i)) != -1){
      caminos[i].push_back(vertices[v].getValor());
      caminos[i].push_back(vertices[i].getValor());
    }
  }
  
  setMarcaVertice(v, true);
  caminos[v].push_back(vertices[v].getValor());
  costosmin[v] = 0;
  while((v = siguienteVertice(costosmin, nv)) != -1){
    setMarcaVertice(v, true);
    for(i = 0 ; i < nv ; i++){
      if(!verticeMarcado(i) && (c = costoArco(v, i)) != -1){
        if(costosmin[i] == -1){
          costosmin[i] = costosmin[v] + c;
          caminos[i] = caminos[v];
          caminos[i].push_back(vertices[i].getValor());
        }
        else
          if((costosmin[v] + c) < costosmin[i]){
            costosmin[i] = costosmin[v] + c;
            caminos[i] = caminos[v];
            caminos[i].push_back(vertices[i].getValor());
          }
      }
    }
  }
  return costosmin;
}

template<class V, class A>
int Grafo<V, A>::siguienteVertice(A costos[], int nv){
  int i, menor = -1;
  for(i = 0 ; i < nv ; i++)
    if(!verticeMarcado(i) && costos[i] != -1)
      if(menor == -1 || costos[menor] > costos[i])
        menor = i;
  if(menor == -1)
    return -1;
  else
    return menor;
}

#endif
//TEORIA_DE_GRAFOS_GRAFO_HXX
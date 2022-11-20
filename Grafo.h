#ifndef TEORIA_DE_GRAFOS_GRAFO_H
#define TEORIA_DE_GRAFOS_GRAFO_H
#include "Vertice.h"
#include <vector>
#include <stack>

template <class V, class A> class Grafo {
private:
  std::vector<Vertice<V, A>> vertices;
  bool dirigido;
  bool ponderado;

public:
  // CONSTRUCTORES:
  Grafo();
  explicit Grafo(const std::vector<Vertice<V, A>> &vertices);
  Grafo(bool dirigido);
  Grafo(const std::vector<Vertice<V, A>> &vertices, bool dirigido,
        bool ponderado);
  Grafo(bool dirigido, bool ponderado);
  Grafo(const std::vector<Vertice<V, A>> &vertices, bool dirigido);
  
  ~Grafo();

  // GETTER Y SETTERS:
  const std::vector<Vertice<V, A>> &getVertices() const;
  void setVertices(const std::vector<Vertice<V, A>> &vertices);
  bool isDirigido() const;
  void setDirigido(bool dirigido);
  bool isPonderado() const;
  void setPonderado(bool ponderado);
  V getValorVertice(int i);
  std::vector<V> getSucesores(int vertice);
  std::vector<Arista<int, int>*> &getAristasVertice(int i);
  int ordenGrafo();
  void setMarcaVertice(int i, bool marcado);
  bool verticeMarcado(int i);
  void desmarcarGrafo();

  // MÉTODOS REALES:
  bool verificarExistencia(V valor);
  bool agregarVertice(V valor);
  bool agregarArista(V valorOrigen, V valorDestino);
  bool agregarArista(V valorOrigen, V valorDestino, A peso);
  bool esVacio();
  void imprimirGrafo();
  int verticeToIndice(V vertice);
  A costoArco(int origen, int destino);

  //Dijkstra
  A * Dijkstra(int v, std::vector<std::vector<V>> &caminos);
  int siguienteVertice(A costos[], int nv);
};

#include "Grafo.hxx"
#endif // TEORIA_DE_GRAFOS_GRAFO_H
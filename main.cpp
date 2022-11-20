#include "Grafo.h"
#include <list>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

bool hayCamino(Grafo<int, int> grafo, int origen, int destino);
int costoCamino(Grafo<int, int> grafo, int v1, int v2);
void recorrerNiveles (Grafo<int, int> grafo, int vertice);
vector<int> costosTodosCaminos(Grafo<int, int> grafo, int vertice);
int * Dijkstra(Grafo<int, int> grafo, int v, vector<vector<int>> &caminos);
int siguienteVertice(Grafo<int, int> &grafo, int costos[], int nv);

int main() {
  Grafo<int, float> grafo(false, true);
  grafo.agregarVertice(1);
  grafo.agregarVertice(2);
  grafo.agregarVertice(3);
  grafo.agregarVertice(4);
  grafo.agregarVertice(5);
  grafo.agregarVertice(6);

  grafo.agregarArista(1, 2, 200);
  grafo.agregarArista(1, 3, 1);
  grafo.agregarArista(6, 1, 1);
  grafo.agregarArista(2, 4, 1);
  grafo.agregarArista(3, 1, 1);
  grafo.agregarArista(3, 4, 200);
  grafo.agregarArista(4, 2, 200);
  grafo.agregarArista(6, 5, 1);
  grafo.agregarArista(5, 2, 20.3);
  
  vector<vector<int>> caminos;
  float * dijkstra = grafo.Dijkstra(1, caminos);
  cout << "----------------------------" << endl;
  cout << "Dijkstra desde " << grafo.getValorVertice(1) << ": " << endl;
  cout << "----------------------------" << endl;
  for(int i = 0 ; i < grafo.ordenGrafo() ; i++){
    cout << "Destino: " << grafo.getValorVertice(i) << endl;
    cout << "Costo: " << dijkstra[i] << endl << "Camino: ";
    for(int j = 0 ; j < caminos[i].size() ; j++)
      cout<< caminos[i][j] << " -> ";
    cout << endl << "----------------------------" << endl;
  }

  return 0;
}

vector<int> costosTodosCaminos(Grafo<int, int> grafo, int vertice){
  vector<int> costos;
  vector<Vertice<int, int>> vertices = grafo.getVertices();
  for(int i = 0; i < vertices.size() ; i++){
    costos.push_back(costoCamino(grafo, vertice, vertices[i].getValor()));
  }
  return costos;
}

bool hayCamino(Grafo<int, int> grafo, int origen, int destino){
  vector<int> sucesores;
  if(grafo.esVacio()) return false;
  else if(origen == destino) return true;
  else{
    grafo.setMarcaVertice(grafo.verticeToIndice(origen), true);
    sucesores = grafo.getSucesores(grafo.verticeToIndice(origen));
    for(int i = 0 ; i < sucesores.size() ; i++){
      if(!grafo.verticeMarcado(grafo.verticeToIndice(sucesores[i]))){
        if(hayCamino(grafo, sucesores[i], destino) && grafo.verticeMarcado(grafo.verticeToIndice(origen))){
         return true;
        }
      }
    }
    grafo.setMarcaVertice(grafo.verticeToIndice(origen), false);
    return false;
  }
}


int costoCamino(Grafo<int, int> grafo, int origen, int destino) {
  vector<Arista<int, int>*> aristas;
  int costo = 0, menor = -1, verticeDestino;

  if(grafo.esVacio()) return 0;
  else if(!hayCamino(grafo, origen, destino)) return -1;
  else if(origen == destino) return 0;
  else{
    grafo.setMarcaVertice(grafo.verticeToIndice(origen), true);
    aristas = grafo.getAristasVertice(grafo.verticeToIndice(origen));
    for(int i = 0 ; i < aristas.size() ; i++){
      verticeDestino = aristas[i]->getValorVerticeDestino();
      if(hayCamino(grafo, origen, verticeDestino)){
        costo = costoCamino(grafo, verticeDestino, destino);
        if(costo != -1){
        costo += aristas[i]->getPeso();
        if(menor == -1) menor = costo;
        else if(costo < menor) menor = costo;
        }
      }
    }
    grafo.setMarcaVertice(grafo.verticeToIndice(origen), false);
    return menor;
  }
}

void recorrerNiveles(Grafo<int,int> grafo, int vertice){
  vector <int> sucesores;
  queue <int> q;
  grafo.desmarcarGrafo();
  q.push(vertice);
  grafo.setMarcaVertice(grafo.verticeToIndice(vertice), true);
  while (!q.empty()){
    int v = q.front();
    q.pop();
    cout << v << endl;
    sucesores = grafo.getSucesores(grafo.verticeToIndice(v));
    for (int i = 0; i < sucesores.size(); i++){
      if(!grafo.verticeMarcado(grafo.verticeToIndice(sucesores[i])))
        q.push(sucesores[i]);
        grafo.setMarcaVertice(grafo.verticeToIndice(sucesores[i]), true);
    }
  }
  vector<Vertice<int,int>> vertices = grafo.getVertices();
  for(int i = 0 ; i < vertices.size() ; i++)
    if(!vertices[i].getMarcado()) cout << vertices[i].getValor() << endl;
}

/*
int * Dijkstra(Grafo<int, int> grafo, int v, vector<vector<int>> &caminos){
  int i, c, nv = grafo.ordenGrafo();
  int * costosmin = new int[nv];
  vector<Vertice<int, int>> vertices = grafo.getVertices();
  grafo.desmarcarGrafo();
  vector<int> caminoBase;
  for(i = 0; i < nv ; i++){
    caminos.push_back(caminoBase);
    if((costosmin[i] = grafo.costoArco(v, i)) != -1){
      caminos[i].push_back(vertices[v].getValor());
      caminos[i].push_back(vertices[i].getValor());
    }
  }
  
  grafo.setMarcaVertice(v, true);
  caminos[v].push_back(vertices[v].getValor());
  costosmin[v] = 0;
  while((v = siguienteVertice(grafo, costosmin, nv)) != -1){
    grafo.setMarcaVertice(v, true);
    for(i = 0 ; i < nv ; i++){
      if(!grafo.verticeMarcado(i) && (c = grafo.costoArco(v, i)) != -1){
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

int siguienteVertice(Grafo<int, int> &grafo, int costos[], int nv){
  int i, menor = -1;
  for(i = 0 ; i < nv ; i++)
    if(!grafo.verticeMarcado(i) && costos[i] != -1)
      if(menor == -1 || costos[menor] > costos[i])
        menor = i;
  if(menor == -1)
    return -1;
  else
    return menor;
}
*/
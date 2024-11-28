/*
*  autor: Benjamin Valdes Aguirre
*  fecha: Diciembre 2020
*  programa: act 4.1 Implementacion Grafos
*  desc: estos programas son solciones parciales a algunos de
*  las actividades planteadas en el curso TC1031
*
*		Nota: Esta imlpementación es Top Down, no divide al árbol para la operacións
*		de barrado
*/
//El grafo necesita saber desde donde llegaste.
//Tambien necesita una lista donde guardes a que nodos ya has ido.
//Finalmente ocupas tambien,  un ¿"stack"? para que a la hora de explorar
//caminos, si al elegir vertice no hay retorno, busques caminos en otro vertice.
#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;


class Graph {
private:
   int edgesList;
   int edgesMat;
   int nodes;
   vector<int> *adjList;
   int *adjMatrix;
   //vector<Type> *vect = new vector<Type>

public:
   Graph(int);
   Graph();
   void addEdgeAdjList(int, int);
   void addEdgeAdjMatrix(int, int);
   string printAdjList();
   string printAdjMat();
   string printAdjMat_clean();
   string DFS(int, int);
   string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int>>&);
   string BFS(int, int);
   string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int>>&);
   string print_visited(list<int>);
   string print_path(vector<vector<int>>&,int ,int);
   bool contains(list<int>, int);
   void sortAdjList();
   void loadGraphList(string, int);
   void loadGraphMat(string, int, int);
};


void Graph::loadGraphList(string lista, int num_nodos){
 adjList = new vector<int>[num_nodos];
 nodes = num_nodos;

 int u, v;
   for (int i = 2;i<lista.size();i++){
     //cout<<"Bandera indice "<<i<<"\n";
     if(isdigit(lista[i-2])&&lista[i-1]==','&&isdigit(lista[i])){
       //cout<<"Bandera 2";
       u = stoi(lista.substr(i-2,1));
       v = stoi(lista.substr(i,1));
       addEdgeAdjList(u,v);
     }

   }
 sortAdjList();
}

void Graph::loadGraphMat(string lista, int a, int b){
 adjMatrix = new int [a*b];
 nodes = a;
 for (int i = 0; i < a*b; i++)
   adjMatrix[i] = 0;

  //------------------

   int u, v;

     for (int i = 2;i<lista.size();i++){
       if(isdigit(lista[i-2])&&lista[i-1]==','&&isdigit(lista[i])){
         u = stoi(lista.substr(i-2,1));
         v = stoi(lista.substr(i,1));
         addEdgeAdjMatrix(u,v);
       }

     }


}

Graph::Graph() {
 edgesList = edgesMat = 0;
}

Graph::Graph(int n) {
 nodes = n;
 adjList = new vector<int>[nodes];
 adjMatrix = new int [nodes*nodes];
 for (int i = 0; i < nodes*nodes; i++)
   adjMatrix[i] = 0;
 edgesList = edgesMat = 0;
}

void Graph::addEdgeAdjList(int u, int v){
 adjList[u].push_back(v);
 adjList[v].push_back(u);
 edgesList++;
}

void Graph::addEdgeAdjMatrix(int u, int v){
 adjMatrix[u*nodes+v] = 1;
 adjMatrix[v*nodes+u] = 1;
 edgesMat++;
}

string Graph::printAdjList(){
   stringstream aux;
   for (int i = 0; i < nodes; i++){
         aux << "vertex "
              << i << " :";
         for (int j = 0; j < adjList[i].size(); j ++){
              aux << " " << adjList[i][j];
         }
         aux << " ";
   }
   return aux.str();

}

void Graph::sortAdjList(){
 for (int i = 0; i < nodes; i++)
   sort(adjList[i].begin(),adjList[i].end());
}

string Graph::printAdjMat(){
 stringstream aux;
 for (int i = 0; i < nodes; i++){
    for (int j = 0; j < nodes; j++){
      aux << adjMatrix[i*nodes+j] << " ";
    }
 }
 return aux.str();
}

string Graph::printAdjMat_clean(){
 stringstream aux;
 aux << "\n nodes \t|";
 for (int i = 0; i < nodes; i++){
     aux << "\t" << i ;
 }
 aux << "\n";
 for (int i = 0; i < nodes; i++){
     aux << "__________";
 }
 aux << "\n";
 for (int i = 0; i < nodes; i++){
    aux << i << "\t|";
    for (int j = 0; j < nodes; j++){
      aux << "\t" << adjMatrix[i*nodes+j];
    }
    aux << "\n";
 }
 return aux.str();
}

string Graph::DFS(int start, int goal){
 //Inicializar stack, lista y vector de vectores.

   stack <int> st_inicial;
   st_inicial.push(start);
   list <int> visitados;
   visitados.push_back(start);
   vector<vector<int>> caminos;
   /*vector<int> camino;
   camino.push_back(start);
   caminos.push_back(camino);*/
   //cout<<"NODES IGUAL A "<<nodes;
   for (int i = 0; i < nodes;i++){
     caminos.push_back({});
   }
   return depthHelper(start,goal,st_inicial,visitados,caminos);
}

string Graph::depthHelper(int current,
                             int goal,
                             stack<int> &st,
                             list<int> &visited,
                             vector<vector<int>> &paths){
   //Tal vez esta cosa varios caminos y cada vez que debo cambiar, pone otro.
   //Entonces podria decir que cada camino es una combinacion de stack distinta

   if (st.empty() ){
     //cout<<"BANDERA";
     //return print_visited(visited)+" "+print_path(paths,visited.front(),goal);
     return "Nodo no encontrado";
   }
   if (current==goal){
      while (!st.empty()) st.pop();
      //Lo vacie porque estaba buscando un error.

     //cout<<"Segunda bandera Prueba camino\n";
     //cout << "Segunda bandera: current=" << current << ", goal=" << goal << endl;
     //visited.push_back(current);
     //visited.push_back(current);

     //cout<<print_path(paths,visited.front(),goal)<<"\n";
     //cout<<visited[0]<<" ";
     /*for (int i=paths.size()-1; paths[i][0]=visited.front();i--){

       cout<<"a";
     }*/

     //visited.push_back(current);
     //En teoria no hace falta hacerlo aqui, los aniado en preorder.
     //Pero el ultimo camino si hace falta.
     /*stack<int> copia = st;
     vector<int> camino_final;
     while(!copia.empty()){
       camino_final.push_back(copia.top());
       //cout<<copia.top()<<"\n";
       copia.pop();
 }
     paths.push_back(camino_final);*/

     //cout<<"Bandera 3\n";
     //string visitados = print_visited(visited);
     //+" "+print_path(paths,visited.front(),goal)
     //print_path(paths,visited.front(),goal);
     //cout<<"final: "<<print_visited(visited)<<"\n";
     //print_path(paths,visited.front(),goal);

     /*
     for (int i = 0; i < paths.size();i++){
       for(int j = 0; j < paths[i].size();j++){
         cout<<paths[i][j]<<" ";
       }
       cout<<"\n";
     }*/

     //cout<<"\n"<<print_path(paths,visited.front(),goal)<<"\n";
     //return print_visited(visited);
     return print_visited(visited)+/*" +"*/print_path(paths,visited.front(),goal);
     //cout<<print_visited(visited);
   }

    //Primero deberia ver como detectar el caso base.
    bool avaible;

      int node;
      //cout<<"Cant. de nodos: "<<nodes<<"\n";
      //Iterar a
     // for(int i = 0; i < nodes; i++ ){
       for(int nodo:adjList[current]){
        avaible = true;
        //node = adjList[current][i];
        //node = nodo;
        for(int visitado:visited){
          //Tristemente no se puede acceder a valores de una lista con index.
          if(nodo == visitado){
            avaible = false;
            //node = nodo;
            break;
          }
        }
        if (avaible){
          stack<int> st_copy(st);
          while(!st_copy.empty()){
            //cout<<"Bucle\n";
            //Tristemente no se puede

            if(st_copy.top() ==nodo){
              avaible = false;
              break;
            }
            st_copy.pop();
          }
          //cout<<"Saliendo bucle while\n";
          //cout<<print_visited(visited);
          //cout<<"\n";
        }

        if(avaible){
          visited.push_back(nodo);
          st.push(nodo);
          //cout<<"anadiendo: {"<<current<<";"<</*nodo<<*/"}\n";
          //paths.push_back({current,nodo});
          paths[nodo].push_back(current);
          //cout<<"visited: ";
          /*
          for(int a:visited){
            cout<<a<<" ";
          }*/
          //cout<<"\n";
          return depthHelper(nodo,goal,st,visited,paths);
        }
        //avaible = true;

      }
      //visited.push_back(current);
      st.pop();
      //paths.pop_back();
      if (!st.empty()){
        return depthHelper(st.top(),goal,st,visited,paths);
      }
      //return print_visited(visited)+" "+print_path(paths,visited.front(),goal);

      //return print_visited(visited) + " " + print_path(paths, visited.front(), goal);


    /*if(current == goal){
      //Esto deberia funcionar, ya lo probe en Zinjal
       return print_visited()+" "+print_path();
    }
    else{

     return " node not found";
   }*/
}


string Graph::BFS(int start, int goal){

  queue<int> cola;
  cola.push(start);
  list<int>visitados;
  vector<vector<int>> caminos;

  for (int i = 0; i < nodes;i++){
    caminos.push_back({});
  }
  //Le inserto el nodo inicial.
  cola.push(start);
   return breadthHelper(start,goal,cola,visitados,caminos);
}

string Graph::breadthHelper(int current,
                             int goal,
                             queue<int> &qu,
                             list<int> &visited,
                             vector<vector<int>> &paths){



    if(current==goal){
      //cout<<"Bandera encontrado";
      visited.push_back(current);
      return print_visited(visited)+print_path(paths,visited.front(),goal);
    }
    bool avaible;
    if(!qu.empty()){

      avaible = true;
      for(int visitado:visited){
        if(qu.front() == visitado){
          avaible = false;
          break;
        }
      }
      //Si el nodo actual del queue no ha sido visitado.
        if(avaible){
          visited.push_back(qu.front());
          //paths[qu.front()].push_back();
          for(int vecino:adjList[qu.front()]){
            paths[vecino].push_back(qu.front());
            qu.push(vecino);
          }

        }
        else{
          qu.pop();
        }



        if(!qu.empty()){
          return breadthHelper(qu.front(),goal,qu,visited,paths);
        }



    }



      return " node not found";




}


bool Graph::contains(list<int> ls, int node){
   list<int>::iterator it;
   it = find(ls.begin(), ls.end(), node);
   if(it != ls.end())
     return true;
   else
     return false;
}

string Graph::print_visited(list<int> q){
 stringstream aux;
 aux << "visited: ";
 while (!q.empty()){
   aux << q.front() << " ";
   q.pop_front();
 }
 return aux.str();
}

string Graph::print_path(vector<vector <int>> &path, int start, int goal){
  //cout<<"\nInicio print_path ";
 int node =  path[goal][0];
 //cout<<path[goal][0];
 stack<int> reverse;
 reverse.push(goal);
 stringstream aux;
 aux  << "path:";
 while (node != start) {
   //cout<<"\nBandera 2 print_path "<< node;
   reverse.push(node);
   node = path[node][0];
 }

 reverse.push(start);
 while (!reverse.empty()) {
   aux << " " << reverse.top() ;
   reverse.pop();
 }
 //cout<<"\nFin print_path";
 return aux.str();
}
#endif /* Graph_H_ */

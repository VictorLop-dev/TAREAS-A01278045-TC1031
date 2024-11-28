#include <iostream>

class Funciones{
  public:
    int sumaDirecta(int n){
      return (n*(n+1))/2;
    }

    int sumaIterativa(int n){
      int suma = 0;
      for (int i = 1;i <= n; i++){
        suma+=i;
      }
      return suma;
    }

    int sumaRecursiva(int n){
      if (n > 0){
        return sumaRecursiva(n-1)+n;
      }
      return 0;
    }

};

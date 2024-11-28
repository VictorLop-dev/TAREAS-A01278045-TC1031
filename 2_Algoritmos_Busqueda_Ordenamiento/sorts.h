//Victor Hugo Lopez Licona
//A01278045
//#include <vector>
//Crei necesitar declarar al menos la clase vector, pero funciono sin eso.
template <class T>
class Sorts {
private:
  void swap(std::vector<T> &source, int a, int b){
    T aux = source[a];
    source[a] = source[b];
    source[b] = aux;
  }
  void mergeUnir(std::vector<T> &A, std::vector<T> &B, int fondo, int mitad, int tope){
    int i, j, k;
    i = fondo;
    j = mitad+1;
    k = fondo;

    while (i <= mitad && j <= tope ){
      if (A[i] < A[j]){
        B[k] = A[i];
        i++;
      }
      else {
        B[k] = A[j];
        j++;
      }
      k++;
    }
    if (i > mitad){
      for (; j <= tope; j++){
        B[k] = A[j];
        k++;
      }
    }
      else {
        for (;i<=mitad; i++){
          B[k] = A[i];
          k++;
        }
      }

  }

  void mergeDividir(std::vector<T> &A, std::vector<T> &B, int fondo, int tope){
    if (fondo != tope){
      //std::cout<<"Ejecutando"<<std::endl;
      int mitad = (tope+fondo)/2;

      mergeDividir(A,B,fondo,mitad);
      mergeDividir(A,B,mitad+1,tope);
      mergeUnir(A,B,fondo,mitad,tope);

      for (int i = fondo; i <= tope;i++){
        A[i] = B[i];
        //std::cout<<"A["<<i<<"] = B["<<i<<"] \n";
      }

    }

  }


public:
  void ordenaSeleccion(std::vector<T> &source){
    int ind_menor;
    for (int i = 0; i < (source.size())-1;i++){
      //Ese -1 es opcional, lo puse para que no intente la ultima iteracion
      //donde ya solo queda un elemento
      ind_menor = i;
      //Para evitar errores, reinicio el valor inicial del indice menor
      for(int j = i; j < source.size();j++){
        if (source[ind_menor] > source[j]){
          ind_menor = j;
        }
      }
      swap(source,i,ind_menor);
    }

  }

  void ordenaBurbuja(std::vector<T> &source){
    for (int i = (source.size())-1; i >= 0; i--){

      for (int j = 0; j < i; j++){
        //std::cout<<"Comparando indices: "<<j<<" y "<<j+1<<std::endl;
        //Lo use para probar si hacia todas las iteraciones que queria.
        if (source[j] > source[j+1]){
          swap(source,j,j+1);
        }
      }
    }
  }
  void ordenaMerge(std::vector<T> &source){

    std::vector<T> aux(source.size());
    //for (int i = 0; i <)
    mergeDividir(source,aux,0,source.size()-1);

  }
  int busqSecuencial(std::vector<T> &source, T num){

    for (int i = 0; i < source.size();i++){
      if (source[i] == num){
        return i;
      }



    }

    return -1;
  }
  /*int auxBusqBinaria(std::vector<T> &source, T num, int fondo, int tope){
    if (fondo != tope){
      int ind_mitad = (fondo+tope)/2;
      if(source[ind_mitad] > num){
        auxBusqBinaria(source, num, fondo, ind_mitad-1);

      }
      else {
        auxBusqBinaria(source, num, ind_mitad+1,tope);
      }
    }
    return ind_mitad;
  }*/
  //Iba a hacerlo recursivo pero despues recorde que es mas facil sin eso.
  int busqBinaria(std::vector<T> &source, T num){
    int fondo, mitad, tope;
    fondo = 0;
    tope = (source.size())-1;

    while(fondo < tope){
      mitad = (fondo+tope)/2;
      if (source[mitad] < num){
        fondo = mitad+1;

      }
      else if (source[mitad] > num){
        tope = mitad-1;
      }
      else{
        return mitad;
      }
    }

    return -1;
  }
};

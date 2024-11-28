//Victor Hugo Lopez Licona
//A01278045
//#include <iostream>
//Crei necesitar <iostream> pero dice en las instrucciones que sin bibliotecas
//extra.
//Se que puede ser un poco complicado pero remplace la "enie" de ni"ni"o con "ni"
template <class T>
class Heap{
private:
  T *data;
  //Utilizamos multiples usingned para evitar que metan indices no validos.
  unsigned int capacidad;
  unsigned int count;
  //Decidi llamar estas funciones: ...ind para indicar que retorna un indice y no el valor.
  unsigned int parent_ind(unsigned int) const; //Voy marcando con comentarios las que ya hice para no perderme.
  unsigned int left_ind(unsigned int) const; //
  unsigned int right_ind(unsigned int) const; //
  void swap(unsigned int, unsigned int);//
  void heapify (unsigned int); //

public:

  Heap(unsigned int); //
  ~Heap(); //
  unsigned int size();
  bool empty() const;//
  bool full() const;//
  void push(T);
  void clear();//
  //La clear la puse por si a caso a pesar de que no viene en las pruebas ni
  //se usa para implementar ninguna otra funcion.
  void pop();
  T top();
  std::string toString() const;
};

template <class T>
//Esta crei enganiosamente que me pedia la capacidad, pero quiere el numero de
//elementos que hay en el heap.
Heap<T>::Heap(unsigned int tamanio){
  capacidad = tamanio;
  data = new T[tamanio];
  if (data == 0){
    //throw OutOfMemory();
    //Comente la excepcion debido a que me marcaba error, la reemplace por un return.
    return;
    //Esto se hace para ver si por algun motivo la asignacion de memoria fallo.
    //No es para verificar si se lanzo con tamanio 0, pues el hacer esto causaria
    //un error mas adelante al intentar aniadir elementos.
  }
  count = 0;
  //Cuenta de cuantos hemos aniadido en realidad.
}
template <class T>
Heap<T>::~Heap(){
  delete [] data;
  data = 0;
  capacidad = 0;
  count = 0;
  //En teoria es opcional lo de los indices, ya que esta vacio pero es mejor asegurarse.
}
template <class T>
unsigned int Heap<T>::size(){
  return count;
}
template <class T>
unsigned int Heap<T>::parent_ind(unsigned int ind_hijo) const{

  return (ind_hijo-1)/2;
}

template <class T>
unsigned int Heap<T>::left_ind(unsigned int ind_padre) const{

  return (ind_padre*2)+1;
}

template <class T>
unsigned int Heap<T>::right_ind(unsigned int ind_padre) const{
  return (ind_padre*2)+2;
}

template <class T>
void Heap<T>::clear(){
  count = 0;

}
template <class T>
bool Heap<T>::empty() const{
  return (count==0);
  //Usamos el numero de elementos aniadidos y no la capacidad o tamanio.
  //Simplificacion de un if.
}
template <class T>
bool Heap<T>::full() const{
  return (count == capacidad);
  //Vemos si el numero de aniadidos es igual a la capacidad.
}
template <class T>
void Heap<T>::swap(unsigned int a, unsigned int b){
  T aux = data[a];
  data[a] = data[b];
  data[b] = aux;
}
template <class T>
void Heap<T>::heapify(unsigned int pos){
  unsigned left = left_ind(pos);
  unsigned right = right_ind(pos);
  unsigned ind_min_num = pos;
  if(left <= count && data[ind_min_num] > data[left]){
    ind_min_num = left;
  }
  if(right <= count && data[ind_min_num] > data[right]){
    ind_min_num = right;
  }
  if (ind_min_num != pos){
    //Si min de hecho ya es min, quiere decir que terminamos.
    swap(ind_min_num,pos);
    heapify(ind_min_num);
    //Llamamos con min en vez de pos para que siga recorriendo en vez de atascarse
    //hasta arriba.
  }
}
template <class T>
void Heap<T>::push(T valor){
  if (full()){
    //Ahora que lo pienso, pude simplemente poner lo que puse en el full en ese
    //parentesis...
    //throw Overflow();
    return;
  }
  unsigned int pos;
  pos = count++;
  //Le doy la posicion actual de count que sera la posicion donde se insertara en
  //caso de ser mayor que su padre y sumo a count para actualizar el numero de
  //elementos en el heap.
  while(pos > 0 && valor < data[parent_ind(pos)]){
    data[pos] = data[parent_ind(pos)];
    pos = parent_ind(pos);

  }
  data[pos] = valor;
}

template <class T>
void Heap<T>::pop(){
  if (empty()){
    //throw NoSuchElement();
    return;
  }

  data[0] = data[--count];
  heapify(0);


}
template <class T>
T Heap<T>::top(){
  //Se refiere a que quiere el que esta en la cima y que se borre o solo el que esta ahi?
  if (empty()){
    //throw NoSuchElement();
    //Debo de definir yo mismo las excepciones? que debo hacer cuando no se cumple
    //si espera recibir un dato a cambio.
    return -1 ;
  }
  //T aux = data[0];
  //pop();
  /*Inicialmente creia que top iba a trabajar enviando el elemento que estaba
  en la raiz y eliminarlo,reacomodar,etc; pero solo tiene que enviarlo.
  */


  //return aux;
  return data[0];
}

template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;
	aux << "[";	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} aux << data[i];
	} aux << "]";
	return aux.str();
}

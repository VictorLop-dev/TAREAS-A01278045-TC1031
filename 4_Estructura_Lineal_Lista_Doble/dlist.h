//Victor Hugo Lopez Licona
//A01278045
template <class T> class DList;

template <class T>
class DLink{
private:
  DLink(T val):valor(val),anterior(0),posterior(0){};

  T valor;
  DLink<T> *anterior;
  DLink<T> *posterior;

  friend class DList<T>;


};

template <class T>
class DList {
private:
  DLink<T> *cabeza;
  DLink<T> *cola;
  int tamanio;
  //Podria ser unsigned.
public:
  DList():tamanio(0),cabeza(0),cola(0){}
  ~DList(){
    DLink<T> *p, *q;

  	p = cabeza;
  	while (p != 0) {
  		q = p->posterior;
  		delete p;
  		p = q;
  	}
  	cabeza = 0;
  	cola = 0;
  	tamanio = 0;
  }
  void insertion(T);
  std::string toStringForward() const;
  std::string toStringBackward() const;
  int search(T);
  void update(int,T);
  void deleteAt(int);

};

template <class T>
void DList<T>::insertion(T val){
  DLink<T> *nuevoLink = new DLink<T>(val);
  if (nuevoLink == 0){
    return;
    //No puedo usar excepciones...
  }
  if(cabeza == 0 && cola == 0){
    cabeza = nuevoLink;
    cola = nuevoLink;
  }
  else{
    cola->posterior = nuevoLink;
    //Cola pasara a ser el penultimo.
    nuevoLink->anterior = cola;
    cola = nuevoLink;
  }
  tamanio++;

}




template <class T>
int DList<T>::search(T val){
  DLink<T> *p = cabeza;
  int pos = 0;
  //Pos es el indice (inicia desde 0).

  while (p != 0){
    if(p->valor == val){
      return pos;
    }
    p = p->posterior;
    pos++;
  }
  return -1;
}

template <class T>
void DList<T>::update(int indice, T val){
  if (indice < 0 || indice >= tamanio){
    return;
  }
  /*Para aprovechar aun mas y no solo en dos funciones la estructura de listas
  dobles y por cierto masoquismo, quise hacer dos formas de cambiar el valor
  para hacerlo de la manera mas rapida posible, en teoria.
  */
  DLink<T> *p;
  if (indice <= ((tamanio-1)-indice) ){
    p = cabeza;
    int pos = 0;
    //Pos es el indice (inicia desde 0).

    while (pos != indice){
      p = p->posterior;
      pos++;
    }

  }
  else {
    p = cola;
    int pos = tamanio-1;
    while (pos != indice){
      p = p->anterior;
      pos--;
    }

  }
  p->valor = val;

}

/*template <class T>
void DList<T>::deleteAt(int indice){
  //Hago doble verificacion por si olvide actualizar el tamanio.
  if (indice < 0 || indice >= tamanio || (cabeza == 0 && cola == 0)){
    return;
  }
  //Aqui iba a hacer algo similar al anterior pero ya va a amanecer, asi que
  //me arrepenti.
  DLink<T> *p = cabeza;
  int pos = 0;
  while (pos != indice){
    pos++;
    p = p->posterior;
  }
  p->anterior->posterior = p->posterior;
  if (p->posterior != 0){
    p->posterior->anterior = p->anterior;
  }

  if(p->anterior == 0 && p->posterior !=0){
    cabeza = p->posterior;
  }
  else if(p->posterior == 0 && p->anterior != 0){
    cola = p->anterior;
  }
  else{
    cola =0;
    cabeza = 0;
  }
  tamanio--;
  delete p;
}*/

template <class T>
void DList<T>::deleteAt(int indice) {
  //Doble verificacion por si me equivoque al actualizar el tamanio.
  if (indice < 0 || indice >= tamanio || (cabeza == 0 && cola == 0)) {
    return;
  }
  //Aqui iba a hacer algo similar al anterior pero ya va a amanecer, asi que
  //me arrepenti.
  DLink<T>* p = cabeza;
  int pos = 0;


  while (pos != indice) {
    pos++;
    p = p->posterior;
  }
  //Funciona incluso cuando solo hay un elemento.
  // Si el nodo no es la cabeza lo actualizamos.
  if (p->anterior != 0) {
    p->anterior->posterior = p->posterior;
    //Actualiza tanto si es la  cola como si no lo es.
  } else {
    // Si p es la cabeza, actualizamos la cabeza.
    cabeza = p->posterior;
  }

  // Si el nodo no es la cola, actualizamos el nodo posterior.
  if (p->posterior != 0) {
    p->posterior->anterior = p->anterior;
    //En el caso de la cabeza, queda asignado el anterior como 0 correctamente.
  } else {
    // Si p es la cola, actualizamos la cola.
    cola = p->anterior;
  }

  // Reducimos el tamaño y liberamos la memoria del nodo.
  tamanio--;
  delete p;
  //std::cout<<std::endl<<"Nueva cabeza: "<<cabeza->valor<<std::endl;
  //std::cout<<"Nueva cola: "<<cola->valor<<std::endl;
  //Use esos para probar si estaba cambiando bien el valor de la cola y de la
  //cabeza.
}







template <class T>
std::string DList<T>::toStringForward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = cabeza;
	aux << "[";
	while (p != 0) {
		aux << p->valor;
		if (p->posterior != 0) {
			aux << ", ";
		}
		p = p->posterior;
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = cola;
	aux << "[";
	while (p != 0) {
		aux << p->valor;
		if (p->anterior != 0) {
			aux << ", ";
		}
		p = p->anterior;
	}
	aux << "]";
	return aux.str();
}

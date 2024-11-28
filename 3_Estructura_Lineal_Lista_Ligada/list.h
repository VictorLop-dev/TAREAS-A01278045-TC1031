//Victor Hugo Lopez Licona
//A01278045
//#include <iostream>
template <class T> class List;
template <class T>
class Link{
public:
  T value;
  Link<T> *next;
private:
  //T value;
  //Link<T> *next;
  Link(T val):value(val),next(0){}
  Link(T val, Link<T> *sig):value(val),next(sig){}
  Link(const Link<T> &source):value(source.value),next(source.next){}
  friend class List<T>;


};

template <class T>
class List{
private:
  Link<T> *head;
  int size;
public:
  List():size(0),head(0){}
  //No se pedia pero aniadi un destructor por cualquier cosa.
  ~List(){
    Link<T> *p,*q;
  	p=head;
  	while(p != 0){
  		q = p->next;
  		delete p;
  		p = q;
  	}
  	head = 0;
  	size = 0;
  }

  std::string toString() const;
  //Ese const indica que no va a modificar nada en el objeto al que pertenece.
  void insertion(T);
  void update(int,T);
  void deleteAt(int);
  int search(T);
};
template <class T>
void List<T>::insertion(T val){
  //Creo el nodo que voy a insertar.
  Link<T> *newLink = new Link<T>(val);
  if (newLink == 0){
    //Veo si pudo crearlo o no para evitar cambiar el tamanio en vano.
    return;
  }
  if (head == 0){
    head = newLink;
    //std::cout<<std::endl<<head->next<<std::endl;
    //Es el primer nodo?
  }
  else{
    //Apuntador para insertar hasta el final.
    Link<T> *p = head;
    while(p->next != 0){
      p = p->next;
    }
    p->next = newLink;
    //El next de newLink ya apunta a 0
  }



  size++;

}
template <class T>
void List<T>::update(int ind, T val){
  //Link<T> *newLink = new Link<T>(val);
  if(ind < 0 || ind >= size){
    //Verificando indice.
    return;
  }

  Link<T> *iterador = head;
  //Apuntador para encontrar el nodo adecuado.
  int pos = 0;
  while (pos != ind){
    iterador=iterador->next;
    pos++;
  }
  iterador->value = val;
  //Afortunadamente solo hace falta cambiar el valor.
}
template <class T>
int List<T>::search(T val){
  Link<T> *p = head;
  int pos = 0;
  while(p != 0){
    if (p->value == val){
      return pos;
    }
    p = p->next;
    pos++;
    //Bastante parecido al anterior pero sin cambiar el valor.
  }
  //Regresa -1 en caso de que no este en la lista que se busca.
  return -1;
}
template <class T>
void List<T>::deleteAt(int ind){
  //std::cout<<"aaaaaa"<<std::endl;
  //Primero reviso si el indice es valido o no.
  if (ind < 0 || ind >= size){
    return;
  }
  Link<T> *iterador = head;
  //Creo el nodo que me ayudara a llegar al indice que quiero.
  if(ind == 0){
    //Verifico si quiero eliminar la cabeza, ya que eso requiere un proceso
    //distinto.
    head = head->next;
    delete  iterador;
    //El iterador ya apuntaba a la cabeza asi que solo lo borro.
    //Uso delete sin los [] debido a que es solo un elemento.
  }
  else{

    for (int pos = 0; pos < ind-1;pos++){
      //Este for hara que llegue hasta el nodo anterior al que quiero borrar.
      iterador = iterador->next;

    }
    //Creo un apuntador al nodo a borrar.
    Link<T> *nodoABorrar = iterador->next;
    //Hago que el nodo anterior al que borrare apunte al siguiente del que
    //borrare.
    iterador->next = nodoABorrar->next;
    delete nodoABorrar;
    //Borro el nodo que quiero borrar.

  }
  size--;
  //Disminuyo el tamanio, aunque realmente no se use mas que para
  //saber si es un indice valido o no.
}


template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

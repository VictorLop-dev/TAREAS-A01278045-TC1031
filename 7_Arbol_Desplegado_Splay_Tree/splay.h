/*
*  autor: Benjamin Valdes Aguirre
*  fecha: Diciembre 2020
*  programa: act 3.3 Implementacion Splay
*  desc: estos programas son solciones parciales a algunos de
*  las actividades planteadas en el curso TC1031
*
*		Nota: Esta imlpementación es bottom up, no divide al árbol para la operacións
*		de barrado
*/


//Creo que solo faltan por implementar las que vienen en los casos de prueba
//Y ya se incluyen todas las piezas para hacerlo, solo debo definir las
//funciones en node y ver que trabajen bien con las del SplayTree.
#ifndef SplayTree_H_
#define SplayTree_H_

#include <string>
#include <sstream>
#include <iostream>

template <class T> class SplayTree;

template <class T>
class Node {
private:
	T value;
	//Valor del nodo, a veces nombrado como "key"
	Node *left, *right, *parent;
	//Apuntadores a nodos, como izquierda, derecha o al padre.

	Node<T>* succesor();
  //Busca cual sera el sucesor, me parece que solo se usa en remove.
	Node<T>* rot_right(Node<T>*);

	//Las rotaciones son desde la perspectiva del padre.
	Node<T>* rot_left(Node<T>*);

public:
	Node(T);
	/*Constructor donde solo pasamos valor, resulta en un nodo
	que no tiene ningun hijo.*/
	Node(T, Node<T>*, Node<T>* ,Node<T>*);
	//Constructor donde tambien asignamos hijos.
	Node<T>* add(T);
	//Auxiliar de la funcion add del splay tree.
	Node<T>* find(T);
	//Auxiliar de la funcion find del splay tree.
	Node<T>* remove(T);
	//Auxiliar de la funcion remove del splay tree.
	void removeChilds();
	//Funcion auxiliar para el destructor?
	void inorder(std::stringstream&) const;
	//Genera el recorrido en orden?
	void print_tree(std::stringstream&) const;
	void preorder(std::stringstream&) const;
	//Genera el recorrido preorden?
	Node<T>* splay(Node<T>*, Node<T>*);

	friend class SplayTree<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0), parent(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, Node<T> *p)
	: value(val), left(le), right(ri), parent(p) {}

template <class T>
Node<T>* Node<T>::add(T val) {

	if (val < value){
		//En la primera iteracion verifica si raiz es mas grande, en base a eso
		//sigue aplicando recursividad.
		if (left != 0){
			//Nos ayuda a encontrar un posible caso base.
			return left->add(val);
			//Sea cual sea el return que se usara al final, se encadenaran para
			//regresar un apuntador del nuevo valor, el cual se usara el splay.
		}
		else {
			left = new Node <T>(val,0,0,this);
			return left;
		}
	}else {
		if(right != 0){
			return right->add(val);
		}
		else {
			right = new Node<T>(val,0,0,this);
			return right;
		}
		}

	}


template <class T>
Node<T>* Node<T>::find(T val) {
	//Va a regresar o un apuntador al nodo que busco o a donde debia estar.
	if (val == value){
		return this;
	}
	else if(val < value){
		if(left != 0 ){
			//Revisamos si llegamos al limite o si podiamos seguir.
			return left->find(val);
		}
		return this;
	}
	else{
		if(right !=0){
			return right->find(val);
		}
		return this;
	}

}

template <class T>
Node<T>* Node<T>::succesor() {

	Node<T> *le, *ri;

	le = left;
	//No se usa para nada?
	ri = right;


	if (right->left == 0) {
		right = right->right;
		//Como no hay sucesor a la izquierda, entonces el hijo de la derecha
		//es el succesor
		ri->right = 0;
		//Desconectamos de su sucesor a la derecha debido a que lo definiremos
		//fuera de esta funcion en el remove de SplayTree.
		return ri;
	}

	Node<T> *parent, *child;
	//En caso de que si hubiera hijos, buscaremos llegar hasta el extremo
	//viajando en linea recta.
	parent = right;
	child = right->left;
	while (child->left != 0) {
		//Mientras no lleguemos hasta el extremo viajando siempre por la izquierda.
		parent = child;
		child = child->left;
	}
	parent->left = child->right;
	child->right = 0;
	//Desconectamos su hijo de la derecha.
	return child;
}

template <class T>
Node<T>* Node<T>::remove(T val) {
		//std::cout<<"\nremoviendo: "<<val<<"\n";
		bool encontrado = false;
		Node<T>* found = this->find(val);
		//std::cout<<"\n\naaaaa"<<found->value<<"\n\n";
		//Node<T>* root = splay(this,found);
    // Verificar si el valor a eliminar estaba en la lista y por lo tanto
		//ahora en la raiz.

    if (found->value == val) {
			encontrado = true;
        Node<T>* toDelete = found;
				//std::cout<<"\n\neeeeee"<<toDelete->value<<"\n\n";
				//std::cout<<"Bandera\n\n";



				if(found->left&&found->right){
					//Si el nodo a eliminar tiene ambos hijos
					found =toDelete->succesor();
					if (found != 0) {
							found->left = toDelete->left;
							found->right = toDelete->right;
							found->parent = 0;
							if(found->left)
								found->left->parent = found;
							if(found->right)
								found->right->parent = found;
					}

					//delete root;
					//root = succ;
					if(toDelete->parent->left&&
						toDelete->parent->left->value==toDelete->value){
						toDelete->parent->left = found;

					}
					else{
						toDelete->parent->right = found;

					}
				}
				else if(found->right){
					//Si solo tiene el hijo derecho
					found = toDelete->right;
					toDelete->right = 0;

					if(toDelete->parent->left&&
						toDelete->parent->left->value==toDelete->value){
						toDelete->parent->left = found;

					}
					else{
						toDelete->parent->right = found;

					}


				}
				else if(found->left){
					//std::cout<<"\n\nCaso correcto\n\n";
					//Si solo tiene el hijo izquierdo
					found = toDelete->left;
					//std::cout<<"\n\nNodo raiz = "<<found->value<<"\n\n";
					toDelete->left = 0;
					if(toDelete->parent->left&&
						toDelete->parent->left->value==toDelete->value){

						//std::cout<<"\n\nConfirmamos que era hijo izq\n\n";
						toDelete->parent->left = found;
					}
					else{
						toDelete->parent->right = found;
					}

				}
				else{
					//Si no tiene ningun hijo
					if(toDelete->parent->left&&
						toDelete->parent->left->value==toDelete->value){
						toDelete->parent->left = 0;
					}
					else{
						toDelete->parent->right = 0;
					}

				}
				if(toDelete->parent->right != 0 || toDelete->parent->left != 0){
					found->parent = toDelete->parent;
				}
				toDelete->parent = 0;



				delete toDelete;
				//found = 0;
				}

        // Caso 1: No tiene hijo izquierdo
        /*if (succ->left == 0) {

            if (root != 0) {
                root->parent = 0;
            }
        }
        // Caso 2: No tiene hijo derecho
        else if (root->right == 0) {
            root = root->left;
            if (root != 0) {
                root->parent = 0;
            }
        }*/



          //  succ->left = found->left;
            //if (found->left != 0) {
              //  found->left->parent = succ;
            //}
            //
            //if (succ != 0) {
                //root->parent = 0;
            //}

         // Eliminar el nodo
				 //std::cout<<"\n\nNodo devuelto: "<<found->value<<"\n\n";
		//Debes regresar el padre para hacer splay sobre el.
	//	std::cout<<"\nComparando value: "<<found->value<<" con val: "<<val<<"\n";
		//return found->parent;
		if(encontrado){
			//std::cout<<"\nSalida con coincidencia\n";
			return found->parent;
		}
		else{
			//std::cout<<"\nSalida sin coincidencia\n";
			return found;
		}
		//return found->parent;
			//Me preocupa que pueda pasar cuando no es el valor que buscaba.
		  // "Devolver la nueva raíz después de la eliminación"
}
  // Devolver la nueva raíz después de la eliminación


template <class T>
void Node<T>::removeChilds() {
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* x){
	//std::cout<<"\nHaciendo zig con "<<x->value<<"\n";
	//std::cout<<"\n\n"<<splay&.print_tree()<<"\n\n";
	Node<T> *y = x->left;
	x->left = y->right;
	if(y->right)
		y->right->parent = x;
	y->right = x;
	// enlace de y con el padre de x
	y->parent = x->parent;
	x->parent = y;
	// hace enlace del padre de x a y
	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::rot_left(Node<T>* x){
	//std::cout<<"\nHaciendo zag con "<<x->value<<"\n";
	//std::cout<<"\n\n"<<splay&.print_tree()<<"\n\n";
	Node<T> *y = x->right;
	x->right = y->left;
	if(y->left)
		y->left->parent = x;
	y->left = x;
	// enlace de y con el padre de x
	y->parent = x->parent;
	x->parent = y;
	// hace enlace del padre de x a y
	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
	while(x->parent != 0){
    //Mientras no lleguemos a la raiz.
		if(x->parent->value == root->value){
      //Aqui notamos que estamos justo debajo de la raiz.
			if(x->parent->left && x->parent->left->value == x->value){
        //Usamos el valor booleano del puntero para ver si apunta a la nada o a
        //un hijo, que luego verificamos si es x.
        //Ya sabemos que es hijo directo, esto revisa cual de ambos.
				rot_right(x->parent);
        //Resulta ser el izquierdo.
			}else{
				rot_left(x->parent);
        //Es el derecho.
        //Es confuso, yo aprendi a rotar con el nodo a hacer splay como inicio.
        //no con el padre de este.
			}
		}else{
			Node<T>*p = x->parent; // parent
			Node<T>*g = p->parent; // granparent
			if(p->left && g->left &&
				x->value == p->left->value && p->value == g->left->value){
        //Verifica si pueden avanzar de dos en dos revisando si el padre y
        //abuelo tienen hijos en la izquierda, los cuales usara el nodo que
        //estamos subiendo para avanzar.
				rot_right(g);
				rot_right(p);
			}else if(p->right && g->right &&
				x->value == p->right->value && p->value == g->right->value){
        //Lo mismo pero del otro lado, no tener el caso anterior no implica
        //que forzosamente tengamos este, por eso hay que verificar.
				rot_left(g);
				rot_left(p);
			}else	if(p->left && g->right &&
				x->value == p->left->value && p->value == g->right->value){
				rot_right(p);
				rot_left(g);
			}else{
				rot_left(p);
				rot_right(g);
			}
		}
	}
	return x;
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void Node<T>::print_tree(std::stringstream &aux) const {
	if (parent != 0){
		aux << "\n node " << value;
		aux << " parent " << parent->value;
	}else
		aux << "\n root " << value;
	if (left != 0)
		aux << " left " << left->value;
	if (right != 0)
		aux << " right " << right->value;
	aux << "\n";

	if (left != 0) {
		left->print_tree(aux);
	}
	if (right != 0) {
		right->print_tree(aux);
	}
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
class SplayTree {
private:
	Node<T> *root;

public:
	SplayTree();
	~SplayTree();
	bool empty() const;
	void add(T);
	bool find(T);
	void remove(T);
	void removeAll();
	std::string inorder() const;
	std::string print_tree() const;
	std::string preorder() const;
};

template <class T>
SplayTree<T>::SplayTree() : root(0) {}

template <class T>
SplayTree<T>::~SplayTree() {
	removeAll();
}

template <class T>
bool SplayTree<T>::empty() const {
	return (root == 0);
}

template<class T>
void SplayTree<T>::add(T val) {

	if (root != 0) {
			Node<T>* added = root->add(val);
			root = root->splay(root,added);
	} else {
		root = new Node<T>(val);
	}
}

template <class T>
void SplayTree<T>::remove(T val) {
	if (root != 0) {
		if (val == root->value) {
			Node<T> *succ = root->succesor();
			if (succ != 0) {
					succ->left = root->left;
					succ->right = root->right;
					succ->parent = 0;
					if(succ->left)
					//Crei que estaban mal, pero es como decir: si existe hijo izq.
					//Y esto es lo que tiene que hacer en caso de que si.
						succ->left->parent = succ;
					if(succ->right)
					//Lo mismo con la derecha.
						succ->right->parent = succ;
			}
			delete root;
			root = succ;
		} else {
			Node<T>* p = root->remove(val);
			root = root->splay(root,p);
		}
	}
}

template <class T>
void SplayTree<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;

}

template <class T>
bool SplayTree<T>::find(T val){
	if (root != 0) {
		Node<T>* found = root->find(val);
		root = root->splay(root,found);
		return (root->value == val);
	} else {
		return false;
	}
}

template <class T>
std::string SplayTree<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string SplayTree<T>::print_tree() const {
	std::stringstream aux;

	aux << "\n ================================ ";
	if (!empty()) {
		root->print_tree(aux);
	}
	aux << " ================================ \n";
	return aux.str();
}



template <class T>
std::string SplayTree<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

#endif /* SplayTree_H_ */

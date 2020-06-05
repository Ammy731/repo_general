/* Desarrollar un mantenimiento utilizando listas doblemente ligadas (insertar, modificar, eliminar,
buscar, mostrar en orden ascendente y descendente por una llave principal). 
La entidad a mantener puede ser seleccionada de forma libre por usted.  
Por ejemplo, mantenimento de estudiantes, o materias, o productos, o vehículos, etc.*/

//Autores: Amanda Roldan, Steven Paguay;
#include <iostream>
using namespace std;

class  nodo
{
	public:
	 nodo(int dato, string nombre, string carrera, nodo *sig=NULL, nodo *ant=NULL) :
	 datoA(dato), nombreA(nombre), carreraA(carrera), siguiente(sig), anterior(ant) {}
	
	private:
	 int datoA;
	 string nombreA;
	 string carreraA;
	 nodo *siguiente;
	 nodo *anterior;
	friend class Estudiante;
};

class Estudiante
{
	public: 
	 Estudiante() {cabecera=actual=final=NULL;}
	 ~Estudiante();

	 void InsertarInicio(int dato, string nombre, string carrera);
	 void Insertar(int dato, string nombre, string carrera);
	 void Eliminar(int dato, string nombre, string carrera);
	 void Mostrar(bool aux);
	 void Buscar(int dato, string nombre, string carrera);
	 void Modificar(int dato, string nombre, string carrera, string ndat);
	private:
	 nodo *cabecera;
	 nodo *actual;
	 nodo *final;
};

 Estudiante:: ~Estudiante(){ //destructor
	nodo *aux;
	while(cabecera){
		aux=cabecera;
		cabecera=cabecera->siguiente;
		delete aux;
	}
	actual=NULL;
}

void Estudiante::InsertarInicio(int dato, string nombre, string carrera){
	nodo *nuevo;
	nuevo=new nodo (dato, nombre, carrera);
	nuevo->siguiente=cabecera;
	cabecera=nuevo;
	final=nuevo;
}

void Estudiante:: Insertar(int dato, string nombre, string carrera){
	nodo *nuevo;
	nuevo=new nodo(dato, nombre, carrera);

	nodo *actual; actual=cabecera;
	nodo *atras; atras=NULL;

	bool aux=true;
	if(nuevo->datoA<actual->datoA){
		nuevo->siguiente=actual;
		actual->anterior=nuevo;
		cabecera=nuevo;
		aux=false;
	}
	while(actual!=NULL&&aux==true){ //insertar en medio
		if(actual->datoA>nuevo->datoA){
			nuevo->siguiente=actual;
			nuevo->anterior=atras;
			atras->siguiente=nuevo;
			actual->anterior=nuevo;
			aux=false;
		}
		if(actual->siguiente==NULL&&aux==true){ //insertar final
			actual->siguiente=nuevo;
			nuevo->anterior=actual;
			aux=false;
			final=nuevo; 
		}
		atras=actual;
		actual=actual->siguiente;
	}
 }

void Estudiante::Mostrar(bool aux){
	nodo *actual;
	cout<<"****LISTA DE INTEGRANTES****"<<endl;
	if(aux==true){ //ascendente
		actual=cabecera;
		while(actual!=NULL){
			cout<<" Codigo: "<<actual->datoA<<endl;
			cout<<" Nombre: "<<actual->nombreA<<endl;
			cout<<" Carrera: "<<actual->carreraA<<endl;
			cout<<"....................................."<<endl;
			actual=actual->siguiente;
		}
	}else{ //descendente
		actual=final;
		while(actual!=NULL){
			cout<<" Codigo: "<<actual->datoA<<endl;
			cout<<" Nombre: "<<actual->nombreA<<endl;
			cout<<" Carrera: "<<actual->carreraA<<endl;
			cout<<"....................................."<<endl;
			actual=actual->anterior;
		}
	}
}

void Estudiante::Eliminar(int dato, string nombre, string carrera){
	nodo *nuevo;
	nuevo=new nodo(dato, nombre, carrera);

	nodo *actual; actual=cabecera;
	nodo *atras; atras=NULL;
	nodo *ax; ax=NULL;

	bool aux=false;
	if(nuevo->datoA==actual->datoA){
		cabecera=actual->siguiente;
		actual->siguiente->anterior=NULL;
		aux=true;
	}
	while(actual!=NULL&&aux==false){
		if(actual->datoA==nuevo->datoA){
			ax=actual;
			atras->siguiente=ax->siguiente;
			if(ax->siguiente!=NULL){
				actual->siguiente->anterior=atras;
			}
			if(ax->siguiente==NULL){
				final=atras;
			}
			actual->siguiente=NULL;
			actual->anterior=NULL;
			aux=true;
		}
		atras=actual;
		actual=actual->siguiente;
	}
	delete ax;
 } 

void Estudiante::Buscar(int dato, string nombre, string carrera){
	nodo *actual; actual=cabecera;
	nodo *nuevo;
	nuevo=new nodo(dato, nombre, carrera);

	while(actual!=NULL){
		if(actual->datoA==nuevo->datoA){
			cout<<"...................................."<<endl;
			cout<<"Codigo: #"<<actual->datoA<<endl;
			cout<<"Nombre: "<<actual->nombreA<<endl;
			cout<<"Carrera: "<<actual->carreraA<<endl;
			cout<<"...................................."<<endl;
		}
		actual=actual->siguiente;
	}
	delete nuevo;
 }

void Estudiante::Modificar(int dato, string nombre, string carrera, string ndat){
	nodo *actual;
	actual=cabecera;
	
	nodo *nuevo;
	nuevo=new nodo(dato, nombre, carrera);
	
	while(actual!=NULL){
		if(actual->nombreA == nuevo->nombreA){
			actual->nombreA=ndat;
		}
		actual=actual->siguiente;
	}
	delete nuevo;
}

int main(){

	Estudiante  EstLista;
	int op, num, dato;
	string nombre, carrera, ndat; 
	bool aux=true, aux2; 
	cout<<"Lista de Estudiantes pertenecientes a un Club Universitario."<<endl;
	do{
		cout<<"*** M E N U ***"<<endl;
		cout<<"[1].Ingresar."<<endl;
		cout<<"[2].ELiminar."<<endl;
		cout<<"[3].Buscar."<<endl;
		cout<<"[4].Modificar."<<endl;
		cout<<"[5].Mostrar."<<endl;
		cout<<"[6].Salir."<<endl;
		cout<<"****************"<<endl;
		cout<<"Su opcion-> "; cin>>op;
		cout<<endl;
		switch (op)
		{
		case 1:
			if(aux==true){
				cout<<"Ingrese codigo: "; cin>>dato;
				cout<<"Ingrese nombre: "; cin>>nombre;
				cout<<"Ingrese carrera: ";cin>>carrera;
				EstLista.InsertarInicio(dato, nombre, carrera);
				aux=false;
			}else{
				cout<<"Ingrese codigo: "; cin>>dato;
				cout<<"Ingrese nombre: ";cin>>nombre;
				cout<<"Ingrese carrera: "; cin>>carrera;
				EstLista.Insertar(dato, nombre, carrera);
			} 	cout<<endl;
		break;
		case 2:
			cout<<"Ingrese codigo que desea eliminar: "<<endl;
			cin>>dato;;
			EstLista.Eliminar(dato, nombre, carrera);
			cout<<endl;
			cout<<"ELiminado correctamete..."<<endl;
			cout<<endl;
		break;
		case 3:
			cout<<"Ingrese codigo que desea buscar: "<<endl;
			cin>>dato;
			EstLista.Buscar(dato, nombre, carrera);
			cout<<endl;
		break;
		case 4:
			cout<<"Ingrese el nombre que desea cambiar: ";cin>>nombre;
			EstLista.Buscar(dato, nombre, carrera);
			cout<<endl;
			cout<<"Ingrese el nuevo nombre: "; cin>> ndat;
			EstLista.Modificar(dato, nombre, carrera, ndat);
			cout<<endl;
			cout<<"Cambio realizado."<<endl;
			cout<<endl;
		break;
		case 5:
			aux2=true;
			cout<<"[1].Mostrar en forma ascendente"<<endl;
			cout<<"[2].Mostrar en forma descendente"<<endl;
			cout<<"Su opcion-> "; cin>>num;
			if(num==2){
				aux2=false;
			}
			cout<<endl;
			EstLista.Mostrar(aux2);
			cout<<endl;
		break;
		default:
			cout<<"Por favor, ingrese una opcion correcta."<<endl;
		break;
		}
	}while(op!=6);
	cin.get();
	return 0;
}













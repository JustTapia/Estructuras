#include <iostream>
#include <string>
#include <string.h>
#include<fstream>
#include <cstdio>
#include <thread>
#include<fstream>
#include <chrono>
#include <mutex>
#include <conio.h>
#include <windows.h>
using namespace std;

class Estudiante {
public:
	Estudiante(string pCarnet, string pCarrera, string pNombre, string pDireccion, string pTelefono) {
		carnet = pCarnet;
		carrera = pCarrera;
		nombre = pNombre;
		direccion = pDireccion;
		telefono = pTelefono;
		siguiente = NULL;
		anterior = NULL;
	}

private:
	string carnet;
	string carrera;
	string nombre;
	string direccion;
	string telefono;
	Estudiante *siguiente;
	Estudiante *anterior;

	friend class ListaEstudiantes;
	friend class ListaCarreras;
	friend class Cola;
};
typedef Estudiante *pEstudiante;

class ListaEstudiantes {
public:
	ListaEstudiantes() { primero = actual = NULL; };
	void leerEstudiante(string txt);
	string buscarCarrera(string codigo);
	string obtenerDatos(string codigo);
	string devolverEstudiantesCarrera(string codCarrera);
	bool ListaVacia() { return primero == NULL; };
private:
	pEstudiante primero;
	pEstudiante actual;
	friend class ListaCarreras;
	friend class Cola;
};

void ListaEstudiantes::leerEstudiante(string txt) {
	ifstream archivo;
	string texto;
	archivo.open(txt, ios::in);
	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo\n";
		system("pause");
		exit(1);
	}
	while (!archivo.eof()) {
		getline(archivo, texto);
		string datos[5];
		int actual = 0;
		for (int i = 0; i != texto.length(); i++) {
			if (texto[i] == ';') {
				actual++;
				i++;
			}
			datos[actual] += texto[i];
		}
		if (ListaVacia())
		{
			primero = new Estudiante(datos[0], datos[1], datos[2], datos[3], datos[4]);
			primero->anterior = primero;
			primero->siguiente = primero;
		}
		else
		{
			pEstudiante nuevo = new Estudiante(datos[0], datos[1], datos[2], datos[3], datos[4]);
			nuevo->anterior = primero->anterior;
			nuevo->siguiente = primero->anterior->siguiente;
			primero->anterior->siguiente = nuevo;
			primero->anterior = nuevo;
		}
	}
	archivo.close();
};
typedef ListaEstudiantes *pListaEstudiantes;

string ListaEstudiantes::buscarCarrera(string codigo) {
	pEstudiante aux = primero;
	while (aux->siguiente != primero) {
		if (aux->carnet == codigo) {
			return aux->carrera;
		}
		aux = aux->siguiente;
	}
	if (aux->carnet == codigo) {
		return aux->carrera;
	}
	return "";
}

string ListaEstudiantes::obtenerDatos(string codigo) {
	string datos = "";
	pEstudiante aux = primero;
	while (aux->siguiente != primero) {
		if (aux->carnet == codigo) {
			datos += aux->nombre;
			datos += ";";
			datos += aux->carnet;
			datos += ";";
			datos += aux->telefono;
			datos += ";";
			datos += aux->direccion;
			return datos;
		}
		aux = aux->siguiente;
	}
	if (aux->carnet == codigo) {
		datos += aux->nombre;
		datos += ";";
		datos += aux->carnet;
		datos += ";";
		datos += aux->telefono;
		datos += ";";
		datos += aux->direccion;
		return datos;
	}
	return datos;
}

string ListaEstudiantes::devolverEstudiantesCarrera(string codCarrera) {
	string estudiantes = "";
	pEstudiante aux = primero;
	while (aux->siguiente != primero) {
		if (aux->carrera == codCarrera) {
			estudiantes += "-";
			estudiantes += aux->nombre;
			estudiantes += ";";
			estudiantes += aux->carnet;
			estudiantes += "\n";
		}
		aux = aux->siguiente;
	}
	if (aux->carrera == codCarrera) {
		estudiantes += "-";
		estudiantes += aux->nombre;
		estudiantes += ";";
		estudiantes += aux->carnet;
		estudiantes += "\n";
	}
	return estudiantes;
}

class Profesor {
public:
	Profesor(string pCodigo, string pCarrera, string pCategoria, string pNombre) {
		codigo = pCodigo;
		carrera = pCarrera;
		categoria = pCategoria;
		nombre = pNombre;
		siguiente = NULL;
		anterior = NULL;
	}

private:
	string codigo;
	string carrera;
	string categoria;
	string nombre;
	Profesor *siguiente;
	Profesor *anterior;

	friend class ListaProfesores;
	friend class Cola;
};
typedef Profesor *pProfesor;

class ListaProfesores {
public:
	ListaProfesores() { primero = actual = NULL; };
	void leerProfesor(string txt);
	bool ListaVacia() { return primero == NULL; };
	bool buscarProfesor(string codigo);
	string getNombre(string codigo);
	void crearReporte();
	void crearReporteServicio();
	string devolverProfesoresCarrera(string codCarrera);
private:
	pProfesor primero;
	pProfesor actual;

	friend class ListaCarreras;
	friend class Cola;
};
typedef ListaProfesores *pListaProfesores;

void ListaProfesores::leerProfesor(string txt) {
	ifstream archivo;
	string texto;
	archivo.open(txt, ios::in);
	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo\n";
		system("pause");
		exit(1);
	}
	while (!archivo.eof()) {
		getline(archivo, texto);
		string datos[4];
		int actual = 0;
		for (int i = 0; i != texto.length(); i++) {
			if (texto[i] == ';') {
				actual++;
				i++;
			}
			datos[actual] += texto[i];
		}
		if (ListaVacia())
		{
			primero = new Profesor(datos[0], datos[1], datos[2], datos[3]);
			primero->anterior = primero;
			primero->siguiente = primero;
		}
		else
		{
			pProfesor nuevo = new Profesor(datos[0], datos[1], datos[2], datos[3]);
			nuevo->anterior = primero->anterior;
			nuevo->siguiente = primero->anterior->siguiente;
			primero->anterior->siguiente = nuevo;
			primero->anterior = nuevo;
		}
	}
	archivo.close();
};

bool ListaProfesores::buscarProfesor(string codigo) {
	bool encontrado = false;
	pProfesor aux = primero;
	while (aux->siguiente != primero) {
		if (codigo == aux->codigo) {
			encontrado = true;
		}
		aux = aux->siguiente;
	}
	if (codigo == aux->codigo) {
		encontrado = true;
	}
	return encontrado;
}

string ListaProfesores::getNombre(string pCodigo) {
	pProfesor aux = primero;
	while (aux->siguiente != primero) {
		if (aux->codigo == pCodigo) {
			return aux->nombre;
		}
		aux = aux->siguiente;
	}
	if (aux->codigo == pCodigo) {
		return aux->nombre;
	}
	else {
		return "";
	}
}

void ListaProfesores::crearReporte() {
	string reporte = "";
	pProfesor aux = primero;
	while (aux->siguiente != primero) {
		reporte += aux->nombre;
		reporte += "\nCodigo: ";
		reporte += aux->codigo;
		reporte += "\nCarrera: ";
		reporte += aux->carrera;
		reporte += "\nCategoría: ";
		if (aux->categoria == "1") {
			reporte += "Enseñanza";
		}
		else {
			reporte += "Servicio";
		}
		reporte += "\n-------------------------------------\n";
		aux = aux->siguiente;
	}
	reporte += aux->nombre;
	reporte += "\nCodigo: ";
	reporte += aux->codigo;
	reporte += "\nCarrera: ";
	reporte += aux->carrera;
	reporte += "\nCategoría: ";
	if (aux->categoria == "1") {
		reporte += "Enseñanza";
	}
	else {
		reporte += "Servicio";
	}
	ofstream archivoReporte;
	archivoReporte.open("Reporte de Profesores.txt");
	archivoReporte << reporte;
	archivoReporte.close();
}

void ListaProfesores::crearReporteServicio() {
	string reporte = "";
	pProfesor aux = primero;
	while (aux->siguiente != primero) {
		if (aux->categoria == "2") {
			reporte += aux->nombre;
			reporte += "\nCodigo: ";
			reporte += aux->codigo;
			reporte += "\nCarrera: ";
			reporte += aux->carrera;
			reporte += "\n-------------------------------------\n";
		}
		aux = aux->siguiente;
	}
	if (aux->categoria == "2") {
		reporte += aux->nombre;
		reporte += "\nCodigo: ";
		reporte += aux->codigo;
		reporte += "\nCarrera: ";
		reporte += aux->carrera;
	}
	ofstream archivoReporte;
	archivoReporte.open("Reporte Profesores de Servicio.txt");
	archivoReporte << reporte;
	archivoReporte.close();
}

string ListaProfesores::devolverProfesoresCarrera(string codCarrera) {
	string profesores = "";
	pProfesor aux = primero;
	while (aux->siguiente != primero) {
		if (aux->carrera == codCarrera) {
			profesores += "-";
			profesores += aux->nombre;
			profesores += ";";
			profesores += aux->codigo;
			profesores += "\n";
		}
		aux = aux->siguiente;
	}
	if (aux->carrera == codCarrera) {
		profesores += "-";
		profesores += aux->nombre;
		profesores += ";";
		profesores += aux->codigo;
		profesores += "\n";
	}
	return profesores;
}

class CursoEstudiante {//Arbol  AA
public:
	CursoEstudiante(string pIdent, string pCodCurso, string pCodGrupo) {
		ident = pIdent;
		codCurso = pCodCurso;
		codGrupo = pCodGrupo;
		congelado = false;
	}
private:
	string ident;
	string codCurso;
	string codGrupo;
	bool congelado;
	CursoEstudiante *siguiente;
	CursoEstudiante *anterior;

	friend class Curso;
	friend class Carrera;
	friend class ListaCarreras;
	friend class Grupo;
	friend class Cola;
};
typedef CursoEstudiante *pCursoEstudiante;

class Grupo {
public:
	Grupo(string pCarrera, string pCurso, string pCodigo, string pProfesor, string pCupos, string pMatriculados, string pCongelados) {
		carrera = pCarrera;
		curso = pCurso;
		codigo = pCodigo;
		profesor = pProfesor;
		cupos = stoi(pCupos);
		matriculados = stoi(pMatriculados);
		congelados = stoi(pCongelados);
		desmatriculados = 0;
	}
	bool listaVacia() { return primerEstudiante == NULL; };
	void insertarEstudiante(string datos[]);
	void matricular(string datos[]);
	void desmatricular(string datos[]);
	void congelar(string datos[]);

private:
	string carrera;
	string curso;
	string codigo;
	string profesor;
	int cupos;
	int matriculados;
	int congelados;
	int desmatriculados;
	mutex atencion;
	pCursoEstudiante primerEstudiante;
	Grupo *siguiente;
	Grupo *anterior;

	friend class Curso;
	friend class Carrera;
	friend class ListaCarreras;
	friend class Cola;
};
typedef Grupo *pGrupo;

void Grupo::insertarEstudiante(string datos[]) {
	if (matriculados - congelados - desmatriculados < cupos) {
		if (listaVacia()) {
			primerEstudiante = new CursoEstudiante(datos[0], datos[1], datos[2]);
			primerEstudiante->anterior = primerEstudiante;
			primerEstudiante->siguiente = primerEstudiante;
			matriculados++;
		}
		else {
			pCursoEstudiante aux = primerEstudiante;
			bool estudianteNuevo = true;
			while (aux->siguiente != primerEstudiante) {
				if (datos[0] == aux->ident) {
					estudianteNuevo = false;
					break;
				}
				aux = aux->siguiente;
			}
			if (datos[0] == aux->ident) {
				estudianteNuevo = false;
			}
			if (estudianteNuevo) {
				pCursoEstudiante nuevo = new CursoEstudiante(datos[0], datos[1], datos[2]);
				nuevo->anterior = primerEstudiante->anterior;
				nuevo->siguiente = primerEstudiante->anterior->siguiente;
				primerEstudiante->anterior->siguiente = nuevo;
				primerEstudiante->anterior = nuevo;
				matriculados++;
			}
		}
	}
}

void Grupo::matricular(string datos[]) {
	atencion.lock();
	if (listaVacia()) {
		primerEstudiante = new CursoEstudiante(datos[0], datos[1], datos[2]);
		primerEstudiante->anterior = primerEstudiante;
		primerEstudiante->siguiente = primerEstudiante;
		matriculados++;
	}
	else {
		pCursoEstudiante aux = primerEstudiante;
		bool estudianteNuevo = true;
		while (aux->siguiente != primerEstudiante) {
			if (datos[0] == aux->ident) {
				estudianteNuevo = false;
				break;
			}
			aux = aux->siguiente;
		}
		if (datos[0] == aux->ident) {
			estudianteNuevo = false;
		}
		if (estudianteNuevo) {
			pCursoEstudiante nuevo = new CursoEstudiante(datos[0], datos[1], datos[2]);
			nuevo->anterior = primerEstudiante->anterior;
			nuevo->siguiente = primerEstudiante->anterior->siguiente;
			primerEstudiante->anterior->siguiente = nuevo;
			primerEstudiante->anterior = nuevo;
			matriculados++;
		}
	}
	atencion.unlock();
}

void Grupo::desmatricular(string datos[]) {
	atencion.lock();
	if (!listaVacia()) {
		pCursoEstudiante aux = primerEstudiante;
		if (datos[0] == aux->ident && aux->congelado == false) {
			aux->siguiente->anterior = aux->anterior;
			aux->anterior->siguiente = aux->siguiente;
			primerEstudiante = aux->siguiente;
			delete aux;
			desmatriculados++;
		}else {
			aux = aux->siguiente;
			while (aux != primerEstudiante) {
				if (datos[0] == aux->ident && aux->congelado == false) {
					aux->siguiente->anterior = aux->anterior;
					aux->anterior->siguiente = aux->siguiente;
					delete aux;
					desmatriculados++;
					break;
				}
				aux = aux->siguiente;
			}
		}
	}
	atencion.unlock();
}

void Grupo::congelar(string datos[]) {
	pCursoEstudiante aux = primerEstudiante;
	if (!listaVacia()) {
		while (aux->siguiente != primerEstudiante) {
			if (datos[0] == aux->ident) {
				aux->congelado = true;
				congelados++;
				break;
			}
			aux = aux->siguiente;
		}
		if (datos[0] == aux->ident) {
			aux->congelado = true;
			congelados++;
		}
	}
}

class Curso {
public:
	Curso(string pCarrera, string pCodigo, string pNombre) {
		carrera = pCarrera;
		codigo = pCodigo;
		nombre = pNombre;
	}
	void insertarGrupo(string datos[]);
	void insertarEstudiante(string datos[]);
	void atender(string datos[]);
	bool listaVacia() { return primerGrupo == NULL; };
private:
	string carrera;
	string codigo;
	string nombre;
	pGrupo primerGrupo;
	Curso *siguiente;
	Curso *anterior;

	friend class Carrera;
	friend class ListaCarreras;
	friend class Cola;
};
typedef Curso *pCurso;

void Curso::insertarGrupo(string datos[]) {
	if (listaVacia()) {
		primerGrupo = new Grupo(datos[0], datos[1], datos[2], datos[3], datos[4], datos[5], datos[6]);
		primerGrupo->anterior = primerGrupo;
		primerGrupo->siguiente = primerGrupo;
	}
	else {
		pGrupo aux = primerGrupo;
		bool grupoNuevo = true;
		while (aux->siguiente != primerGrupo) {
			if (datos[2] == aux->codigo || datos[3] == aux->profesor) {
				grupoNuevo = false;
				break;
			}
			aux = aux->siguiente;
		}
		if (datos[2] == aux->codigo || datos[3] == aux->profesor) {
			grupoNuevo = false;
		}
		if (grupoNuevo) {
			pGrupo nuevo = new Grupo(datos[0], datos[1], datos[2], datos[3], datos[4], datos[5], datos[6]);
			nuevo->anterior = primerGrupo->anterior;
			nuevo->siguiente = primerGrupo->anterior->siguiente;
			primerGrupo->anterior->siguiente = nuevo;
			primerGrupo->anterior = nuevo;
		}
	}
}

void Curso::insertarEstudiante(string datos[]) {
	if (!listaVacia()) {
		pGrupo aux = primerGrupo;
		if (aux->siguiente != primerGrupo) {
			if (datos[2] == aux->codigo) {
				aux->insertarEstudiante(datos);
			}
			aux = aux->siguiente;
		}
		if (datos[2] == aux->codigo) {
			aux->insertarEstudiante(datos);
		}
	}
}

void Curso::atender(string datos[]) {
	if (!listaVacia()) {
		pGrupo aux = primerGrupo;
		if (aux->siguiente != primerGrupo) {
			if (datos[2] == aux->codigo) {
				int accion = stoi(datos[4]);
				switch (accion) {
				case 1:
					aux->matricular(datos);
					break;
				case 2:
					aux->desmatricular(datos);
					break;
				case 3:
					aux->congelar(datos);
					break;
				default:
					break;
				}
			}
			aux = aux->siguiente;
		}
		if (datos[2] == aux->codigo) {
			int accion = stoi(datos[4]);
			switch (accion) {
			case 1:
				aux->matricular(datos);
				break;
			case 2:
				aux->desmatricular(datos);
				break;
			case 3:
				aux->congelar(datos);
				break;
			default:
				break;
			}
		}
	}
}

class Carrera {
public:
	Carrera(string pCodigo, string pNombre) {
		codigo = pCodigo;
		nombre = pNombre;
	}
	void insertarGrupo(string datos[]);
	void insertarEstudiante(string datos[]);
	bool ListaVacia() { return primerCurso == NULL; }
	void atender(string datos[]);
private:
	string codigo;
	string nombre;
	Carrera *siguiente;
	Carrera *anterior;
	pCurso primerCurso;

	friend class ListaCarreras;
	friend class Cola;
};
typedef Carrera *pCarrera;

void Carrera::insertarGrupo(string datos[]) {
	pCurso aux = primerCurso;
	while (aux->siguiente != primerCurso) {
		if (datos[1] == aux->codigo) {
			aux->insertarGrupo(datos);
		}
		aux = aux->siguiente;
	}
	if (datos[1] == aux->codigo) {
		aux->insertarGrupo(datos);
	}
}

void Carrera::insertarEstudiante(string datos[]) {
	pCurso aux = primerCurso;
	while (aux->siguiente != primerCurso) {
		if (datos[1] == aux->codigo) {
			aux->insertarEstudiante(datos);
		}
		aux = aux->siguiente;
	}
	if (datos[1] == aux->codigo) {
		aux->insertarEstudiante(datos);
	}
}

void Carrera::atender(string datos[]) {
	pCurso aux = primerCurso;
	while (aux->siguiente != primerCurso) {
		if (datos[1] == aux->codigo) {
			aux->atender(datos);
		}
		aux = aux->siguiente;
	}
	if (datos[1] == aux->codigo) {
		aux->atender(datos);
	}
}

class ListaCarreras {
public:
	ListaCarreras() { primero = actual = NULL; };
	void leerCarrera(string txt);
	bool ListaVacia() { return primero == NULL; };
	void cargarCurso(string txt);
	void cargarGrupos(string txt, ListaProfesores lista);
	void cargarEstudiantesCurso(string txt, ListaEstudiantes lista);
	void atender(string datos[], pListaEstudiantes lista);
	void crearReporte();
	void crearReporteCursos();
private:
	pCarrera primero;
	pCarrera actual;
	friend class Cola;
};
typedef ListaCarreras *pListaCarreras;

void ListaCarreras::leerCarrera(string txt) {
	ifstream archivo;
	string texto;
	archivo.open(txt, ios::in);
	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo\n";
		system("pause");
		exit(1);
	}
	while (!archivo.eof()) {
		getline(archivo, texto);
		string datos[2];
		int actual = 0;
		for (int i = 0; i != texto.length(); i++) {
			if (texto[i] == ';') {
				actual++;
				i++;
			}
			datos[actual] += texto[i];
		}
		if (ListaVacia())
		{
			primero = new Carrera(datos[0], datos[1]);
			primero->anterior = primero;
			primero->siguiente = primero;
		}
		else
		{
			pCarrera nuevo = new Carrera(datos[0], datos[1]);
			nuevo->anterior = primero->anterior;
			nuevo->siguiente = primero->anterior->siguiente;
			primero->anterior->siguiente = nuevo;
			primero->anterior = nuevo;
		}
	}
	archivo.close();
}

void ListaCarreras::cargarCurso(string txt) {
	ifstream archivo;
	string texto;
	archivo.open(txt, ios::in);
	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo\n";
		system("pause");
		exit(1);
	}
	while (!archivo.eof()) {
		getline(archivo, texto);
		string datos[3];
		int actual = 0;
		for (int i = 0; i != texto.length(); i++) {
			if (texto[i] == ';') {
				actual++;
				i++;
			}
			datos[actual] += texto[i];
		}
		pCarrera aux = primero;
		bool insertado = false;
		while (aux->siguiente != primero) {
			if (datos[0] == aux->codigo) {
				if (aux->ListaVacia()) {
					aux->primerCurso = new Curso(datos[0], datos[1], datos[2]);
					aux->primerCurso->anterior = aux->primerCurso;
					aux->primerCurso->siguiente = aux->primerCurso;
					insertado = true;
				}
				else {
					pCurso auxCursos = aux->primerCurso;
					bool cursoNuevo = true;
					while (auxCursos->siguiente != aux->primerCurso) {
						if (datos[1] == auxCursos->codigo) {
							cursoNuevo = false;
							break;
						}
						auxCursos = auxCursos->siguiente;
					}
					if (cursoNuevo && datos[1] != auxCursos->codigo) {
						pCurso nuevo = new Curso(datos[0], datos[1], datos[2]);
						nuevo->anterior = aux->primerCurso->anterior;
						nuevo->siguiente = aux->primerCurso->anterior->siguiente;
						aux->primerCurso->anterior->siguiente = nuevo;
						aux->primerCurso->anterior = nuevo;
						insertado = true;
					}
				}
				break;
			}
			aux = aux->siguiente;
		}
		if (!insertado) {
			if (datos[0] == aux->codigo) {
				if (aux->ListaVacia()) {
					aux->primerCurso = new Curso(datos[0], datos[1], datos[2]);
					aux->primerCurso->anterior = aux->primerCurso;
					aux->primerCurso->siguiente = aux->primerCurso;
				}
				else {
					pCurso auxCursos = aux->primerCurso;
					bool cursoNuevo = true;
					while (auxCursos->siguiente != aux->primerCurso) {
						if (datos[1] == auxCursos->codigo) {
							cursoNuevo = false;
							break;
						}
						auxCursos = auxCursos->siguiente;
					}
					if (cursoNuevo && datos[1] != auxCursos->codigo) {
						pCurso nuevo = new Curso(datos[0], datos[1], datos[2]);
						nuevo->anterior = aux->primerCurso->anterior;
						nuevo->siguiente = aux->primerCurso->anterior->siguiente;
						aux->primerCurso->anterior->siguiente = nuevo;
						aux->primerCurso->anterior = nuevo;
					}


				}
			}
		}
	}
	archivo.close();
}

void ListaCarreras::cargarGrupos(string txt, ListaProfesores lista) {
	ifstream archivo;
	string texto;
	archivo.open(txt, ios::in);
	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo\n";
		system("pause");
		exit(1);
	}
	while (!archivo.eof()) {
		getline(archivo, texto);
		string datos[7];
		int actual = 0;
		for (int i = 0; i != texto.length(); i++) {
			if (texto[i] == ';') {
				actual++;
				i++;
			}
			datos[actual] += texto[i];
		}
		if (lista.buscarProfesor(datos[3])) {
			pCarrera aux = primero;
			while (aux->siguiente != primero) {
				if (datos[0] == aux->codigo) {
					aux->insertarGrupo(datos);
				}
				aux = aux->siguiente;
			}
			if (datos[0] == aux->codigo) {
				aux->insertarGrupo(datos);
			}
		}
	}
	archivo.close();
}

void ListaCarreras::cargarEstudiantesCurso(string txt, ListaEstudiantes lista) {
	ifstream archivo;
	string texto;
	archivo.open(txt, ios::in);
	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo\n";
		system("pause");
		exit(1);
	}
	while (!archivo.eof()) {
		getline(archivo, texto);
		string datos[4];
		int actual = 0;
		for (int i = 0; i != texto.length(); i++) {
			if (texto[i] == ';') {
				actual++;
				i++;
			}
			datos[actual] += texto[i];
		}
		datos[3] = lista.buscarCarrera(datos[0]);
		if (datos[3] != "") {
			pCarrera aux = primero;
			while (aux->siguiente != primero) {
				if (datos[3] == aux->codigo) {
					aux->insertarEstudiante(datos);
				}
				aux = aux->siguiente;
			}
			if (datos[3] == aux->codigo) {
				aux->insertarEstudiante(datos);
			}
		}

	}
	archivo.close();
}

void ListaCarreras::atender(string datos[], pListaEstudiantes lista) {
	datos[3] = lista->buscarCarrera(datos[0]);
	if (datos[3] != "") {
		pCarrera aux = primero;
		while (aux->siguiente != primero) {
			if (datos[3] == aux->codigo) {
				aux->atender(datos);
			}
			aux = aux->siguiente;
		}
		if (datos[3] == aux->codigo) {
			aux->atender(datos);
		}
	}
}

void ListaCarreras::crearReporte() {
	string reporte = "";
	pCarrera aux = primero;
	while (aux->siguiente != primero) {
		reporte += "Carrera: ";
		reporte += aux->nombre;
		reporte += "\nCodigo: ";
		reporte += aux->codigo;
		reporte += "\n--------------------------------------------------------\n";
		aux = aux->siguiente;
	}
	reporte += "Carrera: ";
	reporte += aux->nombre;
	reporte += "\nCodigo: ";
	reporte += aux->codigo;
	ofstream archivoReporte;
	archivoReporte.open("Reporte de Carreras.txt");
	archivoReporte << reporte;
	archivoReporte.close();
}

void ListaCarreras::crearReporteCursos() {
	string reporte = "";
	pCarrera aux = primero;
	while (aux->siguiente != primero) {
		reporte += "Carrera: ";
		reporte += aux->nombre;
		reporte += "\nCodigo: ";
		reporte += aux->codigo;
		reporte += "\nCursos:\n";
		pCurso auxCurso = aux->primerCurso;
		while (auxCurso->siguiente != aux->primerCurso) {
			reporte += auxCurso->nombre;
			reporte += "\n";
			auxCurso = auxCurso->siguiente;
		}
		reporte += auxCurso->nombre;
		reporte += "\n";
		reporte += "--------------------------------------------------------\n";
		aux = aux->siguiente;
	}
	reporte += "Carrera: ";
	reporte += aux->nombre;
	reporte += "\nCodigo: ";
	reporte += aux->codigo;
	reporte += "\nCursos:\n";
	pCurso auxCurso = aux->primerCurso;
	while (auxCurso->siguiente != aux->primerCurso) {
		reporte += auxCurso->nombre;
		reporte += "\n";
		auxCurso = auxCurso->siguiente;
	}
	reporte += auxCurso->nombre;
	reporte += "\n";
	ofstream archivoReporte;
	archivoReporte.open("Reporte de Cursos por Carrera.txt");
	archivoReporte << reporte;
	archivoReporte.close();
}

class Nodo {
public:
	Nodo(string pDato, string pCurso, string pGrupo, string pAccion);
private:
	string estudiante;
	string curso;
	string grupo;
	string accion;
	Nodo *siguiente;
	friend class Cola;
	friend class ListaString;
	friend class Mostrador;
};
typedef Nodo *pNodo;

Nodo::Nodo(string pEstudiante, string pCurso, string pGrupo, string pAccion) {
	estudiante = pEstudiante;
	curso = pCurso;
	grupo = pGrupo;
	accion = pAccion;
	siguiente = NULL;
};

class ListaString {
public:
	ListaString() { primero = NULL; };
	bool listaVacia() { return primero == NULL; };
	void crearListaAtencion(string txt);
	void insertarFinal(string pEstudiante, string pCurso, string pGrupo, string pAtencion);
	void eliminarInicio();
private:
	pNodo primero;
	friend class Cola;
	friend class Mostrador;
	friend class ListaMostradores;
};
typedef ListaString *pListaString;

void ListaString::crearListaAtencion(string txt) {
	ifstream archivo;
	string texto;
	archivo.open(txt, ios::in);
	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo\n";
		system("pause");
		exit(1);
	}
	while (!archivo.eof()) {
		getline(archivo, texto);
		string datos[4];
		int actual = 0;
		for (int i = 0; i != texto.length(); i++) {
			if (texto[i] == ';') {
				actual++;
				i++;
			}
			datos[actual] += texto[i];
		}
		insertarFinal(datos[0], datos[1], datos[2], datos[3]);
	}
}

void ListaString::insertarFinal(string pEstudiante, string pCurso, string pGrupo, string pAtencion) {
	if (listaVacia()) {
		primero = new Nodo(pEstudiante, pCurso, pGrupo, pAtencion);
	}
	else {
		pNodo aux = primero;
		while (aux->siguiente != NULL)
			aux = aux->siguiente;
		aux->siguiente = new Nodo(pEstudiante, pCurso, pGrupo, pAtencion);
	}
}

void ListaString::eliminarInicio() {
	pNodo aux = primero;
	primero = primero->siguiente;
	delete aux;
}

class Mostrador {
public:
	Mostrador();
private:
	Mostrador * siguiente;
	int atendidos;
	friend class Cola;
	friend class ListaMostradores;
};
typedef Mostrador *pMostrador;

Mostrador::Mostrador() {
	atendidos = 0;
	siguiente = NULL;
}

class ListaMostradores {
public:
	ListaMostradores();
	void crearReporte();
private:
	pMostrador primero;
	pMostrador segundo;
	pMostrador tercero;
	friend class Cola;
};
typedef ListaMostradores *pListaMostradores;

ListaMostradores::ListaMostradores() {
	tercero = new Mostrador();
	segundo = new Mostrador();
	segundo->siguiente = tercero;
	primero = new Mostrador();
	primero->siguiente = segundo;
}

void ListaMostradores::crearReporte() {
	string reporte = "";
	reporte += "Mostrador 1\n";
	reporte += "Personas Atenddidas: ";
	reporte += to_string(primero->atendidos);
	reporte += "\n-------------------------------\n";
	reporte += "Mostrador 2\n";
	reporte += "Personas Atenddidas: ";
	reporte += to_string(segundo->atendidos);
	reporte += "\n-------------------------------\n";
	reporte += "Mostrador 3\n";
	reporte += "Personas Atenddidas: ";
	reporte += to_string(tercero->atendidos);
	ofstream archivoReporte;
	archivoReporte.open("Reporte Personas Atendidas por Mostrador.txt");
	archivoReporte << reporte;
	archivoReporte.close();
}

class Cola {
public:
	Cola(pListaString listaNueva, pListaMostradores mostradores, pListaEstudiantes pEstudiantes, pListaProfesores pProfesores, pListaCarreras pCarreras);
	void actualizar();
	void dormir();
	void atenderPrimero();
	void atenderSegundo();
	void atenderTercero();
	void threadAtender();
	void crearReporteProfesoresCursos();
	void crearReporteEstudianteGrupos();
	void crearReporteEstudianteCarreras();
	void crearReporteProfesorCarreras();
	void crearReportes();
private:
	pNodo cola[10];
	int inicio;
	int fin;
	pListaString lista;
	pListaMostradores mostradores;
	pListaEstudiantes estudiantes;
	pListaProfesores profesores;
	pListaCarreras carreras;
	mutex pausa;
};
typedef Cola *pCola;

Cola::Cola(pListaString listaNueva, pListaMostradores Pmostradores, pListaEstudiantes pEstudiantes, pListaProfesores pProfesores, pListaCarreras pCarreras) {
	inicio = 0;
	fin = -1;
	lista = listaNueva;
	mostradores = Pmostradores;
	estudiantes = pEstudiantes;
	profesores = pProfesores;
	carreras = pCarreras;
}

bool actualizado = false;
bool vacio = false;

void Cola::actualizar() {
	pausa.lock();
	if (inicio <= fin){
		int inicioAux = 0;
		while (inicio <= fin){
			cola[inicioAux] = cola[inicio];
			inicio++;
			inicioAux++;
		}
		fin = inicioAux;
	}else{
		fin = 0;
	}
	inicio = 0;
	while (fin<10){
		if (lista->primero == NULL){
			vacio = true;
			break;
		}
		cola[fin] = lista->primero;
		lista->primero = lista->primero->siguiente;
		fin++;
	}
	fin -= 1;
	actualizado = true;
	pausa.unlock();
}

void Cola::dormir() {
	while (vacio == false) {
		actualizado = false;
		actualizar();
		this_thread::sleep_for(3s);
	}
}

void Cola::atenderPrimero() {
	while (true) {
		if (inicio <= fin && actualizado == true) {
			pausa.lock();
			pNodo prueba = cola[inicio];
			inicio += 1;
			pausa.unlock();
			string datos[5];
			datos[0] = prueba->estudiante;
			datos[1] = prueba->curso;
			datos[2] = prueba->grupo;
			datos[4] = prueba->accion;
			carreras->atender(datos, estudiantes);
			mostradores->primero->atendidos++;
			this_thread::sleep_for(2s);
		}
		else if (vacio == true) {
			break;
		}
	}
}

void Cola::atenderSegundo() {
	while (true) {
		if (inicio <= fin && actualizado == true) {
			pausa.lock();
			pNodo prueba = cola[inicio];
			inicio += 1;
			pausa.unlock();
			string datos[5];
			datos[0] = prueba->estudiante;
			datos[1] = prueba->curso;
			datos[2] = prueba->grupo;
			datos[4] = prueba->accion;
			carreras->atender(datos, estudiantes);
			mostradores->segundo->atendidos++;
			this_thread::sleep_for(2s);
		}
		else if (vacio == true) {
			break;
		}
	}
}

void Cola::atenderTercero() {
	while (true) {
		if (inicio <= fin && actualizado == true) {
			pausa.lock();
			pNodo prueba = cola[inicio];
			inicio += 1;
			pausa.unlock();
			string datos[5];
			datos[0] = prueba->estudiante;
			datos[1] = prueba->curso;
			datos[2] = prueba->grupo;
			datos[4] = prueba->accion;
			carreras->atender(datos, estudiantes);
			mostradores->tercero->atendidos++;
			this_thread::sleep_for(2s);
		}
		else if (vacio == true) {
			break;
		}
	}
}

void Cola::threadAtender() {
	thread actualizar(&Cola::dormir, this);
	thread mostrador1(&Cola::atenderPrimero, this);
	thread mostrador2(&Cola::atenderSegundo, this);
	thread mostrador3(&Cola::atenderTercero, this);
	actualizar.join();
	mostrador1.join();
	mostrador2.join();
	mostrador3.join();
}

void Cola::crearReporteProfesoresCursos() {
	string reporte = "";
	pCarrera aux = carreras->primero;
	while (aux->siguiente != carreras->primero) {
		reporte += aux->nombre;
		reporte += ":\n";
		pCurso auxCurso = aux->primerCurso;
		if (auxCurso != NULL) {
			while (auxCurso->siguiente != aux->primerCurso) {
				reporte += auxCurso->nombre;
				reporte += "\nProfesores:\n";
				pGrupo auxGrupo = auxCurso->primerGrupo;
				if (auxGrupo != NULL) {
					while (auxGrupo->siguiente != auxCurso->primerGrupo) {
						string pCodigo = auxGrupo->profesor;
						reporte += profesores->getNombre(pCodigo);
						reporte += "\n";
						auxGrupo = auxGrupo->siguiente;
					}
					string pCodigo = auxGrupo->profesor;
					reporte += profesores->getNombre(pCodigo);
					reporte += "\n\n";
				}
				auxCurso = auxCurso->siguiente;
			}
			reporte += auxCurso->nombre;
			reporte += "\nProfesores:\n";
			pGrupo auxGrupo = auxCurso->primerGrupo;
			if (auxGrupo != NULL) {
				while (auxGrupo->siguiente != auxCurso->primerGrupo) {
					string pCodigo = auxGrupo->profesor;
					reporte += profesores->getNombre(pCodigo);
					reporte += "\n";
					auxGrupo = auxGrupo->siguiente;
				}
				string pCodigo = auxGrupo->profesor;
				reporte += profesores->getNombre(pCodigo);
				reporte += "\n\n";
			}
		}
		reporte += "------------------------------------------------\n";
		aux = aux->siguiente;
	}
	reporte += aux->nombre;
	reporte += ":\n";
	pCurso auxCurso = aux->primerCurso;
	if (auxCurso != NULL) {
		while (auxCurso->siguiente != aux->primerCurso) {
			reporte += auxCurso->nombre;
			reporte += "\nProfesores:\n";
			pGrupo auxGrupo = auxCurso->primerGrupo;
			if (auxGrupo != NULL) {
				while (auxGrupo->siguiente != auxCurso->primerGrupo) {
					string pCodigo = auxGrupo->profesor;
					reporte += profesores->getNombre(pCodigo);
					reporte += "\n";
					auxGrupo = auxGrupo->siguiente;
				}
				string pCodigo = auxGrupo->profesor;
				reporte += profesores->getNombre(pCodigo);
				reporte += "\n\n";
			}
			auxCurso = auxCurso->siguiente;
		}
		reporte += auxCurso->nombre;
		reporte += "\nProfesores:\n";
		pGrupo auxGrupo = auxCurso->primerGrupo;
		if (auxGrupo != NULL) {
			while (auxGrupo->siguiente != auxCurso->primerGrupo) {
				string pCodigo = auxGrupo->profesor;
				reporte += profesores->getNombre(pCodigo);
				reporte += "\n";
				auxGrupo = auxGrupo->siguiente;
			}
			string pCodigo = auxGrupo->profesor;
			reporte += profesores->getNombre(pCodigo);
		}
	}
	ofstream archivoReporte;
	archivoReporte.open("Reporte Profesores Por Curso.txt");
	archivoReporte << reporte;
	archivoReporte.close();
}

void Cola::crearReporteEstudianteGrupos() {
	string reporte = "";
	pCarrera aux = carreras->primero;
	while (aux->siguiente != carreras->primero) {
		reporte += aux->nombre;
		reporte += ":\n";
		pCurso auxCurso = aux->primerCurso;
		if (auxCurso != NULL) {
			while (auxCurso->siguiente != aux->primerCurso) {
				reporte += auxCurso->nombre;
				pGrupo auxGrupo = auxCurso->primerGrupo;
				if (auxGrupo != NULL) {
					while (auxGrupo->siguiente != auxCurso->primerGrupo) {
						reporte += "\nGrupo ";
						reporte += auxGrupo->codigo;
						pCursoEstudiante auxEstudiante = auxGrupo->primerEstudiante;
						if (auxEstudiante != NULL) {
							while (auxEstudiante->siguiente != auxGrupo->primerEstudiante) {
								if (auxEstudiante->congelado == false) {
									reporte += "\n-";
									string codigo = auxEstudiante->ident;
									reporte += estudiantes->obtenerDatos(codigo);
								}
								auxEstudiante = auxEstudiante->siguiente;
							}
							if (auxEstudiante->congelado == false) {
								reporte += "\n-";
								string codigo = auxEstudiante->ident;
								reporte += estudiantes->obtenerDatos(codigo);
							}
						}
						auxGrupo = auxGrupo->siguiente;
					}
					reporte += "\nGrupo ";
					reporte += auxGrupo->codigo;
					pCursoEstudiante auxEstudiante = auxGrupo->primerEstudiante;
					if (auxEstudiante != NULL) {
						while (auxEstudiante->siguiente != auxGrupo->primerEstudiante) {
							if (auxEstudiante->congelado == false) {
								reporte += "\n-";
								string codigo = auxEstudiante->ident;
								reporte += estudiantes->obtenerDatos(codigo);
							}
							auxEstudiante = auxEstudiante->siguiente;
						}
						reporte += "\n-";
						string codigo = auxEstudiante->ident;
						reporte += estudiantes->obtenerDatos(codigo);
					}
					reporte += "\n\n";
				}
				auxCurso = auxCurso->siguiente;
			}
			reporte += auxCurso->nombre;
			pGrupo auxGrupo = auxCurso->primerGrupo;
			if (auxGrupo != NULL) {
				while (auxGrupo->siguiente != auxCurso->primerGrupo) {
					reporte += "\nGrupo ";
					reporte += auxGrupo->codigo;
					pCursoEstudiante auxEstudiante = auxGrupo->primerEstudiante;
					if (auxEstudiante != NULL) {
						while (auxEstudiante->siguiente != auxGrupo->primerEstudiante) {
							if (auxEstudiante->congelado == false) {
								reporte += "\n-";
								string codigo = auxEstudiante->ident;
								reporte += estudiantes->obtenerDatos(codigo);
							}
							auxEstudiante = auxEstudiante->siguiente;
						}
						if (auxEstudiante->congelado == false) {
							reporte += "\n-";
							string codigo = auxEstudiante->ident;
							reporte += estudiantes->obtenerDatos(codigo);
						}
					}
					auxGrupo = auxGrupo->siguiente;
				}
				reporte += "\nGrupo ";
				reporte += auxGrupo->codigo;
				pCursoEstudiante auxEstudiante = auxGrupo->primerEstudiante;
				if (auxEstudiante != NULL) {
					while (auxEstudiante->siguiente != auxGrupo->primerEstudiante) {
						if (auxEstudiante->congelado == false) {
							reporte += "\n-";
							string codigo = auxEstudiante->ident;
							reporte += estudiantes->obtenerDatos(codigo);
						}
						auxEstudiante = auxEstudiante->siguiente;
					}
					if (auxEstudiante->congelado == false) {
						reporte += "\n-";
						string codigo = auxEstudiante->ident;
						reporte += estudiantes->obtenerDatos(codigo);
					}
				}
				reporte += "\n\n";
			}
		}
		reporte += "\n";
		reporte += "------------------------------------------------\n";
		aux = aux->siguiente;
	}
	reporte += aux->nombre;
	reporte += ":\n";
	pCurso auxCurso = aux->primerCurso;
	if (auxCurso != NULL) {
		while (auxCurso->siguiente != aux->primerCurso) {
			reporte += auxCurso->nombre;
			pGrupo auxGrupo = auxCurso->primerGrupo;
			if (auxGrupo != NULL) {
				while (auxGrupo->siguiente != auxCurso->primerGrupo) {
					reporte += "\nGrupo ";
					reporte += auxGrupo->codigo;
					pCursoEstudiante auxEstudiante = auxGrupo->primerEstudiante;
					if (auxEstudiante != NULL) {
						while (auxEstudiante->siguiente != auxGrupo->primerEstudiante) {
							if (auxEstudiante->congelado == false) {
								reporte += "\n-";
								string codigo = auxEstudiante->ident;
								reporte += estudiantes->obtenerDatos(codigo);
							}
							auxEstudiante = auxEstudiante->siguiente;
						}
						if (auxEstudiante->congelado == false) {
							reporte += "\n-";
							string codigo = auxEstudiante->ident;
							reporte += estudiantes->obtenerDatos(codigo);
						}
					}
					auxGrupo = auxGrupo->siguiente;
				}
				reporte += "\nGrupo ";
				reporte += auxGrupo->codigo;
				pCursoEstudiante auxEstudiante = auxGrupo->primerEstudiante;
				if (auxEstudiante != NULL) {
					while (auxEstudiante->siguiente != auxGrupo->primerEstudiante) {
						if (auxEstudiante->congelado == false) {
							reporte += "\n-";
							string codigo = auxEstudiante->ident;
							reporte += estudiantes->obtenerDatos(codigo);
						}
						auxEstudiante = auxEstudiante->siguiente;
					}
					if (auxEstudiante->congelado == false) {
						reporte += "\n-";
						string codigo = auxEstudiante->ident;
						reporte += estudiantes->obtenerDatos(codigo);
					}
				}
				reporte += "\n\n";
			}
			auxCurso = auxCurso->siguiente;
		}
		reporte += auxCurso->nombre;
		pGrupo auxGrupo = auxCurso->primerGrupo;
		if (auxGrupo != NULL) {
			while (auxGrupo->siguiente != auxCurso->primerGrupo) {
				reporte += "\nGrupo ";
				reporte += auxGrupo->codigo;
				pCursoEstudiante auxEstudiante = auxGrupo->primerEstudiante;
				if (auxEstudiante != NULL) {
					while (auxEstudiante->siguiente != auxGrupo->primerEstudiante) {
						if (auxEstudiante->congelado == false) {
							reporte += "\n-";
							string codigo = auxEstudiante->ident;
							reporte += estudiantes->obtenerDatos(codigo);
						}
						auxEstudiante = auxEstudiante->siguiente;
					}
					if (auxEstudiante->congelado == false) {
						reporte += "\n-";
						string codigo = auxEstudiante->ident;
						reporte += estudiantes->obtenerDatos(codigo);
					}
				}
				auxGrupo = auxGrupo->siguiente;
			}
			reporte += "\nGrupo ";
			reporte += auxGrupo->codigo;
			pCursoEstudiante auxEstudiante = auxGrupo->primerEstudiante;
			if (auxEstudiante != NULL) {
				while (auxEstudiante->siguiente != auxGrupo->primerEstudiante) {
					if (auxEstudiante->congelado == false) {
						reporte += "\n-";
						string codigo = auxEstudiante->ident;
						reporte += estudiantes->obtenerDatos(codigo);
					}
					auxEstudiante = auxEstudiante->siguiente;
				}
				if (auxEstudiante->congelado == false) {
					reporte += "\n-";
					string codigo = auxEstudiante->ident;
					reporte += estudiantes->obtenerDatos(codigo);
				}
			}
		}
	}
	ofstream archivoReporte;
	archivoReporte.open("Reporte Estudiantes Por Grupo.txt");
	archivoReporte << reporte;
	archivoReporte.close();
}

void Cola::crearReporteEstudianteCarreras() {
	string reporte = "";
	pCarrera aux = carreras->primero;
	while (aux->siguiente != carreras->primero) {
		reporte += aux->nombre;
		reporte += "\nEstudiantes:\n";
		string codCarrera = aux->codigo;
		reporte += estudiantes->devolverEstudiantesCarrera(codCarrera);
		reporte += "---------------------------------------\n";
		aux = aux->siguiente;
	}
	reporte += aux->nombre;
	reporte += "\nEstudiantes:\n";
	string codCarrera = aux->codigo;
	reporte += estudiantes->devolverEstudiantesCarrera(codCarrera);
	ofstream archivoReporte;
	archivoReporte.open("Reporte Estudiantes de Carreras.txt");
	archivoReporte << reporte;
	archivoReporte.close();
}

void Cola::crearReporteProfesorCarreras() {
	string reporte = "";
	pCarrera aux = carreras->primero;
	while (aux->siguiente != carreras->primero) {
		reporte += aux->nombre;
		reporte += "\nProfesores:\n";
		string codCarrera = aux->codigo;
		reporte += profesores->devolverProfesoresCarrera(codCarrera);
		reporte += "---------------------------------------\n";
		aux = aux->siguiente;
	}
	reporte += aux->nombre;
	reporte += "\nProfesores:\n";
	string codCarrera = aux->codigo;
	reporte += profesores->devolverProfesoresCarrera(codCarrera);
	ofstream archivoReporte;
	archivoReporte.open("Reporte Profesores de Carreras.txt");
	archivoReporte << reporte;
	archivoReporte.close();
}

void Cola::crearReportes() {
	while (true) {
		cout << "1. Reporte de Carreras\n";
		cout << "2. Reporte de Cursos de Carreras\n";
		cout << "3. Reporte de Profesores\n";
		cout << "4. Reporte de Profesores de Cursos\n";
		cout << "5. Reporte de Estudiantes por Grupo\n";
		cout << "6. Reporte de Estudiantes de Carreras\n";
		cout << "7. Reporte de Profesores de Servivio\n";
		cout << "8. Reporte de Profesores de Carreras\n";
		cout << "9. Reporte de personas atendidas por mostrador\n";
		cout << "10. Crear todos los reportes\n";
		cout << "11. Salir\n";
		int opcion;
		cin >> opcion;
		switch (opcion) {
		case 1:
			carreras->crearReporte();
			cout << "Reporte Creado\n";
			break;
		case 2:
			carreras->crearReporteCursos();
			cout << "Reporte Creado\n";
			break;
		case 3:
			profesores->crearReporte();
			cout << "Reporte Creado\n";
			break;
		case 4:
			crearReporteProfesoresCursos();
			cout << "Reporte Creado\n";
			break;
		case 5:
			crearReporteEstudianteGrupos();
			cout << "Reporte Creado\n";
			break;
		case 6:
			crearReporteEstudianteCarreras();
			cout << "Reporte Creado\n";
			break;
		case 7:
			profesores->crearReporteServicio();
			cout << "Reporte Creado\n";
			break;
		case 8:
			crearReporteProfesorCarreras();
			cout << "Reporte Creado\n";
			break;
		case 9:
			mostradores->crearReporte();
			cout << "Reporte Creado\n";
			break;
		case 10:
			carreras->crearReporte();
			carreras->crearReporteCursos();
			profesores->crearReporte();
			crearReporteProfesoresCursos();
			crearReporteEstudianteGrupos();
			crearReporteEstudianteCarreras();
			profesores->crearReporteServicio();
			crearReporteProfesorCarreras();
			mostradores->crearReporte();
			cout << "Reportes Creados\n";
			break;
		case 11:
			cout << "Muchas Gracias";
			Sleep(500);
			exit(1);
			break;
		default:
			cout << "La opcion elegida no existe.\n";
			break;
		}
	}
}

int main() {
	ListaEstudiantes estudiantes;
	estudiantes.leerEstudiante("Estudiantes.txt");
	ListaProfesores profesores;
	profesores.leerProfesor("Profesores.txt");
	ListaCarreras carreras;
	carreras.leerCarrera("Carreras.txt");
	carreras.cargarCurso("Cursos.txt");
	carreras.cargarGrupos("Grupos.txt", profesores);
	carreras.cargarEstudiantesCurso("Estudiante-Curso.txt", estudiantes);
	ListaString lista;
	lista.crearListaAtencion("Atencion.txt");
	ListaMostradores mostradores;
	Cola cola(&lista, &mostradores, &estudiantes, &profesores, &carreras);
	cola.threadAtender();
	cola.crearReportes();
	return 0;
};
#include <iostream>
#include <windows.h>
#include <time.h>

//definimos constante , sabemos que maximo tablero puede ser 30x30 , para que haya 8 vecinas en todas , añadimos fila y columna
#define MAX 32
//colores
#define color SetConsoleTextAttribute

using namespace std;


void mensajeInicio();
int elegirNivel();
int elegirFilas(int level);
int elegirColumnas(int level);
int elegirMinas(int level);
void InicializaTablero(int row,int col,char space[MAX][MAX], HANDLE hConsole);
void ColocaMinas(int row, int col, char space[MAX][MAX], int minas);
void ColocaNumeros(int row, int col, char space[MAX][MAX], HANDLE hConsole);
void ImprimeTablero(int jugadaFila, int jugadaColumna, char space[MAX][MAX], char space2[MAX][MAX], int row, int col, HANDLE hConsole);
int VerificaGanador(int row,int col, char space[MAX][MAX],int minas);
bool Situaciones(int row, int col, char space[MAX][MAX], int minas,bool partida);



int main() 
{
	
	#pragma region Color
	//colores
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	color(hConsole, 3);
	#pragma endregion


	#pragma region Inicializacion
	//numero de nivel , numero filas , numero columnas,numero minas
	int level, row, col, min;
	//jugada de player
	int jugadaFila, jugadaColumna;
	//situaciones posibles win o lose
	int situacion;
	//bool jugar
	bool partida = true;
	//definimos matrices de tablero
	//space ---> para poder mostrar al usuario lo que yo quiero que vea, todos los elementos con valor de 0(carta boca abajo), y almacenados elementos que usuario quiero voltear(jugada)
	//space2 ---> valores verdaderos que tienen las casillas despues de voltearlas(numero de minas vecinas)
	char space[MAX][MAX], space2[MAX][MAX];
	#pragma endregion 

	#pragma region ValoresPrevios
	//mensaje Bienvenida
	mensajeInicio();
	//nivel que elegimos
	level = elegirNivel();
	//numero de filas
	row = elegirFilas(level);
	//numero de columnas
	col = elegirColumnas(level);
	//numero de minas
	min = elegirMinas(level);
	#pragma endregion 
	
	#pragma region Tablero
	//inicializamos tablero
	InicializaTablero(row, col, space, hConsole);
	#pragma endregion

	#pragma region Aleatorios
	//ColocaMinas y numeros aleatorios
	ColocaMinas(row, col, space2, min);
	ColocaNumeros(row, col, space2,hConsole);
	#pragma endregion

	#pragma region Jugada
	//jugada de player
	while (partida)
	{
		color(hConsole, 3);
		cout << endl << "Ingrese la fila y la columna  de la casilla que quieres dar la vuelta: ";
		cin >> jugadaFila >> jugadaColumna;
		cout << endl;
		color(hConsole, 4);
		//restricciones para hacer jugada
		if (jugadaFila > 0 && jugadaFila < row + 1 && jugadaColumna>0 && jugadaColumna < col + 1)
		{
			//render de tablero con jugada
			ImprimeTablero(jugadaFila, jugadaColumna, space, space2, row, col,hConsole);
			partida = Situaciones(row, col, space, min,partida);
			//comprobamos si sigue la partida
			
		}
		else
		{
			cout << "Valores incorrectos" << endl;
		}

	}
	#pragma endregion

	return 0;
}

void mensajeInicio()
{
	cout << "Bienvenido a BuscaMinas: " << endl;
	cout << endl;
	cout << " Los niveles son: " << endl;
	cout << endl;
	cout << "   <1>Nivel Principiante" << endl;
	cout << "   <2>Nivel Intermedio" << endl;
	cout << "   <3>Nivel Avanzado" << endl;
	cout << "   <4>Nivel Personalizado" << endl;
	cout << endl;
}

int elegirNivel()
{
	//se guarda valor del nivel elegido
	int l;
	//hasta no poner valor correcto pedir nivel
	while (1)
	{
		cout << "Ingrese el nivel que desea jugar: ";
		cin >> l;

		if (l == 1) break;
		else if (l == 2)break;
		else if (l == 3)break;
		else if (l == 4)break;
	}
	return l;
}

int elegirFilas(int level)
{
	int filas;
	//si es nivel principiante
	if (level == 1) filas = 8;
	//si es nivel intermedio
	else if (level == 2) filas = 16;
	//si es nivel avanzado
	else if (level == 3) filas = 16;
	//si es nivel personalizado , maximo 30 filas
	else if (level == 4)
	{
		while (1)
		{
			cout << "Ingrese numero de filas: ";
			cin >> filas;
			if (filas <= 30) break;
		}
	}
	return filas;
}

int elegirColumnas(int level)
{
	int columnas;
	//si es nivel principiante
	if (level == 1) columnas = 8;
	//si es nivel intermedio
	else if (level == 2) columnas = 16;
	//si es nivel avanzado
	else if (level == 3) columnas = 30;
	//si es nivel personalizado , maximo 30 filas
	else if (level == 4)
	{
		while (1)
		{
			cout << "Ingrese numero de columnas: ";
			cin >> columnas;
			if (columnas <= 30) break;
		}
	}
	return columnas;
}

int elegirMinas(int level)
{
	int minas;
	//si es nivel principiante
	if (level == 1) minas = 10;
	//si es nivel intermedio
	else if (level == 2) minas = 40;
	//si es nivel avanzado
	else if (level == 3) minas = 99;
	//si es nivel personalizado , maximo 30 filas
	else if (level == 4)
	{
		while (1)
		{
			cout << "Ingrese numero de minas: ";
			cin >> minas;
			if (minas <= 200) break;
		}
	}
	return minas;
}

void InicializaTablero(int row, int col, char space[MAX][MAX],HANDLE hConsole)
{
	
	//ponemos todo a ?
	for (int i = 0; i < row + 2; i++)
	{
		for (int j = 0; j < col + 2; j++)
		{
			space[i][j] = '?';
		}
	}

	cout <<endl<< "El tablero ha sido creado"<< endl;
	cout << "El tablero actual es:" << endl<<endl;

	color(hConsole, 4);
	//ahora solo mostramos la parte de tablero sin contar vallado
	for (int i = 1; i < row + 1; i++)
	{
		for (int j = 1; j < col + 1; j++)
		{
			cout << space[i][j];
		}
		cout << endl;
	}
}

void ColocaMinas(int row, int col, char space[MAX][MAX], int minas)
{
	int randomRow, randomCol;
	for (int i = 0; i < row + 2; i++)
	{
		for (int j = 0; j < col + 2; j++)
		{
			space[i][j] = '?';
		}
	}


	while (1)
	{
		//fila aleatoria entre 1 y num max de row
		randomRow = 1 + rand() % row;
		randomCol = 1 + rand() % col;
		//sustituimos ese valor
		if (space[randomRow][randomCol] == '?')
		{
			space[randomRow][randomCol] = 'M';
			minas--;
		}
		//vemos cuantas minas nos queda por colocar,si es 0 salimos
		if (minas == 0) break;
	}
	
}

void ColocaNumeros(int row, int col, char space[MAX][MAX], HANDLE hConsole)
{
	int number;
	//tablero sin vallado
	for (int i = 1; i < row + 1; i++)
	{
		for (int j = 1; j < col + 1; j++)
		{
			//contamos cuantas minas hay alrededor si no es mina el espacio
			if (space[i][j] == '?')
			{
				number = 0;
				//8 posiciones vecinas toroidales
				if (space[i - 1][j] == 'M')number++;
				if (space[i - 1][j-1] == 'M')number++;
				if (space[i - 1][j+1] == 'M')number++;
				if (space[i][j-1] == 'M')number++;
				if (space[i][j+1] == 'M')number++;
				if (space[i + 1][j] == 'M')number++;
				if (space[i + 1][j+1] == 'M')number++;
				if (space[i + 1][j-1] == 'M')number++;

				//si es 0
				if (number == 0)
				{
					
					//ponemos posicion vacia
					space[i][j] = '  ';
				}
				else
				{
					
					//numero de minas contiguas, space[i][j] es char , convertimos number en char
					space[i][j] = number + '0';
				}
				
			}
		}
	}
	color(hConsole, 3);
}

void ImprimeTablero(int jugadaFila, int jugadaColumna, char space[MAX][MAX], char space2[MAX][MAX], int row, int col, HANDLE hConsole)
{
	//se copia en la posicion jugada el valor de esta
	space[jugadaFila][jugadaColumna] = space2[jugadaFila][jugadaColumna];
	for (int i = 1; i < row + 1; i++)
	{
		for (int j = 1; j < col + 1; j++)
		{
			//sino es ? es numero
			if (space[i][j] != '?')
			{
				color(hConsole, 5);
			}
			else
			{
				color(hConsole, 4);
			}
			cout << space[i][j];
		}
		cout << endl;
	}
}

int VerificaGanador(int row, int col, char space[MAX][MAX], int minas)
{
	int situacion=0;
	//casillas que faltan por dar la vuelta y cantidad de minas que se han dado la vuelta
	int casillasFaltan=0, cantidadMinas=0;
	for (int i = 1; i < row + 1; i++)
	{
		for (int j = 1; j < col + 1; j++)
		{
			//si se ha tocado una mina se aumenta el numero
			if (space[i][j] == 'M') cantidadMinas++;
			//sino numero de cartas por revelar
			else if (space[i][j] == '?') casillasFaltan++;
		}
	}

	//si se ha explotado alguna Mina,se pierde
	if (cantidadMinas != 0) { situacion = 2; }
	//sino vemos si ha ganado , si la cantidad de casillas que faltan por dar la vuelta = cantidad de minas totales , es que no se ha explotado niguna
	else if (casillasFaltan == minas) situacion = 1;
	 
	return situacion;
}

bool Situaciones(int row, int col, char space[MAX][MAX], int minas,bool partida)
{
	//situacion victoria o derrota o nada
	int situacion = VerificaGanador(row, col, space, minas);

	//si ganan o pierden se acaba la partida
	if (situacion == 1)
	{
		cout << "Usted gano el juego";
		partida = false;
		
	}
	else if (situacion == 2)
	{
		cout << "Usted perdio el juego";
		partida = false;
	}

	return partida;
}





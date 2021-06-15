#ifndef _TATETI_H
#define _TATETI_H

#define JUGADOR_X 'X'
#define JUGADOR_O 'O'

#include <string>

class Tateti{
  private:
    char tablero[3][3];
    char ganador;
    bool juegoTerminado;
    int posicionesLibres;

  public:
    /*
    * Constructor. Carga con VACIO el tablero.
    */
    Tateti();

    /*
    * Realiza la jugada en el tablero y luego determina
    *si la partida termino y si hay algun ganador o no
    *modificando los atributos ganador y juegoTerminado.
    */
    void realizarJugada(const char& caracter, int fil, int col);

    /*
    * Devuelve el tablero en forma de string. Ademas, si el juegoTerminado
    * es true, agrega un mensaje de finalizacion dependiendo del tipo
    * de jugador.
    */
    std::string obtenerTablero(const char& tipoJugador);

    /*
    * Devuelve si juegoTerminado.
    */
    bool estaTerminado();

    /*
    * Destructor.
    */
    ~Tateti();

  private:
    /*
    * Transforma el tablero a un string.
    */
    void construirTablero(std::string& tablero_aux);

    /*
    * Agrega resultado de la partida al final del string del tablero
    * dependiendo del tipoJugador.
    */
    void agregarResultado(std::string& tablero_aux, const char& tipoJugador);

    /*
    * LLama a chequearFil, chequearCol y chequearDiagonales.
    */
    void chequearGanador(const int& fil, const int& col);

    /*
    * Determina si algun jugador lleno las casillas diagonales
    * y gano la partida.
    */
    void chequearDiagonales();

    /*
    * Determina si un jugador lleno toda una columna y gano
    * la partida
    */
    void chequearCol(const int& col);

    /*
    * Determina si un jugador lleno toda una fila y gano
    * la partida
    */
    void chequearFil(const int& fil);
};

#endif

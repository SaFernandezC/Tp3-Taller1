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

    Tateti();

    void realizarJugada(char& caracter, int fil, int col);

    std::string obtenerTablero(const char& tipoJugador);

    bool estaTerminado();

    ~Tateti();

  private:
    void construirTablero(std::string& tablero_aux);
    void agregarResultado(std::string& tablero_aux, const char& tipoJugador);
    void chequearGanador(int& fil, int& col);
    void chequearDiagonales();
    void chequearCol(int& col);
    void chequearFil(int& fil);
};

#endif

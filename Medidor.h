// -- mode: c++ --

// --------------------------------------------------------------
// Alejandro Roca Artiga
// --------------------------------------------------------------

#ifndef MEDIDOR_H_INCLUIDO
#define MEDIDOR_H_INCLUIDO

// ------------------------------------------------------
// ------------------------------------------------------

// Creación de una clase llamada "Medidor" para encapsular todas las funcionalidades relacionadas con la medición.
class Medidor {
  // .....................................................
  // .....................................................

  // Definición de pines utilizados para conexiones de sensores.
  private:
    int pinVGas = 2;     // Pin para el sensor de ozono
    int pinVRef = 17;    // Pin para la referencia
    int pinVTemp = 15;   // Pin para el sensor de temperatura

  // Variables públicas para almacenar los valores medidos.
  public:
    float VeGas;        // Tensión del sensor de ozono
    float VeRef;        // Tensión de referencia
    float VeTemp;       // Tensión del sensor de temperatura

    float aGas;         // Valor analógico del sensor de ozono
    float aRef;         // Valor analógico de referencia
    float aTemp;        // Valor analógico del sensor de temperatura

    float Temp;         // Temperatura medida
    float Vmedida;      // Tensión medida
    float Cx;           // Concentración de ozono
    float Itemp;        // Variación de temperatura
    float fCx;          // Concentración ajustada de ozono

  // .....................................................
  // Constructor
  // .....................................................
  Medidor( ) {
    pinMode(pinVGas, INPUT);
    pinMode(pinVRef, INPUT);
    pinMode(pinVTemp, INPUT);
  } // ()

  // .....................................................
  // Método para realizar inicializaciones necesarias.
  // .....................................................
  void iniciarMedidor() {
    // Realizar configuraciones o inicializaciones adicionales si es necesario.
  } // ()

  // .....................................................
  // Método para medir la concentración de ozono.
  // .....................................................
  int medirCO2() {
    // Leer los valores analógicos de los sensores
    aGas = analogRead(pinVGas);
    aRef = analogRead(pinVRef);
    aTemp = analogRead(pinVTemp);

    // Convertir los valores analógicos en tensiones (0-3.3V)
    VeGas = (aGas / 4096) * 3.3;
    VeRef = (aRef / 4096) * 3.3;
    VeTemp = (aTemp / 4096) * 3.3;
    // Calcular la tensión medida
    Vmedida = VeGas - VeRef;

    // Calcular la concentración de ozono (Cx) utilizando una fórmula específica.
    Cx = (Vmedida) / (42.31 * 499 * 0.000001);

    // Calcular la variación de temperatura (Itemp) en relación a 20°C
    Temp = 87 * VeTemp - 18;
    Itemp = Temp - 20;

    // Inicializar Cx final con el valor de Cx
    fCx = Cx;

    // Realizar un ajuste en la concentración de ozono en función de la temperatura.
    // Si la temperatura es mayor que 20°C, disminuir la concentración en un 3% por grado.
    if (Itemp > 20) {
      fCx = Cx - (Temp * 0.03);
    }

    // Si la temperatura es menor que 20°C, aumentar la concentración en un 3% por grado.
    if (Itemp < 20) {
      fCx = Cx + (Temp * 0.03);
    }

    // Devolver el valor ajustado de la concentración de ozono (fCx).
    Serial.println(fCx);
    return fCx*100;
    } // ()

    // .....................................................
    // Método para medir la temperatura.
    // .....................................................
    int medirTemperatura() {

    return Temp*100;
  } // ()

}; // class


// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
#endif
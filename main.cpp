#include "mbed.h"
#include "C12832.h"
#include "LM75B.h"

C12832 lcd(D11, D13, D12, D7, D10);
//Create an LM75B object at the default address (ADDRESS_0)
LM75B sensor(D14, D15);
/**
* \file main.cpp
* \brief file main
*
*
* \date 29/05/2022
*/
int main()
{
    //Try to open the LM75B
    /**
    * \brief Prova ad aprire il sensore
    */
    if (sensor.open()) {
        printf("Device detected!\n");
        /**
        * \var tempMin temperatura minima
        */
        int tempMin=999;
        /**
        * \var tempMax temperatura massima
        */
        int tempMax;
        /**
        * \var tempAvg temperatura media
        */
        int tempAvg=0;
        /**
        * \var indexAvg numero delle temperature totali acquisite
        */
        int indexAvg=0;
        /**
        * \var sumAvg la somma delle temperature
        */
        int sumAvg;
        while (1) {
            //clear the screen
            /**
            * \brief svuota il display
            */
            lcd.cls();

            //Print the current temperature
            /**
            * \brief stampa la temperatura acquisita sulla console
            */
            printf("Temp = %d\n", (int)sensor.temp());

            /**
            * \var temp valore acquisito
            */
            int temp = sensor.temp();

            //sets the temperature changes
            /**
            * \brief aggiorna le variabili e le temperature sul display se ce n'è bisogno
            */
            if(temp<tempMin){
            tempMin=temp;
            }
            if(temp>tempMax){
                tempMax=temp;
            }
            if(tempAvg==0){
                tempAvg=temp;
                indexAvg++;
                sumAvg=temp;
            }
            else if(tempAvg!=0){
                sumAvg=sumAvg+temp;
                tempAvg=sumAvg/indexAvg;
                indexAvg++;
            }

            //print the current, min, max and avg temperature on display lcd
            /**
            * \brief mostra sul display la temperatura corrente, la minima, la massima e la media
            */
            lcd.locate(3, 2);
            lcd.printf("Temperature: %d'C", temp);
            lcd.locate(3, 12);
            lcd.printf("Min: %d'C Max: %d'C", tempMin, tempMax);
            lcd.locate(3, 22);
            lcd.printf("Avg: %d'C", tempAvg);

            //Sleep for 1 second
            /**
            * \brief rinizia il ciclo dopo 1 secondo
            */
            ThisThread::sleep_for(1000ms);
        }
    } else {
        error("Device not detected!\n");
    }
}

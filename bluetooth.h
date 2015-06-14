#ifndef bluetooth_h
#define bluetooth_h

#include "Arduino.h"
#include <SoftwareSerial.h>


class Bluetooth{
private:
    int rxPin = 2;
    int txPin = 3;
    SoftwareSerial *btSerial = new SoftwareSerial(2, 3);
    char msg[1024];
    void read();
    char Name[256];
    
    void clearArray(char* array, int n);
    
public:
    ///
    /// \brief The valuesTypes enum - enumeracja symbolizująca odpowiednie typy przesyłanych wartości
    ///
    enum valuesTypes{  ACCELERATION, 
                       ANGLE, 
                       BATTERY_VOLTAGE,
                       BATTERY_CURRENT, 
                       SOLAR_VOLTAGE,
                       ENGINE_POWER  };
    ///
    /// \brief Pobranie aktulnego pinu RX
    /// \return
    ///
    int getrxPin();
    ///
    /// \brief Ustawienie aktualnego pinu RX
    /// \param rx - nowy pin RX
    ///
    void setrxPin(int rx);
    ///
    /// \brief Pobranie aktualnego pinu TX
    /// \return
    ///
    int gettxPin();
    ///
    /// \brief Ustawienie aktualnego pinu TX
    /// \param tx - nowy pin TX
    ///
    void settxPin(int tx);
    ///
    /// \brief Funkcja konfigurująca połączenie bluetooth
    ///
    void setupBluetooth();
    ///
    /// \brief Konstruktor tworzący obiekt
    /// \param name - nazwa urządzenie (tak naprawdę może być cokolwiek)
    ///
    Bluetooth(char name[]);
    ///
    /// \brief Konstruktor tworzący obiekt, pozwalający zdefiniować pin RX i TX
    /// \param name - nazwa urządzenie (tak naprawdę może być cokolwiek)
    /// \param r - pin rx
    /// \param t - pin tx
    ///
    Bluetooth(char name[], int r, int t);
    ///
    /// \brief Funkcja pozwalająca na odczytywanie danych z Bluetooth (na nas użytek narazie nie potrzebna)
    /// \return String z wiadomością
    ///
    String Read();
    ///
    /// \brief Bardzo podstawowa funkcja do wysyłania. Służy raczej do konfiguracji i debugowania.
    /// \param c - informacje do wysłaania
    ///
    void Send(char c[]);
    ///
    /// \brief Funckja do pobierania nazwy urządzenia (nieużywana)
    /// \return Zwraca aktualną nazwę urządzenia
    ///
    char *getName();
    ///
    /// \brief Funkcja do ustawiania nazwy urządzenia (nieużywana)
    /// \param c - nowa nazwa urzadzenia
    ///
    void setName(char c[]);
    void SendTo(char c);
    char ReadFrom();
    ///
    /// \brief Funkcja do wysyłania informacji poprzez bluetooth (format informacji: valuesType|inf# np: 1|12.334|232.32|342.4# - służy do przesłania kątu o odpowiednich wartościach)
    /// \param inf - informacja do przesłania kolejne wartości w tablicy to parametry
    /// \param n - ilość parametrów do przesłania
    /// \param type - typ wiadomości
    ///
    void SendInformation(const char inf[], int n, valuesTypes type);
    
    ///
    /// \brief Funkcja do wysyłania przyspieszenia
    /// \param inf - przyspieszenie
    ///
    void SendAcceleration(int inf);
    ///
    /// \brief Funkcja do wysyłania kątów
    /// \param inf_x - kąt x
    /// \param inf_y - kąt y
    /// \param inf_z - kąt z
    ///
    void SendAngle(float inf_x, float inf_y, float inf_z);
    ///
    /// \brief Funkcja do wysyłania napięcia na baterii
    /// \param inf - napięcie na baterii
    ///
    void SendBatteryVoltage(float inf);
    ///
    /// \brief Funkcja do wysyłania natężenia na baterii
    /// \param inf - natężenie na baterii
    ///
    void SendBatteryCurrent(float inf);
    ///
    /// \brief Funkcja do wysyłania napięcia na ogniwach
    /// \param inf - napięcie na ogniwach
    ///
    void SendSolarVoltage(float inf);
    ///
    /// \brief Funkcja do wysyłania mocy silnika
    /// \param inf - moc silnika
    ///
    void SendEnginePower(int inf);
}; 


#endif


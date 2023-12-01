## Symulator IMU

Zadanie polega na napisaniu symulatora IMU, który będzie w stanie naśladować pracę akcelerometru
układu IMU InvenSense ICM-42670-P (akcelerometr i żyroskop). Symulator powinien stanowić odrębną
aplikację, która jest w stanie komunikować się z głównym programem za pomocą dowolnego medium
(np. IPC, połączenie sieciowe). Następnie za pomocą wymyślonego przez kandydata protokołu i formy
jego serializacji należy zaimplementować brakujący sterownik I2C dla głównej aplikacji, który umożliwi
korzystanie ze sterownika IMU na PC w trybie emulacji. Dobrze widziane jest odwzorowanie w
symulatorze wybranych rejestrów układu ICM-42670-P.

Założenia dla symulatora IMU:
• Możliwość odtwarzania danych IMU z pliku CSV – w odpowiedzi na zapytania odczytu
rejestrów z danymi akcelerometru zwracane są poprawnie sformatowane wartości (w 
formacie zgodnym z dokumentacją IMU) z aktualnej linii w pliku CSV. Odczytanie zestawu
danych powoduje przesunięcie wskaźnika odczytu pliku na kolejną linię z danymi.
• Przyjmowanie i przetwarzanie ramek konfiguracyjnych układu IMU


Plik CSV z danymi IMU i opisem formatu zostanie dołączony do zadania.

Symulator pełni rolę pomocniczą. Może więc zostać napisany w dowolnym języku programowania, w
szczególności wspierającym szybkie wytwarzanie oprogramowania (np. Python).

Kryteria oceny etapu zadania:
• Projekt i wdrożenie protokołu komunikacji
• Implementacja symulatora pod kątem zgodności z wymaganiami
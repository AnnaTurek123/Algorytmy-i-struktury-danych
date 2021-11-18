#include <iostream> //cout, cin, endl, back_inserter
#include <string> //to_string
#include <algorithm> //sort, transform
#include <vector> // vector
#include <ctime>
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

std::string GetConcatenatedStringFromVector(std::vector<std::string> vector) {
	std::string concatenatedString = ""; //deklaracja pustej zmiennej typu string
	for (size_t i = 0; i < vector.size(); ++i) { // iteracja tyle razy ile wynosi wielkość wektora
		concatenatedString += vector[i]; //To samo co: concatenatedString = concatenatedString + vector[i] (wszystkie stringi z wektora łączymy w jedno do zmiennej biggestNumber)
	}
	return concatenatedString;
}




std::string GetBiggestNumber(std::vector<int> inputVector) {
	std::vector<std::string> transformedVector; //deklaracja wektora który później będzie miał te same wartości co inputVector tylko w stringach ["1", "2", "3", "4"]


	std::transform( // transformujemy wektor int na wektor string
		inputVector.begin(),  //pierwszy parametr: początkowa wartość inputVector
		inputVector.end(), //drugi parametr: końcowa wartość inputVector
		std::back_inserter(transformedVector), //trzeci parametr: wypełniamy wektor który będzie naszym wynikiem
		[](const int& number) { return std::to_string(number); } // czwarty parametr: funkcja, dzięki kórej wiadomo jak przetransformować wektor
	);

	std::sort(
		transformedVector.begin(), //pierwszy parametr: początkowa wartość transformedVector
		transformedVector.end(), //drugi parametr: końcowa wartość transformedVector
		[](const std::string& lhs, const std::string& rhs) { return rhs + lhs < lhs + rhs; } //funkcja która pobiera 2 parametry, łączy je ze sobą w różnej kolejności i na podstawie większy/mniejszy ustala w jakiej kolejności posortować dane w wektorze
	);  //lhs, rhs - parametry, które przekazujemy do ciała funkcji, łączymy je na dwa sposoby i porównujemy

	std:: string biggestNumber = GetConcatenatedStringFromVector(transformedVector); //uzyskanie biggestNumber poprzez konkatenację elementów wektora w osobnej fukncji

	return biggestNumber;

}





void tests (int NumberOfTests) // funkcja typu void nie zwracca żadnej wartości, danych które później mogłyby być poddane obróbce
{
    std::ofstream test; // zapis do pliku jakim będzie notatnik
    test.open ("wyniki.txt"); // otwieramy połączenie z plikiem
    srand((unsigned) time(NULL)); // funkcja losująca liczby używane do testu

    std::string temp;

    high_resolution_clock::time_point start; // high_resolution_clock to typ zmiennej czasowej
    high_resolution_clock::time_point stop;
    duration<double> time; //przedział czasowy -- "tiki" najmniejsza  reprezentacja czasu
    int n = 100; // liczba elementów wektora
    int m; // liczba testów
    for (m = 0; m < NumberOfTests; m++){ // oblicza czas tyle razy ile wynosi liczba testów wpisanych przez użytkownika
        vector<int> inputVector(n); // bierze 100 losowych elementów z wektora inputVector

            for (int i = 0; i < inputVector.size(); i++)
            inputVector[i] = rand(); // losujemy liczbę i przypisujemy ją do konkretnego elementu w wektorze

        start = high_resolution_clock::now();
        temp = GetBiggestNumber(inputVector);
        stop = high_resolution_clock::now();
        time = stop - start; // obliczanie czasu

        test << "Czas" << setw(10) << time.count();
        test << "Liczba elementów vectora" << n << endl;
        n = n * 3; // mnoży początkowe elementy razy x
    }
    test.close(); // zamykamy połączenie z plikiem

    }



int main(){

	int input; // deklaracja zmiennej
	std::vector<int> inputVector; //deklaracja wektora do którego wrzucimy nasze inputy (int) [1,2,3,4]

	std::cout << " Press \n t - test \n c - continue" << std::endl;
	char option;
	std::cin >> option;
	switch (option){
	case 't': {
        int NumberOfTests;
        std::cout << "input number of test" << std::endl;
        std::cin >> NumberOfTests;
        tests (NumberOfTests);
        break;
    }
    default: {

        std::cout << "Fill vector with numbers." << std::endl;
        std::cout << "Write 'x' if you want to end." << std::endl;

        while (std::cin >> input) { //pętla while gdzie warunek jest spełniony dopóki nie wpiszemy litery
            inputVector.push_back(input); // zapełnianie wartościami wektora
        }
        std::string biggestNumber = GetBiggestNumber(inputVector); //przeniesienie głównej logiki do funkcji GetBiggestNumber()
        std::cout << "Your biggest number is: " + biggestNumber << std::endl;
        break;
    }
    }

}

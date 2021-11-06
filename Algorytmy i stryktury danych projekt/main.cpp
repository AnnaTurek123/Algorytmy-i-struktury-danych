#include <iostream> //cout, cin, endl, back_inserter
#include <string> //to_string
#include <algorithm> //sort, transform
#include <vector> // vector
#include <ctime>

std::string GetConcatenatedStringFromVector(std::vector<std::string> vector) {
	std::string concatenatedString = ""; //deklaracja zmiennej typu string
	for (size_t i = 0; i < vector.size(); ++i) {
		concatenatedString += vector[i]; //To samo co: biggestNumber = biggestNumber + transformedVector[i] (wszystkie stringi z wektora łączymy w jedno do zmiennej biggestNumber)
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
		transformedVector.begin(), //pierwszy parametr: początkowa wartość inputVector
		transformedVector.end(), //drugi parametr: końcowa wartość inputVector
		[](const std::string& lhs, const std::string& rhs) { return rhs + lhs < lhs + rhs; } //funkcja która pobiera 2 parametry, łączy je ze sobą w różnej kolejności i na podstawie większy/mniejszy ustala w jakiej kolejności posortować dane w wektorze
	);  //lhs, rhs - parametry, które przekazujemy do ciała funkcji, łączymy je na dwa sposoby i porównujemy

	std:: string biggestNumber = GetConcatenatedStringFromVector(transformedVector); //uzyskanie biggestNumber poprzez konkatenację elementów wektora w osobnej fukncji

	return biggestNumber;
}

int main() {

	int input; // deklaracja zmiennej
	std::vector<int> inputVector; //deklaracja wektora do którego wrzucimy nasze inputy (int) [1,2,3,4]
	std::clock_t start; //deklaracja zmiennej start
	double duration; // deklaracja zeminnej duration

	std::cout << "Fill vector with numbers." << std::endl;
	std::cout << "Write 'x' if you want to end." << std::endl;

	while (std::cin >> input) { //pętla while gdzie warunek jest spełniony dopóki nie wpiszemy litery
		inputVector.push_back(input); // zapełnianie wartościami wektora
	}
	start = std::clock(); //start odliczania czasu

	std::string biggestNumber = GetBiggestNumber(inputVector); //przeniesienie głównej logiki do funkcji GetBiggestNumber()

	std::cout << "Your biggest number is: " + biggestNumber << std::endl;

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC; // obliczenie czasu trwania pracy aplikacji
	std::cout << "printf: " << duration << '\n'; //wyświetlenie czasu
}


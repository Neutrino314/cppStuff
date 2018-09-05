#include <iostream>
#include <string>
#include <vector>
#include <cmath>

class primeCalculator {

    private:

        int primeCandidate{2};
        int primesAmount;
        std::vector<int> primesArray;
        int primesCalculated{0};

    public:

        void printArray() {

            std::string arrayString = "[ ";

            for (int i = 0; i < primesAmount; i++) {

                arrayString += std::to_string(primesArray[i]) + " ";
            }

            arrayString += "]";

            std::cout << "\n\n" << arrayString << std::endl;

        }

        void choosePrimesAmount() {

            std::cout << "Enter the amount of primes to be calculated: ";
            std::cin >> primesAmount;

            primesArray.resize(primesAmount);
            primesArray.clear();
            primesCalculated = 0;
            primeCandidate = 2;

        }

        bool isPrime() {

            int increment{1};
            int factors{0};

            for (int divisor = 1; divisor <= std::sqrt(primeCandidate) + 1; divisor += increment) {

                if (factors > 1) {

                    return false;

                } else {

                    if (primeCandidate % divisor == 0) factors ++;
                }
            }

            return true;
        }

        void calculate() {

            int whileIncrement = 1;

            choosePrimesAmount();

            while (primesCalculated < primesAmount) {

                std::cout << primesCalculated << " calculations completed" << std::endl;

                if (isPrime()) {

                    primesArray[primesCalculated] = primeCandidate;
                    primesCalculated ++;

                }

                if (primeCandidate == 3) whileIncrement = 2;

                primeCandidate += whileIncrement;

            }

            printArray();

        }

};



int main() {

    primeCalculator calculator;

    int option;

    bool running(true);

    while (running) {

        std::cout << "1:Calculate primes \n2:Print Calculated primes \n3:Quit \n";
        std::cin >> option;

        switch (option) {

            case 1:

                calculator.calculate();
                break;

            case 2:

                calculator.printArray();
                break;

            case 3:

                running = false;
                break;

            default:

                std::cout << "Invalid input please try again \n\n";
                break;

        }

        std::cout << "\n\n\n";
    }

    return 0;
}

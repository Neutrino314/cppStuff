#include <iostream>

using namespace std;

int main()
{

    int primesAmount; //Declares a variable that determines the amount of primes to be calculated

    cout << "How many primes would you like to calculate: ";
    cin >> primesAmount;//defines the previously mentioned variable

    int primesArray[primesAmount]; //defining an array to hold all calculated primes
    int primesCalculated = 0; //keeps track of the amount of primes calculated
    int count = 2; //number being checked as a prime
    int factors = 0; //amount of factors the number has

    time_t start = time(0); //records tme in seconds when the program starts

    while (primesCalculated < primesAmount) { //loops while amount of primes calculated is less than amount specified

        for (int i = 1; i < count; i++) { //loops through all numbers less than current number

            if (factors == 2) { //if the number has 2 factors breakss the loop and sets factors to 0
                    factors = 0;
                break;
            }else {

                if (count % i == 0) { //if the remainder of the number divided by i is equal to 0 the factors ++

                    factors ++;
                }
            }
        }

        if (factors == 1) { //if the number has only one factor(1) then number is prime and is added to the array
            primesArray[primesCalculated] = count;
            primesCalculated ++;
            factors = 0; //sets factors to 0
        }

        if (count == 2) { // if the number being checked i 2 then increment count by 1

            count ++;
        }else { //otherwise increment by 2 allowing the program to skip all other even numbers

            count += 2;
        }

    }

    for (int i = 0; i < primesAmount; i++) { //prints out the contents of the array
        cout << primesArray[i] << ",";
    }

    cout << endl << primesAmount << " primes calculated in " << time(0) - start << " seconds" << endl; //prints time taken to calculate numbers by subtracting current time from starting time
    cout << sizeof(primesArray) << endl;

    return 0;

}

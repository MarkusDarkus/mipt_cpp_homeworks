#include <iostream>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
#include <limits>


int count(const std::vector<char>& digits, char d)
{
    int k =0;
    for (int i=0; i< digits.size(); i++)
        if (digits[i] == d)
            k++;
    return k;
}

void validate(const std::vector<char>& number)
{
    for( int i =0; i< number.size(); i++)
    {
        if(number[i] < '0' || number[i] > '9')
            throw std::runtime_error("The number contains not digits");
        if (count(number, number[i]) != 1)
            throw std::runtime_error("Digits of the number is not unique");
        
    }
}

std::vector<char> user_guess()
{
    std::vector<char> number(4);
    std::cout<<"guess the number: ";
    for (int i=0; i<number.size();i++)
        std::cin >> number[i];
    
    if(!std::cin)
        throw std::runtime_error("Invalid input");
    
    validate(number);
    return number;
}

int main()
try
{
    std::cout<< "Bulls and Cows the game \n"
             << "Computer sets a number of 4 unique digits. \n"
             << "Try to guess it\n"
             << "Bull means right digit in the right position\n"
             << "Cow means right digit in the wrong position. \n\n"
             << "Game is on!!!"<<std::endl;

    std::vector<char> number{'1', '3','7','2'};


    int bulls, cows;

    do
    {
        bulls = cows = 0;
        std::vector<char> ugess = user_guess();
        for( int i =0; i<ugess.size(); i++){
            if(ugess[i] == number[i])
                ++bulls;
            else if(count(number, ugess[i]) == 1)
                ++cows;
        }

        std::cout<< bulls << " bull(s) and "<<cows << " cow(s)"
                 << std::endl;

    } while (bulls !=4);
    std::cout<<"game is over"<<std::endl;
    return 0;

}
catch(std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}

catch(...)
{
    std::cerr << "Unknown error"<<std::endl;
    return 2;
}
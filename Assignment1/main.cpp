#include <iostream>
#include <stdexcept>
using namespace std;

unsigned long long NonZeroModulus(unsigned long long int x, unsigned long long int y)
{
    auto mod = x%y;
    mod += y * (mod == 0);
    return mod;
}

// Assumption : numPeople > 0 and skipLength >= 2 - not checking and throwing for optimization reasons!
unsigned long long int JosephusSurviver (unsigned long long int numPeople, unsigned int skipLength) 
{
    if (numPeople >= skipLength)
    {
        // exactly [numPeople/skipLength] people will be killed 
        // before a person is re-observed for elimination - a 'round'
        auto numPeopleKilled = numPeople/skipLength;
        auto lastKilledInRoundIndex = numPeopleKilled * skipLength;
        auto peopleSkippedAfterLastDead = numPeople - lastKilledInRoundIndex;

        // if you re-assign the values after the last elimination to 1-n
        auto newIndexAfterFirstRound = JosephusSurviver(numPeople - numPeopleKilled, skipLength);

        // converting back to the previous index accounting for dead and skipped people
        auto indexAfterFirstRound = newIndexAfterFirstRound;
        indexAfterFirstRound += (newIndexAfterFirstRound > peopleSkippedAfterLastDead) * (newIndexAfterFirstRound - peopleSkippedAfterLastDead - 1) / (skipLength - 1);

        return NonZeroModulus(lastKilledInRoundIndex + indexAfterFirstRound , numPeople);
    }
    else 
    {
        if (numPeople > 1)
        {
            auto firstKilled = NonZeroModulus(skipLength, numPeople);
            auto indexAfterFirstKilled = JosephusSurviver(numPeople - 1, skipLength);
            return NonZeroModulus(firstKilled + indexAfterFirstKilled, numPeople);
        }
        else if (numPeople == 1)
        {
            return 1;
        }
        else
        {
            throw std::runtime_error("numPeople = 0 in JosephusSurviver : this should never happen!");
        }
    }
}

int main() {
    unsigned long long int numPeople;
    unsigned int skipLength;
    cin >> numPeople >> skipLength;
    cout<< JosephusSurviver(numPeople, skipLength) << std::endl;
}
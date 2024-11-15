#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

#include "ElectoralDistrict.h"
#include <algorithm>

using namespace std;

#pragma region Assignment 
/*Assigned to: Александър Ганчев, фак. 121222032, 45б, КСИ, ФКСТ, 3 Курс*/

/* Да се дефинира клас Избирателен район Член-данните на класа са: 
1) име на района; 2) брой гласоподаватели на района; 3) брой партии, за които се гласува; 
4) динамичен масив, съдържащ броя гласували за всяка партия; 
5) масив от символни низове, съдържащи имената на партиите (инициалите им).

Съставете програма, която:
1.      Създава файл от обейкти - избирателни райони.
2.      Извежда процента гласове за всяка партия по райони, подредени по азбучен ред на името на района.
3.      Извежда имената на районите, в които няма победител в изборите.
4.      Записва имената районите от т.3, както и процента на негласувалите в тях в нов файл. 
*/
#pragma endregion

#pragma region DummyData
vector<string> dummyDistrictNames = {
        "Sofia", "Plovdiv", "Varna", "Burgas", "Ruse", "Blagoevgrad"
};
vector<int> dummyTotalVoters = { 
        100000, 50000, 45000, 35000, 25000, 20000
};
vector<vector<int>> dummyVotes = {
        {5000, 20000, 40000, 30000, 25000, 10000, 35000},
        {2000, 10000, 20000, 8000, 6000, 4000, 12000},
        {4000, 12000, 16000, 11000, 8000, 5000, 16000},
        {3000, 8000, 12000, 7000, 6000, 5000, 12000},
        {500, 6000, 10000, 4000, 2000, 1000, 8000},
        {500, 4000, 8000, 3000, 2000, 1000, 5000}
};

vector<string> dummyInitials = {"Mech", "DPS", "GERB", "ITN", "PP-DB", "V", "BSP"};
#pragma endregion

int main()
{
    vector<ElectoralDistrict> districts;
    for (int i = 0; i < dummyDistrictNames.size(); i++) {
        districts.emplace_back(dummyDistrictNames[i], dummyTotalVoters[i], dummyVotes[i], dummyInitials);
    }

    ofstream mainWriter("districts_results.txt");

    if (!mainWriter) {
        cerr << "Error opening file: no_winner_disctricts.txt" << endl;
        return 1;
    }
    else {
        /* Записът на файла не е сортиран (по проценти и по азбучен ред) 
        с идеята да бъде видна разликата между сотрирания му вид (показан на конзолата)
        и първоначалния му такъв (предоставен в началото на main и съответно написан във файла).
        */
        for (const auto& district : districts) {
            mainWriter << district;
        }
        cout << "Message: Districts information has been successfully saved to the provided datasheet files." << endl;
    }

    mainWriter.close();

    // Операция на сортиране по имена на район след записването във файла.
    sort(districts.begin(), districts.end(), 
        [](const ElectoralDistrict& a, const ElectoralDistrict& b) {
            return a.getDistrict() < b.getDistrict();
        });

    cout << "----------------------------" << "\nVote Percentages by district\n" <<  "----------------------------" << endl;
    for (const auto& district : districts) {
        // Интегрирана сотрирофка на резултатите на база процентно количество
        district.displayPartyVotesPercentage();
    }

    ofstream noWinnerWriter("no_winner_districts.txt");
    if (!noWinnerWriter) {
        cerr << "Error opening file: no_winner_disctricts.txt" << endl;
        return 1;
    }

    cout << "-------------------------------" << "\nDistricts with no clear winner\n" "-------------------------------" << endl;
    for (const auto& district : districts) {
        if (!district.hasClearWinner()) {
            cout << district.getDistrict() << endl;
            double nonVoterPercentage = district.calculateNonVoterPercenatge();
            noWinnerWriter << district.getDistrict() << ": Non-voter percentage " << fixed << setprecision(2) << nonVoterPercentage << "%" << endl;
        }
    }

    noWinnerWriter.close();
    return 0;
}

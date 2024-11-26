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
    20000, 7500, 6000, 6000, 5000, 3500
};
vector<vector<int>> dummyVotes = {
    {300, 500, 10200, 700, 700, 300, 1300}, // Sofia
    {100, 300, 3800, 250, 200, 100, 450},   // Plovdiv
    {200, 400, 3200, 300, 200, 150, 550},   // Varna
    {150, 300, 2400, 400, 300, 150, 600},   // Burgas
    {100, 200, 1400, 400, 300, 100, 300},   // Ruse
    {50, 150, 1000, 300, 200, 100, 300}     // Blagoevgrad
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

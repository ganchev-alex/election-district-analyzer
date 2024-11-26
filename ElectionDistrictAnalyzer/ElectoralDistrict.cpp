#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "ElectoralDistrict.h"

using namespace std;

#pragma region PropertiesManagement

ElectoralDistrict::ElectoralDistrict(const string& aDistrict, int aTotalVoters, const vector<int>& aVotesPerParty, const vector<string>& aPartiesInitials)
	: district(aDistrict), totalVoters(aTotalVoters), totalPartyOptions(aVotesPerParty.size()), votesPerParty(aVotesPerParty), partiesInitials(aPartiesInitials) {};

const string& ElectoralDistrict::getDistrict() const { return district; }
int ElectoralDistrict::getTotalVoters() const { return totalVoters; }
int ElectoralDistrict::getTotalPartyOptions() const { return totalPartyOptions; }
const vector<int>& ElectoralDistrict::getVotesPerParty() const { return votesPerParty; }
const vector<string>& ElectoralDistrict::getPartiesInitials() const { return partiesInitials; }

#pragma endregion

#pragma region Functionallity

void ElectoralDistrict::displayPartyVotesPercentage() const {
	cout << "District: " << district << endl;

	vector<pair<string, double>> calculatedResults;
	for (int i = 0; i < totalPartyOptions; i++) {
		double percentage = static_cast<double>(votesPerParty[i]) / totalVoters * 100;
		calculatedResults.emplace_back(this->partiesInitials[i], percentage);
	}

	sort(calculatedResults.begin(), calculatedResults.end(), 
		[](const auto& a, const auto& b) {
		return a.second > b.second;
	});

	for (const auto& party : calculatedResults) {
		cout << "Party " << party.first << ": " << fixed << setprecision(2) << party.second << "%" << endl;
	}

	cout << "Non-voters percantage: " << calculateNonVoterPercenatge() << fixed << setprecision(2) << "%" << endl;

	cout << "\n";
}

ostream& operator<<(ostream& out, const ElectoralDistrict& district) {
	out << "District: " << district.getDistrict() << endl;
	for (int i = 0; i < district.getTotalPartyOptions(); i++) {
		double percentage = static_cast<double>(district.getVotesPerParty()[i]) / district.getTotalVoters() * 100;
		out << district.getPartiesInitials()[i] << ": " << percentage << "%" << endl;
 	}

	out << endl;
	return out;
}

bool ElectoralDistrict::hasClearWinner() const {
	for (int votes : votesPerParty) {
		double percentage = static_cast<double>(votes) / totalVoters * 100;
		if (percentage > 50.0) {
			return true;
		}
	}
	return false;
}

double ElectoralDistrict::calculateNonVoterPercenatge() const {
	int totalVotes = 0;
	for (int i = 0; i < totalPartyOptions; i++) {
		totalVotes += votesPerParty[i];
	}

	return static_cast<double>(totalVoters - totalVotes) / totalVoters * 100;
}
#pragma endregion

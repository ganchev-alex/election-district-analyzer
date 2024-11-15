#include <ostream>

using namespace std;

#pragma once
class ElectoralDistrict
{
	private:
		string district;
		int totalVoters;
		int totalPartyOptions;
		vector<int> votesPerParty;
		vector<string> partiesInitials; 
	public:
		ElectoralDistrict(const string& aDistrict, int aTotalVoters, const vector<int>& aVotesPerParty, const vector<string>& aPartiesInitials);

		const string& getDistrict() const;
		int getTotalVoters() const;
		int getTotalPartyOptions() const;
		const vector<int>& getVotesPerParty() const;
		const vector<string>& getPartiesInitials() const;

		friend ostream& operator<<(ostream& out, const ElectoralDistrict& district);
		void displayPartyVotesPercentage() const;
		bool hasClearWinner() const;
		double calculateNonVoterPercenatge() const;
};
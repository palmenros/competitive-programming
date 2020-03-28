//
// Created by pedro on 28/3/20.
//

#include <unordered_map>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

struct ProblemInfo
{
	bool accepted;
	int time;
	int wrongSubmissions;

	ProblemInfo() = default;

	ProblemInfo(bool accepted, int time, int wrongSubmissions)
		: accepted(accepted), time(time), wrongSubmissions(wrongSubmissions)
	{}
};

struct TeamInfo
{
	int solvedProblems;
	int time;

	TeamInfo() = default;

	TeamInfo(int solvedProblems, int time)
		: solvedProblems(solvedProblems), time(time)
	{}
};

int main()
{
	int nCasos;
	cin >> nCasos;
	while(nCasos--)
	{
		unordered_map<string, unordered_map<string, ProblemInfo>> problems;
		unordered_map<string, TeamInfo> teamInfo;

		string team;
		while (cin >> team && team != "FIN") {
			string problem;
			int time;
			bool accepted;

			string tmp;
			cin >> problem >> time >> tmp;
			accepted = tmp == "AC";

			auto& teamProblems = problems[team];

			auto it = teamProblems.find(problem);
			if(it == teamProblems.end()) {
				//Not previously submitted
				auto& info = teamProblems[problem];

				if(accepted) {
					info.accepted = true;
					info.time = time;
					info.wrongSubmissions = 0;

					//Add to team info
					teamInfo[team].solvedProblems++;
					teamInfo[team].time += info.time + info.wrongSubmissions * 20;
				} else {
					info.accepted = false;
					info.wrongSubmissions = 1;
				}

			} else {
				//Previously submitted
				if(it->second.accepted) {
					//If already accepted, continue
					continue;
				}

				if(accepted) {
					it->second.time = time;
					it->second.accepted = true;

					//Add to team info
					teamInfo[team].solvedProblems++;
					teamInfo[team].time += it->second.time + it->second.wrongSubmissions * 20;
				} else {
					it->second.wrongSubmissions++;
				}
			}

			if(teamInfo.find(team) == teamInfo.end()) {
				teamInfo[team] = TeamInfo{0, 0};
			}
		}

		vector<pair<string, TeamInfo>> v;

		//Generate ranking
		for(const auto& p : teamInfo){
			v.push_back(p);
		}

		sort(v.begin(), v.end(), [](const pair<string, TeamInfo>& a, const pair<string, TeamInfo>& b){
			const auto& [aName, aInfo] = a;
			const auto& [bName, bInfo] = b;

			if(aInfo.solvedProblems != bInfo.solvedProblems) {
				return aInfo.solvedProblems > bInfo.solvedProblems;
			}

			if(aInfo.time != bInfo.time) {
				return aInfo.time < bInfo.time;
			}

			return aName < bName;

		});

		for(const auto& [key, val] : v) {
			cout << key << " " << val.solvedProblems << " " << val.time << endl;
		}

		cout << "---" << endl;
	}
}
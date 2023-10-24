// string tournamentWinner(
//   vector<vector<string>> competitions, vector<int> results
// ) {
//   // Write your code here.
//   unordered_map<string, int> m1;
//   for(int i=0; i<competitions.size(); i++) {
//     int winner = results[i] == 0 ? 1 : 0;
//     if(m1.find(competitions[i][winner]) != m1.end()) {
//       m1[competitions[i][winner]] += 3;
//     } else {
//       m1[competitions[i][winner]] = 3;
//     }
//   }
//   int bestScore = -1;
//   string bestTeam = "";
//   for(auto p1 : m1) {
//     if(p1.second > bestScore) {
//       bestScore = p1.second;
//       bestTeam = p1.first;
//     }
//   }
//   return bestTeam;
// }

bool comp(const pair<string, int>& a, const pair<string, int>& b) {
    return a.second < b.second;
}

string tournamentWinner(
  vector<vector<string>> competitions, vector<int> results
) {
  // Write your code here.
  map<string, int>scores;
  for(int i=0; i<competitions.size(); i++) {
    int winnerTeam = results[i] == 1 ? 0 : 1;
    if(scores.find(competitions[i][winnerTeam]) == scores.end()) {
      scores[competitions[i][winnerTeam]] = 3;
    } else {
      scores[competitions[i][winnerTeam]] += 3;
    }
  }
  
  return (max_element(scores.begin(), scores.end(), comp))->first;
}

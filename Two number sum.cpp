// Two number sum

vector<int> twoNumberSum(vector<int> array, int targetSum) {
  // unordered_set<int> uniques = {};
  // for(auto num : array) {
  //   int targetNum = targetSum - num;
  //   if(uniques.find(targetNum) != uniques.end()) {
  //     return {num, targetNum};
  //   } else {
  //     uniques.insert(num);
  //   }
  // }
  // return {};

  sort(array.begin(), array.end());
  int left=0, right=array.size() - 1;
  if(array.size() <= 1) {
    return {};
  } 
  while(left<right) {
    int currentSum = array[left] + array[right];
    if(currentSum > targetSum) {
      right--;
    } else if(currentSum <targetSum) {
      left++;
    } else {
      return {array[left], array[right]};
    }
  }

  return {};
}
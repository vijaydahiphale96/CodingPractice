vector<vector<int>> threeNumberSum(vector<int> array, int targetSum) {
  sort(array.begin(), array.end());
  vector<vector<int> > v1;
  for(int i=0; i< array.size() - 2 ; i++) {
    int left = i+1;
    int right = array.size() - 1;
    while(left < right) {
      int currentSum = array[i] + array[left] + array[right];
      if(currentSum > targetSum) {
        right--;
      } else if(currentSum < targetSum) {
        left++;
      } else {
        v1.push_back({array[i], array[left], array[right]});
        left++;
        right--;
      }
    }
  }
	
  return v1;
}
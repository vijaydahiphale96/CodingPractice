class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        if(nums.size() == 0) {
            return 0;
        }
        int start = 0, end = nums.size() - 1;
        int mid = (start + end)/2;
        while(start<=end) {
            mid = start + (end - mid)/2;
            if(nums[mid] > target) {
                end = mid - 1;
            } else if (nums[mid] < target) {
                start = mid + 1;
            } else {
                return mid;
            }
        }
        return start;
    }
};
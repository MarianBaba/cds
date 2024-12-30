public class Solution {

    private int binarySearch(Integer[] arr, Integer target){
        int low = 0;
        int high = arr.length;
        while (low <= high) {
            int middle = low + ((high - low) / 2);
            if (arr[middle] == target) {
                return middle;
            }
            if (arr[middle] > target) {
                high = middle - 1;
            } else {
                low = middle + 1;
            }
        }
        return -1;
    }

    public static void main(String... args) {
        Integer[] arr = {1, 2, 3, 4, 4, 5};
        Solution sol = new Solution();
        int res = sol.binarySearch(arr, 4);

        while (res != -1) {
            
        }
    }
}
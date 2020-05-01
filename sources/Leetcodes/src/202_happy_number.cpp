class Solution {
public:
    bool isHappy(int n) {
        int sum = 0;
        while(1){
            int digit = n%10;
            sum += digit*digit;
            n = n/10;
            if(n == 0){
                if(sum >= 0 && sum <= 9){
                    break;
                }
                n = sum;
                sum = 0;
            }
        }
        if(sum == 1 || sum == 7){
        return true;
        }
        else{
            return false;
        }
    }
};

int main()
{
    return 0;
}
//
//  main.cpp
//  Leetcode Exercises
//
//  Created by Walt Semrau on 3/4/23.
//

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <map>

using namespace std;

long long countSubarrays(vector<int>&, int, int);

int minimumVarience(vector<int>);


int main(int argc, const char * argv[]) {
    // insert code here...
    int mynums[] = {3,4,5,6};
    vector<int> nums(mynums,mynums+4);
    
    cout<< countSubarrays(nums, 1, 5)<<endl;
    return 0;
}

long long countSubarrays(vector<int>& nums, int minK, int maxK) {
    queue<long> maxIndex, minIndex, outIndex;
    long long numSubArrays = 0;
    
    for(long i = 0; i<nums.size();i++){
        int num = nums[i];
        if(num == minK){
            minIndex.push(i);
        }
        else if(num == maxK){
            maxIndex.push(i);
        }
        else if(num<minK || num>maxK){
            outIndex.push(i);
        }
    }
    outIndex.push(nums.size());
    
    for(long i = 0; i<nums.size(); i++){
        int num = nums[i];
        if(num<minK || num>maxK){
            outIndex.pop();
        }
        else if(num == minK){
            minIndex.pop();
            if(maxIndex.empty()) return numSubArrays;
            long diff = outIndex.front() - maxIndex.front();
            if(diff>0){
                numSubArrays += diff;
            }

        }
        else if(num == maxK){
            maxIndex.pop();
            if(minIndex.empty()) return numSubArrays;
            long diff = outIndex.front() - minIndex.front();
            if(diff>0){
                numSubArrays += diff;
            }
        }
        else{
            if(minIndex.empty() || maxIndex.empty()) return numSubArrays;
            long min = minIndex.front(), max = maxIndex.front(), out = outIndex.front();
            if(min<out && max<out){
                numSubArrays += (out - std::max(max, min));
            }
        }
    }
        
    return numSubArrays;
    }

int minimumVarience(vector<int> nums){
    map<int,int> data;
    for(int i = 0; i<nums.size();i++){
        int count = 0;
        int num = nums[i];
        if(num%2 == 1) count++;
        while(num%2==0){
            count++;
            num /= 2;
        }
        if(data.count(num)){
            data[num] = min(count, data[num]);
        }else data[num] = count;
    }
    
    map<int,int>::iterator curr, next, temp;
    curr = data.begin();
    next = data.begin();
    next++;
    while(next != data.end() && curr->second != 0){
        int num = curr->first;
        int hold = num;
        int nextNum = next->first;
        temp = data.begin();
        int min = temp->first;
        temp = data.end();
        temp--;
        int max = temp->first;
        int count = 0;
        while(num*2<nextNum && count < curr->second){
            num*=2;
            count++;
        }
        if(std::max(max, num*2)-nextNum < max-min && count<curr->second){
            data[num*2] = data[hold]-(count+1);
            data.erase(hold);
            curr = data.begin();
            next = curr;
            next++;
        }
        else{
            data[num] = data[hold] - count;
            curr++;
            next = curr;
            next++;
            if(hold<num) data.erase(hold);
        }
    }
    temp = data.end();
    temp--;
    int max = temp->first;
    return max - data.begin()->first;
}

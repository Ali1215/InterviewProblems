/*
Name: Ali Muneer
Student ID: 1615694
CMPUT 275; Winter 2021
Weekly Exercise 7: Divide and Conquer
*/

#include <iostream>
typedef unsigned int uint;
using namespace std;
uint calculate_time(const uint *heights, uint length, uint rest, int jump)
{
    /*
    Description:  calculates the time needed to reach the top of the mountain
                    for a particular jump value

    args: heights  = array of unsigned integers that show the heights of cliffs
          length = the amount of cliffs, (length of heights array)
          rest    = the resting time after each climb
          jump   = the particular jump value being computed
    
    returns: uint
    */
    int current = 0; //current cliff
    int time = 0;
    for (int i = 1; i < length; i++)
    {
        //if the cliff is too high for the jump
        if ((heights[i] - current) > jump)
        {
            //add the time difference between last reachable cliff and current
            time += heights[i - 1] - current;
            //resting time
            time += rest;
            //update current
            current = heights[i - 1];
        }
    }
    //add time to get to last cliff
    time += heights[length - 1] - current;
    return time;
}

int max_delta(const uint *heights, uint length)
{
    /*
    Description:  Calculates the maximum difference in cliff heights to be
                    used as a minimum for binary search. (anything less will not allow
                    for the climber to reach the top).

    args: heights*  = array of unsigned integers that show the heights of cliffs
          length = the amount of cliffs, (length of heights array)
          
    
    returns: int
  */
    int ans = 0;
    for (int i = 1; i < length; i++)
    {
        //if delta is greater than current max, update max
        if ((heights[i] - heights[i - 1]) > ans)
            ans = heights[i] - heights[i - 1];
    }
    return ans;
}

uint climbing(const uint *heights, uint length, uint rest, uint limit)
{
    /*
    Description:  calculates the minimum amount of a "jump value" needed to
                    climb the mountain within the limit

    args: heights  = array of unsigned integers that show the heights of cliffs
          length = the amount of cliffs, (length of heights array)
          rest    = the resting time after each climb
          limit   = the time limit to ascend the mountain
    
    returns: uint
    */
    //low for binary search is the max delta in the cliff heights, or the height
    //of the first cliff, whichever is higher. 1 is subtracted to make lower bound
    int low = max(max_delta(heights, length), static_cast<int>(heights[0])) - 1;
    int high = limit;

    while (low + 1 < high)
    {
        int mid = (low + high) / 2; // integer division
        //calculate time needed for given jump value
        int time = calculate_time(heights, length, rest, mid);

        if (time > limit)
        {
            //if limit is exceeded jump needs to be higher
            low = mid;
        }
        else
        {
            //jump can be lower otherwise
            high = mid;
        }
    }
    return high;
}

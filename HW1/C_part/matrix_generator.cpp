#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>

double irand(double min, double max) {
    return ((double)rand() / ((double)RAND_MAX + 1.0)) * (max - min + 1) + min;
}

int main()
{
    double COUNT = 9,    // X
    	ROWS = 1,
        MAX_VAL = 10,  // Y
        MAX_SUM = 10; // Z

	srand(time(0));
    for(int k = 0; k < ROWS; ++k){
    std::vector<double> buckets(COUNT, 0);
    
    double remaining = MAX_SUM;
    while (remaining > 0)
    {
        double rndBucketIdx = irand(0, COUNT-1);
        if (buckets[rndBucketIdx] == MAX_VAL)
            continue;                       // this bucket is already full
        buckets[rndBucketIdx]++;
        remaining--;
    }

    for (size_t i = 0; i < COUNT; ++i)
        std::cout << buckets[i]/10 << ' ';

    //std::cout << std::endl;
}
}
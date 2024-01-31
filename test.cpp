#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main()
{
    std::vector<int> myVector;

    myVector.push_back(5);
    myVector.push_back(6);
    myVector.push_back(7);
    int temp = myVector.front();
    std::cout << temp << std::endl;
    myVector.erase(myVector.begin());
    if (!myVector.empty())
    {
        std::cout << 1 << std::endl;
    }
    for (const auto &element : myVector)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    queue<int> myQueue;
    myQueue.push(5);
    myQueue.push(6);
    myQueue.push(7);
    int tempQueue = myQueue.front();
    cout << tempQueue << endl;
    myQueue.pop();
    // Print the elements of the vector
    while (!myQueue.empty())
    {
        std::cout << myQueue.front() << " ";
        myQueue.pop();
    }

    return 0;
}

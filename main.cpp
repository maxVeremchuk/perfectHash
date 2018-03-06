#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <limits>
#include <cmath>
using namespace std;

#define HashPrimeNumber 	101

int hashFunc(int a, int b, int prime, int size, int key)
{
	return abs(((a*key + b) % prime) % size);
}
int q = 0;
class Node
{
private:
	vector<int> backet;
	int size;
	int a, b;
	int prime;
public:
	Node()
	{}

	void Init()
	{
		prime = HashPrimeNumber;
		a = rand() % prime;
		b = 1 + rand() % (prime - 1);
		
	}

	void Construct(vector<int> input)
	{
		if (input.empty())
		{
			size = 0;
			return;
		}

		int max = numeric_limits<int>::max();

		size = input.size() * input.size();	
		int hashKey;
		bool flag = true;
		while (flag)
		{
			Init();
			backet.assign(size, max);
			for (vector<int>::iterator i = input.begin(); i != input.end(); i++)
			{
				hashKey = hashFunc(a, b, prime, size, *i);
				if (backet[hashKey] != numeric_limits<int>::max())
				{
					flag = false;
					break;
				}
				backet[hashKey] = *i;
			}
			flag = !flag;
		}
	}

	bool Contains(int elem)
	{
		if (size == 0)
		{
			return false;
		}
		int hashKey = hashFunc(a, b, prime, size, elem);
		if (backet[hashKey] == elem)
		{
			return true;
		}
		return false;
	}
};

class PerfectHash
{
	int size;
	int hashA;
	int hashB; 
	int prime;
	vector<vector<int>> elements;
	vector<Node> backets;
public:
	PerfectHash()
	{
		prime = HashPrimeNumber;
		hashA = rand() % prime;
		hashB = 1 + rand() % (prime - 1);
	}

	vector<vector<int>> getElements()
	{
		return elements;
	}

	void Init(vector<int> num)
	{
		size = num.size();
		backets.resize(num.size());
		elements.resize(num.size());
		int hashKey;
		for (int i = 0; i < size; i++)
		{
			hashKey = hashFunc(hashA, hashB, prime, size, num[i]);
			elements[hashKey].push_back(num[i]);
		}
		for (int i = 0; i < num.size(); i++)
		{
			backets[i].Construct(elements[i]);
		}
	}

	bool Contains(int elem)
	{
		int hashKey = hashFunc(hashA, hashB, prime, size, elem);
		return backets[hashKey].Contains(elem);
	}
};



int main()
{
	srand(time(0));
	int size;
	cout << "Enter size:" << endl;
	cin >> size;
	PerfectHash ph;
	vector<int> input;
	
	for (int i = 0; i < size; i++)
	{
		int elem = rand() % 100;
		cout << elem << " ";
		input.push_back(elem);
	}

	ph.Init(input);
	
	int toFind;
	cout << "\nEnter elem" << endl;
	cin >> toFind;


	for (int i = 0; i < ph.getElements().size(); i++)
	{
		for (int j = 0; j < ph.getElements()[i].size(); j++)
		{
			cout << ph.getElements()[i][j] << " ";

		}
		cout << endl;
	}

	if (ph.Contains(toFind))
	{
		cout << "Contains" << endl;
	}
	else
	{
		cout << "Not contains" << endl;
	}


	return 0;
}

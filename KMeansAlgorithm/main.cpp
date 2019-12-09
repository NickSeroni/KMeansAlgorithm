#include "KMeansCluster.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const char* smallTestData = "C:\\ComputerScience\\ArtificialIntelligence\\KMeansAlgorithm\\KMeansAlgorithm\\smallTestData.txt";
const char* bigTestData = "C:\\ComputerScience\\ArtificialIntelligence\\KMeansAlgorithm\\KMeansAlgorithm\\iris-versicolor-setosa-no-labels.txt";

int find_nth(char* str, char* delim, int nth)
{
	char* res = str;
	for (int i = 1; i <= nth; i++)
	{
		res = strstr(res, delim);
		if (!res)
			return -1;
		else if (i != nth)
			res = res++;
	}
	return res - str + 1;
}

vector<string> split(const string& s, char delim)
{
	string lastTwo = s.substr(find_nth((char*)s.c_str(), (char*)",", 2));

	stringstream ss(lastTwo);
	string item;
	vector<string> retval;

	while (getline(ss, item, delim))
	{
		retval.push_back(item);
	}
	return retval;
}

vector<vector<double>> readData(const char*& filePath)
{
	vector<vector<double>> retval;
	unordered_map<string, int> uniques;

	ifstream infile;
	infile.open(filePath);

	if (!infile.is_open())
	{
		cerr << "File couldn't be opened at: " << filePath << endl;
	}
	else
	{
		string line;
		int iter = 0;
		while (getline(infile, line))
		{
			vector<double> doubles;
			
			vector<string> splitLine = split(line, ',');

			string s = splitLine[0] + splitLine[1];
			if (uniques.find(s) == uniques.end())
			{
				uniques.emplace(s, 1);

				for (int i = 0; i < splitLine.size(); i++)
				{
					doubles.push_back(stod(splitLine[i]));
				}

				retval.push_back(doubles);
			}
		}
	}

	infile.close();

	return retval;
}

int main(int argc, char* argv[])
{
	vector<vector<double>> petalData = readData(smallTestData);

	for (int row = 0; row < petalData.size(); row++)
	{
		for (int col = 0; col < petalData[row].size(); col++)
		{
			cout << petalData[row][col] << " ";
		}
		cout << endl;
	}

	KMeansCluster kmc(petalData);

	/*unordered_map<string, vector<vector<double>>> minimumClusterCenter = kmc.createClusters(2, 100);

	for (auto it = minimumClusterCenter.begin(); it != minimumClusterCenter.end(); ++it)
	{
		pair<string, vector<vector<double>>> clusterCenter = *it;

		string clusterCenterString = clusterCenter.first;

		cout << "Cluster Center: " << clusterCenterString << endl;

		vector<vector<double>> clusterData = clusterCenter.second;

		for (int i = 0; i < clusterData.size(); i++)
		{
			for (int j = 0; j < clusterData[i].size(); j++)

			{
				cout << clusterData[i][j] << " ";
			}
			cout << endl;
		}
	}*/

	return 0;
}
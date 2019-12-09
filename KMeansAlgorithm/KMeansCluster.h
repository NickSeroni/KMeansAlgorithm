#pragma once
#include <unordered_map>
#include <vector>

using namespace std;

class KMeansCluster
{
public:
	KMeansCluster(vector<vector<double>>& kmd);

	unordered_map<string, vector<vector<double>>> createClusters(int numClusters, int attempts);

private:
	vector<vector<double>> kmd;
};


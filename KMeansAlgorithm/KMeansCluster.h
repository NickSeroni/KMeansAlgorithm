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

	double euclidianDistance(double p1, double q1, double p2, double q2);
	double euclidianDistance(vector<double>& data, vector<double>& cent);

	string centroidToString(vector<double>& centroid);
	vector<double> stringToCentroid(string centroid);
	bool isConverged(unordered_map<string, vector<vector<double>>>& prev, unordered_map<string, vector<vector<double>>>& curr);
	
	//calculates new centroid point
	vector<double> newCentroid(vector<vector<double>>& dataPoints);
	//calculate average of the average of the distances from data points to their cluster center
	double calcAvg(unordered_map<string, vector<vector<double>>>& clusters);



	void printClusters(unordered_map<string, vector<vector<double>>>& clust, int iter);
};


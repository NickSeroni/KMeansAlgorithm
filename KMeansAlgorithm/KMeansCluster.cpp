#include "KMeansCluster.h"
#include <time.h>
#include <string>
#include <iostream>

KMeansCluster::KMeansCluster(vector<vector<double>>& kmd)
{
	this->kmd = kmd;
}

double KMeansCluster::euclidianDistance(double kmd1, double cent1, double kmd2, double cent2)
{
	double x = kmd1 - cent1;
	cout << "x: " << x << endl;
	double y = kmd2 - cent2;
	cout << "y: " << y << endl;
	double dist = pow(x, 2) + pow(y, 2);
	dist = sqrt(dist);

	cout << "dist: " << dist << endl;

	return dist;
}

string KMeansCluster::centroidToString(vector<double>& centroid)
{
	string s = to_string(centroid[0]) + "-" + to_string(centroid[1]);
	return s;
}

unordered_map<string, vector<vector<double>>> KMeansCluster::createClusters(int numClusters, int attempts)
{
	unordered_map<string, vector<vector<double>>> clusters;
	srand(time(0));

	vector<vector<double>> centroids(numClusters);

	//initialize centroids
	int prevrnd = INT_MAX;
	for (size_t i = 0; i < numClusters; i++)
	{
		int rnd = rand() % kmd.size();
		while (prevrnd == rnd)
		{
			rnd = rand() % kmd.size();
		}
		prevrnd = rnd;
		
		for (size_t j = 0; j < kmd.at(rnd).size(); j++)
		{
			centroids.at(i).push_back(kmd.at(rnd).at(j));
		}
	}

	for (size_t i = 0; i < centroids.size(); i++)
	{
		cout << "C " << i << ": ";
		for (size_t j = 0; j < centroids.at(i).size(); j++)
		{
			cout << centroids[i][j] << " ";
		}
		cout << endl;
	}

	//for (size_t i = 0; i < attempts; i++)
	{
		//for each data point: measure distance to centroid, find shortest
		for (size_t j = 0; j < kmd.size(); j++)
		{
			unordered_map<double, int> centroidToAssign; //keeps track of distance per centroid

			for (size_t k = 0; k < numClusters; k++)
			{
				double dist = euclidianDistance(kmd.at(j).at(0), centroids.at(k).at(0), kmd.at(j).at(1), centroids.at(k).at(1));
				double shortestDistance = dist;

				if (dist < shortestDistance)
				{
					dist = shortestDistance;
				}

				centroidToAssign.emplace(dist, k);

				cout << dist << " " << k << " " << j << endl;
				cout << endl;
			}

			//string censtr = centroidToString(centroids.at(centroidToAssign.at(shortestDistance)));

			//cout << censtr << endl;
		}
	}

	return clusters;
}
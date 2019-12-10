#include "KMeansCluster.h"
#include <time.h>
#include <string>
#include <iostream>
#include <sstream>

KMeansCluster::KMeansCluster(vector<vector<double>>& kmd)
{
	this->kmd = kmd;
}

double KMeansCluster::euclidianDistance(double p1, double q1, double p2, double q2)
{
	double x = p1 - q1;
	double y = p2 - q2;
	double dist = pow(x, 2) + pow(y, 2);
	dist = sqrt(dist);

	return dist;
}
double KMeansCluster::euclidianDistance(vector<double>& data, vector<double>& cent)
{
	double dist = 0;

	for (int i = 0; i < data.size(); i++)
	{
		dist += pow(data[i] - cent[i], 2);
	}

	dist = sqrt(dist);

	return dist;
}


string KMeansCluster::centroidToString(vector<double>& centroid)
{
	string s;
	for (int i = 0; i < centroid.size(); i++)
	{
		if (i == centroid.size() - 1)
		{
			s += to_string(centroid[i]);
		}
		else
		{
			s += to_string(centroid[i]) + "-";
		}
	}

	return s;
}

vector<double> KMeansCluster::stringToCentroid(string centroid)
{
	vector<double> c;

	stringstream ss(centroid);
	string item;

	while (getline(ss, item, '-'))
	{
		c.push_back(stod(item));
	}

	return c;
}

bool KMeansCluster::isConverged(unordered_map<string, vector<vector<double>>>& prev, unordered_map<string, vector<vector<double>>>& curr)
{
	bool isit = true;

	//iterate thru each key of the current clusters to see if they are all identical to the previous
	for (auto it : curr)
	{
		if (prev.find(it.first) == prev.end())
		{
			isit = false;
		}
	}

	return isit;
}

void KMeansCluster::printClusters(unordered_map<string, vector<vector<double>>>& clust, int iter)
{
	cout << "While loop iteration: " << iter << endl;
	for (auto it : clust)
	{
		cout << "Center: " << it.first << endl;
		cout << "Points: " << endl;
		for (int i = 0; i < it.second.size(); i++)
		{
			cout << i << ". " << it.second.at(i).at(0) << ", " << it.second.at(i).at(1) << endl;
		}
		cout << endl;
	}
	cout << "------------------------------------" << endl;
}

vector<double> KMeansCluster::newCentroid(vector<vector<double>>& dataPoints)
{
	vector<double> c;

	for (int col = 0; col < dataPoints[0].size(); col++)
	{
		double dimensionSum = 0;

		for (int row = 0; row < dataPoints.size(); row++)
		{
			dimensionSum += dataPoints[row][col];
		}

		c.push_back(dimensionSum / dataPoints.size());
	}

	return c;
}

double KMeansCluster::calcAvg(unordered_map<string, vector<vector<double>>>& clusters)
{
	double totalAvg = 0;

	for (auto it : clusters)
	{
		double avg = 0;
		vector<double> c = stringToCentroid(it.first);

		for (auto d : it.second)
		{
			avg += euclidianDistance(d, c);
		}

		totalAvg += (avg / it.second.size());
	}
	
	return totalAvg / clusters.size();
}

unordered_map<string, vector<vector<double>>> KMeansCluster::createClusters(int numClusters, int attempts)
{
	unordered_map<string, vector<vector<double>>> clusters;
	unordered_map<string, vector<vector<double>>> retClusters;
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

	//Prints initial centroids
	/*for (size_t i = 0; i < centroids.size(); i++)
	{
		cout << "Initial Centroid " << i + 1 << ": ";
		for (size_t j = 0; j < centroids.at(i).size(); j++)
		{
			cout << centroids[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;*/


	double bestVariance = INT_MAX; //average distance of each data point from center
	double variance = 0.0; //keeps track of the current variance

	for (size_t i = 0; i < attempts; i++)
	{
		unordered_map<string, vector<vector<double>>> prevClusters;
		//int count = 1;
		bool notConverged = true;
		
		while (notConverged)
		{
			clusters.clear();
			//for each data point: measure distance to centroid, find shortest
			for (size_t j = 0; j < kmd.size(); j++)
			{
				unordered_map<double, int> centroidToAssign; //keeps track of distance per centroid
				double shortestDistance = INT_MAX;

				for (size_t k = 0; k < numClusters; k++)
				{
					double dist = euclidianDistance(kmd.at(j), centroids.at(k));

					if (dist < shortestDistance)
					{
						shortestDistance = dist;
					}

					centroidToAssign.emplace(dist, k);
				}

				string censtr = centroidToString(centroids.at(centroidToAssign.at(shortestDistance)));

				if (clusters.find(censtr) == clusters.end())
				{
					vector<vector<double>> v{ kmd.at(j) };
					clusters.emplace(censtr, v);
				}
				else
				{
					clusters.at(censtr).push_back(kmd.at(j));
				}
			}
			
			centroids.clear();
			
			// move cluster centers to avg of all x and y of the group
			for (auto it : clusters)
			{
				centroids.push_back(newCentroid(it.second));
			}

			notConverged = !isConverged(prevClusters, clusters);

			//printClusters(clusters, count);
			//printClusters(prevClusters, count);

			prevClusters = clusters;
			//count++;
		} 

		variance = calcAvg(clusters);

		if (variance < bestVariance)
		{
			bestVariance = variance;
			retClusters = clusters;
		}
	}

	return retClusters;
}
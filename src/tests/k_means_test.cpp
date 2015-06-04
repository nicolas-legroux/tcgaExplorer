#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include "k_means_test.hpp"
#include "../dataReader.hpp"
#include "../k_means.hpp"

#include "../distanceMatrix.hpp"
#include "../utilities.hpp"
#include "../unsupervisedNormalization.hpp"

using namespace std;

void kMeansTest1(int K, int Nmax, string cancerName, int patientId) {
	vector<string> cancers { cancerName };
	Data data;
	readData(cancers, data, 0, patientId + 1);
	vector<double> dataToCluster(
			data.getPatientTumorData(cancerName, patientId));
	std::vector<int> clusters(dataToCluster.size(), 0);

	K_Means<double> kMeans(dataToCluster, clusters, K, Nmax, NormedVectorSpace<double>());

	std::vector<double> means = kMeans.compute();

	std::vector<int> clusterCount(K, 0);
	for (int i : clusters) {
		clusterCount[i]++;
	}

	for (int i = 0; i != K; ++i) {
		std::cout << "Cluster " << (i + 1) << ": " << means[i] << ", size="
				<< clusterCount[i] << std::endl;
	}
}

void iteratedBinaryKMeans_test(int N_iter, string cancerName, int patientId) {
	vector<string> cancers { cancerName };
	Data data;
	readData(cancers, data, 0, patientId + 1);
	vector<double> dataToCluster(
			data.getPatientTumorData(cancerName, patientId));
	std::vector<int> clusters(dataToCluster.size(), 0);

	K_Means<double> kMeans(dataToCluster, clusters, 2, 100, NormedVectorSpace<double>());

	kMeans.computeIteratedBinaryKMeans(N_iter);

	std::vector<int> clusterCount(2, 0);
	for (int i : clusters) {
		clusterCount[i]++;
	}

	for (int i = 0; i != 2; ++i) {
		std::cout << "Cluster " << (i + 1) << ": size=" << clusterCount[i]
				<< std::endl;
	}
}

void twodimensionalKmeans_test() {
	unsigned int K = 2;
	int Nmax = 10;
	vector<double> vec1 { 0, 0 };
	vector<double> vec2 { 1, 1 };
	vector<double> vec3 { 0, 1 };
	vector<double> vec4 { 8, 7 };
	vector<double> vec5 { 8, 8 };
	vector<vector<double>> data { vec1, vec2, vec3, vec4, vec5 };
	vector<int> clusters(data.size(), 0);

	unsigned int n = data[0].size();

	K_Means<vector<double>> kMeans(data, clusters, K, Nmax, EuclideanSpace<double>(n));

	vector<vector<double>> means = kMeans.compute();
	std::vector<int> clusterCount(K, 0);
	for (int i : clusters) {
		clusterCount[i]++;
	}

	for (unsigned int i = 0; i != K; ++i) {
		cout << "Cluster " << (i + 1) << ": { ";
		for_each(means[i].cbegin(), means[i].cend(),
				[](double d) {cout << d << " ";});
		cout << "}, size=" << clusterCount[i] << endl;
	}
}

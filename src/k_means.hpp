#ifndef SRC_K_MEANS_HPP_
#define SRC_K_MEANS_HPP_

#include <vector>
#include <random>
#include <algorithm>
#include "utilities.hpp"

template<class T> class K_Means {
	typedef double (*DistanceFunction)(const T &,
			const T &);
	typedef void (*AddToFunction)(T &, const T &);
	typedef void (*DivisionByConstantFunction)(T &, double);

private:
	const std::vector<T> &data;
	std::vector<int> &clusters;
	unsigned int K;
	int Nmax;
	DistanceFunction distanceFunction;
	AddToFunction addToFunction;
	DivisionByConstantFunction divisionByConstantFunction;
	T nullValue;

	std::vector<T> means;
	std::vector<bool> dataToCluster;

	void initializeClustersRandomly() {
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(0, data.size() - 1);
		for (unsigned int i = 0; i < K; i++) {
			while (true) {
				int randomInt = distribution(generator);
				if (dataToCluster[randomInt]) {
					T randomData(data[randomInt]);
					if (find(means.begin(), means.begin() + i, randomData)
							== (means.begin() + i)) {
						means[i] = randomData;
						break;
					}
				}
			}
		}
	}

	int findClosestClusterFromDataPoint(const T &dataPoint) {
		int closestCluster = 0;
		double closestDistance = distanceFunction(dataPoint, means[0]);
		for (unsigned int i = 1; i < K; ++i) {
			double d = distanceFunction(dataPoint, means[i]);
			if (d < closestDistance) {
				closestCluster = i;
				closestDistance = d;
			}
		}
		return closestCluster;
	}

	void recalculateMeans() {
		std::vector<int> clusterSize(K, 0);
		fill(means.begin(), means.end(), nullValue);
		for (unsigned int i = 0; i != clusters.size(); ++i) {
			int cluster = clusters[i];
			if (cluster != -1) {
				++clusterSize[cluster];
				addToFunction(means[cluster], data[i]);
			}
		}
		for (unsigned int i  = 0; i < K; ++i) {
			divisionByConstantFunction(means[i], (double) clusterSize[i]);
		}
	}

	bool kMeansIteration() {
		bool clustersChanged = false;
		//Assign clusters
		for (unsigned int i = 0; i != data.size(); ++i) {
			int oldCluster = clusters[i];
			if (oldCluster != -1) {
				int newCluster = findClosestClusterFromDataPoint(data[i]);
				if (newCluster != clusters[i]) {
					clustersChanged = true;
					clusters[i] = newCluster;
				}
			}
		}
		//Recalculate means
		recalculateMeans();
		return clustersChanged;
	}

	void assignSortedClusters(const std::vector<size_t> &clusterRanks) {
		for (unsigned int i = 0; i != clusters.size(); ++i) {
			int currentCluster = clusters[i];
			if (currentCluster != -1) {
				clusters[i] = clusterRanks.at(currentCluster);
			}
		}
	}

public:
	K_Means(const std::vector<T> &_data, std::vector<int> &_clusters, unsigned int _K,
			int _Nmax, DistanceFunction _distanceFunction,
			AddToFunction _addToFunction,
			DivisionByConstantFunction _divisionByConstantFunction,
			T _nullValue) :
			data(_data), clusters(_clusters), K(_K), Nmax(_Nmax), distanceFunction(
					_distanceFunction), addToFunction(_addToFunction), divisionByConstantFunction(
					_divisionByConstantFunction),nullValue(_nullValue) {
	}

	std::vector<T> compute() {
		means = std::vector<T>(K, nullValue);
		dataToCluster = std::vector<bool>(data.size());
		transform(clusters.cbegin(), clusters.cend(), dataToCluster.begin(),
				[](int cluster) {
					return (cluster != -1);
				});

		initializeClustersRandomly();

		//Iterate
		int i = 0;
		while (i < Nmax && kMeansIteration()) {
			++i;
		}

		//Sort the clusters
		std::vector<size_t> clusterRanks(get_rank_increasing(means));
		assignSortedClusters(clusterRanks);
		sort(means.begin(), means.end());

		if (i == Nmax) {
			std::cout << "K-Means did not converge." << std::endl;
		}

		return means;
	}

	void computeIteratedBinaryKMeans(int Niteration){
		assert(K == 2);

		for (int i = 0; i < Niteration; ++i) {
			compute(); //1000 should be enough
			transform(clusters.cbegin(), clusters.cend(),
					clusters.begin(), [](int cluster) {
						return (cluster == 0)? 0 : -1;
					});
		}
		transform(clusters.cbegin(), clusters.cend(),
				clusters.begin(), [](int cluster) {
					return (cluster == 0)? 0 : 1;
				});
	}
};

#endif /* SRC_K_MEANS_HstPP_ */

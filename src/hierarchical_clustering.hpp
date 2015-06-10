// Copyright 2015 <Nicolas Legroux>

#ifndef SRC_HIERARCHICAL_CLUSTERING_HPP_
#define SRC_HIERARCHICAL_CLUSTERING_HPP_

#include <vector>
#include <set>
#include <utility>
#include "distanceMatrix.hpp"

// cf http://en.wikipedia.org/wiki/Hierarchical_clustering#Linkage_criteria
// Complete linkage : "worst case"
// Single linkage : "best case"
// Average linkage: easy to understand
enum LinkageMethod {
	COMPLETE, SINGLE, AVERAGE
};

class Hierarchical_Clustering {
private:
	LinkageMethod linkageMethod;
	MatrixType matrixType;
	std::vector<int> unionFindDataStructure;
	std::set<int> clusterRepresentatives;
	std::vector<int> clusterSizes;
	std::vector<double> data;
	unsigned int n;

	bool verbose;

	// Utility functions
	double& getDistance(int i, int j);
	double worstPossibleDistance();
	bool isBetterDistance(double oldDistance, double newDistance);

	void updateDistances(int deletedCluster, int newCluster);
	void mergeClusters(int i, int j);
	std::pair<int, int> findClustersToMerge();

	int findClusterRepresentative(int i);

public:
	Hierarchical_Clustering(const MatrixX &matrix,
			LinkageMethod _linkageMethod, MatrixType _matrixType,
			bool _verbose = false);
	std::vector<int> compute(unsigned int k);
};

#endif /* SRC_HIERARCHICAL_CLUSTERING_HPP_ */

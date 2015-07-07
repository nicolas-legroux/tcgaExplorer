/*
 * parameters.hpp
 *
 *  Created on: Jun 24, 2015
 *      Author: nicolas
 */

#ifndef PARAMETERS_HPP_
#define PARAMETERS_HPP_

#include <vector>
#include <memory>
#include <ClusterXX/metrics/metrics.hpp>
#include <ClusterXX/clustering/clusterer_parameters.hpp>
#include "config.hpp"

/* ------------------ General parameters -----------------*/
unsigned int PROGRAM_MODE = 0;
bool VERBOSE = true;
/*---------------------------------------------------------*/

/* ------------------ Data loader parameters -----------------*/
std::set<std::string> CANCERS = { "BRCA", "LUAD" };
unsigned int MAX_CONTROL_SAMPLES = 20;
unsigned int MAX_TUMOR_SAMPLES = 20;
/*---------------------------------------------------------*/

/* ------------------ Normalization parameters -----------------*/
auto DEFAULT_NORMALIZATION_METHOD = BINARY_QUANTILE_NORMALIZATION;
int K_MEANS_NORMALIZATION_PARAM = 2;
int K_MEANS_MAX_ITERATIONS = 1000;
double BINARY_QUANTILE_NORMALIZATION_PARAM = 0.995;
/*---------------------------------------------------------*/

/* ------------------ Metric parameters -----------------*/
std::shared_ptr<ClusterXX::Metric> METRIC = ClusterXX::buildMetric("pearson");
/*---------------------------------------------------------*/

/* ------------------ Clustering parameters -----------------*/
unsigned int K_CLUSTER = 0;
ClusterXX::HierarchicalParameters::LinkageMethod DEFAULT_LINKAGE_METHOD =
		ClusterXX::HierarchicalParameters::COMPLETE;

ClusterXX::SpectralParameters::GraphTransformationMethod::GraphTransformationMethodName SPECTRAL_GRAPH_K_NEAREST_NEIGHBORS =
		ClusterXX::SpectralParameters::GraphTransformationMethod::K_NEAREST_NEIGHBORS;

ClusterXX::SpectralParameters::GraphTransformationMethod::GraphTransformationMethodName SPECTRAL_GRAPH_GAUSSIAN_MIXTURE =
		ClusterXX::SpectralParameters::GraphTransformationMethod::GAUSSIAN_MIXTURE;

ClusterXX::SpectralParameters::GraphTransformationMethod::GraphTransformationMethodName SPECTRAL_GRAPH_NO_TRASNFORMATION =
		ClusterXX::SpectralParameters::GraphTransformationMethod::NO_TRANSFORMATION;

int SPECTRAL_K_NEAREST_NEIGHBORS = 3;
double SPECTRAL_GAUSSIAN_MIXTURE_STDDEV = 150.0;

std::pair<
		ClusterXX::SpectralParameters::GraphTransformationMethod::GraphTransformationMethodName,
		double> DEFAULT_GRAPH_TRANSFORMATION = {
		SPECTRAL_GRAPH_K_NEAREST_NEIGHBORS, SPECTRAL_K_NEAREST_NEIGHBORS };
/*---------------------------------------------------------*/

/* ------------------ Module search -----------------*/
std::vector<double> WEIGHTS =
		{ 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 4.0, 5.0 };
std::string GRAPH_NODE_FILE = "biogrid-nodes.txt";
std::string GRAPH_EDGE_FILE = "biogrid-edges.txt";
/*---------------------------------------------------------*/

#endif /* PARAMETERS_HPP_ */

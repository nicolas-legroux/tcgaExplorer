#ifndef SRC_K_MEANS_HPP_
#define SRC_K_MEANS_HPP_

#include <vector>

std::vector<double> computeKMeans(const std::vector<double> &data, std::vector<int> &clusters, int K, int Nmax);
void iteratedBinaryKMeans(const std::vector<double> &data, std::vector<int> &clusters, int N_iter);

#endif /* SRC_K_MEANS_HPP_ */

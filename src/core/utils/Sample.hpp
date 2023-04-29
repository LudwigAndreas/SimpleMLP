#ifndef SAMPLE_HPP
#define SAMPLE_HPP

#include <utility>

#include "../matrix/Matrix.hpp"

namespace s21 {
	struct Sample {
		Sample() = default;
		Sample(const Matrix<float>& x_, const Matrix<float>& y_) : x(std::move(x_)),
																   y(std::move(y_)) {}
		Matrix<float>	x;
		Matrix<float>	y;
	};

	struct DatasetGroup {
	private:
		std::vector<Sample> samples;
	public:
		explicit DatasetGroup(std::vector<Sample> smpl) : samples(std::move(smpl)) {}
		Sample &operator[](int index)				{ return samples[index]; }
		const Sample &operator[](int index) const	{ return samples[index]; }
		size_t size()								{ return samples.size(); }
	};

	class Dataset {
	private:
		std::vector<DatasetGroup> groups;
	public:
		int current_iteration;

		explicit Dataset(std::vector<DatasetGroup> samples) : groups(std::move(samples)), current_iteration(0) {}
		Dataset(const std::vector<Sample>& samples, int k) : current_iteration(0) {
			int group_size = samples.size() / k + (samples.size() % k > 0);
			std::vector<Sample> group;
			group.reserve(group_size);
			groups.reserve(k);
			for (const auto& it : samples) {
				group.push_back(it);
				if (group.size() >= (size_t) group_size) {
					groups.emplace_back(group);
					group.resize(0);
					group.reserve(group_size);
				}
			}
		}

		DatasetGroup &operator[](size_t index)				{ return groups[index]; }
		const DatasetGroup &operator[](size_t index) const	{ return groups[index]; }
		
		size_t size()		{ return groups.size(); }
		bool isUsedUp() 	{ return (size_t) current_iteration >= groups.size(); }
		void resetDataset()	{ current_iteration = 0; } 
	};
}

#endif
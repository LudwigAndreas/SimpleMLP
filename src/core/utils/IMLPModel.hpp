#ifndef IMLPMODEL_HPP
#define IMLPMODEL_HPP

#include <vector>
#include "Sample.hpp"
#include "ActivationFunction.hpp"
#include "IMLPLayer.hpp"

namespace s21 {
    class IMLPModel {
    protected:
        ActivationFunction *af;
        std::vector<size_t> units_per_layer;
        float lr;
        float start_lr;
        bool auto_decrease;
        std::vector<IMLPLayer *> layers;

    public:
		virtual std::vector<float> Forward(Matrix<float>) = 0;
		virtual void Backward(Matrix<float>) = 0;
		virtual int Predict(Matrix<float>) = 0;
		// virtual int getMostProbablePrediction(std::vector<float> vector) = 0;
		// virtual float TestOutput(std::vector<Sample> samples, bool silent_mode = false, std::string filename = "") = 0;

		int getMostProbablePrediction(std::vector<float> value) {
			double max = value[0];
			int prediction = 0;
			double tmp;
			for (int j = 1; j < (int) value.size(); ++j) {
				tmp = value[j];
				if (tmp > max) {
					prediction = j;
					max = tmp;
				}
			}
			return prediction; // +1 for dataset (who tf thought that it would be a good idea to numerate dataset choices from 1 and not from 0)
		}
		virtual ~IMLPModel() {}
	};
}

#endif
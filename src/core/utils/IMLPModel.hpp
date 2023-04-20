#ifndef IMLPMODEL_HPP
#define IMLPMODEL_HPP

#include <vector>
#include "Sample.hpp"
#include "ActivationFunction.hpp"

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
		virtual std::vector<float> Forward(Matrix<T>) = 0;
		virtual void Backward(Matrix<float>) = 0;
		virtual int Predict(Matrix<float>) = 0;
		virtual int getMostProbablePrediction(std::vector<float> vector) = 0;
		virtual float TestOutput(std::vector<Sample> samples, bool silent_mode = false, std::string filename = "") = 0;

//		virtual IMLPModel *Instance(size_t in_channels, size_t out_channels, size_t hidden_units_per_layer, int hidden_layers, float lr);
	};
}

#endif
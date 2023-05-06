#pragma once

#include <fstream>

#include "../utils/IMLPModel.h"
#include "../utils/ActivationFunction.h"
#include "../graph/MLPGraphLayer.h"
#include "../DatasetReading.h"

namespace s21 {
	typedef float T;

	class MLPGraphModel : public IMLPModel {
	private:
		std::vector<size_t>				units_per_layer;
		ActivationFunction				af;
		bool							auto_decrease;
		float							lr;
		float							start_lr;
		std::vector<MLPGraphLayer *>	layers;
			
	public:
		explicit MLPGraphModel(std::vector<size_t> units_per_layer,
								const ActivationFunction &func,
								bool use_auto_decrease = true,
								float lr = .05f);

		MLPGraphModel() : af(ActivationFunction()) {}

		~MLPGraphModel() { for (auto layer : layers) delete layer; }
								
		MLPGraphLayer *AddLayer(MLPGraphLayer *layer);

		const std::vector<size_t> &get_units_per_layer() const;
		void setUnitsPerLayer(const std::vector<size_t> &unitsPerLayer);

		const std::vector<MLPGraphLayer *> &get_layers() const;
		void set_layers(const std::vector<MLPGraphLayer *> &layers);

		const ActivationFunction &getAf() const;
		void setAf(ActivationFunction &af);

		float getStartLr() const;
		void setStartLr(float startLr);

		float getLr() const;
		void setLr(float lr);

		bool isAutoDecrease() const;
		void setAutoDecrease(bool autoDecrease);

		std::vector<MLPGraphLayer *> &get_layers();
		// std::vector<MLPGraphLayer *> &set_layers();

		static IMLPModel *MakeModel(size_t in_channels, size_t out_channels,
									size_t hidden_units_per_layer, 
									int hidden_layers, float lr, 
									ActivationFunction func, 
									bool use_auto_decrease = true);

		virtual std::vector<T> Forward(Matrix<T>);
		virtual void Backward(Matrix<T>);
		virtual float Train(DatasetGroup samples, bool b = false);
		virtual float Test(DatasetGroup samples, bool b = false);
		virtual int Predict(Matrix<float>);
		// virtual float TestOutput(std::vector<Sample> samples, bool silent_mode = false, std::string filename = "");
	};

	std::istream &operator>>(std::istream &is, MLPGraphModel &model);
	std::ostream &operator<<(std::ostream &os, MLPGraphModel &model);
}
#pragma once

#include <fstream>

#include "../utils/IMLPModel.hpp"
#include "../utils/ActivationFunction.hpp"
#include "../graph/MLPGraphLayer.hpp"
#include "../DatasetReading.hpp"

namespace s21 {
	typedef float T;

	class MLPGraphModel : public IMLPModel {
	private:
		std::vector<size_t>				units_per_layer;
		std::vector<MLPGraphLayer *>	layers;
		ActivationFunction				*af;
		float							start_lr;
		float							lr;
		
		bool							auto_decrease;
		
	
	public:
		explicit MLPGraphModel(std::vector<size_t> units_per_layer,
								ActivationFunction *func,
								bool use_auto_decrease = true,
								float lr = .05f);

		MLPGraphModel() {}
								
		MLPGraphLayer *AddLayer(MLPGraphLayer *layer);

		const std::vector<size_t> &getUnitsPerLayer() const;

		void setUnitsPerLayer(const std::vector<size_t> &unitsPerLayer);

		const std::vector<MLPGraphLayer *> &getLayers() const;

		void setLayers(const std::vector<MLPGraphLayer *> &layers);

		ActivationFunction *getAf() const;

		void setAf(ActivationFunction *af);

		float getStartLr() const;

		void setStartLr(float startLr);

		float getLr() const;

		void setLr(float lr);

		bool isAutoDecrease() const;

		void setAutoDecrease(bool autoDecrease);

		virtual std::vector<T> Forward(Matrix<T>);
		virtual void Backward(Matrix<T>);
		virtual float Train(DatasetGroup samples, bool b = false);
		virtual float Test(DatasetGroup samples, bool b = false);
		virtual int Predict(Matrix<float>);
		virtual float TestOutput(std::vector<Sample> samples, bool silent_mode = false, std::string filename = "");
	};

	std::istream &operator>>(std::istream &is, MLPGraphModel &model);
	std::ostream &operator<<(std::ostream &os, MLPGraphModel &model);
}
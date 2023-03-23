#ifndef SIMPLEMLP_MODELTRAINWORKER_HPP
#define SIMPLEMLP_MODELTRAINWORKER_HPP

#include "QObject"
#include "src/core/utils/IMLPModel.hpp"

#include "ModelWorker.hpp"

class ModelTrainWorker: ModelWorker {

public slots:
	void process() override;
};

#endif //SIMPLEMLP_MODELTRAINWORKER_HPP

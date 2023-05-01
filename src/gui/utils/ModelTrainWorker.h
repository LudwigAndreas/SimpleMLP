#ifndef SIMPLEMLP_MODELTRAINWORKER_HPP
#define SIMPLEMLP_MODELTRAINWORKER_HPP

#include "QObject"
#include "src/core/utils/IMLPModel.hpp"

#include "ModelWorker.hpp"

class ModelTrainWorker : public ModelWorker {

Q_OBJECT
public:
    ModelTrainWorker();

public slots:
	void process() override;

signals:
	void statusChanged(int epoch, int completion, float accuracy);

	void finished();

};

#endif //SIMPLEMLP_MODELTRAINWORKER_HPP

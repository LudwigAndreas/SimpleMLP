#ifndef SIMPLEMLP_MODELTRAINWORKER_H
#define SIMPLEMLP_MODELTRAINWORKER_H

#include "QObject"
#include "core/utils/IMLPModel.h"

#include "ModelWorker.h"

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

#endif //SIMPLEMLP_MODELTRAINWORKER_H

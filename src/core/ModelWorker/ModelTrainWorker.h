#ifndef SIMPLEMLP_MODELTRAINWORKER_H
#define SIMPLEMLP_MODELTRAINWORKER_H

#include "ModelWorker.h"
#include "QObject"
#include "core/utils/IMLPModel.h"

class ModelTrainWorker : public ModelWorker {
  Q_OBJECT
public:
  ModelTrainWorker();

public slots:
  void process() override;

signals:
  void statusChanged(int epoch, int completion, float accuracy);
  void MeanErrorCalculated(int epoch, float mse);

  void finished();

private:
  float CalculateMSE(s21::DatasetGroup &batch);
};

#endif // SIMPLEMLP_MODELTRAINWORKER_H

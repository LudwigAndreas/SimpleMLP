#ifndef SIMPLEMLP_MODELTESTWORKER_H
#define SIMPLEMLP_MODELTESTWORKER_H

#include "ModelWorker.h"

#include "core/utils/ConfusionMatrix.h"

class ModelTestWorker : public ModelWorker {

    Q_OBJECT
protected:
    int fraction;

public:
    ModelTestWorker();

    void setDatasetFraction(int value);

public slots:
    void process() override;

signals:
    void statusChanged(int completion);

    void finishedResult(std::vector<s21::ConfusionMatrix> *accuracy,
                        float time = 0);

    void finished();
};

#endif // SIMPLEMLP_MODELTESTWORKER_H

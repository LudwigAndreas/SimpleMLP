#ifndef SIMPLEMLP_MODELTESTWORKER_HPP
#define SIMPLEMLP_MODELTESTWORKER_HPP

#include "ModelWorker.hpp"

#include "src/core/utils/ConfusionMatrix.hpp"


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

	void finishedResult(std::vector<s21::ConfusionMatrix> *accuracy);

	void finished();
};


#endif //SIMPLEMLP_MODELTESTWORKER_HPP

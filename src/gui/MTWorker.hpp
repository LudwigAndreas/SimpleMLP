#ifndef SIMPLEMLP_MTWORKER_HPP
#define SIMPLEMLP_MTWORKER_HPP

#include "QObject"
#include "../core/utils/IMLPModel.hpp"


class MTWorker: public QObject {
	Q_OBJECT

private:
	s21::IMLPModel<float> *model;
	std::string dataset_file_name;


public:
	MTWorker();
	~MTWorker();

	void setModel(s21::IMLPModel<float> *model);
	void setDatasetFileName(std::string file_name);

public slots:
	void process();
//	void stop();

signals:
	void statusChanged(int epoch, int completion, float accuracy);

	void finished();
};

#endif //SIMPLEMLP_MTWORKER_HPP

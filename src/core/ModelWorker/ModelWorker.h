#ifndef SIMPLEMLP_MODELWORKER_H
#define SIMPLEMLP_MODELWORKER_H

#include <QObject>

#include "core/utils/IMLPModel.h"

class ModelWorker : public QObject {
  Q_OBJECT

 protected:
  s21::IMLPModel *model;
  std::string dataset_file_name;
  int num_of_epochs;
  bool stop;

  void SaveModel(s21::IMLPModel *model, int iteration);

 public:
  ModelWorker();
  virtual ~ModelWorker();

  void setModel(s21::IMLPModel *model);
  void setDatasetFileName(std::string file_name);
  void setNumOfEpochs(int num);
  void stopTraining();

 public slots:
  virtual void process() = 0;
};

#endif  // SIMPLEMLP_MODELWORKER_H

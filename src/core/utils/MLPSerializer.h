#ifndef SIMPLEMLP_MLPSERIALIZER_H
#define SIMPLEMLP_MLPSERIALIZER_H

#include <algorithm>
#include <exception>
#include <fstream>
#include <string>

#include "../exceptions/UploadFileException.h"
#include "../graph/MLPGraphModel.h"
#include "../matrix/MLPMatrixModel.h"

namespace s21 {
template <typename T>
class MLPSerializer {
 private:
  static void CloseStream(std::istream &is) {
    try {
      auto &ifs = dynamic_cast<std::ifstream &>(is);
      ifs.close();
    } catch (std::bad_cast &) {
    }
  }

 public:
  static void SerializeMLPModel(IMLPModel *model, const std::string &filename) {
    std::fstream file;
    file.open(filename, std::ofstream::out | std::ofstream::trunc);
    if (!file) {
      throw UploadFileException("Couldn't open file for writing.");
      return ;
    }

    auto *matrix_model = dynamic_cast<s21::MLPMatrixModel *>(model);
    auto *graph_model = dynamic_cast<s21::MLPGraphModel *>(model);
    if (matrix_model)
      SerializeMLPMatrixModel(matrix_model, file);
    else if (graph_model)
      SerializeMLPGraphModel(graph_model, file);
    else
      throw std::runtime_error("Eto chto za pokemon?");
    file.close();
  }

  static void SerializeMLPMatrixModel(MLPMatrixModel *model,
                                      std::ostream &file) {
    const std::string signature = "M";
    file << signature << "\n" << *model;
  }

  static void SerializeMLPGraphModel(MLPGraphModel *model,
                                     std::ostream &file) {
    const std::string signature = "G";
    file << signature << "\n" << *model;
  }

  static s21::IMLPModel *DeserializeMLPModel(const std::string &filename) {
    std::fstream file;
    std::string signature;
    file.open(filename, std::ofstream::in);
    if (!file) {
      throw UploadFileException("Couldn't open file for reading.");
      return nullptr;
    }
    if (std::getline(file, signature)) {
      if (signature[0] == 'M')
        return DeserializeMLPMatrixModel(file);
      else if (signature[0] == 'G')
        return DeserializeMLPGraphModel(file);
      file.close();
    }
    throw UploadFileException("Unknown or empty model file signature");
    return nullptr;
  }

  static s21::IMLPModel *DeserializeMLPMatrixModel(std::istream &is) {
    s21::MLPMatrixModel *model =
        reinterpret_cast<s21::MLPMatrixModel *>(s21::MLPMatrixModel::MakeModel(
            0, 0, 0, 0, 0, ActivationFunction(ActivationFunction::Sigmoid)));
    is >> *model;
    CloseStream(is);
    return model;
  }

  static s21::IMLPModel *DeserializeMLPGraphModel(std::istream &is) {
    s21::MLPGraphModel *model = new s21::MLPGraphModel();
    is >> *model;
    CloseStream(is);
    return model;
  }
};
}  // namespace s21

#endif  // SIMPLEMLP_MLPSERIALIZER_H

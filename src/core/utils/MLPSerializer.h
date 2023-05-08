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
template <typename T> class MLPSerializer {
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
    auto *matrix_model = dynamic_cast<s21::MLPMatrixModel *>(model);
    auto *graph_model = dynamic_cast<s21::MLPGraphModel *>(model);
    if (matrix_model)
      SerializeMLPMatrixModel(matrix_model, filename);
    else if (graph_model)
      SerializeMLPGraphModel(graph_model, filename);
    else
      throw std::runtime_error("Eto chto za pokemon?");
  }

  static void SerializeMLPMatrixModel(MLPMatrixModel *model,
                                      const std::string &filename) {
    const std::string signature = "M";
    std::fstream file;
    file.open(filename, std::ofstream::out | std::ofstream::trunc);
    file << signature << "\n" << *model;
    file.close();
  }

  static void SerializeMLPGraphModel(MLPGraphModel *model,
                                     const std::string &filename) {
    const std::string signature = "G";
    std::fstream file;
    file.open(filename, std::ofstream::out | std::ofstream::trunc);
    file << signature << "\n" << *model;
    file.close();
  }

  static s21::IMLPModel *DeserializeMLPModel(const std::string &filename) {
    std::fstream file;
    std::string signature;
    file.open(filename, std::ofstream::in);
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
} // namespace s21

#endif // SIMPLEMLP_MLPSERIALIZER_H

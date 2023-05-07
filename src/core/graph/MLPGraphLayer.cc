#include "MLPGraphLayer.h"

namespace s21 {
MLPGraphLayer::MLPGraphLayer(size_t size, const ActivationFunction &af,
                             MLPGraphLayer *input, MLPGraphLayer *output)
    : size(size), af(af) {
  this->neurons = std::vector<MLPGraphNode>(this->size);
  this->set_input_layer(input);
  this->set_output_layer(output);
}

// MLPGraphLayer::MLPGraphLayer(std::vector<MLPGraphNode> &&neurons,
// 							 ActivationFunction *af,
// 							 MLPGraphLayer *input,
// 							 MLPGraphLayer *output)
// { 	this->neurons = std::move(neurons); 	this->size 	  =
// this->neurons.size(); 	this->af 	  = af;
// this->set_input_layer(input); 	this->set_output_layer(output);
// }

void MLPGraphLayer::GenerateLayer() {
  if (input) {
    std::vector<float> ndvector =
        GenerateNDMatrix<float>(size, input->Size()).ToVector();

    for (size_t i = 0; i < size; ++i) {
      neurons[i].bias = ndvector[i];
      neurons[i].weight =
          std::vector<float>(ndvector.begin() + input->Size() * i,
                             ndvector.begin() + input->Size() * (i + 1));
    }
  }
}

const MLPGraphNode &MLPGraphLayer::operator[](int index) const {
  return (neurons[index]);
}

MLPGraphNode &MLPGraphLayer::operator[](int index) { return (neurons[index]); }

void MLPGraphLayer::set_layer_values(Matrix<float> &values) {
  if (values.size() != size) throw std::exception();
  for (size_t i = 0; i < size; ++i) {
    neurons[i].value = values[i];
  }
}

void MLPGraphLayer::set_input_layer(MLPGraphLayer *input) {
  this->input = input;
}

void MLPGraphLayer::set_output_layer(MLPGraphLayer *output) {
  this->output = output;
}

std::vector<float> MLPGraphLayer::get_resulting_vector() {
  std::vector<float> value;
  for (auto &neuron : neurons) value.push_back(neuron.value);
  return value;
}

void MLPGraphLayer::CalculateLayer(ActivationFunction &af) {
  for (size_t i = 0; i < neurons.size(); ++i) {
    neurons[i].raw_value = 0;
    for (size_t j = 0; j < neurons[i].weight.size(); ++j)
      neurons[i].raw_value += neurons[i].weight[j] * (*input)[j].value;

    if (output) {
      neurons[i].value = af.ApplyFunction(neurons[i].raw_value);
    }
  }
  if (!output) {
    std::vector<float> temp;
    for (auto neuron : neurons) temp.push_back(neuron.raw_value);
    temp = softmax(temp);
    for (size_t i = 0; i < temp.size(); ++i) neurons[i].value = temp[i];
  }
}

void MLPGraphLayer::CalculateError(std::vector<float> *target) {
  if (target) {
    for (size_t i = 0; i < neurons.size(); ++i) {
      neurons[i].error = neurons[i].value - (*target)[i];
    }
  } else if (output) {
    for (size_t i = 0; i < neurons.size(); ++i) {
      neurons[i].error = 0;
      for (size_t j = 0; j < output->Size(); ++j) {
        neurons[i].error += (*output)[j].error * (*output)[j].weight[i];
      }
      neurons[i].error *= af.ApplyDerivative(neurons[i].raw_value);
    }
  }
}

void MLPGraphLayer::UpdateWeights(float lr) {
  for (size_t i = 0; i < neurons.size(); ++i) {
    for (size_t j = 0; j < neurons[i].weight.size(); ++j) {
      neurons[i].weight[j] -= (*input)[j].value * neurons[i].error * lr;
    }
  }
  for (auto &neuron : neurons) neuron.bias -= lr * neuron.error;
}

size_t MLPGraphLayer::InputSize() const { return input->size; }

size_t MLPGraphLayer::Size() const { return size; }

std::istream &operator>>(std::istream &is, MLPGraphLayer &layer) {
  std::stringstream ss;
  std::string line;
  size_t input_size;
  size_t size;
  size_t i;
  size_t j;
  float weight = 0;

  line = "";
  while (line.empty()) std::getline(is, line);
  ss = std::stringstream(line);
  ss >> input_size >> size;
  if (layer.InputSize() != input_size || layer.Size() != size)
    throw UploadFileException("Incorrect weight matrix size.");
  for (j = 0; j < input_size && std::getline(is, line); ++j) {
    ss = std::stringstream(line);
    i = 0;
    while (ss >> weight) {
      layer[i].weight.push_back(weight);
      ++i;
    }
    if (i != size) throw UploadFileException("Invalid weight's line length.");
  }
  if (j != input_size) {
    throw UploadFileException("File ended unexpectedly.");
  }

  line = "";
  while (line.empty()) std::getline(is, line);
  ss = std::stringstream(line);
  ss >> input_size >> size;
  if (1 != input_size || layer.Size() != size)
    // std::raise(SIGTRAP);
    throw UploadFileException("Incorrect bias vector size.");
  if (std::getline(is, line)) {
    ss = std::stringstream(line);
    i = 0;
    while (ss >> weight) {
      layer[i].bias = weight;
      ++i;
    }
    if (i != size) throw UploadFileException("Invalid bias line length.");
  } else {
    throw UploadFileException("File ended unexpectedly.");
  }
  return is;
}

std::ostream &operator<<(std::ostream &os, const MLPGraphLayer &layer) {
  os << layer.InputSize() << ' ' << layer.Size() << std::endl;
  for (size_t j = 0; j < layer.InputSize(); ++j) {
    for (size_t i = 0; i < layer.Size(); ++i) {
      os << layer[i].weight[j] << ' ';
    }
    os << std::endl;
  }
  os << std::endl;

  os << "1" << ' ' << layer.Size() << std::endl;
  for (size_t i = 0; i < layer.Size(); ++i) {
    os << layer[i].bias << ' ';
  }
  os << std::endl << std::endl;
  return os;
}
}  // namespace s21

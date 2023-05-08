#include "MLPGraphModel.h"

#include "libs21/include/libs21.h"

namespace s21 {
MLPGraphModel::MLPGraphModel(std::vector<size_t> units_per_layer,
                             const ActivationFunction &func,
                             bool use_auto_decrease, float lr)
    : units_per_layer(units_per_layer),
      af(func),
      auto_decrease(use_auto_decrease),
      lr(lr) {
    start_lr = lr;
    MLPGraphLayer *input_layer = nullptr;
    for (auto size : units_per_layer)
        input_layer = AddLayer(new MLPGraphLayer(size, af, input_layer));
    for (auto layer : layers) layer->GenerateLayer();
}

MLPGraphLayer *MLPGraphModel::AddLayer(MLPGraphLayer *layer) {
    if (layers.size()) {
        layer->set_input_layer(layers.back());
        layers.back()->set_output_layer(layer);
    }
    layers.push_back(layer);
    return layer;
}

std::vector<T> MLPGraphModel::Forward(Matrix<T> input) {
    layers.front()->set_layer_values(input);
    for (auto it = layers.begin() + 1; it < layers.end(); ++it) {
        (*it)->CalculateLayer(af);
    }
    return layers.back()->get_resulting_vector();
}

void MLPGraphModel::Backward(Matrix<T> target) {
    assert(std::get<1>(target.get_shape()) == units_per_layer.back());

    layers.back()->CalculateError(&(target.ToVector()));
    for (size_t i = layers.size() - 2; i > 0; --i) {
        layers[i]->CalculateError();
    }
    for (size_t i = layers.size() - 1; i > 0; --i) layers[i]->UpdateWeights(lr);
}

float MLPGraphModel::Train(DatasetGroup samples, bool silent_mode) {
    int correct_guesses = 0;
    for (size_t i = 0; i < samples.size(); ++i) {
        if (Predict(samples[i].x) ==
                GetMostProbablePrediction(samples[i].y.ToVector()))
            ++correct_guesses;
        else
            Backward(samples[i].y);
    }
    float accuracy = ((float)correct_guesses / (float)samples.size());
    if (!silent_mode)
        std::cerr << "Train: " << accuracy * 100 << "% accuracy" << std::endl;
    return accuracy;
}

float MLPGraphModel::Test(DatasetGroup samples, bool silent_mode) {
    int correct_guesses = 0;
    float accuracy;
    for (size_t i = 0; i < samples.size(); ++i) {
        if (Predict(samples[i].x) ==
                GetMostProbablePrediction(samples[i].y.ToVector()))
            ++correct_guesses;
    }
    accuracy = ((float)correct_guesses / samples.size());
    if (!silent_mode)
        std::cerr << "Test: " << accuracy * 100 << "% accuracy" << std::endl;
    return accuracy;
}

int MLPGraphModel::Predict(Matrix<float> x) {
    return GetMostProbablePrediction(Forward(x));
}

const std::vector<size_t> &MLPGraphModel::get_units_per_layer() const {
    return units_per_layer;
}

void MLPGraphModel::set_units_per_layer(
    const std::vector<size_t> &unitsPerLayer) {
    units_per_layer = unitsPerLayer;
}

const std::vector<MLPGraphLayer *> &MLPGraphModel::get_layers() const {
    return layers;
}

void MLPGraphModel::set_layers(const std::vector<MLPGraphLayer *> &layers) {
    MLPGraphModel::layers = layers;
}

const ActivationFunction &MLPGraphModel::get_af() const {
    return af;
}

void MLPGraphModel::set_af(ActivationFunction &af) {
    MLPGraphModel::af = af;
}

float MLPGraphModel::get_start_lr() const {
    return start_lr;
}

void MLPGraphModel::set_start_lr(float startLr) {
    start_lr = startLr;
}

float MLPGraphModel::get_lr() const {
    return lr;
}

void MLPGraphModel::set_lr(float lr) {
    MLPGraphModel::lr = lr;
}

bool MLPGraphModel::is_auto_decrease() const {
    return auto_decrease;
}

void MLPGraphModel::set_auto_decrease(bool auto_decrease) {
    this->auto_decrease = auto_decrease;
}

std::vector<MLPGraphLayer *> &MLPGraphModel::get_layers() {
    return layers;
}

IMLPModel *MLPGraphModel::MakeModel(size_t in_channels, size_t out_channels,
                                    size_t hidden_units_per_layer,
                                    int hidden_layers, float lr,
                                    ActivationFunction func,
                                    bool use_auto_decrease) {
    std::vector<size_t> units_per_layer;
    units_per_layer.push_back(in_channels);

    for (int i = 0; i < hidden_layers; ++i)
        units_per_layer.push_back(hidden_units_per_layer);

    units_per_layer.push_back(out_channels);
    auto *model = new MLPGraphModel(units_per_layer, func, use_auto_decrease, lr);
    return model;
}

std::istream &operator>>(std::istream &is, MLPGraphModel &model) {
    std::string units_per_layer_str;
    std::string af_str;
    // std::string line;
    std::getline(is, units_per_layer_str);
    std::getline(is, af_str);

    auto upls = s21::Split(units_per_layer_str, " ");
    auto af = ActivationFunction(af_str);
    std::vector<size_t> units_per_layer;
    for (auto i = upls.begin(); i < upls.end() - 1; ++i)
        units_per_layer.push_back(std::atoi(i->data()));
    model.set_units_per_layer(units_per_layer);
    model.set_lr(std::atof(upls.rbegin()->data()));
    model.set_af(af);

    MLPGraphLayer *input_layer = nullptr;
    for (auto size : units_per_layer)
        input_layer = model.AddLayer(new MLPGraphLayer(
                                         size, ActivationFunction(model.get_af()), input_layer));
    auto &layers = model.get_layers();
    for (size_t i = 1; i < layers.size(); ++i) is >> *layers[i];
    return is;
}

std::ostream &operator<<(std::ostream &os, MLPGraphModel &model) {
    // os << "G" << std::endl;
    for (auto unit : model.get_units_per_layer()) os << unit << ' ';
    os << model.get_lr() << std::endl;
    os << model.get_af() << std::endl;
    for (auto it = model.get_layers().begin() + 1; it != model.get_layers().end();
            ++it) {
        os << **it;
    }
    return os;
}
}  // namespace s21

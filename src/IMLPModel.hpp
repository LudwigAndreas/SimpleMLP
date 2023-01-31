#include <vector>

namespace s21 {
	template <typename T>
	class IMLPModel {
	protected:
		virtual int Forward(std::vector<T>) = 0;
		virtual int Backward(std::vector<T>) = 0;
		IMLPModel();
	public:
		virtual int Import() = 0;
		virtual int Export() = 0;
		virtual int Train(std::vector<T>) = 0;
		virtual int Test(std::vector<T>) = 0;
		virtual int Predict() = 0;
		virtual IMLPModel *MakeModel(size_t in_channels, size_t out_channels, size_t hidden_units_per_layer, int hidden_layers, float lr);
	};
}
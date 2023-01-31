#include <vector>

namespace s21 {
	class IMLPModel {
	protected:
		virtual int Forward() = 0;
		virtual int Backward() = 0;
		IMLPModel();
	public:
		virtual int Import() = 0;
		virtual int Export() = 0;
		virtual int Train() = 0;
		virtual int Test() = 0;
		virtual int Predict() = 0;
		virtual IMLPModel *MakeModel();
	};
}
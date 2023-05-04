#ifndef SIMPLEMLP_CONFUSIONMATRIX_H
#define SIMPLEMLP_CONFUSIONMATRIX_H

namespace s21 {
	struct ConfusionMatrix {
		int tp;
		int fp;
		int tn;
		int fn;

		ConfusionMatrix() :
				tp(0),
				fp(0),
				tn(0),
				fn(0) {}
	};
}

#endif //SIMPLEMLP_CONFUSIONMATRIX_H

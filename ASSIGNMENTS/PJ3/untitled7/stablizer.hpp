#ifndef STABLIZER_HPP
#define STABLIZER_HPP
#include <QtCore>
class Stablizer {
  public:
	// constructor
	Stablizer(double initX, double initV, double initA,
			  double initPx, double initPv, double initPa)
		: x(initX), v(initV), a(initA),
		  Px(initPx), Pv(initPv), Pa(initPa) {
	}

	// predict step
	void predict(double dt) {
		// update x, v, and a
		x += v * dt + 0.5 * a * dt * dt;
		v += a * dt;

		// update covariance matrix
		Px += Pv * dt + 0.5 * Pa * dt * dt;
		Pv += Pa * dt;
		Pa += Pa; // assumes constant acceleration
	}

	// update step
	void update(double z, double R) {
		// compute Kalman gain
		double K = Px / (Px + R);

		// update x, v, and a
		x += K * (z - x);
		v += K * (z - x);
		a += K * (z - x);

		// update covariance matrix
		Px *= (1 - K);
		Pv *= (1 - K);
		Pa *= (1 - K);
	}

	// get current state
	QVector<double> state() const {
		return QVector<double> {x, v, a};
	}

  private:
	double x;   // position
	double v;   // velocity
	double a;   // acceleration

	double Px;  // covariance matrix for position
	double Pv;  // covariance matrix for velocity
	double Pa;  // covariance matrix for acceleration
};
#endif // STABLIZER_HPP

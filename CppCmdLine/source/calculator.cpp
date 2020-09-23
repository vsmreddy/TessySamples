#include "calculator.h"

//
// Calculator
//
Calculator::Calculator() {
	Value = 0;
}

Calculator::Calculator(int value) {
	Value = value;
}

//
void Calculator::calculate(t_operation operation, int operand) {
	switch (operation) {
	case plus:
		Value += operand;
		break;
	case minus:
		Value -= operand;
		break;
	case mul:
		Value *= operand;
		break;
	case div:
		if (operand == 0) {
			throw "Division by 0";
		} else {
			Value /= operand;
		}
		break;
	default:
		throw "Unsupported operation";
	}
}

int Calculator::value(void) {
	return Value;
}

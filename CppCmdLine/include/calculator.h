#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

typedef enum op {
	plus,
	minus,
	mul,
	div
}t_operation;

class Calculator {

public:
	Calculator ();
	Calculator (int value);

	void calculate (t_operation operation, int operand);
	int value (void);

private:
	int Value;
};

#endif

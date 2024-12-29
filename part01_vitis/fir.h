#define N 99

typedef int coeff_t;
typedef int data_t;
typedef int acc_t;

// Optimized FIR filter
//void fir_opt (data_t *input_stream, data_t *output_stream, int len, coeff_t *coeff);

// Base FIR filter
void fir_base (data_t *input_stream, data_t *output_stream, int len, coeff_t *coeff);

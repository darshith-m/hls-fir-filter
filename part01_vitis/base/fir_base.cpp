#include "fir.h"

void fir_base(data_t *y, data_t *x, int length, coeff_t *coeff) {
    #pragma HLS INTERFACE m_axi depth=100 port=y
    #pragma HLS INTERFACE m_axi depth=100 port=x
    #pragma HLS INTERFACE m_axi depth=99 port=coeff
    #pragma HLS INTERFACE s_axilite port=length bundle=CTRL
    #pragma HLS INTERFACE s_axilite port=return bundle=CTRL

    static data_t shift_reg[N] = {0};
    static coeff_t co[N] = {0};
    
    // Initialize coefficient array
    CO_EFFICIENTS:
    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE II=1
        co[i] = coeff[i];
    }
    
    // Process input samples
    SWEEP:
    for (int i = 0; i < length; i++) {
        #pragma HLS LOOP_TRIPCOUNT max=100 min=100
        
        acc_t acc = 0;
        data_t current_input = x[i];
        
        // Shift and accumulate
        SHIFT_ACCUMULATE:
        for (int j = N - 1; j >= 0; j--) {
            if (j == 0) {
                acc += current_input * co[0];
                shift_reg[0] = current_input;
            }
            else {
                shift_reg[j] = shift_reg[j-1];
                acc += shift_reg[j] * co[j];
            }
        }
        
        y[i] = acc;
    }
}
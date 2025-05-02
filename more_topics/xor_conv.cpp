void FWHT (int A[], int k, int inv) {
    for (int j = 0; j < k; j++)
        for (int i = 0; i < (1 << k); i++)
            if (~i & (1 << j)) {
                int p0 = A[i];
                int p1 = A[i | (1 << j)];
                
                A[i] = p0 + p1;
                A[i | (1 << j)] = p0 - p1;
                
                if (inv) {
                    A[i] /= 2;
                    A[i | (1 << j)] /= 2;
                }
            }
}

void XOR_conv (int A[], int B[], int C[], int k) {
    FWHT(A, k, false);
    FWHT(B, k, false);
    
    for (int i = 0; i < (1 << k); i++)
        C[i] = A[i] * B[i];
    
    FWHT(A, k, true);
    FWHT(B, k, true);
    FWHT(C, k, true);
}

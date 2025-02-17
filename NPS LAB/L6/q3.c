#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Function to calculate parity bits
void calculate_parity(int data[], int r, int m) {
    int parity_pos, i, j;
    int parity;

    // Calculate parity bits for positions that are powers of 2
    for (parity_pos = 0; parity_pos < r; parity_pos++) {
        parity = 0;
        // Check all the bits which have 1 in their corresponding binary position
        for (i = (1 << parity_pos) - 1; i < m + r; i++) {
            if (((i + 1) & (1 << parity_pos)) != 0) { // Check if the i-th position is affected by this parity
                parity ^= data[i];  // XOR the bit values
            }
        }
        data[(1 << parity_pos) - 1] = parity;  // Insert the parity bit at the correct position
    }
}

// Function to detect and correct errors in the received data
void detect_and_correct_error(int data[], int r, int m) {
    int parity_pos, i, error_position = 0;
    int parity;

    // Check parity bits for error detection
    for (parity_pos = 0; parity_pos < r; parity_pos++) {
        parity = 0;
        // Check all the bits which have 1 in their corresponding binary position
        for (i = (1 << parity_pos) - 1; i < m + r; i++) {
            if (((i + 1) & (1 << parity_pos)) != 0) {
                parity ^= data[i];  // XOR the bit values
            }
        }
        error_position |= (parity << parity_pos);  // Build the error position
    }

    // If error_position is non-zero, we have an error at the corresponding bit
    if (error_position != 0) {
        printf("Error detected at position: %d\n", error_position);
        data[error_position - 1] = !data[error_position - 1]; // Correct the error (flip the bit)
        printf("Error corrected!\n");
    } else {
        printf("No errors detected.\n");
    }
}

// Function to display the bits
void display_bits(int data[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", data[i]);
    }
    printf("\n");
}

int main() {
    int data[100];
    int m, r, i;

    // Input the data bits
    printf("Enter number of data bits (m): ");
    scanf("%d", &m);

    printf("Enter the data bits: ");
    for (i = 0; i < m; i++) {
        scanf("%d", &data[i]);
    }

    // Calculate the number of parity bits required (r)
    r = 0;
    while ((m + r + 1) > (1 << r)) {
        r++;
    }

    // Create an array to hold the codeword (data + parity bits)
    int codeword[m + r];
    memset(codeword, 0, sizeof(codeword)); // Initialize with 0 (no parity bits yet)

    // Insert data bits into the codeword at positions that are not powers of 2
    int j = 0;
    for (i = 0; i < m + r; i++) {
        if ((i + 1) & (i)) {  // Check if this is not a power of 2 position
            codeword[i] = data[j++];
        }
    }

    // Calculate and insert the parity bits
    calculate_parity(codeword, r, m);

    printf("\nGenerated Hamming Codeword (with parity bits): ");
    display_bits(codeword, m + r);

    // Simulate error (for testing purposes)
    printf("\nSimulating error at position 4...\n");
    codeword[3] = !codeword[3]; // Manually flip a bit (error)

    // Detect and correct error in the received data
    detect_and_correct_error(codeword, r, m);

    printf("\nCorrected Codeword: ");
    display_bits(codeword, m + r);

    return 0;
}

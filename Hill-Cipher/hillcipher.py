import numpy as np
import math

substitution = {'A': 0, 'B': 1, 'C': 2, 'D': 3, 'E': 4, 'F': 5, 'G': 6, 'H': 7, 'I': 8, 'J': 9,
                'K': 10, 'L': 11, 'M': 12, 'N': 13, 'O': 14, 'P': 15, 'Q': 16, 'R': 17, 'S': 18,
                'T': 19, 'U': 20, 'V': 21, 'W': 22, 'X': 23, 'Y': 24, 'Z': 25}

inverse_substitution = {value: key for key, value in substitution.items()}

def gcd(a, b):
    return math.gcd(a, b)

def is_invertible(matrix, modulus):
    det = int(np.round(np.linalg.det(matrix))) % modulus
    return gcd(det, modulus) == 1

def mod_inverse(matrix, modulus):
    determinant = int(np.round(np.linalg.det(matrix)))
    determinant_mod = determinant % modulus
    determinant_inv = pow(determinant_mod, -1, modulus)
    matrix_mod = matrix % modulus
    adjugate = np.round(determinant * np.linalg.inv(matrix_mod)).astype(int) % modulus
    return (determinant_inv * adjugate) % modulus

def encrypt(plain_text, key_matrix):
    plain_text = plain_text.upper().replace(" ", "")
    n = len(key_matrix)
    if len(plain_text) % n != 0:
        padding_length = n - (len(plain_text) % n)
        plain_text += 'X' * padding_length

    cipher_text = ''
    for i in range(0, len(plain_text), n):
        block = plain_text[i:i+n]
        block_vector = np.array([substitution[ch] for ch in block])
        encrypted_vector = np.dot(key_matrix, block_vector) % 26
        encrypted_block = ''.join([inverse_substitution[num] for num in encrypted_vector])
        cipher_text += encrypted_block

    return cipher_text

def decrypt(cipher_text, key_matrix):
    if not is_invertible(key_matrix, 26):
        raise ValueError("The key matrix is not invertible and thus cannot be used for decryption.")
    
    key_matrix_inv = mod_inverse(key_matrix, 26)
    n = len(key_matrix)
    plain_text = ''
    for i in range(0, len(cipher_text), n):
        block = cipher_text[i:i+n]
        if len(block) < n:
            block += 'X' * (n - len(block))
        block = block.upper()
        block_vector = np.array([substitution[ch] for ch in block])
        decrypted_vector = np.dot(key_matrix_inv, block_vector) % 26
        decrypted_block = ''.join([inverse_substitution[num] for num in decrypted_vector])
        plain_text += decrypted_block
    
    return plain_text.rstrip('X')


def find_key_matrix(plain_text, cipher_text, matrix_size):
    if len(plain_text) != len(cipher_text):
        raise ValueError("Plaintext and ciphertext must be the same length.")

    pt_in_number = [substitution[ch] for ch in plain_text.upper()]
    ct_in_number = [substitution[ch] for ch in cipher_text.upper()]
    
    pt_matrix = np.array(pt_in_number).reshape(-1, matrix_size)
    ct_matrix = np.array(ct_in_number).reshape(-1, matrix_size)
    
    p_matrix = pt_matrix[:matrix_size]
    c_matrix = ct_matrix[:matrix_size]
    
    p_det = int(np.round(np.linalg.det(p_matrix))) % 26
    if gcd(p_det, 26) != 1:
        raise ValueError("The determinant of the plaintext matrix is not invertible modulo 26.")
    
    p_matrix_inv = mod_inverse(p_matrix, 26)
    
    key_matrix = (np.dot(c_matrix, p_matrix_inv) % 26).astype(int)
    
    return key_matrix


def get_key_matrix():
    """ Prompt user to input the key matrix """
    while True:
        try:
            n = int(input("Enter the size of the key matrix (e.g., 2 for a 2x2 matrix): "))
            matrix_entries = input(f"Enter the {n*n} entries of the matrix separated by spaces: ").split()
            if len(matrix_entries) != n*n:
                print(f"Please enter exactly {n*n} entries.")
                continue
            matrix_entries = [int(x) for x in matrix_entries]
            key_matrix = np.array(matrix_entries).reshape(n, n)
            return key_matrix
        except ValueError:
            print("Invalid input. Please enter integers only.")

def main():
    modulus = 26
    print("Hill Cipher Program")
    mode = input("Choose mode (encrypt/decrypt/find_key): ").strip().lower()
    
    if mode == "encrypt":
        plain_text = input("Enter the plaintext: ")
        key_matrix = get_key_matrix()
        if is_invertible(key_matrix, modulus):
            cipher_text = encrypt(plain_text, key_matrix)
            print("Cipher Text:", cipher_text)
        else:
            print("The key matrix is not invertible and cannot be used.")
    
    elif mode == "decrypt":
        cipher_text = input("Enter the ciphertext: ")
        key_matrix = get_key_matrix()
        if is_invertible(key_matrix, modulus):
            plain_text = decrypt(cipher_text, key_matrix)
            print("Plain Text:", plain_text)
        else:
            print("The key matrix is not invertible and cannot be used.")
    
    elif mode == "find_key":
        plain_text = input("Enter the plaintext: ")
        cipher_text = input("Enter the ciphertext: ")
        matrix = int(input("Enter the matrix size 2 for 2x2: "))
       
        try:
            key_matrix = find_key_matrix(plain_text, cipher_text, matrix)
            print("Found Key Matrix:\n", key_matrix)
        except ValueError as e:
            print(e)
    
    else:
        print("Invalid mode selected. Choose 'encrypt', 'decrypt', or 'find_key'.")

if __name__ == "__main__":
    main()
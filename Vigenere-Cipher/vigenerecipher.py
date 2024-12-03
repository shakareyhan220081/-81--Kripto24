# Vigenere Cipher in Python

# Function to encrypt plaintext using Vigenere Cipher
def vigenere_encrypt(plaintext, key):
    plaintext = plaintext.upper()
    key = key.upper()
    ciphertext = ""
    key_index = 0
    
    for char in plaintext:
        if char.isalpha():  # Only encrypt alphabetic characters
            shift = ord(key[key_index]) - ord('A')
            encrypted_char = chr((ord(char) - ord('A') + shift) % 26 + ord('A'))
            ciphertext += encrypted_char
            key_index = (key_index + 1) % len(key)
        else:
            ciphertext += char  # Keep non-alphabetic characters unchanged
    
    return ciphertext

# Function to decrypt ciphertext using Vigenere Cipher
def vigenere_decrypt(ciphertext, key):
    ciphertext = ciphertext.upper()
    key = key.upper()
    plaintext = ""
    key_index = 0
    
    for char in ciphertext:
        if char.isalpha():  # Only decrypt alphabetic characters
            shift = ord(key[key_index]) - ord('A')
            decrypted_char = chr((ord(char) - ord('A') - shift + 26) % 26 + ord('A'))
            plaintext += decrypted_char
            key_index = (key_index + 1) % len(key)
        else:
            plaintext += char  # Keep non-alphabetic characters unchanged
    
    return plaintext

# Main program
if __name__ == "__main__":
    # Input from user
    plaintext = input("Enter the plaintext: ").strip()
    key = input("Enter the key: ").strip()

    # Encrypt the plaintext
    ciphertext = vigenere_encrypt(plaintext, key)
    print(f"Ciphertext: {ciphertext}")

    # Decrypt the ciphertext
    decrypted_text = vigenere_decrypt(ciphertext, key)
    print(f"Decrypted Text: {decrypted_text}")

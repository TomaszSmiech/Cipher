# Cipher
Qt Widgets project allowing to cipher and decipher files


xor_cipher()
~xor_cipher()

bool cipher(string key, const string name, const string path_to_save="")
 Function ciphers a files with xor cipher.

 string key - key generating by key_generator()
 const string name - name of encrypted file
 const string path_to_save - path to save enrypted file

void decipher(const string name, const string path_to_save ="");
 Function deciphers files ciphered by  cipher function.

 const string name - name of deciphered file
 const string path_to_save - path to save deciphered file.

bool load_file(const string path_to_file)
 Function loads file to cipher or decipher. It returns true if file is loaded properly and false if it is not.




To cipher a file:
1. Load file using load function.
2. Generate a key using key_generator function.
   Generator creating key basics on loaded file so it is neccessery to load file first!
3. Call cipher function.
   It creates new ciphered file with attached key and special mark as a binary string at the beginng of file.
   Special mark means that your file was ciphered by this function.

To decipher a file:
1. Load ciphered file using load function.
2. Call decipher function.
   Your file should be ciphered by cipher function before, otherwise function thorw an invalid_argument type exeption.
 

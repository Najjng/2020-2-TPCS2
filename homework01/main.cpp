//
// Created by Nakyeong Kim on 2020/09/11.
//
// SNU-ID: 2018-15185
//
// Homework 01
//
// In this homework we will solve several problems related to vectors,
// using the vector object from the standard template library (STL)
// in the std (standard) namespace
//
// there comes up an error if I put a message with an upper case letter to encrypt
// since I worked under the convention that plain text will be written in lowercase letters
//
// Solved a problem with x, y, z when they are with positive int keys
// and also a problem with a, b, c when they are with negative int keys
//
// Made another if loop for space(' ')
//
// this file is recently updated on 2020/09/16
// This homework deals with alphabets and space only
// Since I'm not really sure about how to deal with other ASCII codes,
// I remained codes about them as comments(//)
//

#include <iostream>
#include <vector>
#include <string>

int encode (char c) {
    int a_val = (int) 'a'; // a_val = 97
    int val = (int) c; // ASCII value of c
    int encoding = val - a_val; // numeric values in the table of the given hw pdf
    //std::cout << encoding << std::endl; //it was used to check if encode function works correctly
    return encoding;
}

// int_to_plaintext_char function was written under the assumption that the given int is an alphabet
// this assumption was made because I limited the plaintext as a string consisted of lower case alphabet letters
char int_to_plaintext_char(int i){
    // in case the given int is already a value of a lower case character
    // and for another case if a space(empty char) was given
    if (i >= 97 && i <= 122 || i == 32) // ( i < 65 || (i > 90 && i <= 127) <- it was to deal with other ASCII chars
        {
        char ch(i); // turn int into lower case character
        std::cout << ch;
        }
    else if (i >= 65 && i <= 90) // in case the given int is a value of an upper case character
        {
        i += 32; // turn the given int into a value of a lower case character by adding 32
        char ch(i); // turn int into lower case character
        std::cout << ch;
        }
    else {
        return 0; // do nothing
    }
}

// int_to_cyphertext_char function was written under the assumption that the given int is an alphabet
// as well as int_to_plaintext_char function
char int_to_cyphertext_char(int i){
    // in case the given int is already a value of an upper case character
    // and for another case if a space(empty char) was given
    if (i <= 90 && i >= 65 || i == 32) // ( i < 97 || (i > 122 && i <= 127)
    {
        char ch(i); // turn the given int into an upper case character
        std::cout << ch;
    }
    else if (i >= 97 && i <= 122) // in case the given int is a value of a lower case character
    {
        i -= 32; // turn the given int into an upper case character by subtracting 32
        char ch(i); // turn the given int into an upper case character
        std::cout << ch;
    }
    else {
        return 0; // do nothing
    }
}

// encrypt function turns a message into a vector of ints which can be turned into cypher
// the output consists of ints for upper case alphabets
std::vector<int> encrypt(std::string message, int key){
    std::vector<int> result = {}; // an empty of ints vector for the result
    int len = message.length();
    for (int i=0; i<len; i++){
        int l = (int) message[i]; // l represents a letter
        // if (l==32), l represents a space, ' '
        // if (l < 65 || 90 < l < 97 || l > 122) to deal with all the other ASCII chars
        if (l == 32) {
            result.insert(result.end(), l);
        }
        // else if l is not a space but a letter
        else {
            int c = 65 + ((encode(l) + key) % 26); // equal to l - 97 + key
            result.push_back(c);
        }
    }
    printf("The message is encrypted successfully. \n");
    return result;
}

// decrypt function turns a vector of ints, which is a cypher, into a different vector of ints for plaintext
// the output consists of ints for lower case alphabets for plaintext
std::vector<int> decrypt(std::vector<int> message, int key){
    std::vector<int> result = {}; // an empty vector of ints for the result
    int len = message.size();
    for (int i=0; i<len; i++){
        int n = message[i]; // n represents a number
        // if (n==32), n represents a space, ' '
        // if (l < 65 || 90 < l < 97 || l > 122) to deal with all the other ASCII chars
        if (n==32){
            result.push_back(n);
        }
        // else if n is not a space but a number
        else {
            int c = 97 + ((n - 39 - key)%26); // 65 - 26 = 39: in case n - 65 is smaller than 0
            result.push_back(c);
        }
    }
    printf("The message is decrypted successfully. \n");
    return result;
}

void print_cypher(std::vector<int> cypher) {
    std::vector<char> result({}); // an empty vector of char for the result
    int len = cypher.size();
    for (int i=0; i<len; i++){
        char c = int_to_cyphertext_char(cypher[i]); // turn vector of ints into text
        result.push_back(c);
    }
    // printf("The cypher was turned into a cyphertext. \n");
    // the upper sentence was deleted because it was printed after encryption
    std::string c(result.begin(), result.end()); // c represents cypher
    std::cout << c << std::endl;
}

void print_plaintext(std::vector<int> plaintext) {
    std::vector<char> result = {}; // an empty vector of char for the result
    int len = plaintext.size();
    for (int i=0; i<len; i++){
        char c = int_to_plaintext_char(plaintext[i]); // turn vector of ints into text
        result.push_back(c);
    }
    // printf("The ints were turned into a plaintext. \n");
    // the upper sentence was deleted because it was printed after decryption
    std::string p(result.begin(), result.end()); // p represents for plaintext
    std::cout << p << std::endl;
}

int main() {
    // test1 with alphabets
    std::vector<int> encrypt_msg1 = encrypt("abcdefghijklmnopqrstuvwxyz", 5);
    print_cypher(encrypt_msg1);
    std::vector<int> decrypt_msg1 = decrypt(encrypt_msg1, 5);
    print_plaintext(decrypt_msg1);
    // test2 with a positive int key and a string with space
    std::vector<int> encrypt_msg2 = encrypt("hello world", 3);
    print_cypher(encrypt_msg2);
    std::vector<int> decrypt_msg2 = decrypt(encrypt_msg2, 3);
    print_plaintext(decrypt_msg2);
    // test3 with a negative int key and a string with space
    std::vector<int> encrypt_msg3 = encrypt("hello world", -3);
    print_cypher(encrypt_msg3);
    std::vector<int> decrypt_msg3 = decrypt(encrypt_msg3, -3);
    print_plaintext(decrypt_msg3);
}

#include "Crypto.h"
#include "GrayscaleImage.h"


// Extract the least significant bits (LSBs) from SecretImage, calculating x, y based on message length
std::vector<int> Crypto::extract_LSBits(SecretImage& secret_image, int message_length) {
    std::vector<int> LSB_array;
    // 1. Reconstruct the SecretImage to a GrayscaleImage.
    // 2. Calculate the image dimensions.
    // 3. Determine the total bits required based on message length.
    // 4. Ensure the image has enough pixels; if not, throw an error.
    // 5. Calculate the starting pixel from the message_length knowing that  
    //    the last LSB to extract is in the last pixel of the image.
    // 6. Extract LSBs from the image pixels and return the result.

    GrayscaleImage image = secret_image.reconstruct();

    int starting_row = (image.get_height() - (message_length*7 / image.get_width())) - 1;
    int starting_col = image.get_width() - (message_length*7 % image.get_width());

    if (starting_col >= 0) {
        for (int j = starting_col; j < image.get_width(); j++) {
            LSB_array.push_back(image.get_pixel(starting_row, j) % 2);
        }
    }
    for (int i = starting_row + 1; i < image.get_height(); i++) {
        for (int j = 0; j < image.get_width(); j++) {
            LSB_array.push_back(image.get_pixel(i, j) % 2);
        }
    }

    return LSB_array;
}


// Decrypt message by converting LSB array into ASCII characters
std::string Crypto::decrypt_message(const std::vector<int>& LSB_array) {
    std::string message;
    // 1. Verify that the LSB array size is a multiple of 7, else throw an error.
    // 2. Convert each group of 7 bits into an ASCII character.
    // 3. Collect the characters to form the decrypted message.
    // 4. Return the resulting message.

    for (size_t i = 0; i < LSB_array.size(); i += 7) {
        std::string binary_string;
        for (size_t j = 0; j < 7; ++j) {
            binary_string += std::to_string(LSB_array[i + j]);
        }

        std::bitset<7> bitset_value(binary_string);
        char ascii_char = static_cast<char>(bitset_value.to_ulong());

        message += ascii_char;

    }

    return message;
}

// Encrypt message by converting ASCII characters into LSBs
std::vector<int> Crypto::encrypt_message(const std::string& message) {
    std::vector<int> LSB_array;
    // 1. Convert each character of the message into a 7-bit binary representation.
    //    You can use std::bitset.
    // 2. Collect the bits into the LSB array.
    // 3. Return the array of bits.

    for (size_t i = 0; i < message.length(); i++) {
        std::bitset<7> bits(message[i]);
        for (int j = 6; j >= 0; j--) {
            LSB_array.push_back(bits[j]);
        }
    }

    return LSB_array;
}

// Embed LSB array into GrayscaleImage starting from the last bit of the image
SecretImage Crypto::embed_LSBits(GrayscaleImage& image, const std::vector<int>& LSB_array) {
    // 1. Ensure the image has enough pixels to store the LSB array, else throw an error.
    // 2. Find the starting pixel based on the message length knowing that  
    //    the last LSB to embed should end up in the last pixel of the image.
    // 3. Iterate over the image pixels, embedding LSBs from the array.
    // 4. Return a SecretImage object constructed from the given GrayscaleImage 
    //    with the embedded message.

    int starting_row = (image.get_height() - (LSB_array.size() / image.get_width())) - 1;
    int starting_col = image.get_width() - (LSB_array.size() % image.get_width());

    int LSB_index = 0;

    if (starting_col >= 0) {
        for (int j = starting_col; j < image.get_width() && LSB_index < LSB_array.size(); j++) {
            int pixel_value = image.get_pixel(starting_row, j);
            image.set_pixel(starting_row, j, (pixel_value & ~1) | LSB_array[LSB_index++]);
        }
    }

    for (int i = starting_row + 1; i < image.get_height() && LSB_index < LSB_array.size(); i++) {
        for (int j = 0; j < image.get_width() && LSB_index < LSB_array.size(); j++) {
            int pixel_value = image.get_pixel(i, j);
            image.set_pixel(i, j, (pixel_value & ~1) | LSB_array[LSB_index++]);
        }
    }

    SecretImage secret_image(image);

    return secret_image;
}
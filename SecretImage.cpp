#include "SecretImage.h"

#include <cmath>
#include <vector>


// Constructor: split image into upper and lower triangular arrays
SecretImage::SecretImage(const GrayscaleImage& image) {
    // TODO: Your code goes here.
    // 1. Dynamically allocate the memory for the upper and lower triangular matrices.
    // 2. Fill both matrices with the pixels from the GrayscaleImage.

    width = image.get_width();
    height = image.get_height();

    upper_triangular = new int [(width * (width + 1)) / 2];
    lower_triangular = new int [(width * (width - 1)) / 2];

    int upper_index = 0;
    int lower_index = 0;

    // Fill both matrices
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (col >= row) {
                // Array for upper triangular part (including diagonal)
                upper_triangular[upper_index] = image.get_pixel(row, col);
                upper_index++;
            }
            if (col < row) {
                // Array for lower triangular part (excluding diagonal)
                lower_triangular[lower_index] = image.get_pixel(row, col);
                lower_index++;
            }
        }
    }
}

// Constructor: instantiate based on data read from file
SecretImage::SecretImage(int w, int h, int * upper, int * lower) {
    // TODO: Your code goes here.
    // Since file reading part should dynamically allocate upper and lower matrices.
    // You should simply copy the parameters to instance variables.

    width = w;
    height = h;

    upper_triangular = new int [(width * (width + 1)) / 2];
    lower_triangular = new int [(width * (width - 1)) / 2];

    int upper_index = 0;
    int lower_index = 0;

    // Fill both matrices
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (col >= row) {
                // Array for upper triangular part (including diagonal)
                upper_triangular[upper_index] = upper[upper_index];
                upper_index++;
            }
            if (col < row) {
                // Array for lower triangular part (excluding diagonal)
                lower_triangular[lower_index] = lower[lower_index];
                lower_index++;
            }
        }
    }
}


// Destructor: free the arrays
SecretImage::~SecretImage() {
    // TODO: Your code goes here.
    // Simply free the dynamically allocated memory
    // for the upper and lower triangular matrices.

    delete[] upper_triangular;
    delete[] lower_triangular;
}

// Reconstructs and returns the full image from upper and lower triangular matrices.
GrayscaleImage SecretImage::reconstruct() {
    GrayscaleImage image(width, height);
    // TODO: Your code goes here.
    int upperIndex = 0;
    int lowerIndex = 0;

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (j >= i) {
                image.set_pixel(i, j, upper_triangular[upperIndex++]);
            } else {
                image.set_pixel(i, j, lower_triangular[lowerIndex++]);
            }
        }
    }
    return image;
}

// Save the filtered image back to the triangular arrays
void SecretImage::save_back(const GrayscaleImage& image) {
    // TODO: Your code goes here.
    // Update the lower and upper triangular matrices 
    // based on the GrayscaleImage given as the parameter.
}

// Save the upper and lower triangular arrays to a file
void SecretImage::save_to_file(const std::string& filename) {
    // TODO: Your code goes here.
    // 1. Write width and height on the first line, separated by a single space.
    // 2. Write the upper_triangular array to the second line.
    // Ensure that the elements are space-separated. 
    // If there are 15 elements, write them as: "element1 element2 ... element15"
    // 3. Write the lower_triangular array to the third line in a similar manner
    // as the second line.

    std::ofstream outFile(filename);

    outFile << width << " " << height << std::endl;
    // upper_triangular
    for (int i = 0; i < (width * (width + 1)) / 2; i++) {
        outFile << upper_triangular[i];
        if (i < (width * (width + 1)) / 2 - 1) {
            outFile << " ";
        }
    }
    outFile << std::endl;
    // lower_triangular
    for (int i = 0; i < (width * (width - 1)) / 2; i++) {
        outFile << lower_triangular[i];
        if (i < (width * (width - 1)) / 2 - 1) {
            outFile << " ";
        }
    }
    outFile << std::endl;

    outFile.close();
}

// Static function to load a SecretImage from a file
SecretImage SecretImage::load_from_file(const std::string& filename) {
    // TODO: Your code goes here.
    // 1. Open the file and read width and height from the first line, separated by a space.
    // 2. Calculate the sizes of the upper and lower triangular arrays.
    // 3. Allocate memory for both arrays.
    // 4. Read the upper_triangular array from the second line, space-separated.
    // 5. Read the lower_triangular array from the third line, space-separated.
    // 6. Close the file and return a SecretImage object initialized with the
    //    width, height, and triangular arrays.

    std::ifstream file(filename);

    //split the lines
    std::string line1;
    std::vector<std::string> tokens;
    while (std::getline(file, line1)) {
        std::stringstream ss(line1);
        std::string token;
        // Satırı belirli bir ayırıcıya göre böl
        while (std::getline(ss, token)) {
            tokens.push_back(token);
        }
    }

    std::vector<std::string> upper_vector;
    std::vector<std::string> lower_vector;

    //upper
    std::string input = tokens.at(1);
    std::vector<int> vec;
    std::stringstream ss(input);
    int number;

    while (ss >> number) {
        vec.push_back(number);
    }

    int size = vec.size();
    int* arr = new int[size];

    for (int i = 0; i < size; ++i) {
        arr[i] = vec[i];
    }

    //lower
    std::string input1 = tokens.at(2);
    std::vector<int> vec1;
    std::stringstream ss1(input1);
    int number1;

    while (ss1 >> number1) {
        vec1.push_back(number1);
    }

    int size1 = vec1.size();
    int* arr1 = new int[size1];

    for (int i = 0; i < size1; ++i) {
        arr1[i] = vec1[i];
    }

    int dimensions = std::sqrt(vec.size()+vec1.size());
    SecretImage secret_image(dimensions, dimensions, arr, arr1);
    return secret_image;
}

// Returns a pointer to the upper triangular part of the secret image.
int * SecretImage::get_upper_triangular() const {
    return upper_triangular;
}

// Returns a pointer to the lower triangular part of the secret image.
int * SecretImage::get_lower_triangular() const {
    return lower_triangular;
}

// Returns the width of the secret image.
int SecretImage::get_width() const {
    return width;
}

// Returns the height of the secret image.
int SecretImage::get_height() const {
    return height;
}

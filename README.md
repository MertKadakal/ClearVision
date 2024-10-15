***ClearVision Defense***

ClearVision Defense is a C++ application that focuses on enhancing image clarity and security by applying image filters and embedding/decrypting secret messages within images. The application is particularly useful in defense operations, such as satellite reconnaissance, low-light surveillance, and classified intelligence.



**Features**

Mean Filter: Reduces noise by averaging the pixel values in a neighborhood.

Gaussian Smoothing Filter: Blurs the image while preserving details using a Gaussian function.

Unsharp Masking: Enhances edges and sharpens the image.

Secret Message Embedding: Embeds a secret message into an image by modifying the least significant bits of the pixel values.

Secret Message Decryption: Extracts and decrypts hidden messages from images.



**Project Structure**

├── Crypto.cpp
├── Crypto.h
├── Filter.cpp
├── Filter.h
├── GrayscaleImage.cpp
├── GrayscaleImage.h
├── SecretImage.cpp
├── SecretImage.h
└── README.md



**How to Compile**

Use the following command to compile the project:

*g++ -g -std=c++11 -o clearvision main.cpp SecretImage.cpp GrayscaleImage.cpp Filter.cpp Crypto.cpp*

Alternatively, you can use the provided Makefile or CMake configuration:

*make*
or
*mkdir clearvision_build
cmake -S . -B clearvision_build/
make -C clearvision_build/*

**How to Run**



Below are some sample commands to run the application:

-Apply a mean filter:

*./clearvision mean input_image.png 3*

-Embed a secret message into an image:

*./clearvision enc input_image.png "Your Secret Message"*

-Decrypt a hidden message from an image:

*./clearvision dec secret_image.png 25*



**License**

This project is a part of the BBM203 Software Practicum I course at Hacettepe University. All rights reserved.



You can customize the image links and content based on your actual setup. The sample provides instructions and highlights important parts of your project.

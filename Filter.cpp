#include "Filter.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <numeric>
#include <math.h>
#include "GrayscaleImage.h"
#include <ostream>

// Mean Filter
void Filter::apply_mean_filter(GrayscaleImage& image, int kernelSize) {
    // TODO: Your code goes here.
    // 1. Copy the original image for reference.
    // 2. For each pixel, calculate the mean value of its neighbors using a kernel.
    // 3. Update each pixel with the computed mean.
    int** data = image.get_data();

    //copy the input image into another image
    GrayscaleImage imageCopy(image);

    //this for loop executes mean filter for each pixel
    for (int i = 0; i < image.get_height(); i++) {
        for (int j = 0; j < image.get_width(); j++) {
            int total = 0;
            int starting_height = i - (kernelSize-1)/2;
            int starting_width = j - (kernelSize-1)/2;
            for (int h = 0; h < kernelSize; h++) {
                for (int w = 0; w < kernelSize; w++) {
                    if (!(starting_height + h >= image.get_height() || starting_width + w >= image.get_width() || starting_height + h < 0 || starting_width + w < 0)) {
                        total += data[starting_height + h][starting_width + w];
                    }
                }
            }
            int average = total/(kernelSize*kernelSize);
            imageCopy.set_pixel(i, j, average);
        }
    }

    //save the new image file as output.jpg
    imageCopy.save_to_file("MeanFilter_output.jpg");
}

// Gaussian Smoothing Filter
void Filter::apply_gaussian_smoothing(GrayscaleImage& image, int kernelSize, double sigma) {
    // TODO: Your code goes here.
    // 1. Create a Gaussian kernel based on the given sigma value.
    // 2. Normalize the kernel to ensure it sums to 1.
    // 3. For each pixel, compute the weighted sum using the kernel.
    // 4. Update the pixel values with the smoothed results.

    int** data = image.get_data();

    //copy the input image into another image
    GrayscaleImage imageCopy(image);

    //this for loop executes gauss filter for each pixel
    for (int i = 0; i < image.get_height(); i++) {
        for (int j = 0; j < image.get_width(); j++) {
            std::vector<double> gausses;
            std::vector<int> pixel_datas;
            int starting_height = i - (kernelSize-1)/2;
            int starting_width = j - (kernelSize-1)/2;
            for (int h = 0; h < kernelSize; h++) {
                for (int w = 0; w < kernelSize; w++) {
                    //Gauss formülünü uyguluyoruz
                    int x = h - (kernelSize - 1)/2;
                    int y = w - (kernelSize - 1)/2;
                    double gauss = 1.0 / (2 * M_PI * sigma * sigma) * exp((-1)*(x*x + y*y) / (2 * sigma * sigma));
                    // Gauss değerini ve piksel bilgisini kaydediyoruz
                    gausses.push_back(gauss);
                    if (!(starting_height + h >= image.get_height() || starting_width + w >= image.get_width() || starting_height + h < 0 || starting_width + w < 0)) {
                        pixel_datas.push_back(data[starting_height+h][starting_width+w]);
                    } else {
                        pixel_datas.push_back(0);
                    }
                }
            }

            double total_gausses = 0;
            double total_weights = 0;
            for (int h = 0; h < gausses.size(); h++) {
                total_gausses += gausses[h];
                total_weights += gausses[h]*pixel_datas[h];
            }
            double final_gauss = total_weights/total_gausses;

            imageCopy.set_pixel(i, j, static_cast<int>(final_gauss));
        }
    }

    //save the new image file as output.jpg
    imageCopy.save_to_file("GaussFilter_output.jpg");
}

// Unsharp Masking Filter
void Filter::apply_unsharp_mask(GrayscaleImage& image, int kernelSize, double amount) {
    //creating a GaussianFilter-applied image
    GrayscaleImage imageGaussed(image);
    apply_gaussian_smoothing(imageGaussed, kernelSize, 1);

    //creating an image defines "amount*(original-gaussianFiltered)"
    GrayscaleImage substractedImg = image - substractedImg;
    for (int i = 0; i < substractedImg.get_height(); i++) {
        for (int j = 0; j < substractedImg.get_width(); j++) {
            substractedImg.set_pixel(i, j, amount*substractedImg.get_pixel(i, j));
        }
    }

    //adding amount*(original-gaussianFiltered) to original
    image = image + substractedImg;

    // Sonucu bir dosyaya kaydet
    image.save_to_file("UnsharpMask_output.jpg");
}


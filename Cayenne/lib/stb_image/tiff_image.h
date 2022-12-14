#include <cayennepch.h>
#include <fstream>
#ifndef CAYENNE_TIFF_IMAGE_H
#define CAYENNE_TIFF_IMAGE_H

namespace Cayenne
{
    struct TiffImage {
        int width;
        int height;
        std::vector<unsigned char> pixels;
    };

//#include <iostream>
//#include <fstream>
//#include <cstdint>
//
//    int main()
//    {
//        // Open the TIFF image file for reading
//        std::ifstream file("image.tiff", std::ios::binary);
//
//        // Read the TIFF image file header
//        uint16_t byte_order;
//        file.read((char*)&byte_order, sizeof(byte_order));
//        uint16_t version;
//        file.read((char*)&version, sizeof(version));
//        uint32_t offset;
//        file.read((char*)&offset, sizeof(offset));
//
//        // Check the byte order of the TIFF image
//        bool big_endian = false;
//        if (byte_order == 0x4d4d) {
//            big_endian = true;
//        } else if (byte_order == 0x4949) {
//            big_endian = false;
//        } else {
//            std::cout << "Error: Unknown byte order in TIFF image" << std::endl;
//            return 1;
//        }
//
//        // Read the TIFF image file directory
//        file.seekg(offset);
//        uint16_t num_entries;
//        file.read((char*)&num_entries, sizeof(num_entries));
//        if (big_endian) {
//            num_entries = ((num_entries >> 8) & 0xff) | (num_entries << 8);
//        }
//
//        // Search the TIFF image directory for the image width and height
//        uint32_t width = 0;
//        uint32_t height = 0;
//        for (int i = 0; i < num_entries; i++) {
//            uint16_t tag;
//            file.read((char*)&tag, sizeof(tag));
//            if (big_endian) {
//                tag = ((tag >> 8) & 0xff) | (tag << 8);
//            }
//            uint16_t type;
//            file.read((char*)&type, sizeof(type));
//            if (big_endian) {
//                type = ((type;


        static void LoadTiffImage(const std::string& filePath,TiffImage& image) {

        std::ifstream file(filePath, std::ios::in | std::ios::binary);
        if (!file) {
            CY_CORE_ASSERT(file, "Error: Unable to open file!");
            return;
        }

        // Read the width and height of the image
        file.read((char*)&(image.width), sizeof(int));
        file.read((char*)&(image.height), sizeof(int));

        // Reserve space for the pixels
        image.pixels.reserve(image.width * image.height);

        // Read the pixels
        for (int i = 0; i < image.width * image.height; i++) {
            unsigned char pixel;
            file.read((char*)&pixel, sizeof(unsigned char));
            image.pixels.push_back(pixel);
        }

        // Close the file
        file.close();
    }
}

#endif //CAYENNE_TIFF_IMAGE_H

#include <iostream>
#include <fstream>
#include <span>
#include <filesystem>

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "libs/pugixml/src/pugixml.hpp"
#include "libs/stb/stb_image_write.h"
#include "structs/Scene.hpp"

using namespace std;
namespace fs = filesystem;

bool checkInput(const span<const string> args) {
    if (args.size() != 2) {
        cerr << "Usage: <path to XML file>\n";
        return false;
    }
    if (!args[1].ends_with(".xml")) {
        cerr << "Must end with .xml!\n";
        return false;
    }
    ifstream fp{args[1]};
    if (!fp.is_open()) {
        cerr << args[1] << " not found in " << fs::current_path() << '\n';
        return false;
    }
    return true;
}

void write_image(const Scene &scene, const span<const uint8_t> pixels) {
    const uint64_t imageHeight = scene.camera.resolution.vertical;
    const uint64_t imageWidth = scene.camera.resolution.vertical;

    const uint64_t stride = Scene::CHANNELS * imageWidth;

    fs::path filename{"../output"};
    if (!fs::exists(filename))
        fs::create_directories(filename);

    filename /= scene.output_file;

    if (!stbi_write_png(filename.string().c_str(), static_cast<int>(imageWidth), static_cast<int>(imageHeight),
                        static_cast<int>(Scene::CHANNELS), pixels.data(), static_cast<int>(stride)))
        cerr << "Failed to write image: " << filename << '\n';
}

int main(int argc, char *argv[]) {
    const vector<string> args{argv, argv + argc};
    if (!checkInput(args))
        return 1;

    pugi::xml_document doc;

    if (pugi::xml_parse_result result = doc.load_file(args[1].c_str()); !result) {
        cerr << "pugixml had problems reading " << args[1] << '\n';
        return 1;
    }

    const Scene scene{doc.child("scene")};
    const vector<uint8_t> pixels = scene.raytracing();
    write_image(scene, pixels);

    return 0;
}

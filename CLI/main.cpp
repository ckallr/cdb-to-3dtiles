#include "CDBTo3DTiles.h"
#include "cxxopts.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    cxxopts::Options options("CDBConverter", "Convert CDB to 3D Tiles");

    // clang-format off
    options.add_options()
        ("i, input", "CDB directory", cxxopts::value<std::string>())
        ("o, output", "3D Tiles output directory", cxxopts::value<std::string>())
        ("elevation-normal", "Generate elevation normal", cxxopts::value<bool>()->default_value("false"))
        ("elevation-lod", "Generate elevation and imagery based on elevation LOD only", cxxopts::value<bool>()->default_value("false"))
        ("elevation-decimate-error", "Set target error when decimating elevation mesh. Target error is normalized to 0..1 (0.01 means the simplifier maintains the error to be below 1% of the mesh extents)", cxxopts::value<float>()->default_value("0.01"))
        ("elevation-threshold-indices", "Set target percent of indices when decimating elevation mesh", cxxopts::value<float>()->default_value("0.3"))
        ("h, help", "Print usage");
    // clang-format on

    auto result = options.parse(argc, argv);
    if (result.count("help")) {
        std::cout << options.help() << "\n";
        return 0;
    }

    if (result.count("input") && result.count("output")) {
        std::filesystem::path CDBPath = result["input"].as<std::string>();
        std::filesystem::path outputPath = result["output"].as<std::string>();

        bool generateElevationNormal = result["elevation-normal"].as<bool>();
        bool elevationLOD = result["elevation-lod"].as<bool>();
        float elevationDecimateError = result["elevation-decimate-error"].as<float>();
        float elevationThresholdIndices = result["elevation-threshold-indices"].as<float>();

        CDBTo3DTiles::GlobalInitializer initializer;
        CDBTo3DTiles::Converter converter(CDBPath, outputPath);
        converter.setGenerateElevationNormal(generateElevationNormal);
        converter.setElevationLODOnly(elevationLOD);
        converter.setElevationDecimateError(elevationDecimateError);
        converter.setElevationThresholdIndices(elevationThresholdIndices);

        converter.convert();
    } else {
        std::cout << options.help();
        return 0;
    }

    return 0;
}

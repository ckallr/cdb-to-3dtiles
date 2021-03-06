#pragma once

#include "CDBAttributes.h"
#include "CDBTileset.h"
#include "tiny_gltf.h"
#include <fstream>
#include <functional>
#include <sstream>

namespace CDBTo3DTiles {

void writeToTilesetJson(const CDBTileset &tileset, bool replace, std::ofstream &fs);

size_t writeToI3DM(std::string GltfURI,
                   const CDBModelsAttributes &modelsAttribs,
                   const std::vector<int> &attribIndices,
                   std::ofstream &fs);

void writeToB3DM(tinygltf::Model *gltf, const CDBInstancesAttributes *instancesAttribs, std::ofstream &fs);

void writeToCMPT(uint32_t numOfTiles,
                 std::ofstream &fs,
                 std::function<uint32_t(std::ofstream &fs, size_t tileIdx)> writeToTileFormat);

} // namespace CDBTo3DTiles

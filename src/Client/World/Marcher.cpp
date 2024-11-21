#include "pch.h"
#include "Chunk.h"
#include "Core/Logger.h"

#ifndef DIST
std::vector<uint8_t> unidentified;
#endif
void LogUnimplementedCase(uint8_t blockId, uint8_t bitsEnabled){
#ifndef DIST
    for(size_t i = 0; i < unidentified.size(); i++)
        if(unidentified[i] == blockId)return;
    unidentified.emplace_back(blockId);
    std::bitset<sizeof(uint8_t) * 8> bits(blockId);
    CORE_ERROR("Marcher: block id not implemented {0}. Bits enabled {1}", bits.to_string(), bitsEnabled);
#endif
}

void Chunk::CreateBlock(uint8_t x, uint8_t y, uint8_t z, uint8_t blockId){
    uint8_t bitsEnabled=blockId & 1;
    for(uint8_t i = 1; i < 8; i++)
        bitsEnabled+=(blockId>>i) & 1;
    switch(bitsEnabled){
    case 0:
    case 8:
        break;
    case 1:
        CreateSingle(x, y, z, blockId);
        break;
    default:
        LogUnimplementedCase(blockId, bitsEnabled);
        return;
    }
}

void Chunk::CreateSingle(uint8_t x, uint8_t y, uint8_t z, uint8_t blockId){
    m_Vertices.reserve(m_Vertices.size() + 3);
    switch(blockId){
    case 0b00000001:
        AddVertex(x + 1, y, z + 2);
        AddVertex(x + 2, y + 2, z + 2);
        AddVertex(x + 2, y, z + 1);
        AddFaces(1);
        break;
    case 0b00000010:
        AddVertex(x + 1, y + 2, z + 2);
        AddVertex(x + 2, y + 2, z + 1);
        AddVertex(x + 2, y + 1, z + 2);
        AddFaces(1);
        break;
    case 0b00000100:
        AddVertex(x + 2, y, z + 1);
        AddVertex(x + 2, y + 1, z);
        AddVertex(x + 1, y, z);
        AddFaces(1);
        break;
    case 0b00001000:
        AddVertex(x + 1, y + 2, z + 1);
        AddVertex(x + 2, y + 1, z);
        AddVertex(x + 1, y + 2, z);
        AddFaces(1);
        break;
    case 0b00010000:
        AddVertex(x, y, z + 1);
        AddVertex(x, y + 1, z + 2);
        AddVertex(x + 1, y, z + 2);
        AddFaces(1);
        break;
    case 0b00100000:
        AddVertex(x, y + 2, z + 1);
        AddVertex(x + 1, y + 2, z + 2);
        AddVertex(x, y + 1, z + 2);
        AddFaces(1);
        break;
    case 0b01000000:
        AddVertex(x, y, z + 1);
        AddVertex(x + 1, y, z);
        AddVertex(x, y + 1, z);
        AddFaces(1);
        break;
    case 0b10000000:
        AddVertex(x, y + 2, z + 1);
        AddVertex(x, y + 1, z);
        AddVertex(x + 1, y + 2, z);
        AddFaces(1);
        break;
    default:
        LogUnimplementedCase(blockId, 1);
        return;
    }
}

void Chunk::AddVertex(uint8_t x, uint8_t y, uint8_t z){
    m_Vertices.emplace_back(x);
    m_Vertices.emplace_back(y);
    m_Vertices.emplace_back(z);
}

void Chunk::AddFaces(uint8_t faces){
    m_Indices.reserve(m_Indices.size() + faces * 3);
    for(uint8_t i = 0; i < faces; i++){
        m_Indices.emplace_back(m_VertexIndex);
        m_Indices.emplace_back(m_VertexIndex + 1);
        m_Indices.emplace_back(m_VertexIndex + 2);
        m_VertexIndex+=3;
    }
}
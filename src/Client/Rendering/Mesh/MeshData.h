#pragma once

//Types are assigned in this order to have specific values for easy addition with GLFW
enum VertexType{
    VT_INT8 = 0,
    VT_UINT8,

    VT_INT16,
    VT_UINT16,
    
    VT_INT32,
    VT_UINT32,

    VT_FLOAT
};

enum IndexType{
    FT_UINT8 = 0,

    FT_UINT16 = 2,

    FT_UINT32 = 4,
};
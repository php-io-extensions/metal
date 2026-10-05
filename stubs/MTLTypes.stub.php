<?php

/** @generate-class-entries */

final class MTLOrigin
{
    public int $x = 0;

    public int $y = 0;

    public int $z = 0;

    public function __construct(int $x, int $y, int $z) {}
}

final class MTLSize
{
    public int $width = 0;

    public int $height = 0;

    public int $depth = 0;

    public function __construct(int $width, int $height, int $depth) {}
}

final class MTLRegion
{
    public MTLOrigin $origin;

    public MTLSize $size;

    public function __construct(MTLOrigin $origin, MTLSize $size) {}
}

final class MTLClearColor
{
    public float $red = 0.0;

    public float $green = 0.0;

    public float $blue = 0.0;

    public float $alpha = 0.0;

    public function __construct(float $red, float $green, float $blue, float $alpha) {}
}

final class MTLViewport
{
    public float $originX = 0.0;

    public float $originY = 0.0;

    public float $width = 0.0;

    public float $height = 0.0;

    public float $znear = 0.0;

    public float $zfar = 0.0;

    public function __construct(float $originX, float $originY, float $width, float $height, float $znear, float $zfar) {}
}

final class MTLScissorRect
{
    public int $x = 0;

    public int $y = 0;

    public int $width = 0;

    public int $height = 0;

    public function __construct(int $x, int $y, int $width, int $height) {}
}

enum MTLPixelFormat: int
{
    case INVALID = 0;
    case A8_UNORM = 1;
    case R8_UNORM = 10;
    case R8_UNORM_SRGB = 11;
    case R8_SNORM = 12;
    case R8_UINT = 13;
    case R8_SINT = 14;
    case R16_UNORM = 20;
    case R16_SNORM = 22;
    case R16_UINT = 23;
    case R16_SINT = 24;
    case R16_FLOAT = 25;
    case RG8_UNORM = 30;
    case RG8_UNORM_SRGB = 31;
    case RG8_SNORM = 32;
    case RG8_UINT = 33;
    case RG8_SINT = 34;
    case B5G6R5_UNORM = 40;
    case A1BGR5_UNORM = 41;
    case ABGR4_UNORM = 42;
    case BGR5A1_UNORM = 43;
    case R32_UINT = 53;
    case R32_SINT = 54;
    case R32_FLOAT = 55;
    case RG16_UNORM = 60;
    case RG16_SNORM = 62;
    case RG16_UINT = 63;
    case RG16_SINT = 64;
    case RG16_FLOAT = 65;
    case RGBA8_UNORM = 70;
    case RGBA8_UNORM_SRGB = 71;
    case RGBA8_SNORM = 72;
    case RGBA8_UINT = 73;
    case RGBA8_SINT = 74;
    case BGRA8_UNORM = 80;
    case BGRA8_UNORM_SRGB = 81;
    case RGB10A2_UNORM = 90;
    case RGB10A2_UINT = 91;
    case RG11B10_FLOAT = 92;
    case RGB9E5_FLOAT = 93;
    case BGR10A2_UNORM = 94;
    case BGR10_XR = 554;
    case BGR10_XR_SRGB = 555;
    case RG32_UINT = 103;
    case RG32_SINT = 104;
    case RG32_FLOAT = 105;
    case RGBA16_UNORM = 110;
    case RGBA16_SNORM = 112;
    case RGBA16_UINT = 113;
    case RGBA16_SINT = 114;
    case RGBA16_FLOAT = 115;
    case BGRA10_XR = 552;
    case BGRA10_XR_SRGB = 553;
    case RGBA32_UINT = 123;
    case RGBA32_SINT = 124;
    case RGBA32_FLOAT = 125;
    case BC1_RGBA = 130;
    case BC1_RGBA_SRGB = 131;
    case BC2_RGBA = 132;
    case BC2_RGBA_SRGB = 133;
    case BC3_RGBA = 134;
    case BC3_RGBA_SRGB = 135;
    case BC4_RUNORM = 140;
    case BC4_RSNORM = 141;
    case BC5_RG_UNORM = 142;
    case BC5_RG_SNORM = 143;
    case BC6H_RGB_FLOAT = 150;
    case BC6H_RGB_UFLOAT = 151;
    case BC7_RGBA_UNORM = 152;
    case BC7_RGBA_UNORM_SRGB = 153;
    case PVRTC_RGB_2BPP = 160;
    case PVRTC_RGB_2BPP_SRGB = 161;
    case PVRTC_RGB_4BPP = 162;
    case PVRTC_RGB_4BPP_SRGB = 163;
    case PVRTC_RGBA_2BPP = 164;
    case PVRTC_RGBA_2BPP_SRGB = 165;
    case PVRTC_RGBA_4BPP = 166;
    case PVRTC_RGBA_4BPP_SRGB = 167;
    case EAC_R11_UNORM = 170;
    case EAC_R11_SNORM = 172;
    case EAC_RG11_UNORM = 174;
    case EAC_RG11_SNORM = 176;
    case EAC_RGBA8 = 178;
    case EAC_RGBA8_SRGB = 179;
    case ETC2_RGB8 = 180;
    case ETC2_RGB8_SRGB = 181;
    case ETC2_RGB8A1 = 182;
    case ETC2_RGB8A1_SRGB = 183;
    case ASTC_4X4_SRGB = 186;
    case ASTC_5X4_SRGB = 187;
    case ASTC_5X5_SRGB = 188;
    case ASTC_6X5_SRGB = 189;
    case ASTC_6X6_SRGB = 190;
    case ASTC_8X5_SRGB = 192;
    case ASTC_8X6_SRGB = 193;
    case ASTC_8X8_SRGB = 194;
    case ASTC_10X5_SRGB = 195;
    case ASTC_10X6_SRGB = 196;
    case ASTC_10X8_SRGB = 197;
    case ASTC_10X10_SRGB = 198;
    case ASTC_12X10_SRGB = 199;
    case ASTC_12X12_SRGB = 200;
    case ASTC_4X4_LDR = 204;
    case ASTC_5X4_LDR = 205;
    case ASTC_5X5_LDR = 206;
    case ASTC_6X5_LDR = 207;
    case ASTC_6X6_LDR = 208;
    case ASTC_8X5_LDR = 210;
    case ASTC_8X6_LDR = 211;
    case ASTC_8X8_LDR = 212;
    case ASTC_10X5_LDR = 213;
    case ASTC_10X6_LDR = 214;
    case ASTC_10X8_LDR = 215;
    case ASTC_10X10_LDR = 216;
    case ASTC_12X10_LDR = 217;
    case ASTC_12X12_LDR = 218;
    case ASTC_4X4_HDR = 222;
    case ASTC_5X4_HDR = 223;
    case ASTC_5X5_HDR = 224;
    case ASTC_6X5_HDR = 225;
    case ASTC_6X6_HDR = 226;
    case ASTC_8X5_HDR = 228;
    case ASTC_8X6_HDR = 229;
    case ASTC_8X8_HDR = 230;
    case ASTC_10X5_HDR = 231;
    case ASTC_10X6_HDR = 232;
    case ASTC_10X8_HDR = 233;
    case ASTC_10X10_HDR = 234;
    case ASTC_12X10_HDR = 235;
    case ASTC_12X12_HDR = 236;
    case GBGR422 = 240;
    case BGRG422 = 241;
    case DEPTH16_UNORM = 250;
    case DEPTH32_FLOAT = 252;
    case STENCIL8 = 253;
    case DEPTH24_UNORM_STENCIL8 = 255;
    case DEPTH32_FLOAT_STENCIL8 = 260;
    case X32_STENCIL8 = 261;
    case X24_STENCIL8 = 262;
}

enum MTLLoadAction: int
{
    case DONT_CARE = 0;
    case LOAD = 1;
    case CLEAR = 2;
}

enum MTLStoreAction: int
{
    case DONT_CARE = 0;
    case STORE = 1;
    case MULTISAMPLE_RESOLVE = 2;
    case STORE_AND_MULTISAMPLE_RESOLVE = 3;
    case UNKNOWN = 4;
    case CUSTOM_SAMPLE_DEPTH_STORE = 5;
}

enum MTLPrimitiveType: int
{
    case POINT = 0;
    case LINE = 1;
    case LINE_STRIP = 2;
    case TRIANGLE = 3;
    case TRIANGLE_STRIP = 4;
}

enum MTLIndexType: int
{
    case UINT16 = 0;
    case UINT32 = 1;
}

enum MTLTextureUsage: int
{
    case UNKNOWN = 0;
    case SHADER_READ = 1;
    case SHADER_WRITE = 2;
    case RENDER_TARGET = 4;
    case PIXEL_FORMAT_VIEW = 16;
    case SHADER_ATOMIC = 32;
}

enum MTLStorageMode: int
{
    case SHARED = 0;
    case MANAGED = 1;
    case PRIVATE = 2;
    case MEMORYLESS = 3;
}

/**
 * Storage-mode, CPU-cache-mode and hazard-tracking bits, shifted as in the SDK.
 * The zero case of each field is the same integer, and a PHP enum case value
 * cannot repeat, so 0 is STORAGE_MODE_SHARED. CPU_CACHE_MODE_DEFAULT_CACHE and
 * HAZARD_TRACKING_MODE_DEFAULT are that zero. Deprecated aliases that repeat a
 * value are not separate cases.
 */
enum MTLResourceOptions: int
{
    case CPU_CACHE_MODE_WRITE_COMBINED = 1;
    case STORAGE_MODE_SHARED = 0;
    case STORAGE_MODE_MANAGED = 16;
    case STORAGE_MODE_PRIVATE = 32;
    case STORAGE_MODE_MEMORYLESS = 48;
    case HAZARD_TRACKING_MODE_UNTRACKED = 256;
    case HAZARD_TRACKING_MODE_TRACKED = 512;
}

enum MTLTextureType: int
{
    case TYPE_1D = 0;
    case TYPE_1D_ARRAY = 1;
    case TYPE_2D = 2;
    case TYPE_2D_ARRAY = 3;
    case TYPE_2D_MULTISAMPLE = 4;
    case CUBE = 5;
    case CUBE_ARRAY = 6;
    case TYPE_3D = 7;
    case TYPE_2D_MULTISAMPLE_ARRAY = 8;
    case TEXTURE_BUFFER = 9;
}

enum MTLVertexFormat: int
{
    case INVALID = 0;
    case UCHAR2 = 1;
    case UCHAR3 = 2;
    case UCHAR4 = 3;
    case CHAR2 = 4;
    case CHAR3 = 5;
    case CHAR4 = 6;
    case UCHAR2_NORMALIZED = 7;
    case UCHAR3_NORMALIZED = 8;
    case UCHAR4_NORMALIZED = 9;
    case CHAR2_NORMALIZED = 10;
    case CHAR3_NORMALIZED = 11;
    case CHAR4_NORMALIZED = 12;
    case USHORT2 = 13;
    case USHORT3 = 14;
    case USHORT4 = 15;
    case SHORT2 = 16;
    case SHORT3 = 17;
    case SHORT4 = 18;
    case USHORT2_NORMALIZED = 19;
    case USHORT3_NORMALIZED = 20;
    case USHORT4_NORMALIZED = 21;
    case SHORT2_NORMALIZED = 22;
    case SHORT3_NORMALIZED = 23;
    case SHORT4_NORMALIZED = 24;
    case HALF2 = 25;
    case HALF3 = 26;
    case HALF4 = 27;
    case FLOAT = 28;
    case FLOAT2 = 29;
    case FLOAT3 = 30;
    case FLOAT4 = 31;
    case INT = 32;
    case INT2 = 33;
    case INT3 = 34;
    case INT4 = 35;
    case UINT = 36;
    case UINT2 = 37;
    case UINT3 = 38;
    case UINT4 = 39;
    case INT1010102_NORMALIZED = 40;
    case UINT1010102_NORMALIZED = 41;
    case UCHAR4_NORMALIZED_BGRA = 42;
    case UCHAR = 45;
    case CHAR = 46;
    case UCHAR_NORMALIZED = 47;
    case CHAR_NORMALIZED = 48;
    case USHORT = 49;
    case SHORT = 50;
    case USHORT_NORMALIZED = 51;
    case SHORT_NORMALIZED = 52;
    case HALF = 53;
    case FLOAT_RG11B10 = 54;
    case FLOAT_RGB9E5 = 55;
}

enum MTLVertexStepFunction: int
{
    case CONSTANT = 0;
    case PER_VERTEX = 1;
    case PER_INSTANCE = 2;
    case PER_PATCH = 3;
    case PER_PATCH_CONTROL_POINT = 4;
}

enum MTLBlendFactor: int
{
    case ZERO = 0;
    case ONE = 1;
    case SOURCE_COLOR = 2;
    case ONE_MINUS_SOURCE_COLOR = 3;
    case SOURCE_ALPHA = 4;
    case ONE_MINUS_SOURCE_ALPHA = 5;
    case DESTINATION_COLOR = 6;
    case ONE_MINUS_DESTINATION_COLOR = 7;
    case DESTINATION_ALPHA = 8;
    case ONE_MINUS_DESTINATION_ALPHA = 9;
    case SOURCE_ALPHA_SATURATED = 10;
    case BLEND_COLOR = 11;
    case ONE_MINUS_BLEND_COLOR = 12;
    case BLEND_ALPHA = 13;
    case ONE_MINUS_BLEND_ALPHA = 14;
    case SOURCE1_COLOR = 15;
    case ONE_MINUS_SOURCE1_COLOR = 16;
    case SOURCE1_ALPHA = 17;
    case ONE_MINUS_SOURCE1_ALPHA = 18;
}

enum MTLBlendOperation: int
{
    case ADD = 0;
    case SUBTRACT = 1;
    case REVERSE_SUBTRACT = 2;
    case MIN = 3;
    case MAX = 4;
}

enum MTLColorWriteMask: int
{
    case NONE = 0;
    case RED = 8;
    case GREEN = 4;
    case BLUE = 2;
    case ALPHA = 1;
    case ALL = 15;
}

enum MTLSamplerMinMagFilter: int
{
    case NEAREST = 0;
    case LINEAR = 1;
}

enum MTLSamplerAddressMode: int
{
    case CLAMP_TO_EDGE = 0;
    case MIRROR_CLAMP_TO_EDGE = 1;
    case REPEAT = 2;
    case MIRROR_REPEAT = 3;
    case CLAMP_TO_ZERO = 4;
    case CLAMP_TO_BORDER_COLOR = 5;
}

enum MTLCompareFunction: int
{
    case NEVER = 0;
    case LESS = 1;
    case EQUAL = 2;
    case LESS_EQUAL = 3;
    case GREATER = 4;
    case NOT_EQUAL = 5;
    case GREATER_EQUAL = 6;
    case ALWAYS = 7;
}

enum MTLStencilOperation: int
{
    case KEEP = 0;
    case ZERO = 1;
    case REPLACE = 2;
    case INCREMENT_CLAMP = 3;
    case DECREMENT_CLAMP = 4;
    case INVERT = 5;
    case INCREMENT_WRAP = 6;
    case DECREMENT_WRAP = 7;
}

enum MTLCullMode: int
{
    case NONE = 0;
    case FRONT = 1;
    case BACK = 2;
}

enum MTLWinding: int
{
    case CLOCKWISE = 0;
    case COUNTER_CLOCKWISE = 1;
}

enum MTLCommandBufferStatus: int
{
    case NOT_ENQUEUED = 0;
    case ENQUEUED = 1;
    case COMMITTED = 2;
    case SCHEDULED = 3;
    case COMPLETED = 4;
    case ERROR = 5;
}


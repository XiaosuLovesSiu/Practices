#include <cstdint> // int32_t, uint32_t, uint16_t
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;


#pragma pack(push, 1) // 本行不可删改！
typedef struct
{
    uint16_t signature;   // "BM" (0x4D42)
    uint32_t file_size;   // 文件总大小
    uint16_t reserved1;   // 保留
    uint16_t reserved2;   // 保留
    uint32_t data_offset; // 图像数据起始偏移
} BMPFileHeader;

typedef struct
{
    uint32_t biSize;         // 本结构大小(40字节)
    int32_t biWidth;         // 图像宽度（像素）
    int32_t biHeight;        // 图像高度（像素）
    uint16_t biPlanes;       // 颜色平面数（必须为1）
    uint16_t biBitCount;     // 每像素位数（在本题中，统一为24，即3个字节存储一个像素点）
    uint32_t biCompression;  // 压缩类型
    uint32_t biSizeImage;    // 图像数据大小（字节）
    int32_t biXPelsPerMeter; // 水平分辨率（像素/米）
    int32_t biYPelsPerMeter; // 垂直分辨率（像素/米）
    uint32_t biClrUsed;      // 实际使用的颜色数
    uint32_t biClrImportant; // 重要颜色数
} BMPInfoHeader;
#pragma pack(pop) // 本行不可删改！

int main()
{
    ifstream fin("image.bmp", ios::binary);
    if (!fin)
    {
        cerr << "Error opening input file" << endl;
        return 1;
    }
    ofstream fout("image_info.txt");
    if (!fout)
    {
        cerr << "Error opening output file" << endl;
        return 1;
    }

    BMPFileHeader fheader;
    BMPInfoHeader iheader;

    fin.read(reinterpret_cast<char *>(&fheader), sizeof(fheader));
    fin.read(reinterpret_cast<char *>(&iheader), sizeof(iheader));

    if (fheader.signature != 0x4D42)
    {
        cerr << "invalid BMP file" << endl;
        return 1;
    }

    const int width=500;

    fin.close();
    fout.close();
    return 0;
}
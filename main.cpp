#include "modules.h"
#include "bmp.h"

#include "config.cpp"

class BitMap {
public:
    std::vector<char> buffer;
    PBITMAPFILEHEADER file_header;
    PBITMAPINFOHEADER info_header;
    
    BitMap(const std::string path) {
        this->_read(path);
    }
    
    void replace(const std::string path, std::vector<int> bytes) {
        const char offset = 0b0000001;
        
        for (int value : bytes)
            this->buffer[value] = this->buffer[value] + offset;
        
        std::ofstream out(path);
        out.write(reinterpret_cast<const char*>(&buffer[0]), buffer.size() * sizeof(char));
        out.close();
    }
    
private:
    void _read(const std::string path) {
        std::ifstream file(path, std::ios::binary);
        
        if (file) {
            file.seekg(0, std::ios::end);
            std::streampos length = file.tellg();
            file.seekg(0, std::ios::beg);

            this->buffer.resize(length);
            file.read(&this->buffer[0],length);

            file_header = (PBITMAPFILEHEADER)(&this->buffer[0]);
            info_header = (PBITMAPINFOHEADER)(&this->buffer[0] + sizeof(BITMAPFILEHEADER));
        }
    }
};

int main() {
    Config config = Config("/Users/mak/Documents/programming/education/mospolytech/labs/bmp_image/bmp_image/data/bytes.txt");
    
    BitMap bitmap = BitMap("/Users/mak/Documents/programming/education/mospolytech/labs/bmp_image/bmp_image/data/9.bmp");
    bitmap.replace("/Users/mak/Documents/programming/education/mospolytech/labs/bmp_image/bmp_image/data/out.bmp", config.replaced_bytes);

    return 0;
}

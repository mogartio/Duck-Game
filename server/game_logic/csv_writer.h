#include <fstream>
#ifndef CSV_WRITER_H

#define ROW_NUMBER 50
#define COLUMN_NUMBER 50
#define FLOOR 1
#define BACKGROUND 0
//Esta clase se encarga de crear mapas en formato csv
class CSVWriter{
public:
    static void write_map(const std::string& file_name){
        std::ofstream file;
        file.open(file_name, std::ios::trunc);
        file << ROW_NUMBER << "," << COLUMN_NUMBER << std::endl; //Mapas de distintos tamanios
        for (int i=0; i < ROW_NUMBER; i ++){
            for (int j=0; j < COLUMN_NUMBER; j++){
                if (j == 20 && i < 36){
                    file << FLOOR << ",";
                    continue;
                }
                if ((i == 40 || i ==  41) && j > 10 && j < 40){
                    file << FLOOR << ",";
                    continue;
                }
                file << BACKGROUND;
                if (j != COLUMN_NUMBER - 1){
                    file << ",";
                }
            }
            file << std::endl;
        }
    }
};

#endif

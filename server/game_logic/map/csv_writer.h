#include <fstream>
#include <string>

#include "../config/config.h"
#ifndef CSV_WRITER_H

// Esta clase se encarga de crear mapas en formato csv
class CSVWriter {
public:
    static void write_map(const std::string& file_name) {
        int total_rows = Config::get_instance()->rows_map;
        int total_columns = Config::get_instance()->columns_map;
        std::ofstream file;
        file.open(file_name, std::ios::trunc);
        file << total_rows << "," << total_columns << std::endl;  // Mapas de distintos tamanios
        for (int i = 0; i < total_rows; i++) {
            for (int j = 0; j < total_columns; j++) {
                // if (j == 20 && i < 36) {
                //     file << Config::get_instance()->mapsId["wall"] << ",";
                //     continue;
                // }
                if ((j == 7 || j == 6) && i >= 35) {
                    file << Config::get_instance()->mapsId["floor"] << ",";
                    continue;
                }
                if ((i == 40 || i == 41) && j > 10 && j < 140) {
                    file << Config::get_instance()->mapsId["floor"] << ",";
                    continue;
                }
                if ((i > 40) && j > 10 && j < 140) {
                    file << Config::get_instance()->mapsId["floor"] << ",";
                    continue;
                }
                file << Config::get_instance()->mapsId["background"];
                if (j != total_columns - 1) {
                    file << ",";
                }
            }
            file << std::endl;
        }
    }
};

#endif

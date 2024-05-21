#ifndef DOC_FILE_VRML_CLASS_H
#define DOC_FILE_VRML_CLASS_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class ReadFile {
public:
	ReadFile(){}
	static std::vector<float> readVBO(std::vector<float>& VBO, std::vector<int>& EBO) {

        std::vector<float> v;

        std::ifstream inputFile("villa_22.wrl");

        if (inputFile.is_open()) {
            std::string line;

            std::vector<float> tran;
            std::vector<float> color;
            int countvetex = 0;

            while (getline(inputFile, line)) {
                
                if (xet(line, "translation")) {
                    tran = getTran(line);
                }
                if (xet(line, "diffuseColor")) {
                    color = getColor(line);
                }
                if (xet(line, "Coordinate")) {
                    getVBO(VBO, inputFile, tran, color);
                }
                if (xet(line, "coordIndex")) {
                    getEBO(EBO, inputFile, countvetex);

                    countvetex = VBO.size() / 6;
                }

            }

            inputFile.close();
        }
        else {
            std::cout << "error file" << std::endl;
        }

        return v;
	}

	static std::vector<int> readEBO() {

	}

    static bool xet(std::string s1, std::string s2) {
        size_t pos = s1.find(s2);

        if (pos != std::string::npos) {
            return true;
        }
        else {
            return false;
        }
    }

    static std::vector<float> getTran(std::string& line) {
        std::vector<float> v;
        
        char delimiter = ' ';

        std::stringstream ss(line);
        std::string token;

        while (getline(ss, token, delimiter)) {
            float f;
            
            try{
                f = std::stof(token);
                v.push_back(f);
            }
            catch (const std::exception& ex) {

            }
            
        }
        std::cout << "translation" << v[0] << " " << v[1] << " " << v[2] << " " << "\n";
        return v;
    }

    static std::vector<float> getColor(std::string line) {
        std::vector<float> v;

        char delimiter = ' ';

        std::stringstream ss(line);
        std::string token;

        while (getline(ss, token, delimiter)) {
            float f;

            try {
                f = std::stof(token);
                v.push_back(f);
            }
            catch (const std::exception& ex) {

            }

        }
        std::cout << "Color" << v[0] << " " << v[1] << " " << v[2] << " " << "\n";
        return v;
    }

    static void getVBO(std::vector<float>& v, std::ifstream& file, std::vector<float> tran, std::vector<float> color) {
        

        std::string line;
        while (getline(file, line)) {
            std::string p = "}";
            if (xet(line, p)) break;
            std::vector<std::string> s = getstring(line, ',');
            
            for (int i = 0; i < s.size(); ++i) {
                if (s[i].size() > 1) {

                    std::vector<float> v1 = getCoor(s[i]);

                    v.push_back(v1[0] + tran[0]);
                    v.push_back(v1[1] + tran[1]);
                    v.push_back(v1[2] + tran[2]);
                    v.push_back(color[0]);
                    v.push_back(color[1]);
                    v.push_back(color[2]);

                }
            }

        }
    }

    static void getEBO(std::vector<int>& v, std::ifstream& file, int countvertex) {
        
        std::string line;
        while (getline(file, line)) {
            std::string p = "}";
            if (xet(line, p)) break;
            std::vector<std::string> s = getstring(line, ',');

            for (int i = 0; i < s.size(); i += 4) {
                int index1;
                int index2;
                int index3;
                try {
                    index1 = countvertex + std::stoi(s[i]);
                    index2 = countvertex + std::stoi(s[i + 1]);
                    index3 = countvertex + std::stoi(s[i + 2]);

                    v.push_back(index1);
                    v.push_back(index2);
                    v.push_back(index3);

                    //std::cout << index1 << " " << index2 << " " << index3 << "\n";
                }
                catch (const std::exception& ex) {

                }
             }
            //std::cout << std::endl;

        }
    }

    static std::vector<std::string> getstring(std::string line, char delimiter) {
        std::vector<std::string> v;
        
        std::stringstream ss(line);
        std::string token;

        while (getline(ss, token, delimiter)){
            //std::cout << token << "\n";

            v.push_back(token);
        }
        
        return v;
    }

    static std::vector<float> getCoor(std::string line) {
        std::vector<float> v;

        char delimiter = ' ';

        std::stringstream ss(line);
        std::string token;

        while (getline(ss, token, delimiter)) {
            float f;

            try {
                f = std::stof(token);
                v.push_back(f);
            }
            catch (const std::exception& ex) {

            }

        }
        //std::cout << "Coor" << v[0] << " " << v[1] << " " << v[2] << " " << "\n";
        return v;
    }
};

#endif // DOC_FILE_CLASS_H

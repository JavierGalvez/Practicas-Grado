#include "global.h"
#include "score.h"
#include "algorithms.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>

template<typename T>
bool readFile(std::string path, std::vector<std::vector<T> >& vect){
    std::string line;
    std::ifstream file(path);
    bool file_open = file.is_open();

    if(file_open){
        std::cout << "Leyendo datos de " << path << std::endl;
        while(getline(file,line)){
            std::stringstream ss(line);
            T x; std::vector<T> aux;
            while(ss >> x){
                aux.push_back(x);
                if(ss.peek() == ',')
                    ss.ignore();
            }
            vect.push_back(aux);
        }
        file.close();
    } else{
        std::cout << "No se ha podido abrir " << path << std::endl;
    }
    return file_open;
}

void output(std::string option, std::string path, bool output_to_file=false){
    using namespace std::chrono;

    srand(seed);
    random_engine = std::default_random_engine(seed);
    Solution S;
    auto start = high_resolution_clock::now();
    if(option == "a") S = bbbc(30, 100000, 1.0);
    else if(option == "b") S = bbbc(30, 100000, 0.2);
    else if(option == "c") S = bbbc(30, 100000, 1.0, true);
    else if(option == "d") S = bbbc(30, 100000, 0.2, true);
    else { std::cout << option << " no es una opción válida" << std::endl; return; }
    auto stop = high_resolution_clock::now();
    duration<double> t = duration_cast<duration<double> > (stop - start);

    double c = C(S), infe = infeasibility(S);

    std::cout << "time: " << t.count() << std::endl;
    std::cout << "f: " << S.f << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << "infeasibility: " << infe << std::endl;

    if(output_to_file){
        std::ofstream file(path, std::ostream::trunc);
        if(file.is_open()){
            file << "time\t" << t.count() << std::endl;
            file << "f\t" << S.f << std::endl;
            file << "c\t" << c << std::endl;
            file << "infeasibility\t" << infe << std::endl;
            file.close();
            std::cout << "Salida guardada en: " << path << std::endl;
        } else {
            std::cout << "No se ha podido abrir " << path << std::endl;
        }
    }


}

int main(int argc, char* argv[]){
    if(argc !=6){
        std::cout << "Error en los argumentos de entrada" << std::endl;
        std::cout << "./test dataset %restrictions clusters seed option" << std::endl;
        std::cout << "a: original\n" << "b: original mejorado\n" 
            << "c: original + ls\n" << "d: mejorado + ls" << std::endl;
        return 1;
    }

    std::string dataset(argv[1]);
    std::string r(argv[2]);

    k = std::atoi(argv[3]);
    seed = std::atoi(argv[4]);

    bool read_data = readFile("./data/" + dataset + "_set.dat", data);
    bool read_rest = readFile("./data/" + dataset + "_set_const_" + r + ".const", restrictions);

    if(!read_data || !read_rest) return 1;
    std::cout << "Datos leidos correctamente" << std::endl;

    lambda = calc_lambda();
    bounds = get_bounds();

    std::string option(argv[5]);
    std::string output_path("./output/" + option + "_" + dataset + "_" + r + "_" + argv[4] + ".output");

    output(option, output_path);

    return 0;
}

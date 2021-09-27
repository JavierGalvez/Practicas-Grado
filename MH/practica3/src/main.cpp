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

void output(std::string alg, std::string path, bool verbose=false){
    using namespace std::chrono;

    srand(seed);
    random_engine = std::default_random_engine(seed);
    Solution s;
    auto start = high_resolution_clock::now();
    if(alg == "es") s = es(0.3, 0.3, 100000);
    else if(alg == "bmb") s = bmb(10, 10000);
    else if(alg == "ils-ls") s = ils_ls(10, 10000);
    else if(alg == "ils-es") s = ils_es(10, 10000);
    else { std::cout << "No existe el algoritmo " << alg << std::endl; return; }
    auto stop = high_resolution_clock::now();
    duration<double> t = duration_cast<duration<double> > (stop - start);

    double c = C(s.s), infe = infeasibility(s.s);

    if(verbose){
        std::cout << "time: " << t.count() << std::endl;
        std::cout << "f: " << s.f << std::endl;
        std::cout << "c: " << c << std::endl;
        std::cout << "infeasibility: " << infe << std::endl;
    }

    std::ofstream file(path, std::ostream::trunc);
    if(file.is_open()){
        file << "time\t" << t.count() << std::endl;
        file << "f\t" << s.f << std::endl;
        file << "c\t" << c << std::endl;
        file << "infeasibility\t" << infe << std::endl;
        file.close();
        std::cout << "Salida guardada en: " << path << std::endl;
    } else {
        std::cout << "No se ha podido abrir " << path << std::endl;
    }


}

int main(int argc, char* argv[]){
    if(argc !=6){
        std::cout << "Error en los argumentos de entrada" << std::endl;
        std::cout << "./test dataset %restrictions clusters seed alg" << std::endl;
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

    std::string alg(argv[5]);
    std::string output_path("./output/" + alg + "_" + dataset + "_" + r + "_" + argv[4] + ".output");

    output(alg, output_path, true);

    return 0;
}

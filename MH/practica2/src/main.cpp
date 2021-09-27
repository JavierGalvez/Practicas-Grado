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

void output(Chromosome (*genetico)(int, float, float, int), int n, float pm, std::string path, bool verbose=false){
    using namespace std::chrono;

    srand(seed);
    random_engine = std::default_random_engine(seed);
    auto start = high_resolution_clock::now();
    Chromosome a = genetico(n, pm, 0.001, 100000);
    auto stop = high_resolution_clock::now();
    duration<double> t = duration_cast<duration<double> > (stop - start);

    double c = C(a.s), infe = infeasibility(a.s);

    if(verbose){
        std::cout << "time: " << t.count() << std::endl;
        std::cout << "f: " << a.f << std::endl;
        std::cout << "c: " << c << std::endl;
        std::cout << "infeasibility: " << infe << std::endl;
    }

    std::ofstream file(path, std::ostream::trunc);
    if(file.is_open()){
        file << "time\t" << t.count() << std::endl;
        file << "f\t" << a.f << std::endl;
        file << "c\t" << c << std::endl;
        file << "infeasibility\t" << infe << std::endl;
        file.close();
        std::cout << "Salida guardada en: " << path << std::endl;
    } else {
        std::cout << "No se ha podido abrir " << path << std::endl;
    }


}

int main(int argc, char* argv[]){
    if(argc !=6) return 1;

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

    if(alg == "aggun") output(&aggun, 50, 0.7, output_path, true);
    else if(alg == "aggsf") output(&aggsf, 50, 0.7, output_path, true);
    else if(alg == "ageun") output(&ageun, 50, 1.0, output_path, true);
    else if(alg == "agesf") output(&agesf, 50, 1.0, output_path, true);
    else if(alg == "am_all") output(&am_all, 10, 0.7, output_path, true);
    else if(alg == "am_random") output(&am_random, 10, 0.7, output_path, true);
    else if(alg == "am_best") output(&am_best, 10, 0.7, output_path, true);
    else std::cout << "No existe el algoritmo " << alg << std::endl;

    return 0;
}

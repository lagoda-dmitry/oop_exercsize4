#include <iostream>
#include <vector>
#include <map>
#include "figures.hpp"

enum { 
    ERR, CLASS,
    PRINT,
    REC, EXIT,
    CENTR, AREA,
    TRAP, RHOMB,
    SIZE, HELP, INT,
    DOUBLE, FLOAT, FIGURE, 
    TYPE, NEW,
    FUNC, COOR, TUPLE
};

void help() {
    std::cout << "\nCommands: save, load, add, del, print, area, size, quit, help, centr, less_then and undo\n";
    std::cout << "Supported Figures: rectangle, trap, rhombus\n\n";
    std::cout << "For rectangle: 2 diagonal points (0 0 2 2)\n";
    std::cout << "For trap: 2 points of founding of a trap, angle and a length of a side ( 0 0 4 4 45 2)\n";
    std::cout << "For rhombus: 2 diagonal points and a length if a side ( 0 0 0 3 5)\n";
}


int main() {
    Rectangle<int>  RI;
    Rectangle<float>  RF;
    
    Rhombus<int>  RoI;
    Rhombus<float>  RoF;
 
    Trap<int>  TI;
    Trap<float>  TF;
    
    std::tuple<PairWIO<int,int>, PairWIO<int,int>, PairWIO<int,int>, PairWIO<int,int>> TuI;
    std::tuple<PairWIO<float,float>, PairWIO<float,float>, PairWIO<float,float>, PairWIO<float,float>> TuF;
   
    using Point = PairWIO<double,double>;
    Point tmpP1, tmpP2, tmpP3, tmpP4;
    std::string comId, figType, typeId;
  
    int id;
    double length, angle, overallArea;
    int status = 1;
    Figure* workingFigure;
    std::map <std::string, int> command;
    std::map <std::string, int> figures;
    std::map <std::string, int> types;
    command["print"] = PRINT;
    figures["rec"] = REC;
    figures["trap"] = TRAP;
    figures["rhomb"] = RHOMB;
    figures["tuple"] = TUPLE;
    types["int"] = INT;
    types["double"] = DOUBLE;
    types["float"] = FLOAT;
    command["class"] = CLASS;
    command["new"] = NEW;
    command["rectangle"] = REC;
    command["quit"] = EXIT;
    command["q"] = EXIT;
    command["centr_of"] = CENTR;
    command["centr"] = CENTR;
    command["area_of"] = AREA;
    command["area"] = AREA;
    command["size_of"] = AREA;
    command["size"] = SIZE;
    command["help"] = HELP;
    command["h"] = HELP;

    help();
    int state = FIGURE;
    while (status) {
        switch (state) {
            case FIGURE:
                std::cout << "For ";
                std::cin >> figType;
                if (figures[figType] == ERR) {
                    state = FIGURE;
                    std::cout << "Invalid figure\n";
                    break;
                }
                state = TYPE;
                break;
            case TYPE: 
                std::cout << "Of ";
                std::cin >> typeId;
                if (types[typeId] == ERR) {
                    state = TYPE;
                    std::cout << "Invalid type\n";
                    break;
                }
                state = COOR;
                break;
            case COOR:
                std::cout << "With coordinats: ";
                switch (figures[figType]) {
                    case REC:
                        if (!( std::cin >> tmpP1 >> tmpP2)) {
                            std::cout << "Invalid Params\n";
                            break;
                        }
                        switch (types[typeId]) {
                            case INT:
                                RI.restruct(PairWIO<int,int>((int)tmpP1.first, (int)tmpP1.second), PairWIO<int,int>((int)tmpP2.first, (int)tmpP2.second));
                                break;
                            case FLOAT:
                                RF.restruct(PairWIO<float,float>((float)tmpP1.first, (float)tmpP1.second), PairWIO<float,float>((float)tmpP2.first, (float)tmpP2.second));
                                break;
                            
                        }
                        std::cout << "Rectangle added\n";
                        state = FUNC;
                        break;
                    
                    case RHOMB:
                        if (!( std::cin >> tmpP1 >> tmpP2 >> length)) {
                            std::cout << "Invalid Params\n";
                            break;
                        }
                        switch (types[typeId]) {
                            case INT:
                                RoI.restruct(PairWIO<int,int>((int)tmpP1.first, (int)tmpP1.second), PairWIO<int,int>((int)tmpP2.first, (int)tmpP2.second), length);
                                break;
                            case FLOAT:
                                RoF.restruct(PairWIO<float,float>((float)tmpP1.first, (float)tmpP1.second), PairWIO<float,float>((float)tmpP2.first, (float)tmpP2.second), length);
                                break;
                            
                        }
                        std::cout << "Rhombus added\n";
                        state = FUNC;
                        break;
                    case TRAP:
                        if (!( std::cin >> tmpP1 >> tmpP2 >> angle >> length)) {
                            std::cout << "Invalid Params\n";
                            break;
                        }
                        switch (types[typeId]) {
                            case INT:
                                TI.restruct(PairWIO<int,int>((int)tmpP1.first, (int)tmpP1.second), PairWIO<int,int>((int)tmpP2.first, (int)tmpP2.second), angle, length);
                                break;
                            case FLOAT:
                                TF.restruct(PairWIO<float,float>((float)tmpP1.first, (float)tmpP1.second), PairWIO<float,float>((float)tmpP2.first, (float)tmpP2.second), angle, length);
                                break;
                            
                        }
                        std::cout << "Trap added\n";
                        state = FUNC;
                        break;
                    case TUPLE:
                        if (!( std::cin >> tmpP1 >> tmpP2 >> tmpP3 >> tmpP4)) {
                            std::cout << "Invalid Params\n";
                            break;
                        }
                        switch (types[typeId]) {
                            case INT:
                                std::get<0>(TuI) = PairWIO<int,int>((int)tmpP1.first, (int)tmpP1.second);
                                std::get<1>(TuI) = PairWIO<int,int>((int)tmpP2.first, (int)tmpP2.second);
                                std::get<2>(TuI) = PairWIO<int,int>((int)tmpP3.first, (int)tmpP3.second);
                                std::get<3>(TuI) = PairWIO<int,int>((int)tmpP4.first, (int)tmpP4.second);
                                break;
                            case FLOAT:
                                std::get<0>(TuF) = PairWIO<float,float>((float)tmpP1.first, (float)tmpP1.second);
                                std::get<1>(TuF) = PairWIO<float,float>((float)tmpP2.first, (float)tmpP2.second);
                                std::get<2>(TuF) = PairWIO<float,float>((float)tmpP3.first, (float)tmpP3.second);
                                std::get<3>(TuF) = PairWIO<float,float>((float)tmpP4.first, (float)tmpP4.second);
                                break;
                            
                        }
                        state = FUNC;
                        break;
                }
                while(getchar() != '\n');
                std::cin.clear();
                break;
            case FUNC:
                std::cin >> comId;
                switch (command[comId]) {
                    case PRINT:
                        state = PRINT;
                        break;
                    case CENTR:
                        state = CENTR;
                        break;
                    case AREA:
                        state = AREA;
                        break;
                    case NEW:
                        state = FIGURE;
                        break;
                    case EXIT:
                        status = 0;
                        break;
                    case ERR:
                        std::cout << "Invalid command\n";
                        break;
                }
                while(getchar() != '\n');
                break;
            case PRINT:
                switch (figures[figType]) {
                    case REC:
                        switch (types[typeId]) {
                            case INT:
                                printCoor(RI);
                                break;
                            case FLOAT:
                                printCoor(RF);
                                break;
                            
                        }
                        break;
                    case RHOMB:
                        switch (types[typeId]) {
                            case INT:
                                printCoor(RoI);
                                break;
                            case FLOAT:
                                printCoor(RoF);
                                break;
                            
                        }
                        break;
                    case TRAP:
                        switch (types[typeId]) {
                            case INT:
                                printCoor(TI);
                                break;
                            case FLOAT:
                                printCoor(TF);
                                break;
                            
                        }
                        break;
                    case TUPLE:
                        switch (types[typeId]) {
                            case INT:
                                printCoor(TuI);
                                break;
                            case FLOAT:
                                printCoor(TuF);
                                break;
                            
                        }
                        break;
                }
                state = FUNC;
                break;
            case CENTR:
                switch (figures[figType]) {
                    case REC:
                        switch (types[typeId]) {
                            case INT:
                                std::cout << centr(RI) << '\n';
                                break;
                            case FLOAT:
                                std::cout << centr(RF) << '\n';
                                break;
                           
                        }
                        break;
                    case RHOMB:
                        switch (types[typeId]) {
                            case INT:
                                std::cout << centr(RoI) << '\n';
                                break;
                            case FLOAT:
                                std::cout << centr(RoF) << '\n';
                                break;
                            
                        }
                        break;
                    case TRAP:
                        switch (types[typeId]) {
                            case INT:
                                std::cout << centr(TI) << '\n';
                                break;
                            case FLOAT:
                                std::cout << centr(TF) << '\n';
                                break;
                            
                        }
                        break;
                    case TUPLE:
                        switch (types[typeId]) {
                            case INT:
                                std::cout << centr(TuI) << '\n';
                                break;
                            case FLOAT:
                                std::cout << centr(TuF) << '\n';
                                break;
                          
                        }
                        break;
                }
                state = FUNC;
                break;
            case AREA:
                switch (figures[figType]) {
                    case REC:
                        switch (types[typeId]) {
                            case INT:
                                std::cout << area(RI) << '\n';
                                break;
                            case FLOAT:
                                std::cout << area(RF) << '\n';
                                break;
                            
                        }
                        break;
                    case RHOMB:
                        switch (types[typeId]) {
                            case INT:
                                std::cout << area(RoI) << '\n';
                                break;
                            case FLOAT:
                                std::cout << area(RoF) << '\n';
                                break;
                            case DOUBLE:
                                std::cout << area(RoD) << '\n';
                                break;
                        }
                        break;
                    case TRAP:
                        switch (types[typeId]) {
                            case INT:
                                std::cout << area(TI) << '\n';
                                break;
                            case FLOAT:
                                std::cout << area(TF) << '\n';
                                break;
                           
                        }
                        break;
                    case TUPLE:
                        switch (types[typeId]) {
                            case INT:
                                std::cout << area(TuI) << '\n';
                                break;
                            case FLOAT:
                                std::cout << area(TuF) << '\n';
                                break;
                            
                        }
                        break;
                }
                state = FUNC;
                break;
            case HELP:
                help();
                break;
            case EXIT:
                status = 0;
                break;
        }
        
        std::cin.clear();
    }
    return 0;
}

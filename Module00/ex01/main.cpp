#include "Graph.hpp"
#include <iostream>
#include <string>

const char* USAGE_SAVE = "graph [--save <filepath>] [--print] [--load <filepath>]";


int main(int argc, char const *argv[]) try
{
    (void)argc;
    bool saveFile = false;
    bool load = false;
    bool isPrint = false;
    std::string saveFilePath = "";
    std::string loadFilePath = "";
    Graph gr(Vector2(800, 600));
    gr.addPoint(Vector2(50, 800));
    gr.addPoint(Vector2(2, 2));
    gr.addPoint(Vector2(32, 20));
    gr.addPoint(Vector2(95, 50));
    // gr.addPoint(Vector2(20, 5));
    gr.addLine(Vector2(0, 0), Vector2(800, 600));
    // gr.printToConsole();
    while (++argv && *argv)
    {
        if (std::string(*argv) == "--save")
        {
            ++argv;
            saveFile = true;
            if (!*argv)
                throw std::logic_error(USAGE_SAVE);
            saveFilePath = *argv;
        }
        else if (std::string(*argv) == "--print")
        {
            ++argv;
            isPrint = true;
        }
        else if (std::string(*argv) == "--load")
        {
            ++argv;
            if (!*argv)
                throw std::logic_error(USAGE_SAVE);
            load = true;
            loadFilePath = *argv;
        }
    }
    
    if ( !isPrint && !saveFile)
        throw std::logic_error(USAGE_SAVE);
    if ( load )
        gr.readFromFile(loadFilePath);
    if ( saveFile && !saveFilePath.empty() )
        gr.saveToImage(saveFilePath.c_str());
    if ( isPrint )
        gr.printToConsole();
    return 0; 
}
catch(const std::exception& ex)
{
    std::cerr << ex.what() << std::endl;
}

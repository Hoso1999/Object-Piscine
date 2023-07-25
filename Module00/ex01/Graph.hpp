#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include "Vector2.hpp"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Graph
{
    private:
        Vector2                                         m_bounds;
        std::vector<Vector2>                            m_points;
        std::vector<std::pair<Vector2, Vector2> >       m_lines;
        sf::RenderTexture                               m_texture;

        void draw();
        void drawLines();
        void parsePoints(const std::string& line, std::vector<Vector2>& points);
        void parseLines(const std::string& line, std::vector<std::pair<Vector2, Vector2> >& lines);
        std::string trim(const std::string&);
        std::string ignoreLine(const std::string& line);
    public:
        Graph(const Vector2& p_bounds);
        const Vector2& getBounds() const;
        void addPoint(const Vector2& p_point);
        void addLine(const Vector2& start, const Vector2& end);
        void printToConsole() const;
        void saveToImage(const std::string& filename);
        void readFromFile(const std::string& filepath);
};


#endif
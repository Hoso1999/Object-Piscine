#include "Graph.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include <fstream>

Graph::Graph(const Vector2& p_bounds)
    :   m_bounds(p_bounds)
{
    if( !m_texture.create(m_bounds.getX(), m_bounds.getY()) )
        throw std::runtime_error("Couldn't create image");
}

const Vector2& Graph::getBounds() const
{
    return m_bounds;
}


void Graph::addPoint(const Vector2& m_point)
{
    m_points.push_back(m_point);
}
void Graph::printToConsole() const
{
    std::vector<std::string> p_map(m_bounds.getY() + 1);
    for (size_t i = 0; i < m_bounds.getY(); i++)
    {
        p_map.resize(m_bounds.getX() + 1);
        p_map[i] = std::string(m_bounds.getX(), '.');
    }
    for (std::vector<Vector2>::const_iterator it = m_points.begin(); it != m_points.end(); ++it)
    {
        try
        {
            p_map.at(it->getY()).at(it->getX()) = 'X';
        }
        catch(const std::exception& e)
        {}
        
    }
    for (size_t i = 0; i < m_bounds.getY(); ++i)
    {
        for (size_t j = 0; j < m_bounds.getX(); ++j)
        {
            std::cout << p_map[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    
    
}

void Graph::draw()
{
    float m = 0.01;
    float ratioX = m_bounds.getX() * m;
    float ratioY = m_bounds.getY() * m;
    float ratio = std::sqrt(ratioX * ratioX + ratioY * ratioY);
    for (std::vector<Vector2>::const_iterator it = m_points.begin(); it != m_points.end(); ++it) {
        sf::CircleShape circle(5 * ratio);
        circle.setPosition(sf::Vector2f(it->getX() * ratioX - 5 * ratio , it->getY() * ratioY - 5 * ratio));
        circle.setFillColor(sf::Color::Red);
        m_texture.draw(circle);
    }
}

void Graph::drawLines()
{
    for (std::vector<std::pair<Vector2, Vector2> >::const_iterator it = m_lines.begin(); it != m_lines.end(); ++it) {
        sf::VertexArray lines(sf::Lines);
        lines.append(sf::Vertex(sf::Vector2f(it->first.getX(), it->first.getY()), sf::Color::White));
        lines.append(sf::Vertex(sf::Vector2f(it->second.getX(), it->second.getY()), sf::Color::White));
        m_texture.draw(lines);
    }
}

void Graph::addLine(const Vector2& start, const Vector2& end)
{
    m_lines.push_back(std::make_pair(start, end));
}


void Graph::saveToImage(const std::string& filename)
{
  
    m_texture.setSmooth(true);

    m_texture.clear(sf::Color::Black);
    draw();
    drawLines();
    m_texture.display();
    sf::Image image = m_texture.getTexture().copyToImage();
    if (!image.saveToFile(filename))
        throw std::runtime_error("Couldn't save PNG file.");
    else
        std::cout << "PNG file saved successfully." << std::endl;
}


void Graph::parsePoints(const std::string& line, std::vector<Vector2>& points)
{
    std::stringstream ss(line);
    char ch;
    while (ss >> std::ws >> ch)
    {
        if (ch != '(')
            throw std::logic_error("Error parsing points expected \'(\'");
        Vector2 p;
        float x;
        float y;
        if (!(ss >> std::ws >> x))
            throw std::runtime_error("Error parsing x-coordinate of point.");
        if (!(ss >> std::ws >> y))
            throw std::runtime_error("Error parsing y-coordinate of point.");
        ss >> std::ws >> ch >> std::ws; // Read the closing parenthesis
        if (ch != ')')
            throw std::logic_error("Error parsing points expected \')\'");
        p.setX(x);
        p.setY(y);
        points.push_back(p);
    }
}

void Graph::parseLines(const std::string& line, std::vector<std::pair<Vector2, Vector2>>& lines)
{
    if (line[line.size() - 1] != ')')
            throw std::logic_error("Error parsing lines expected \')\'");
    if (line[0] != '(')
            throw std::logic_error("Error parsing lines expected \'(\'");
    std::vector<Vector2> curr;
    parsePoints(std::string(line.c_str() + 1, line.c_str() + line.size() - 1), curr);
    if (curr.size() != 2)
        throw std::logic_error("Error parsing lines. Should contain 2 points");
    std::pair<Vector2, Vector2> l = std::make_pair(curr[0], curr[1]);
    lines.push_back(l);
}
std::string Graph::ignoreLine(const std::string& line)
{
    size_t pos = line.find_first_of('#');
    
    return (pos != std::string::npos) ? std::string(line.c_str(), line.c_str() + pos) : line;
}
std::string Graph::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) {
        return ""; // No non-whitespace characters found, return an empty string
    }
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

void Graph::readFromFile(const std::string& filepath)
{
    std::ifstream inputFile(filepath);
    if (!inputFile.is_open())
       throw std::runtime_error("Failed to open file");

    std::string line;
    bool pointsMode = false;
    bool linesMode = false;
    std::vector<std::pair<Vector2, Vector2> > lines;
    std::vector<Vector2> points;
    try {
        while (std::getline(inputFile, line))
        {
            line = trim(line);
            line = ignoreLine(line);
            bool openBrace = line.find("{") != std::string::npos; 
            bool closeBrace = line.find("}") != std::string::npos;
            std::stringstream ss(line);
            if (line.find("points") != std::string::npos)
            {
                pointsMode = true;
                linesMode = false;
                continue;
            } else if (line.find("lines") != std::string::npos)
            {
                pointsMode = false;
                linesMode = true;
                continue;
            } else if (openBrace || closeBrace || line.empty())
                continue;
            if (pointsMode && !linesMode)
               parsePoints(line, points);
            else if (linesMode && !pointsMode)
                parseLines(line, lines);
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Error on loading file: " << e.what() << std::endl;
    }

    inputFile.close();
    m_points = points;
    m_lines = lines;
}
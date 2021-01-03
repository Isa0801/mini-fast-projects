#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <map>
#include <memory>


class baseObj{
public:
    virtual void render(sf::RenderWindow& window) {std::cout << "got this one";}
};


class xObj : public baseObj
{
private:
    sf::RectangleShape firstSq, secondSq;
public:

    xObj(sf::Vector2f size, sf::Vector2f pos, sf::Color color = sf::Color::Black){

        if (size.x < size.y)
            size.x = size.x;
        else
           size.x = size.y;

    firstSq = sf::RectangleShape(sf::Vector2f(size.x, 3.f));
    secondSq = sf::RectangleShape(sf::Vector2f(size.x, 3.f));

    firstSq.setOrigin(sf::Vector2f(size.x/2, 3.f/2));
    secondSq.setOrigin(sf::Vector2f(size.x/2, 3.f/2));

    firstSq.rotate(45);
    secondSq.rotate(-45);

    firstSq.setPosition(pos);
    secondSq.setPosition(pos);

    firstSq.setFillColor(color);
    secondSq.setFillColor(color);

    };

    void render(sf::RenderWindow& window) override{
        window.draw(firstSq);
        window.draw(secondSq);
    }
};


class cirObj : public baseObj
{
private:
    sf::CircleShape outerCir, innerCir;
public:
    cirObj(sf::Vector2f size, sf::Vector2f pos, sf::Color color = sf::Color::Black){

        float r;

        if (size.x < size.y)
            r = size.x/2 - size.x*0.05;
        else
            r = size.y/2 - size.y*0.05;
        
        

        outerCir = sf::CircleShape(r, 150);
        innerCir = sf::CircleShape(r/1.5, 150);

        outerCir.setOrigin(sf::Vector2f(r, r));
        innerCir.setOrigin(sf::Vector2f((r/1.5), (r/1.5)));

        outerCir.setPosition(pos);
        innerCir.setPosition(pos);

        outerCir.setFillColor(color);
        innerCir.setFillColor(sf::Color::White);

    };

    void render(sf::RenderWindow& window) override{
        window.draw(outerCir);
        window.draw(innerCir);
    }

};

class TicTaceToe
{
private:
std::vector<std::shared_ptr<baseObj>> gameObj;
std::map<std::string, sf::RectangleShape> baseGObj;
int H,W;
bool player1Turn = false;
bool player2Turn = false;
int gameMap[3][3] = {{-1, -1, -1},
                    {-1, -1, -1},           
                    {-1, -1, -1}
                                };
int xTurn = 1;
public:
    TicTaceToe(sf::Vector2f, sf::Vector2f, float);
    ~TicTaceToe();
    bool winCond();
    void render(sf::RenderWindow&);
    void update(sf::RenderWindow&);
};

TicTaceToe::TicTaceToe(sf::Vector2f windowSize, sf::Vector2f boxSize, float borderThickness){

sf::RectangleShape box(sf::Vector2f(boxSize.x, boxSize.y));
box.setOrigin(sf::Vector2f(boxSize.x/2.f, boxSize.y/2.f));
box.setPosition(sf::Vector2f(windowSize.x/2.f, windowSize.y/2.f));
baseGObj["box"] = box;

// first line up
sf::RectangleShape line(sf::Vector2f(borderThickness, box.getSize().y));
line.setOrigin(sf::Vector2f(borderThickness/2.f, box.getSize().y/2.f));
line.setPosition(sf::Vector2f(box.getPosition().x - box.getSize().x/6.f, box.getPosition().y));
line.setFillColor(sf::Color::Black);
baseGObj["up1"] = line;

// second line up
line.setPosition(sf::Vector2f(box.getPosition().x + box.getSize().x/6.f, box.getPosition().y));
baseGObj["up2"] = line;

// first line to right
line = sf::RectangleShape(sf::Vector2f(box.getSize().x, borderThickness));
line.setOrigin(sf::Vector2f(box.getSize().x/2.f, borderThickness/2.f));
line.setPosition(sf::Vector2f(box.getPosition().x, box.getPosition().y - box.getSize().y/6.f));
line.setFillColor(sf::Color::Black);
baseGObj["right1"] = line;
// second line to right
line.setPosition(sf::Vector2f(box.getPosition().x, box.getPosition().y + box.getSize().y/6.f));
baseGObj["right2"] = line;

}

TicTaceToe::~TicTaceToe(){
}


bool TicTaceToe::winCond(){

    // check for vert win
    for (size_t x = 0; x <= 2; x++){

        if ((gameMap[x][0] == 1 && gameMap[x][1] == 1 && gameMap[x][2] == 1))
        {
            std::cout << "x won\n";
            return true;
            break;
        } else if ((gameMap[x][0] == 2 && gameMap[x][1] == 2 && gameMap[x][2] == 2))
        {
            std::cout << "o won\n";
            return true;
            break;
        }
    }

    // check for hor win
    for (size_t y = 0; y <= 2; y++){

        if ((gameMap[0][y] == 1 && gameMap[1][y] == 1 && gameMap[2][y] == 1))
        {
            std::cout << "x won\n";
            return true;
            break;
        } else if ((gameMap[0][y] == 2 && gameMap[1][y] == 2 && gameMap[2][y] == 2))
        {
            std::cout << "o won\n";
            return true;
            break;
        }
    }

    // check for dia win
        if ((gameMap[0][0] == 1 && gameMap[1][1] == 1 && gameMap[2][2] == 1))
        {
            std::cout << "x won\n";
            return true;
        } else if ((gameMap[0][0] == 2 && gameMap[1][1] == 2 && gameMap[2][2] == 2))
        {
            std::cout << "o won\n";
            return true;
        } else if ((gameMap[0][2] == 1 && gameMap[1][1] == 1 && gameMap[2][0] == 1))
        {
            std::cout << "x won\n";
            return true;
        } else if ((gameMap[0][2] == 2 && gameMap[1][1] == 2 && gameMap[2][0] == 2))
        {
            std::cout << "o won\n";
            return true;
        }

        // check for draw
        for (size_t x = 0; x <= 2; x++){

            if (gameMap[x][0] == -1 || gameMap[x][1] == -1 || gameMap[x][2] == -1){
                break;
            } else if (x == 2){
                std::cout << "draw\n";
                return true;
            }
        }
        
        
    

    return false;

}

void TicTaceToe::render(sf::RenderWindow& window){

    // render base layout
    for (auto& obj: baseGObj){
        window.draw(obj.second);
    }

    // render main obj
    for (auto& obj: gameObj){
        //window.draw(obj);
        obj->render(window);
    }
    

}

void TicTaceToe::update(sf::RenderWindow& window){

        if (winCond())
        {
            gameObj.clear();

            for (size_t i = 0; i <= 2; i++){

                gameMap[i][0] = -1;
                gameMap[i][1] = -1;
                gameMap[i][2] = -1;

                xTurn = 1;
                sf::sleep(sf::milliseconds(1000));
            }
            
            
        }
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        int x = -1, y = -1;
        sf::Vector2f cords;
        sf::Vector2f size;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);

        //left side
        if (mousePosF.x > baseGObj["box"].getPosition().x - baseGObj["box"].getSize().x/2 && mousePosF.x < baseGObj["up1"].getPosition().x ){

            cords.x = baseGObj["box"].getPosition().x - baseGObj["box"].getSize().x/3;
            size.x = ( baseGObj["up1"].getPosition().x - (baseGObj["box"].getPosition().x - baseGObj["box"].getSize().x/2));
            size.x = abs(size.x); 
            x = 0;
            //std::cout << "left side\n";
        }
        //middle side
        else if (mousePosF.x > baseGObj["up1"].getPosition().x && mousePosF.x < baseGObj["up2"].getPosition().x){

            cords.x = baseGObj["box"].getPosition().x;
            size.x = (baseGObj["up2"].getPosition().x - baseGObj["up1"].getPosition().x);
            size.x = abs(size.x); 
            x = 1;
            //std::cout << "middle side\n";
        }
        //right side
        else if (mousePosF.x > baseGObj["up2"].getPosition().x && mousePosF.x < baseGObj["box"].getPosition().x + baseGObj["box"].getSize().x/2){

            cords.x = baseGObj["box"].getPosition().x + baseGObj["box"].getSize().x/3;
            size.x = ((baseGObj["box"].getPosition().x + baseGObj["box"].getSize().x/2) - baseGObj["up2"].getPosition().x); 
            size.x = abs(size.x);

            x = 2;
            //std::cout << "right side\n";
        } else
            return;

    
        //top side
        if (mousePosF.y >  baseGObj["box"].getPosition().y - baseGObj["box"].getSize().y/2 && mousePosF.y < baseGObj["right1"].getPosition().y ){
            
            cords.y = baseGObj["box"].getPosition().y - baseGObj["box"].getSize().y/3;
            size.y =  baseGObj["right1"].getPosition().y - (baseGObj["box"].getPosition().y - baseGObj["box"].getSize().y/2) ;
            size.y = abs(size.y);

            y = 0;
            //std::cout << "top side\n";
        }
        // middle side
        else if (mousePosF.y > baseGObj["right1"].getPosition().y && mousePosF.y < baseGObj["right2"].getPosition().y){
            
            cords.y = baseGObj["box"].getPosition().y;
            size.y = (baseGObj["box"].getPosition().y +  baseGObj["box"].getSize().y/2) - baseGObj["right2"].getPosition().y;
            size.y = abs(size.y);
    
            y = 1;
            //std::cout << "middle side\n";
        } 
        // bottom side
        else if (mousePosF.y > baseGObj["right2"].getPosition().y && mousePosF.y < baseGObj["box"].getPosition().y + baseGObj["box"].getSize().y/2){
            
            cords.y = baseGObj["box"].getPosition().y + baseGObj["box"].getSize().y/3;
            size.y = ((baseGObj["box"].getPosition().y + baseGObj["box"].getSize().y/2) - baseGObj["right2"].getPosition().y); 
            size.y = abs(size.y);
            y = 2;
            //std::cout << "bottom side\n";
        } else
            return;
        
        

        //std::cout << "x: " << x << " y: " << y << std::endl;

        if (gameMap[x][y] == -1){
            

            std::shared_ptr<baseObj> temp;

            if (xTurn%2 != 0){
                temp = std::make_shared<xObj>(size, cords, sf::Color::Green);
                gameMap[x][y] = 1;
            } else {
                temp = std::make_shared<cirObj>(size, cords, sf::Color::Red);
                gameMap[x][y] = 2;
            }
            // sf::RectangleShape temp(size);
            // temp.setOrigin(sf::Vector2f(size.x/2, size.y/2));
            // temp.setPosition(cords);
            // temp.setFillColor(sf::Color::Green);

            gameObj.push_back(temp);

            xTurn++;
        }

    }
}



int main()
{
    sf::Vector2f winodwSize(1920, 1080);
    
    sf::RenderWindow window(sf::VideoMode(winodwSize.x, winodwSize.y), "SFML works!");
    TicTaceToe game(winodwSize, sf::Vector2f(1280, 720), 2.5f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear();
        game.update(window);
        game.render(window);
        window.display();
    }
    return 0;
}
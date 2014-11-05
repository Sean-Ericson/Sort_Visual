/*
 * File:   main.cpp
 * Author: anonymous
 *
 * Created on March 10, 2014, 6:52 AM
 */

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <iostream>

const int INIT_WIN_X = 500;
const int INIT_WIN_Y = 500;

void handleResize(sf::RenderWindow &window, sf::Event event, sf::View view);
int randInt(int min, int max);
void initialize(void);
void sort(void);
void drawStuff(void);
void drawRect(int num, sf::Color color);

sf::RenderWindow window(sf::VideoMode(INIT_WIN_X, INIT_WIN_Y, 32), "Test");
sf::Event event;
sf::View view;



int array[100];
sf::RectangleShape rect, rect2;

int main( void )
{   
    srand( time(NULL) );
    
    view.setCenter( sf::Vector2f( INIT_WIN_X / 2, INIT_WIN_Y / 2 ) );
    view.setSize( sf::Vector2f(INIT_WIN_X, INIT_WIN_Y) );
    
    //window.setKeyRepeatEnabled(false);
    window.setView(view);
    
    window.clear(sf::Color::Black);
    window.display();
    
    initialize();
    
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            if (event.type == sf::Event::Resized)
            {
                handleResize(window, event, view);
            }
            
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::S)
                    sort();
                
                if (event.key.code == sf::Keyboard::R)
                    initialize();
            }
            
            while (window.pollEvent(event)){}
        }
    }
    window.clear(sf::Color::Black);
    drawStuff();
    window.display();
    
    return 0;
}

void handleResize(sf::RenderWindow &window, sf::Event event, sf::View view)
{
    bool limitWindowSize = true;
    int minWindowSize = 71, smallSide;
    
    if ( (limitWindowSize) && (event.size.height < minWindowSize) )
    {
        event.size.height = minWindowSize;
        window.setSize( sf::Vector2u(event.size.width, event.size.height) );
    }
    
    view.setSize(event.size.width, event.size.height);
    
    if (event.size.width <= event.size.height)
    {
        view.zoom(1.0 * INIT_WIN_X / event.size.width);
    }
    else
    {
        view.zoom(1.0 * INIT_WIN_Y / event.size.height);
    }

    window.setView(view);
}

int randInt( int min, int max )
{
    if( min > max ){
        
        return (min + 1);
    }
    
    return (int)( ( ( rand() / (RAND_MAX * 1.0) ) * (1 + max - min) ) + min );
}

void initialize(void)
{
    window.clear(sf::Color::Black);
    
    for (int i = 0; i < 100; ++i)
    {
        array[i] =  randInt(1, 100);
        rect.setFillColor(sf::Color::Red);
        rect.setPosition( 5.0 * i, 500.0 - (5 * array[i]) );
        rect.setSize( sf::Vector2f(5.0, 5 * array[i]) );
        window.draw(rect);
    }
    window.display();
}

void sort(void)
{
    sf::Clock clock;
    sf::Time time = sf::milliseconds(0);
    sf::Time time2 = sf::milliseconds(0);
    
    int tmp, switches = 0;
    
    for (int i = 0; i < 99; ++i)
    {
        for (int j = 0; j < (99 - i); ++j)
        {
            clock.restart();
            window.clear(sf::Color::Black);
            drawStuff();
            drawRect(j, sf::Color::Green);
            drawRect(j+1, sf::Color::Green);
            window.display();
            while (clock.getElapsedTime() < time2){}
            
            if (array[j] > array[j+1])
            {
                clock.restart();
                window.clear(sf::Color::Black);
                drawStuff();
                drawRect(j, sf::Color::Blue);
                drawRect(j+1, sf::Color::Blue);
                window.display();
                while (clock.getElapsedTime() < time){}
                
                tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
                switches += 1;
                
                clock.restart();
                window.clear(sf::Color::Black);
                drawStuff();
                drawRect(j, sf::Color::Blue);
                drawRect(j+1, sf::Color::Blue);
                window.display();
                while (clock.getElapsedTime() < time){}
            }
            window.clear(sf::Color::Black);
            drawStuff();
        }
        
        if (switches == 0)
            break;
        else
            switches = 0;
    }
}

void drawStuff(void)
{
    window.clear(sf::Color::Black);
    
    for (int i = 0; i < 100; ++i)
    {
        drawRect(i, sf::Color::Red);
    }
    
    window.display();
}

void drawRect(int num, sf::Color color)
{
    rect.setFillColor(color);
    rect.setPosition( 5.0 * num, 500.0 - (5 * array[num]) );
    rect.setSize( sf::Vector2f(5.0, 5 * array[num]) );
    window.draw(rect);
}
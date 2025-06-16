#include <SFML/Graphics.hpp>
#include <iostream> // Para depuración, si es necesario

int main()
{
    // Crear una ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "¡Hola SFML!");

    // Crear un círculo verde
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(350.f, 250.f); // Posición inicial

    // Cargar una fuente (asegúrate de que arial.ttf esté en la misma carpeta que tu .exe)
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Error: No se pudo cargar la fuente arial.ttf. Asegúrate de que está en la carpeta output." << std::endl;
        return -1; // Salir si la fuente no se carga
    }

    // Crear un texto
    sf::Text text;
    text.setFont(font);
    text.setString("¡SFML funcionando!");
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    text.setPosition(200.f, 50.f);

    // Bucle principal de la aplicación
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black); // Limpiar la ventana (fondo negro)
        window.draw(shape);              // Dibujar el círculo
        window.draw(text);               // Dibujar el texto
        window.display();                // Mostrar lo que se ha dibujado
    }

    return 0;
}
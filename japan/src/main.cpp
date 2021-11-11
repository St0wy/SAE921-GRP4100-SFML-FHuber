#include <SFML/Graphics.hpp>

constexpr int WINDOW_WIDTH = 900;
constexpr int WINDOW_HEIGHT = 600;
constexpr int CENTER_SIZE = 150;
constexpr int NBR_STRIPES = 16;
constexpr int FRAMERATE = 60;
constexpr float ROTATION_ANGLE = 360.0f / (NBR_STRIPES * 2.0f) * 2.0f;
constexpr int STRIPES_DISTANCE = 300;
constexpr int STIPES_WIDTH = 60;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Japan");

    // Basic Setup of the window
    // Vertical sync, framerate
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(FRAMERATE);

    while (window.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis
        // la précédente itération
        sf::Event event{};

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                // évènement "fermeture demandée" : on ferme la fenêtre
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        // Graphical Region
        window.clear(sf::Color::White);

        // window.draw(something to draw);
        sf::Vector2f center_window(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);

        // Create the red circle in the center
        sf::CircleShape center_circle;
        center_circle.setRadius(CENTER_SIZE);
        center_circle.setFillColor(sf::Color::Red);
        center_circle.setOrigin(CENTER_SIZE, CENTER_SIZE);
        center_circle.setPosition(center_window);

        // Create the transform that moves the triangles in the center of the screen
        sf::Transform move_to_origin;
        move_to_origin.translate(center_window);

        // Create the vectors that holds the triangles and the transforms
        std::vector<sf::VertexArray> triangles;
        std::vector<sf::Transform> transforms;
        triangles.reserve(NBR_STRIPES);
        transforms.reserve(NBR_STRIPES);

        for (std::size_t i = 0; i < NBR_STRIPES; i++)
        {
            // Create the stripe
            sf::VertexArray stripe(sf::Triangles, 3);
            stripe[0].position = sf::Vector2f(0, 0);
            stripe[1].position = sf::Vector2f(-STIPES_WIDTH, -WINDOW_HEIGHT / 2.0f - STRIPES_DISTANCE);
            stripe[2].position = sf::Vector2f(STIPES_WIDTH, -WINDOW_HEIGHT / 2.0f - STRIPES_DISTANCE);
            stripe[0].color = sf::Color::Red;
            stripe[1].color = sf::Color::Red;
            stripe[2].color = sf::Color::Red;
            triangles.push_back(stripe);

            // Create the rotation and multiplies it to the movement to the origin
            sf::Transform rotation;
            rotation.rotate(i * ROTATION_ANGLE);
            transforms.push_back(move_to_origin * rotation);
        }

        // Draw everything
        window.draw(center_circle);
        for (size_t i = 0; i < triangles.size(); i++)
        {
            window.draw(triangles[i], transforms[i]);
        }

        window.display();
    }
}
